#ifndef RESPONSEHANDLER
#define RESPONSEHANDLER

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "ErrorReason.h"
#include "smf-2.11/RequestServiceResponseHandler.h"

#include "Common.h"
#include "ThreadQueue.h"
#include "TRLogService.h"
#include "JsonHandler.h"

static smf2js::SafeQueue<std::string> WsIncomingQueue;
static smf2js::SafeQueue<std::string> SmfResponseQueue;

namespace smf2js
{
	class LoginResponse
	{
	public:
		BYTE Response[1024];
	};
}
static smf2js::SafeQueue<smf2js::LoginResponse> ByteQueue;


namespace smf2js
{
	[event_source(native)]
	class ArsResponseHandler : public smf::RequestServiceResponseHandler
	{
	public:
		ArsResponseHandler()
		{
			char* failures[] = {
				"Success",
				"UnclassifiedFailure",
				"UnknownReceiver",
				"ReceiverConnectionFailure",
				"SenderConnectionFailure",
				"DuplicatedRegistration",
				"InvalidSenderId",
				"CodingError", //this means there is something wrong with the code
				"MissedMessage", //this is originated at the client side 
				"ServerOverloaded",
				"SizeMismatch",
				"UnsupportedMessageType",
				"UnknownMessage",
				"TotalMessageSizeTooBig",
				0
			};
			m_ErrorReason.Set(failures);
		}

		virtual ~ArsResponseHandler() { }

		__event void UpdateChar(int type, const char* msg);
		__event void UpdateByte(int type, BYTE msg[]);

		virtual void Response(const std::string &receiver, UnsignedInt id, Payload &payload)
		{
			int pipeCounter = 0;
			int byteIndex = 0;
			BYTE type[1024];
			BYTE response[1024];

			std::cout << "\n\tReceiver: " << receiver.c_str() << " ID: " << id << "\n";

			std::cout << "\tContent: ";

			for (unsigned int i = 0; i < payload.PayloadSize(); i++)
			{
				if (payload[i] == (char)124)
				{
					std::cout << "\n";
					++pipeCounter;
					byteIndex = 0;
				}
				if (pipeCounter == 3)
				{
					response[byteIndex++] = payload[i];
					// NOTE - Provides quick means to have an 'end of line' without looping through entire array.
					//		And found that memset appeared to create an issue with accessing memory.
					response[byteIndex] = 0;
				}
				if (pipeCounter == 2)
					++pipeCounter;
				if (pipeCounter == 0)
				{
					type[byteIndex++] = payload[i];
					// NOTE - Provides quick means to have an 'end of line' without looping through entire array.
					//		And found that memset appeared to create an issue with accessing memory.
					type[byteIndex] = 0;
				}
				std::cout << payload[i];
			}
			JsonHandler json;
			std::string msgType = reinterpret_cast<const char*>(type);
			if (msgType == "REG.GET")
			{
				json.AddKeyValue("type", "ars-message");

				std::istringstream results(reinterpret_cast<const char*>(response));
				std::vector<std::string> res1;
				std::string s;
				while (std::getline(results, s, ';'))
					res1.push_back(s);

				for (int i = 0; i < res1.size(); ++i)
					json.AddKeyValue(_arsFields[i], res1[i]);

				SmfResponseQueue.enqueue(json.Stringify());
			}
			else if (msgType == "LOGON_AUTHEN.REQUEST")
			{
				__raise UpdateByte(1, response);
			}
		}

		virtual void ReportFailure(const std::string &receiver, UnsignedInt id, UnsignedInt reason)
		{
			std::cout << "\n\tReceiver: " << receiver.c_str() << " ID: " << id
				<< "\tFailure reason: " << m_ErrorReason.ReasonToString(reason).c_str() << "\n\n";
		}

		void AddRequestedFields(std::vector<std::string> arsFields)
		{
			for (std::vector<std::string>::iterator iter = arsFields.begin(); iter != arsFields.end(); ++iter)
			{
				if (std::find(_arsFields.begin(), _arsFields.end(), iter->c_str()) == _arsFields.end())
				{
					std::cout << iter->c_str() << std::endl;
					_arsFields.push_back(iter->c_str());
				}
			}
		}

	private:
		ErrorReason m_ErrorReason;
		std::vector<std::string> _arsFields;
	};
}

#endif