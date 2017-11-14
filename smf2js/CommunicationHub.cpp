
#include "CommunicationHub.h"

#include <assert.h>
#include <stdio.h>

#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <memory>
#include <string>
#include <cstdio>
#include <cstdint>

#include "smf-2.11/CheckedCast.h"
#include "smf-2.11/CriticalError.h"
#include "smf-2.11/ParameterServiceRequestHandlerExt2.h"
#include "smf-2.11/ParameterService.h"
#include "smf-2.11/BulkParameterService.h" //#include "ParameterService.h"

#include "Encrypter.h"
#include "Common.h"
#include "PsdResponseHandler.h"

static smf2js::SafeQueue<std::string> WsMonitor;
static smf2js::SafeQueue<std::string> PsdUpdateValuesFlag;
static smf2js::SafeQueue<std::string> ArsUpdateValuesFlag;

smf::ServiceChannel* smf2js::Common::Channel;

smf2js::CommunicationHub::CommunicationHub()
{
	_seqNum = 0;
	_psdRequester = 0;
	_blkRequester = 0;
	_subscriptionFileCount = INT32_MAX;
	_subscriptionFileIndex = 0;

	_allowLogin = false;
	_running = false;
	_psdUpdateRunning = false;
	_arsUpdateRunning = false;

	_encrypter = new smf2js::Encrypter();
}

smf2js::CommunicationHub::~CommunicationHub()
{
	if (_encrypter)
		delete _encrypter;
}

void smf2js::CommunicationHub::Init(const char* pWSUri, const char* pSMFHost,
	const char* pLogFile, unsigned short iPort)
{
	// Need to add log severity level to init step
	smf2js::TRLogService::GetInstance()->Init(pLogFile, smf::LogEntry::Warning);

	//connect to SMF
	smf::Logger* logger = smf2js::TRLogService::GetInstance()->GetLogger();
	smf2js::Common::Channel = smf::Client::Connect(pSMFHost, iPort, logger, 100);
	Sleep(1000);
	smf2js::TRLogService::GetInstance()->Subscribe();

	//set service status
	SenderServiceStatus channelStatus;
	smf2js::Common::Channel->SetServiceStatus(&channelStatus);

	// Opening connection for standard ARS connection
	_arsRequester = smf::SenderService::OpenRequestChannel(
		&_arsHandler, smf2js::Common::Channel, smf2js::TRLogService::GetInstance()->GetLogger(), 10);
	if (!_arsRequester) {
		std::cout << "Error: Cannot Create Request Handler!\n";
		smf::Client::Disconnect(smf2js::Common::Channel);
		return /* throw exception ??? */;
	}

	Sleep(1000);

	RegisterEvent(&_arsHandler);

	_running = true;
	_wsMonitorConnectionThread = std::thread(&CommunicationHub::WsMonitorConnection, this, pWSUri);
	WsMonitor.enqueue("connect");
	_wsIncomingListenerThread = std::thread(&CommunicationHub::WsIncomingListener, this);
	_smfIncomingListenerThread = std::thread(&CommunicationHub::SmfIncomingListener, this);
	_psdUpdateThread = std::thread(&CommunicationHub::RequestUpdateFromPsd, this);
	_arsUpdateThread = std::thread(&CommunicationHub::RequestUpdateFromArs, this);


	//// HACK -- TESTING of psdKeys ////
	//std::vector<std::string> sl;
	//std::vector<std::string> dl;
	//std::vector<std::string> blk;
	//sl.push_back("/TradsIPCSessionStats/0/PeakCompBitsSentRate");
	//sl.push_back("/TradsIPCSessionStats/0/CurBufferPercentage");
	//sl.push_back("/TradsIPCSessionStats/0/PeakBufferPercentage");
	//sl.push_back("/TradsIPCSessionStats/0/MountTime");
	//// TEMP WORK ////
	//blk.push_back("/TradsChannelStats/*/Name");
	//blk.push_back("/TradsChannelStats/*/ClientMountChannelNumber");
	//blk.push_back("/TradsChannelStats/*/Protocol");
	//blk.push_back("/TradsChannelStats/*/Hostname");
	//blk.push_back("/TradsChannelStats/*/Position");
	//blk.push_back("/TradsChannelStats/*/RequestRate");

	//smf::BulkCompParameterRequestHandler::Schema schemaComp;
	//for (std::string val : blkList)
	//	schemaComp.push_back(smf::PsdField(val));

	//RequestBulkHandles(schemaComp);

	//_arsHandler.AddRequestedFields(_arsFields);
	//UpdateSubscriptionList(sl, dl, blk);
	//// END OF HACK -- 
}

