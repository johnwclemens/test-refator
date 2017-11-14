#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <atomic>

#include "smf-2.11/RequestServiceRequestHandler.h"
#include "smf-2.11/ParameterServiceRequestHandlerExt2.h"
#include "smf-2.11/BulkCompParameterRequestHandlerExt2.h"
#include "smf-2.11/ConnectionException.h"
#include "smf-2.11/Warning.h"
#include "smf-2.11/SmfClient.h"
#include "smf-2.11/SenderService.h"
#include "smf-2.11/Error.h"
#include "smf-2.11/ServiceChannel.h"

#include "SenderServiceStatus.h"
#include "ArsResponseHandler.h"
#include "PsdResponseHandler.h"
#include "BlkCompResponseHandler.h"
#include "Encrypter.h"
#include "TRLogService.h"

//// WEBSOCKET
#include "websocketpp.hpp"

class Encrypter;

namespace smf2js
{
	[event_receiver(native)]
	class CommunicationHub
	{
	public:
		CommunicationHub();
		virtual ~CommunicationHub();

		void Login(std::string username, std::string password);
		void Logout(std::string ussername);
		//void SmfMessageCB(const std::string & message);

		void Init(const char* pWSUri, const char* pSMFHost,
			const char* pLogFile, unsigned short iPort);
		void WsReconnect();
		void Exit();

		void RegisterEvent(ArsResponseHandler* source);
		void UnregisterEvent(ArsResponseHandler* source);

		void OnUpdateChar(int type, const char* msg);
		void OnUpdateByte(int type, BYTE msg[]);

		void RequestPsdValues(smf::ParameterServiceRequestHandler::Handles psdHandles);
		void RequestSubscriptionList();

	private:
		void WsMonitorConnection(std::string uri);
		void WsIncomingListener();
		void SmfIncomingListener();
		//void ByteIncomingListener();

		void RequestPsdHandles(smf::ParameterServiceRequestHandler::Fields fields, bool dynamic);
		void RequestBulkHandles(smf::BulkCompParameterRequestHandler::Schema schemaComp);
		void UpdateValues(std::string key, std::string value, std::string keyType, smf::ParameterServiceRequestHandlerExt2* psdRequester, 
			smf2js::PsdResponseHandler* psdResponder, smf::Logger* logger);
		void RequestUpdateFromPsd();
		void RequestUpdateFromArs();

		void RequestValuesByHandle(smf::ParameterServiceRequestHandler::Fields fields, smf::ParameterServiceRequestHandlerExt2* psdRequester, PsdResponseHandler* psdResponder, bool dynamic, smf::Logger* logger);

		void UpdateSubscriptionList(std::vector<std::string> sl, std::vector<std::string> dl, std::vector<std::string> blk);

		std::atomic_bool _running;
		std::atomic_bool _psdUpdateRunning;
		std::atomic_bool _arsUpdateRunning;
		std::atomic_int _subscriptionFileCount;
		std::atomic_int _subscriptionFileIndex;
		std::atomic_bool _allowLogin;
		int _count;
		int _seqNum;

		std::vector<std::string> _arsFields;
		smf::ParameterServiceRequestHandler::Fields _dynamicFields;
		smf::BulkCompParameterRequestHandler::Schema _schemaComp;

		Encrypter* _encrypter;

		smf::RequestServiceRequestHandler* _arsRequester;
		smf::ParameterServiceRequestHandlerExt2* _psdRequester;
		smf::BulkCompParameterRequestHandlerExt2* _blkRequester;

		ArsResponseHandler _arsHandler;
		PsdResponseHandler _psdHandler;
		BlkCompResponseHandler _blkHandler;

		smf::ParameterServiceRequestHandler::Handles _psdStaticHandles;
		smf::ParameterServiceRequestHandler::Handles _psdDynamicHandles;

		std::thread _wsMonitorConnectionThread;
		std::thread _wsIncomingListenerThread;
		std::thread _smfIncomingListenerThread;
		//std::thread _byteIncomingListenerThread;
		std::thread _psdUpdateThread;
		std::thread _arsUpdateThread;

		websocket_endpoint _wsClient;
		int _connectionId;
	};
}

