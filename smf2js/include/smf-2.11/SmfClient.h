
#ifndef SMFCLIENT_H
#define SMFCLIENT_H

#include <stddef.h>

namespace smf{
	class ServiceChannel;
    class ServiceChannelExt1;
	class Logger;
	class SecurityInfo;
	class SocksProxyInfo;
	class ServiceChannelResourcePool;
	class ServiceBufferPool;
	
	namespace Client{
		const char* LibName();


		//! \brief Make a connection to the SMF server. You can use this connection to open
		//! request channels to this server. You cannot open multiple request channels
		//! for the same service on a single service channel.
		//! \param server           The server hostname or IP address
		//! \param port             The port (by default SMF listens on 8603)
		//! \param logger           can be 0, your own implementation of an smf::Logger or
		//!                       an smf file logger (use smf::fileLogger)
		//! \param queuesizes       The queue size for the outgoing queue, in number of queued items.
		//!                         If 0, the default value of 10 is used.
		//! \param connectionTimeout Timeout (in milliseconds) for trying to connect, send or receive a message.
		//!                             Note: If there are no messages being send or received, this timeout will not be triggered.
		//! \return A pointer to a ServiceChannel object
		//! \remark     Include: SmfClient.h, Logger.h, Error.h, ConnectionException.h
		//! \post       Cleanup: You must call smf::Client::Disconnect to cleanup (see Closing An Smf Service Channel)
		//! \exception smf::Error and smf::ConnectionException Specific exceptions that might be thrown are defined in ConnectionException.h.
		//! \note       These functions are thread safe.
		//!             These functions will block (upto the timeout period) whilst trying to establish a connecion.
		ServiceChannel* Connect(
							const char* server, 
							unsigned short port,
							Logger*logger,
							unsigned int queuesizes = 0,//If 0 default values will be used
							unsigned int connectionTimeout = 0
							);

		//! \brief Make a connection to the SMF server. You can use this connection to open
		//! request channels to this server. You cannot open multiple request channels
		//! for the same service on a single service channel.
		//! \param server           The server hostname or IP address
		//! \param networkservice   A service name as defined in the services file in the OS. 
		//!                         Note, you will need to edit the services file  (
		//!                         C:\WINDOWS\system32\drivers\etc \services) to add this service name if it does not exist.
		//! \param logger           can be 0, your own implementation of an smf::Logger or
		//!                          an SMF file logger (use smf::fileLogger) (see "Opening a Logger")
		//! \param queuesizes       The queue size for the outgoing queue, in number of queued items.
		//!                         If 0, the default value of 10 is used. 
		//! \param connectionTimeout Timeout (in milliseconds) for trying to connect, send or receive a message. 
		//!                             Note: If there are no messages being send or received, this timeout will not be triggered.
		//! \return A pointer to a ServiceChannel object
		//! \remark     Include: SmfClient.h, Logger.h, Error.h, ConnectionException.h
		//! \post       Cleanup: You must call smf::Client::Disconnect to cleanup (see Closing An Smf Service Channel)
		//! \exception smf::Error and smf::ConnectionException Specific exceptions that might be thrown are defined in ConnectionException.h.
		//! \note       These functions are thread safe. 
		//!             These functions will block (upto the timeout period) whilst trying to establish a connecion.
		ServiceChannel* Connect(
							const char* server, 
							const char* networkservice, 
							Logger*logger,
							unsigned int queuesizes = 0,//If 0 default values will be used
							unsigned int connectionTimeout = 0
							);