void smf2js::CommunicationHub::RequestSubscriptionList()
{
	if (_dynamicFields.empty())
	{
		// request subscriptions from NodeJS server.
		JsonHandler json;
		json.AddKeyValue("type", "request-subscription-list");
		SmfResponseQueue.enqueue(json.Stringify());
	}
}

void smf2js::CommunicationHub::RequestUpdateFromPsd()
{
	while (PsdUpdateValuesFlag.dequeue() != "wakeup")
	{
		while (_psdUpdateRunning)
		{
			if (_wsClient.get_status(_connectionId) == "Closed_1006" || _wsClient.get_status(_connectionId) == "Failed")
			{
				WsReconnect();
				Sleep(1000);
			}
			// !!!! HACK (maybe) !!!!
			RequestPsdValues(_psdStaticHandles); // лл HACK
			// !!!! END HACK !!!!
			RequestPsdValues(_psdDynamicHandles);
			//Sleep(2000);
			RequestBulkHandles(_schemaComp);
			Sleep(5000);
		}
	}
}

void smf2js::CommunicationHub::RequestUpdateFromArs()
{
	while (ArsUpdateValuesFlag.dequeue() != "wakeup")
	{
		while (_arsUpdateRunning)
		{
			if (_wsClient.get_status(_connectionId) == "Closed_1006" || _wsClient.get_status(_connectionId) == "Failed")
				Sleep(1000);

			if (_arsFields.size() > 0)
			{
				std::string payloadStr = "REG.GET|";
				for (std::vector<std::string>::iterator iter = _arsFields.begin(); iter != _arsFields.end(); ++iter)
				{
					payloadStr += iter->data();
					payloadStr += ";";
				}
				_arsRequester->Request("RSCHandler", _seqNum++, smf::ArsPayload(payloadStr.data(), (int)payloadStr.length()));
			}
			Sleep(5000);
		}
	}
}

void smf2js::CommunicationHub::SmfIncomingListener()
{
	while (_running)
	{
		std::string msg = SmfResponseQueue.dequeue();
		if (msg == "wakeup")
			return;
		_wsClient.send(_connectionId, msg.c_str());
	}
}

void smf2js::CommunicationHub::WsIncomingListener()
{
	while (_running)
	{
		std::string msg = WsIncomingQueue.dequeue();
		if (msg == "wakeup")
			return;

		if (msg == "ws-connected")
		{
			RequestSubscriptionList();
			continue;
		}

		JsonHandler json;
		json.Parse(msg.c_str());

		std::string tmp = json.GetValue("detail");
		if ((tmp.compare("login") == 0) && (_subscriptionFileCount == _subscriptionFileIndex))
		{
			std::cout << "**** login is being processed ****" << std::endl;
			Login(json.GetValue("username"), json.GetValue("password"));
		}
		else if (tmp.compare("logout") == 0)
		{
			Logout(json.GetValue("username"));
		}
		else if (tmp.compare("subscriptions-done") == 0)
		{
			std::string t = json.GetValue("count");
			_subscriptionFileCount = atoi(t.c_str());
		}
		else if (tmp.compare("subscriptions") == 0)
		{
			std::vector<std::string> sl;
			std::vector<std::string> dl;
			std::vector<std::string> blk;

			json.GetArray("staticList", sl);
			json.GetArray("dynamicList", dl);
			json.GetArray("arsList", _arsFields);
			json.GetArray("blkList", blk);

			//// TEMP WORK ////
			//blk.push_back("/TradsChannelStats/*/Name");
			//blk.push_back("/TradsChannelStats/*/ClientMountChannelNumber");
			//blk.push_back("/TradsChannelStats/*/Protocol");
			//blk.push_back("/TradsChannelStats/*/Hostname");
			//blk.push_back("/TradsChannelStats/*/Position");
			//blk.push_back("/TradsChannelStats/*/RequestRate");

			//smf::BulkCompParameterRequestHandler::Schema schemaComp;
			//for (std::string val : blkList)
			//	schemaComp.push_back(smf::PsdField(val));

			//RequestBulkHandles(schemaComp);
			//// END OF TEMP WORK -- 

			_arsHandler.AddRequestedFields(_arsFields);
			UpdateSubscriptionList(sl, dl, blk);
		}
		else if (tmp.compare("psd-update") == 0)
		{
			std::string key;
			std::vector<std::string> values;
			std::vector<std::string> keyTypes;

			key = json.GetValue("key");
			values.push_back(json.GetValue("values"));
			keyTypes.push_back(json.GetValue("keyTypes"));

			for (int i = 0; i < values.size(); ++i)
				UpdateValues(key, values[i], keyTypes[i], _psdRequester, &_psdHandler, smf2js::TRLogService::GetInstance()->GetLogger());
		}
	}
}

