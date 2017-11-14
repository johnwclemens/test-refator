#ifndef REQUESTSERVICETRANSMITTEREXT1_H
#define REQUESTSERVICETRANSMITTEREXT1_H

#include "RequestServiceTransmitter.h"
#include "ConnectionIdentity.h"
#include "Error.h"
#include "ArsPayload.h"
#include "Types.h"
#include <string>

namespace smf {

    class RequestServiceReceiver;
    class ServiceChannel;
    class Logger;

	//! Use this class to send a respond after receiving a request through RequestServiceReceiver
    class RequestServiceTransmitterExt1 : public smf::RequestServiceTransmitter
    {
    public:
	    typedef ArsPayload Payload;

        //! \brief Sends a request response back to the sender.
		//! \param sender			The identifier of the SMF client that was passed in RequestServiceReceiver::Request
		//!	\param receiverName		The receiver name (the application can have more than one receiver) 
		//! \param payload			The arbitrary binary data sent back to sender in vector<char>
		//! \post	SMF will call back smf::RequestServiceReceiver::ReportFailure if SMF can't send a reponse
        //! \note	This function is thread-safe and will return immediately
	    virtual void Response(const ConnectionIdentity sender, const std::string& receiverName, 
							    const Payload &payload) = 0;
		
        //! \brief Sends a command response back to the sender.
		//! \param sender			The identifier of the SMF client that was passed in RequestServcieReceiverExt1::Request
		//!	\param receiverName		The receiver name (the application can have more than one receiver) 
		//! \param command			The name of the command 
		//! \param responseCode		The response code that is going to pass back to the sender.
		//! \param payload			The arbitrary binary data sent back to sender in vector<char>
		//! \post SMF will call back smf::RequestServiceReceiver::ReportFailure if SMF can't send a reponse
        //! \note	This function is thread-safe and will return immediately
		virtual void Response(const CommandBasedConnectionIdentity sender, 
							  const std::string & receiverName, 
							  const std::string& command, 
							  UnsignedInt responseCode, 
							  const Payload & payload) = 0;
		

		//! \brief An application must register one or more receivers by name in order to receive requests
		//!			An application can register any name(s) it wants but it must be unique to the server
		//! \param receiver		Receiver name to be registered
		//! \param identifier	This is an identifier defined by the application. 
		//!						SMF will pass this back to you in the callback function.
		//! \post	SMF will call back smf::RequestServiceReceiver::RegistrationSuccess or
		//!			smf::RequestServiceReceiver::RegistrationFailure
	    virtual void Register(const std::string &receiver, UnsignedInt identifier) = 0;
		
		//! \brief An application can use this to request information about the connection associated with this
		//!        ConnectionIdentity
		//! \param receiver		Receiver name (must already be registered)
		//! \param connection   The ConnectionIdentity of the connection to request information about. This is passed
		//!					    into the RequestServiceReceiver::Request function when your application receives a request.
		//! \param identifier	This is an identifier defined by the application. 
		//!						SMF will pass this back to you in the callback function.
		virtual void RequestConnectionInfo(const std::string& receiver, const ConnectionIdentity connection, UnsignedInt identifier) = 0;
		
		//! \brief Use this function to subscribe to a command, such that you can receive the command if sender sends it to all subscribers. 
		//! \param receiver 	Receiver name (must already be registered)
		//! \param command      The case insensitive command that is going to be subscribed
		//! \param identifier   This is an identifier defined by the application. 
		//!                     SMF will pass this back to you in the callback function.
        //! \note	This function is thread-safe and will return immediately
        virtual void SubscribeCommand(const std::string & receiver, const std::string & command, UnsignedInt identifier) = 0;
		
		//! \brief Use this function to unsubscribe to a command, to stop receiving the command if sender sends it to all subscribers. 
		//! \param receiver		Receiver name (must already be registered)
		//! \param command      The case insensitive command that is going to be unsubscribed
		//! \param identifier	This is an identifier defined by the application. 
		//!                     SMF will pass this back to you in the callback function.
        //! \note	This function is thread-safe and will return immediately
		virtual void UnsubscribeCommand(const std::string & receiver, const std::string & command, UnsignedInt identifier) = 0;
		
	    virtual ~RequestServiceTransmitterExt1(){}

        
	    class ServerNotSupportSubscription;
        class CommandNameEmpty;
        class ReceiverNameEmpty;
    };

    class RequestServiceTransmitterExt1::ServerNotSupportSubscription : public smf::Error
    {
    public:
        ServerNotSupportSubscription() : smf::Error("SMF server does not support command subscription API.") {}
        ~ServerNotSupportSubscription() {}
    };
    class RequestServiceTransmitterExt1::CommandNameEmpty : public smf::Error
    {
    public:
        CommandNameEmpty() : smf::Error("Command name is empty.") {}
        ~CommandNameEmpty() {}
    };

    class RequestServiceTransmitterExt1::ReceiverNameEmpty : public smf::Error
    {
    public:
        ReceiverNameEmpty() : smf::Error("Receiver name is empty.") {}
        ~ReceiverNameEmpty() {}
    };

}

#endif