		//! \brief Make a connection to the SMF server over SSH. You can use this connection to open
		//! request channels to this server. You cannot open multiple request channels
		//! for the same service on a single service channel.
		//! \param server           The server hostname or IP address
		//! \param port             The port (by default SMF listens on 8603)
		//! \param logger           can be 0, your own implementation of an smf::Logger or
		//!                       an smf file logger (use smf::fileLogger)
		//! \param proxyInfo       The intance of SocksProxyInfo which provide information for 
		//!                       setting up SSH connection to the SMF server.
		//! \param queuesizes       The queue size for the outgoing queue, in number of queued items.
		//!                         If 0, the default value of 10 is used.
		//! \param connectionTimeout Timeout (in milliseconds) for trying to connect, send or receive a message.
		//!                             Note: If there are no messages being send or received, this timeout will not be triggered.
		//! \return A pointer to a ServiceChannel object
		//! \remark     Include: SmfClient.h, Logger.h, Error.h, ConnectionException.h
		//! \post       Cleanup: You must call smf::Client::Disconnect to cleanup (see Closing An Smf Service Channel)
		//! \exception smf::Error and smf::ConnectionException Specific exceptions that might be thrown are defined in ConnectionException.h.
		//! \note       These functions are thread safe.
		//!             These functions will block (upto the timeout period) whilst trying to establish a connecion.
		ServiceChannel* Connect(
							const char* server, 
							unsigned short port,
							Logger*logger,
							SocksProxyInfo* proxyInfo,
							unsigned int queuesizes = 0,//If 0 default values will be used
							unsigned int connectionTimeout = 0
							);
        //! \brief Make a connection to the SMF server. You can use this connection to open
		//! request channels to this server. You cannot open multiple request channels
		//! for the same service on a single service channel. Returns ServiceChannelExt1 which 
        //! supports setting TCP keep alive interval.
		//! \param server           The server hostname or IP address
		//! \param port             The port (by default SMF listens on 8603)
		//! \param logger           can be 0, your own implementation of an smf::Logger or
		//!                       an smf file logger (use smf::fileLogger)
		//! \param queuesizes       The queue size for the outgoing queue, in number of queued items.
		//!                         If 0, the default value of 10 is used.
		//! \param connectionTimeout Timeout (in milliseconds) for trying to connect, send or receive a message.
		//!                             Note: If there are no messages being send or received, this timeout will not be triggered.
		//! \return A pointer to a ServiceChannelExt1 object
		//! \remark     Include: SmfClient.h, Logger.h, Error.h, ConnectionException.h
		//! \post       Cleanup: You must call smf::Client::Disconnect to cleanup (see Closing An Smf Service Channel)
		//! \exception smf::Error and smf::ConnectionException Specific exceptions that might be thrown are defined in ConnectionException.h.
		//! \note       These functions are thread safe.
		//!             These functions will block (upto the timeout period) whilst trying to establish a connecion.
		ServiceChannelExt1* ConnectExt1(
							const char* server, 
							unsigned short port,
							Logger*logger,
							unsigned int queuesizes = 0,//If 0 default values will be used
							unsigned int connectionTimeout = 0
							);
		//! \brief Make a connection to the SMF server. You can use this connection to open
		//! request channels to this server. You cannot open multiple request channels
		//! for the same service on a single service channel. Returns ServiceChannelExt1 which 
        //! supports setting TCP keep alive interval.
		//! \param server           The server hostname or IP address
		//! \param networkservice   A service name as defined in the services file in the OS. 
		//!                         Note, you will need to edit the services file  (
		//!                         C:\WINDOWS\system32\drivers\etc \services) to add this service name if it does not exist.
		//! \param logger           can be 0, your own implementation of an smf::Logger or
		//!                          an SMF file logger (use smf::fileLogger) (see "Opening a Logger")
		//! \param queuesizes       The queue size for the outgoing queue, in number of queued items.
		//!                         If 0, the default value of 10 is used. 
		//! \param connectionTimeout Timeout (in milliseconds) for trying to connect, send or receive a message. 
		//!                             Note: If there are no messages being send or received, this timeout will not be triggered.
		//! \return A pointer to a ServiceChannel object
		//! \remark     Include: SmfClient.h, Logger.h, Error.h, ConnectionException.h
		//! \post       Cleanup: You must call smf::Client::Disconnect to cleanup (see Closing An Smf Service Channel)
		//! \exception smf::Error and smf::ConnectionException Specific exceptions that might be thrown are defined in ConnectionException.h.
		//! \note       These functions are thread safe. 
		//!             These functions will block (upto the timeout period) whilst trying to establish a connecion.
		ServiceChannelExt1* ConnectExt1(
							const char* server, 
							const char* networkservice, 
							Logger*logger,
							unsigned int queuesizes = 0,//If 0 default values will be used
							unsigned int connectionTimeout = 0
							);