void smf2js::CommunicationHub::UpdateSubscriptionList(std::vector<std::string> staticList, std::vector<std::string> dynamicList, std::vector<std::string> blkList)
{
	smf::ParameterServiceRequestHandler::Fields fields;
	for (std::string val : staticList)
		fields.push_back(val);
	RequestPsdHandles(fields, false);
	for (std::string val : dynamicList)
		_dynamicFields.push_back(val);
	RequestPsdHandles(_dynamicFields, true);
	
	for (std::string val : blkList)
		_schemaComp.push_back(smf::PsdField(val));
	RequestBulkHandles(_schemaComp);
}

void smf2js::CommunicationHub::WsMonitorConnection(std::string uri)
{
	while (WsMonitor.dequeue() != "wakeup")
	{
		try {
			_connectionId = _wsClient.connect(uri);
		}
		catch (websocketpp::exception const & e) {
			std::cout << e.what() << std::endl;
		}
	}
}

void smf2js::CommunicationHub::Logout(std::string username)
{
	_psdUpdateRunning = false;
	_arsUpdateRunning = false;
	std::ostringstream tmp;
	tmp << "Logging out [" << username << "]";
	smf2js::TRLogService::GetInstance()->LogMessage(smf::LogEntry::Informational, tmp.str());
}

void smf2js::CommunicationHub::Login(std::string username, std::string password)
{
	for (int i = (int)username.length(); i < 14; ++i)
		username += " ";
	// added 1 for the character 13
	password += (char)13;
	// fill password in a fixed length with character return
	for (int i = (int)password.length(); i < 15; ++i)
		password += " ";

	char buff[20];
	time_t now = time(NULL);
	std::strftime(buff, 20, "%m/%d/%y %H:%M:%S", localtime(&now));

	std::string nowStr(buff); // "08/30/17 08:45:53";
	std::string login = nowStr + username + password;

	// LOGON_AUTHEN.REQUEST
	std::cout << login << std::endl;
	const BYTE* result = _encrypter->Encrypt(login);
	std::string payloadStr = "LOGON_AUTHEN.REQUEST|";
	int len = (int)strlen(reinterpret_cast<const char*>(result));
	std::string str2(result, result + len);
	payloadStr += str2;

	_arsRequester->Request("RSCHandler", _seqNum++, smf::ArsPayload(payloadStr.data(), (int)payloadStr.length()));
}

//void smf2js::CommunicationHub::SmfMessageCB(const std::string &message)
//{
//	smf2js::JsonHandler json;
//	json.Parse(message.c_str());
//	Login(json.GetValue("username"), json.GetValue("password"));
//}

void smf2js::CommunicationHub::WsReconnect()
{
	WsMonitor.enqueue("reconnect");
}

void smf2js::CommunicationHub::Exit()
{
	_running = false;
	_psdUpdateRunning = false;
	_arsUpdateRunning = false;
	SmfResponseQueue.wakeup();
	WsIncomingQueue.wakeup();
	PsdUpdateValuesFlag.wakeup();
	ArsUpdateValuesFlag.wakeup();
	WsMonitor.wakeup();
	//_wsClient.stop_perpetual();
	//_wsClient.close(_hdl, websocketpp::close::status::normal, "exiting");
	_wsClient.close(_connectionId, websocketpp::close::status::going_away, "exiting...");

	_psdUpdateThread.join();
	_arsUpdateThread.join();
	//_psdPrefetchThread.join();
	_wsIncomingListenerThread.join();
	_wsMonitorConnectionThread.join();
	_smfIncomingListenerThread.join();

	smf::SenderService::CloseRequestChannel(smf2js::Common::Channel, _arsRequester);
	smf::Client::Disconnect(smf2js::Common::Channel);
	smf2js::TRLogService::GetInstance()->Unsubscribe();
}

