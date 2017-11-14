#ifndef CONNECTIONEXCEPTION_H
#define CONNECTIONEXCEPTION_H

#include <winsock2.h>
#include "Error.h"
#include "CodingError.h"

namespace smf{
	class NetworkError{
		unsigned int lasterror;
		public:
			NetworkError::NetworkError(){
				lasterror = WSAGetLastError();
			}
			unsigned int NetworkError::error(){
				return lasterror;
			}
			virtual ~NetworkError(){}
	};

	class ConnectionException:
		public NetworkError
	{	

	public:
		virtual ~ConnectionException() {}
		ConnectionException(){
		}

	};

	class ClientSecurityCheckFailed:
		public smf::Error
	{
	public:
		ClientSecurityCheckFailed(const char* why)
			:
		smf::Error("Client failed the security check: ")
		{
			(*this) << why;
		}

	};


	class FailedToSetIdleTimeout :
	public smf::Error,
	public ConnectionException
	{
	public:
		FailedToSetIdleTimeout()
			: smf::Error("Failed to set the connection idle time: last error: ")
		{
			(*this) << error();
		}
	};

	class FailedToGetService:
	public smf::Error,
	public ConnectionException
	{
	public:
		FailedToGetService(const char* serviceName):
		smf::Error("Could not retrieve service information for ")
		{
			(*this)  << serviceName << " last system error: " << error();

		}

	private:
		FailedToGetService();

	};

	class RecvMoreThanRequest:
	public smf::CodingError,
	public ConnectionException
	{
	public:
		RecvMoreThanRequest( )
			: smf::CodingError( "Comms", "Number of byte recv more then requested: last error: ")
		{
			( *this ) << error( );
		}
	};

	class SendMoreThanRequest:
	public smf::CodingError,
	public ConnectionException
	{
	public:
		SendMoreThanRequest( )
			: smf::CodingError( "Comms", "Number of byte send more then requested: last error: ")
		{
			( *this ) << error( );
		}
	};

	class ConnectionTimeout : 
	public smf::Error,
	public ConnectionException
	{
		unsigned int dataRead;
        unsigned int bufferSize;
	public:
		ConnectionTimeout(	unsigned int dataRead, 
							unsigned int bufferSize,
							const char* why = "",
							unsigned int timeElapsed = -1):
		dataRead(dataRead),bufferSize(bufferSize),
            smf::Error("Connection timeout: "){
                (*this) << " (" << dataRead << ", " 
						<< bufferSize << ", "
						<< timeElapsed << "). "
						<< why;
		}
		unsigned int DataRead() const
        {
			return dataRead;
		}
        unsigned int BufferSize() const
        {
            return bufferSize;
        }
		virtual ~ConnectionTimeout() {}
	};



	class ConnectionFailure : 
	public smf::Error,
	public ConnectionException
	{
	public:
		ConnectionFailure():
		smf::Error("Connection failure - "){
			(*this) << (int)error();
		}
		virtual ~ConnectionFailure(){}
	};

	class ConnectionClosed : 
	public ConnectionException,
	public smf::LogMsg
	{
	public:
		virtual ~ConnectionClosed() {};

		ConnectionClosed():
		smf::LogMsg("The connection has been closed"){}
	};


	class SocketFailure : 
	public smf::Error,
	public ConnectionException
	{
	public:
		SocketFailure(const char* reason = "reason not specified"):smf::Error("Socket Failure ("){
			(*this) << reason << ").";
		}
		virtual ~SocketFailure() {}
	};

	class InvalidAddress : 
	public smf::Error,
	public ConnectionException
	{
	public:
		InvalidAddress():smf::Error("Connection Failed: address is invalid"){}
		virtual ~InvalidAddress() {}
	};

	class AcceptFailure : 
	public smf::Error,
	public ConnectionException
	{
	public:
		AcceptFailure():
		smf::Error("Accept failure"){

		}
		virtual ~AcceptFailure() {}
	};

	class ClosedConnectionOnTryEstablishTls:
		public smf::Error,
		public ConnectionException
	{
	public:
		ClosedConnectionOnTryEstablishTls():Error("The connection was closed by the server when we tried to initialise TLS.")
		{
		}
		virtual ~ClosedConnectionOnTryEstablishTls(){}

	};

	class SocksConnectionFailed:		
		public smf::Error,
		public ConnectionException
	{
	public:
		SocksConnectionFailed(const char* reason):
		  Error("The connection was closed when we tried to establish a tunnel through SSH. Details; ")
		{
			(*this) << reason;
		}
		virtual ~SocksConnectionFailed(){}

	};
}
#endif