		//! \brief Make a connection to the SMF server over SSH. You can use this connection to open
		//! request channels to this server. You cannot open multiple request channels
		//! for the same service on a single service channel. Returns ServiceChannelExt1 which 
        //! supports setting TCP keep alive interval.
		//! \param server           The server hostname or IP address
		//! \param port             The port (by default SMF listens on 8603)
		//! \param logger           can be 0, your own implementation of an smf::Logger or
		//!                       an smf file logger (use smf::fileLogger)
		//! \param proxyInfo       The intance of SocksProxyInfo which provide information for 
		//!                       setting up SSH connection to the SMF server.
		//! \param queuesizes       The queue size for the outgoing queue, in number of queued items.
		//!                         If 0, the default value of 10 is used.
		//! \param connectionTimeout Timeout (in milliseconds) for trying to connect, send or receive a message.
		//!                             Note: If there are no messages being send or received, this timeout will not be triggered.
		//! \return A pointer to a ServiceChannel object
		//! \remark     Include: SmfClient.h, Logger.h, Error.h, ConnectionException.h
		//! \post       Cleanup: You must call smf::Client::Disconnect to cleanup (see Closing An Smf Service Channel)
		//! \exception smf::Error and smf::ConnectionException Specific exceptions that might be thrown are defined in ConnectionException.h.
		//! \note       These functions are thread safe.
		//!             These functions will block (upto the timeout period) whilst trying to establish a connecion.
		ServiceChannelExt1* ConnectExt1(
							const char* server, 
							unsigned short port,
							Logger*logger,
							SocksProxyInfo* proxyInfo,
							unsigned int queuesizes = 0,//If 0 default values will be used
							unsigned int connectionTimeout = 0
							);

							
							
		//! \brief You should call this to close a smf::ServiceChannel once you have finished with it.
		//! Note: you should close the LogServiceRequestHandler and the ParameterServiceRequestHandler (if they were opened) before you try to close the service channel.
		//! \param sc A smf::ServiceChannel pointer created using the smf::Client::Connect function
		//! \exception smf::Error
		//! \remark Include: SmfClient.h, Logger.h
		//! \note This function is thread safe.
		void Disconnect(ServiceChannel* sc);

		void Disconnect(ServiceChannel* sc, size_t uniqueKey);

		unsigned int SetChannelLimit(unsigned int limit);

		//! \brief You should call this to create an object of smf::SocksProxyInfo for making a connection to SMF through SSH.		
		//! \param bindAddress The bind address used to bind the SSH tunnel to a specific local address
		//! \param portMin The port number to setup SSH tunnel for port forwarding
		//! \param numPortsAvail The number of port availble for setting up SSH tunnel. If it is 1, it will try the port number portMin and portMin + 1
		//! \param privateKeyFile The private key file to setup SSH tunnel
		//! \param userId The user name to setup SSH tunnel e.g. reutadmin in Windows and Solaris platform
		//! \param sshTunnelPort The port number for setting up SSH tunnel to connect to SSH daemon
		//! \remark Include: SmfClient.h, Logger.h
		//! \note This function is thread safe.
		SocksProxyInfo *CreateSocksProxyInfo(const char* bindAddress, 
											unsigned short portMin, 
											unsigned short numPortsAvail, 
											const char* privateKeyFile,
											const char* userId, 
											unsigned short sshTunnelPort);