void smf2js::CommunicationHub::RegisterEvent(smf2js::ArsResponseHandler* source)
{
	__hook(&smf2js::ArsResponseHandler::UpdateChar, source, &smf2js::CommunicationHub::OnUpdateChar);
	__hook(&smf2js::ArsResponseHandler::UpdateByte, source, &smf2js::CommunicationHub::OnUpdateByte);
}

void smf2js::CommunicationHub::UnregisterEvent(smf2js::ArsResponseHandler* source)
{
	__unhook(&smf2js::ArsResponseHandler::UpdateChar, source, &smf2js::CommunicationHub::OnUpdateChar);
	__unhook(&smf2js::ArsResponseHandler::UpdateByte, source, &smf2js::CommunicationHub::OnUpdateByte);
}

void smf2js::CommunicationHub::OnUpdateChar(int type, const char* msg)
{
	// Check the 'type' and then do the proper behavior

	// If type == 1, that means successful login, so register for SMF Parameter Service Response Handler
	if (type == 1)
	{
		_psdUpdateRunning = true;
		_arsUpdateRunning = true;
		// Now that we are logged in, request the PSD data.
		PsdUpdateValuesFlag.enqueue("start");
		ArsUpdateValuesFlag.enqueue("start");
	}
}

void smf2js::CommunicationHub::OnUpdateByte(int type, BYTE msg[])
{
	//////   NOTE FOR MONDAY MORNING....
	// I believe the memory issue is with the decrypt step - the call to the MS DLL
	//  Trying to understand how to make this call memory / thread safe
	//
	//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	JsonHandler json;
	std::string results = reinterpret_cast<const char*>(_encrypter->Decrypt(msg));

	std::string t1 = results.substr(0, 17).c_str();
	std::string t2 = results.substr(17, 14).c_str();
	char t3 = results[(results.length() - 1)];

	json.AddKeyValue("type", "login-message");
	json.AddKeyValue("datetime", t1);
	json.AddKeyValue("username", t2);

	if (t3 == 'S')
	{
		json.AddKeyValue("success", "S");
		smf2js::TRLogService::GetInstance()->LogMessage(smf::LogEntry::Informational, json.Stringify());
		OnUpdateChar(1, json.Stringify().c_str());
	}
	else if (t3 == 'F')
	{
		json.AddKeyValue("success", "F");
		smf2js::TRLogService::GetInstance()->LogMessage(smf::LogEntry::Warning, json.Stringify());
		OnUpdateChar(0, json.Stringify().c_str());
	}
	else
		std::cout << "NO IDEA";

	SmfResponseQueue.enqueue(json.Stringify());
}

void smf2js::CommunicationHub::UpdateValues(std::string key, std::string value, std::string keyType, smf::ParameterServiceRequestHandlerExt2* psdRequester, 
	smf2js::PsdResponseHandler* psdResponder, smf::Logger* logger)
{
	Log log(logger);

	if (!psdRequester->IsConnected())
		return;

	try
	{
		smf::ParameterServiceRequestHandler::HandleValues handleValues;
		if (std::find(_arsFields.begin(), _arsFields.end(), key) != _arsFields.end())
		{
			std::string payloadStr = "COMPLEX_PARA.SET|";
			payloadStr += key;
			payloadStr += '=';
			payloadStr += value;
			_arsRequester->Request("RSCHandler", _seqNum++, smf::ArsPayload(payloadStr.data(), (int)payloadStr.length()));
		}
		else
		{
			smf::ParameterServiceResponseHandler::Handle para1 = psdResponder->FindHandle(key.c_str());
			if (para1 != 0)
			{
				if (keyType == "int")
				{
					int t = atoi(value.c_str());
					handleValues.push_back(smf::PsdHandleValue(para1, t));
				}
				else if (keyType == "string")
					handleValues.push_back(smf::PsdHandleValue(para1, value.c_str()));
				psdRequester->UpdateValues(handleValues, _seqNum++);
			}
		}
	}
	catch (smf::ParameterServiceRequestHandler::CouldNotGetBuffer) {
		log << "Could not get a buffer in ParameterServiceRequestHandler.\n";
	}
	catch (smf::ParameterServiceRequestHandler::ConnectionDropped) {
		log << "Connection has been dropped.\n";
	}
	catch (smf::Error& e) {
		log << e;
	}
	catch (smf::Warning& w) {
		log << w;
	}
}

