// trsc-server.cpp : Defines the entry point for the console application.
//

//#ifdef _WIN32
//#pragma comment( lib, "ws2_32" )
//#include <WinSock2.h>
//#endif

#include <assert.h>
#include <stdio.h>

#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <memory>
#include <string>
#include <cstdio>
#include <cstdint>
#include <thread>

#include "smf-2.11/RequestServiceRequestHandler.h"
#include "smf-2.11/ConnectionException.h"
#include "smf-2.11/Warning.h"
#include "smf-2.11/SmfClient.h"
#include "smf-2.11/SenderService.h"
#include "smf-2.11/Error.h"
#include "smf-2.11/ServiceChannel.h"

#include "SenderServiceStatus.h"
#include "ArsResponseHandler.h"

#include "smf-2.11/CheckedCast.h"
#include "smf-2.11/CriticalError.h"

#include "CommunicationHub.h"

using namespace smf2js;

int main(int argc, char**argv)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	CommunicationHub* pHub;

	int counter = 0;
#ifdef _WIN32
	INT rc;
	WSADATA wsaData;

	rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (rc) {
		printf("WSAStartup Failed.\n");
		return 1;
	}
#endif

	if (argc != 5) {
		std::cout << "Usage: " << argv[0] << " [WSUri] [SMFHostLocation] [SMFConnectionPort] [LogFile]\n";
		return -1;
	}
	std::cout << "Starting...\n";

	const char* pWSUri = argv[1];
	const char* pSMFHost = argv[2];
	const char* pLogFile = argv[4];
	unsigned short iPort = atoi(argv[3]);

	try {
		pHub = new CommunicationHub();
		pHub->Init(pWSUri, pSMFHost, pLogFile, iPort);
		Sleep(1000);

		std::string sCmd = "";
		int iCmd;
		bool running = true;
		while (running) {
			//print the menu
			std::cout << "/***************MENU***************\\\n";
			std::cout << "0: Exit\n";
			std::cout << "1: Re-connect\n";
			std::cout << "2: Login\n";
			std::cout << "3: Subscription\n";
			std::cout << "Please input code: ";

			//send the cmd
			std::getline(std::cin, sCmd);
			iCmd = atoi(sCmd.c_str());
			switch (iCmd)
			{
			case 0:
				running = false;
				break;
			case 1:
				pHub->WsReconnect();
				break;
			case 2:
				pHub->Login("ReutersModify", "Reuters.Modify");
				break;
			case 3:
				pHub->RequestSubscriptionList();
				break;
			default:
				std::cout << "Invalid input!\n";
				break;
			}
		}

		////exit
		pHub->Exit();
	}
	catch (smf::ConnectionClosed &e) {
		std::cout << e.Value() << "\n";
	}
	catch (smf::ConnectionTimeout &e) {
		std::cout << e.Value() << "\n";
	}
	catch (smf::Error e) {
		std::cout << "SMF Error:" << e.Value() << "\n";
	}
	catch (smf::Warning w) {
		std::cout << "SMF Warning:" << w.Value() << "\n";
	}
	catch (...) {
		std::cout << "Catch unknown exception\n";
	}

#ifdef _WIN32
	WSACleanup();
#endif

	return 0;
}