		void DestroySocksProxyInfo(SocksProxyInfo* info);

#ifdef WIN32
		//! \brief You can call this to create an object of smf::ServiceChannelResourcePool, which provide 
		//         shared resources for multiple SMF connections. By using smf::ServiceChannelResourcePool, multiple
		//         SMF connections will share the threads and buffers in the resource pool. You should only use
		//         smf::ServiceChannelResourcePool if you need to create large amount of SMF connections.
		//! \param logger can be 0, your own implementation of an smf::Logger or an smf file logger (use smf::fileLogger)
		//! \param maxChannels Max number of SMF channels that will be assigned to the resource pool
		//! \param numReceiveThreads The number of receive threads
		//                   If 0, default number is used.
		//! \param numSendThreadsAndOutputQueues The number of send threads and output queues
		//                   If 0, default number is used.
		//! \param outputQueueSize The size of each output queue
		//                  If 0, default number is used.
		//! \param numReconnectThreads The number of threads for auto-reconnection of the channels
		//                  If 0, default number is used.
		//! \param defaultMessageSize The size of each piece of buffer in bytes
		//                  If 0, default number is used.
		//! \param allocationLimit The size of dynamic allocation limit for each output queue, in bytes
		//                  If 0, default number is used.
		//! \remark Include: SmfClient.h, Logger.h
		//! \note This function is thread safe.
		ServiceChannelResourcePool* CreateServiceChannelResourcePool(Logger*logger,
																	unsigned int maxChannels,
																	unsigned int numReceiveThreads = 0,
																	unsigned int numSendThreadsAndOutputQueues = 0,
																	unsigned int outputQueueSize = 0,
																	unsigned int numReconnectThreads = 0,
																	unsigned int defaultMessageSize = 0,
																	unsigned int allocationLimit = 0
																	);

		void DestroyServiceChannelResourcePool(ServiceChannelResourcePool* rp);

		//! \brief You can call this to create an object of smf::ServiceBufferPool, which provide buffers
		//         for multiple SMF services. By using smf::ServiceBufferPool, multiple services of the same
		//         type will share the same set of buffers. You should only use smf::ServiceBufferPool
		//         if you need to create large amount of SMF connections.
		//! \param logger can be 0, your own implementation of an smf::Logger or an smf file logger (use smf::fileLogger)
		//! \param poolSize The number of pieces of buffer available for each type of service
		//                  If 0, default number is used.
		//! \param defaultMessageSize The size of each piece of buffer in bytes
		//                  If 0, default number is used.
		//! \param allocationLimit The size of dynamic allocation limit for each type of service, in bytes
		//                  If 0, default number is used.
		//! \remark Include: SmfClient.h, Logger.h
		//! \note This function is thread safe.
		ServiceBufferPool* CreateServiceBufferPool(	Logger* logger,
													unsigned int poolSize = 0,
													unsigned int defaultMessageSize = 0,
													unsigned int allocationLimit = 0);

		void DestroyServiceBufferPool(ServiceBufferPool* bufferPool);

		//! \brief Make a connection to the SMF server. You can use this connection to open
		//! request channels to this server. You cannot open multiple request channels
		//! for the same service on a single service channel.
		//! \param rp				The resource pool object created by CreateServiceChannelResourcePool function
		//! \param server           The server hostname or IP address
		//! \param port             The port (by default SMF listens on 8603)
		//! \param logger           can be 0, your own implementation of an smf::Logger or
		//!                       an smf file logger (use smf::fileLogger)
		//! \param queuesizes       The queue size for the outgoing queue, in number of queued items.
		//!                         If 0, the default value of 10 is used.
		//! \param connectionTimeout Timeout (in milliseconds) for trying to connect, send or receive a message.
		//!                             Note: If there are no messages being send or received, this timeout will not be triggered.
		//! \return A pointer to a ServiceChannel object
		//! \remark     Include: SmfClient.h, Logger.h, Error.h, ConnectionException.h
		//! \post       Cleanup: You must call smf::Client::Disconnect to cleanup (see Closing An Smf Service Channel)
		//! \exception smf::Error and smf::ConnectionException Specific exceptions that might be thrown are defined in ConnectionException.h.
		//! \note       These functions are thread safe.
		//!             These functions will block (upto the timeout period) whilst trying to establish a connecion.
		ServiceChannel* Connect(
							ServiceChannelResourcePool* rp,
							const char* server, 
							unsigned short port,
							Logger*logger,
							unsigned int connectionTimeout = 0
							);