void smf2js::CommunicationHub::RequestValuesByHandle(smf::ParameterServiceRequestHandler::Fields fields, smf::ParameterServiceRequestHandlerExt2* psdRequester, smf2js::PsdResponseHandler* psdResponder, bool dynamic, smf::Logger* logger)
{
	Log log(logger);

	if (!psdRequester->IsConnected())
		return;

	try
	{
		psdRequester->RequestHandles(fields, ++_seqNum);

		// transactions are not allowed to cross partitions
		for (std::vector<smf::PsdField>::iterator iter = fields.begin(); iter != fields.end(); ++iter)
		{
			smf::ParameterServiceResponseHandler::Handle para1 = psdResponder->FindHandle(iter->FieldName());
			if (dynamic)
				_psdDynamicHandles.push_back(smf::PsdHandle(para1));
			else
				_psdStaticHandles.push_back(smf::PsdHandle(para1));
		}

		if (!dynamic)
		{
			//RequestPsdValues(_psdStaticHandles);
			log << "\n**\n*** Static subscriptions complete ***\n**\n";
		}
		else
			log << "\n**\n*** Dynamic subscriptions complete ***\n**\n";
		_subscriptionFileIndex++;
		if (_subscriptionFileCount == _subscriptionFileIndex)
		{
			std::cout << "All files are loaded" << std::endl;
			Sleep(1000);
		}
	}
	catch (smf::ParameterServiceRequestHandler::CouldNotGetBuffer) {
		log << "Could not get a buffer in ParameterServiceRequestHandler.\n";
	}
	catch (smf::ParameterServiceRequestHandler::ConnectionDropped) {
		log << "Connection has been dropped.\n";
	}
	catch (smf::Error& e) {
		log << e;
	}
	catch (smf::Warning& w) {
		log << w;
	}
}

void smf2js::CommunicationHub::RequestPsdValues(smf::ParameterServiceRequestHandler::Handles psdHandles)
{
	_psdRequester->RequestValues(true, psdHandles, _seqNum++); // transactional read
														  //psdRequester->RequestValues(false, handles, seqNum); // non-transactional read
}

void smf2js::CommunicationHub::RequestBulkHandles(smf::BulkCompParameterRequestHandler::Schema schemaComp)
{
	Log log(smf2js::TRLogService::GetInstance()->GetLogger());
	{
		try
		{
			if (!_blkRequester)
			{
				_blkRequester = smf::BulkParameterService::OpenRequestChannelExt2(
					&_blkHandler,
					smf2js::Common::Channel,
					smf2js::TRLogService::GetInstance()->GetLogger(),
					0);
			}

			if (!_blkRequester->IsConnected())
				return;

			try
			{
				if (schemaComp.size() > 0)
				{
					//bulkRequester->RequestRecords(false, schema , seqNum, true); // non-transactional query
					_blkRequester->RequestRecords(true, schemaComp, _seqNum++, true); // transactional query
				}
			}
			catch (smf::BulkCompParameterRequestHandler::CouldNotGetBuffer) {
				log << "Could not get a buffer in BulkCompParameterRequestHandler.\n";
			}
			catch (smf::BulkCompParameterRequestHandler::ConnectionDropped) {
				log << "Connection has been dropped.\n";
			}
			catch (smf::Error& e) {
				log << e;
			}
			catch (smf::Warning& w) {
				log << w;
			}

		}
		catch (smf::Error& e)
		{
			log << e.Value() << "\n";
		}
	}
}

void smf2js::CommunicationHub::RequestPsdHandles(smf::ParameterServiceRequestHandler::Fields fields, bool dynamic)
{
	Log log(smf2js::TRLogService::GetInstance()->GetLogger());
	{
		try {
			if (!_psdRequester)
			{
				_psdRequester = smf::ParameterService::OpenRequestChannelExt2(
					&_psdHandler,
					smf2js::Common::Channel,
					smf2js::TRLogService::GetInstance()->GetLogger(),
					0);
			}

			if (!_psdRequester)
			{
				smf::Client::Disconnect(smf2js::Common::Channel);
				return /*OpenRequestChannelError*/;
			}

			RequestValuesByHandle(fields, _psdRequester, &_psdHandler, dynamic, smf2js::TRLogService::GetInstance()->GetLogger());
		}
		catch (smf::Error& e) {
			log << e.Value() << "\n";
		}
		catch (smf::Warning& w) {
			log << w.Value() << "\n";
		}
		catch (...) {
			log << "Unknown exception caught in main()\n";
			return /*UnknownError*/;
		}
	}
}