		//! \brief Make a connection to the SMF server. You can use this connection to open
		//! request channels to this server. You cannot open multiple request channels
		//! for the same service on a single service channel.
		//! \param rp				The resource pool object created by CreateServiceChannelResourcePool function
		//! \param server           The server hostname or IP address
		//! \param networkservice   A service name as defined in the services file in the OS. 
		//!                         Note, you will need to edit the services file  (
		//!                         C:\WINDOWS\system32\drivers\etc \services) to add this service name if it does not exist.
		//! \param logger           can be 0, your own implementation of an smf::Logger or
		//!                          an SMF file logger (use smf::fileLogger) (see "Opening a Logger")
		//! \param queuesizes       The queue size for the outgoing queue, in number of queued items.
		//!                         If 0, the default value of 10 is used. 
		//! \param connectionTimeout Timeout (in milliseconds) for trying to connect, send or receive a message. 
		//!                             Note: If there are no messages being send or received, this timeout will not be triggered.
		//! \return A pointer to a ServiceChannel object
		//! \remark     Include: SmfClient.h, Logger.h, Error.h, ConnectionException.h
		//! \post       Cleanup: You must call smf::Client::Disconnect to cleanup (see Closing An Smf Service Channel)
		//! \exception smf::Error and smf::ConnectionException Specific exceptions that might be thrown are defined in ConnectionException.h.
		//! \note       These functions are thread safe. 
		//!             These functions will block (upto the timeout period) whilst trying to establish a connecion.
		ServiceChannel* Connect(
							ServiceChannelResourcePool* rp,
							const char* server, 
							const char* networkservice,
							Logger*logger,
							unsigned int connectionTimeout = 0
							);

		//! \brief Make a connection to the SMF server over SSH. You can use this connection to open
		//! request channels to this server. You cannot open multiple request channels
		//! for the same service on a single service channel.
		//! \param rp				The resource pool object created by CreateServiceChannelResourcePool function
		//! \param server           The server hostname or IP address
		//! \param port             The port (by default SMF listens on 8603)
		//! \param logger           can be 0, your own implementation of an smf::Logger or
		//!                       an smf file logger (use smf::fileLogger)
		//! \param proxyInfo       The intance of SocksProxyInfo which provide information for 
		//!                       setting up SSH connection to the SMF server.
		//! \param queuesizes       The queue size for the outgoing queue, in number of queued items.
		//!                         If 0, the default value of 10 is used.
		//! \param connectionTimeout Timeout (in milliseconds) for trying to connect, send or receive a message.
		//!                             Note: If there are no messages being send or received, this timeout will not be triggered.
		//! \return A pointer to a ServiceChannel object
		//! \remark     Include: SmfClient.h, Logger.h, Error.h, ConnectionException.h
		//! \post       Cleanup: You must call smf::Client::Disconnect to cleanup (see Closing An Smf Service Channel)
		//! \exception smf::Error and smf::ConnectionException Specific exceptions that might be thrown are defined in ConnectionException.h.
		//! \note       These functions are thread safe.
		//!             These functions will block (upto the timeout period) whilst trying to establish a connecion.
		ServiceChannel* Connect(
							ServiceChannelResourcePool* rp,
							const char* server, 
							unsigned short port,
							Logger*logger,
							SocksProxyInfo* proxyInfo,
							unsigned int connectionTimeout = 0
							);

		//! \brief Make a connection to the SMF server. You can use this connection to open
		//! request channels to this server. You cannot open multiple request channels
		//! for the same service on a single service channel. Returns ServiceChannelExt1 which 
        //! supports setting TCP keep alive interval.
		//! \param rp				The resource pool object created by CreateServiceChannelResourcePool function
		//! \param server           The server hostname or IP address
		//! \param port             The port (by default SMF listens on 8603)
		//! \param logger           can be 0, your own implementation of an smf::Logger or
		//!                       an smf file logger (use smf::fileLogger)
		//! \param queuesizes       The queue size for the outgoing queue, in number of queued items.
		//!                         If 0, the default value of 10 is used.
		//! \param connectionTimeout Timeout (in milliseconds) for trying to connect, send or receive a message.
		//!                             Note: If there are no messages being send or received, this timeout will not be triggered.
		//! \return A pointer to a ServiceChannel object
		//! \remark     Include: SmfClient.h, Logger.h, Error.h, ConnectionException.h
		//! \post       Cleanup: You must call smf::Client::Disconnect to cleanup (see Closing An Smf Service Channel)
		//! \exception smf::Error and smf::ConnectionException Specific exceptions that might be thrown are defined in ConnectionException.h.
		//! \note       These functions are thread safe.
		//!             These functions will block (upto the timeout period) whilst trying to establish a connecion.
		ServiceChannelExt1* ConnectExt1(
							ServiceChannelResourcePool* rp,
							const char* server, 
							unsigned short port,
							Logger*logger,
							unsigned int connectionTimeout = 0
							);

		//! \brief Make a connection to the SMF server. You can use this connection to open
		//! request channels to this server. You cannot open multiple request channels
		//! for the same service on a single service channel. Returns ServiceChannelExt1 which 
        //! supports setting TCP keep alive interval.
		//! \param rp				The resource pool object created by CreateServiceChannelResourcePool function
		//! \param server           The server hostname or IP address
		//! \param networkservice   A service name as defined in the services file in the OS. 
		//!                         Note, you will need to edit the services file  (
		//!                         C:\WINDOWS\system32\drivers\etc \services) to add this service name if it does not exist.
		//! \param logger           can be 0, your own implementation of an smf::Logger or
		//!                          an SMF file logger (use smf::fileLogger) (see "Opening a Logger")
		//! \param queuesizes       The queue size for the outgoing queue, in number of queued items.
		//!                         If 0, the default value of 10 is used. 
		//! \param connectionTimeout Timeout (in milliseconds) for trying to connect, send or receive a message. 
		//!                             Note: If there are no messages being send or received, this timeout will not be triggered.
		//! \return A pointer to a ServiceChannel object
		//! \remark     Include: SmfClient.h, Logger.h, Error.h, ConnectionException.h
		//! \post       Cleanup: You must call smf::Client::Disconnect to cleanup (see Closing An Smf Service Channel)
		//! \exception smf::Error and smf::ConnectionException Specific exceptions that might be thrown are defined in ConnectionException.h.
		//! \note       These functions are thread safe. 
		//!             These functions will block (upto the timeout period) whilst trying to establish a connecion.
		ServiceChannelExt1* ConnectExt1(
							ServiceChannelResourcePool* rp,
							const char* server, 
							const char* networkservice,
							Logger*logger,
							unsigned int connectionTimeout = 0
							);

		//! \brief Make a connection to the SMF server over SSH. You can use this connection to open
		//! request channels to this server. You cannot open multiple request channels
		//! for the same service on a single service channel. Returns ServiceChannelExt1 which 
        //! supports setting TCP keep alive interval.
		//! \param rp				The resource pool object created by CreateServiceChannelResourcePool function
		//! \param server           The server hostname or IP address
		//! \param port             The port (by default SMF listens on 8603)
		//! \param logger           can be 0, your own implementation of an smf::Logger or
		//!                       an smf file logger (use smf::fileLogger)
		//! \param proxyInfo       The intance of SocksProxyInfo which provide information for 
		//!                       setting up SSH connection to the SMF server.
		//! \param queuesizes       The queue size for the outgoing queue, in number of queued items.
		//!                         If 0, the default value of 10 is used.
		//! \param connectionTimeout Timeout (in milliseconds) for trying to connect, send or receive a message.
		//!                             Note: If there are no messages being send or received, this timeout will not be triggered.
		//! \return A pointer to a ServiceChannel object
		//! \remark     Include: SmfClient.h, Logger.h, Error.h, ConnectionException.h
		//! \post       Cleanup: You must call smf::Client::Disconnect to cleanup (see Closing An Smf Service Channel)
		//! \exception smf::Error and smf::ConnectionException Specific exceptions that might be thrown are defined in ConnectionException.h.
		//! \note       These functions are thread safe.
		//!             These functions will block (upto the timeout period) whilst trying to establish a connecion.
		ServiceChannelExt1* ConnectExt1(
							ServiceChannelResourcePool* rp,
							const char* server, 
							unsigned short port,
							Logger*logger,
							SocksProxyInfo* proxyInfo,
							unsigned int connectionTimeout = 0
							);
#endif
        
		void SetQueueSleep(unsigned int);

		void SetReservedStackSize(unsigned int);

	}
}

#endif
