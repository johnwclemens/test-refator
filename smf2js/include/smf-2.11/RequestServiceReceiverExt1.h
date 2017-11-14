
#ifndef REQUESTSERVICERECEIVERRESPONSEHANDLEREXT1_H
#define REQUESTSERVICERECEIVERRESPONSEHANDLEREXT1_H

#include "ConnectionIdentity.h"
#include "ResponsePayload.h"
#include "RequestServiceConnectionInfo.h"
#include "RequestServiceReceiver.h"
#include "Types.h"

#include <string>

namespace smf {
		
	
    //! You will need to implement your own version of RequestServiceReceiver
    //! After you've registered using the RequestServiceTransmitter::Register you'll receive all requests through your implementation of this class
    class RequestServiceReceiverExt1 : public RequestServiceReceiver
    {
    public:
        
        typedef ResponsePayload Payload;
        typedef std::vector<RequestServiceConnectionInfo> ConnectionInformation;

        //! \brief Callback function from smf::RequestServiceTransmitter::Register
        //! \param receiver     The receiver that registered succesfully
        //! \param identifier   This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
        virtual void RegistrationSuccess(const std::string &receiver, UnsignedInt identifier) = 0;

        //! \brief Callback function from smf::RequestServiceTransmitter::Register
        //! \param receiver     The receiver that failed to register
        //! \param identifier   This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
        //! \param reason       Reason of the registration failure. Refer to ArsMessage.h for possible failure reasons
        virtual void RegistrationFailure(   const std::string &receiver, 
                                            UnsignedInt identifier,
                                            UnsignedInt reason) = 0;
                   
		//! \brief Callback function from smf::RequestServiceTransmitterExt1::Subscribe
		//!	       When this function is called, subscription on the command is completed successfully.
		//! \param receiver 	The name of the receiver which subscribed the command successfully.
		//! \param command		The name of the command that subscribed successfully
		//! \param identifier	The identifier supplied by in the SubscribeCommand call.
        virtual void SubscribeCommandSuccess(const std::string & receiver, 
                                              const std::string & command,
                                              UnsignedInt identifier) = 0;
        
		//! \brief Callback function from smf::RequestServiceTransmitterExt1::Subscribe
		//!	       When this function is called, subscription on the command is failed.
		//! \param receiver 	The name of the receiver which failed to subscribe the command
		//! \param command		The name of the command that failed to subscribe.
		//! \param identifier	The identifier supplied by in the SubscribeCommand call.		
		//! \param reason		Reason of the subscription failure. Reger to ArsMessage.h for
		//!			            possible failure reasons.
        virtual void SubscribeCommandFailure(const std::string & receiver,
                                      const std::string & command,
                                      UnsignedInt identifier,
                                      UnsignedInt reason) = 0;
		
		//! \brief Callback function from smf::RequestServiceTransmitterExt1::Unsubscribe
		//!	       When this function is called, unsubscription on the command is completed successfully.
		//! \param receiver 	The name of the receiver which unsubscribed the command successfully.
		//! \param command		The name of the command that unsubscribed the command successfully.
		//! \param identifier	The identifier supplied by in the UnsubscribeCommand call.		
		virtual void UnsubscribeCommandSuccess(const std::string & receiver, 
                                        const std::string & command,
                                        UnsignedInt identifier) = 0;
        
		//! \brief Callback function from smf::RequestServiceTransmitterExt1::Unsubscribe
		//!	       When this function is called, unsubscription on the command is failed.
		//! \param receiver 	The name of the receiver which failed to unsubscribe the command
		//! \param command		The name of the command that failed to unsubscribe
		//! \param identifier	The identifier supplied by in the UnsubscribeCommand call.			
		//! \param reason		Reason of the unsubscription failure. Reger to ArsMessage.h for
		//!			            possible failure reasons.
        virtual void UnsubscribeCommandFailure(const std::string & receiver,
                                        const std::string & command,
                                        UnsignedInt identifier,
                                        UnsignedInt reason) = 0;                                

        //! \brief This is how you receive request from the sender application
        //! \param id   This identifies the sender.  if you wish to send a response, you'll need to pass this to RequestServiceTransmitter::Response
        //! \param receiver This is the name of the receiver registered using RequestServiceTransmitter::Register
        //! \param payload  This is the request (it is arbitrary binary data)
        //! \note You should use RequestServiceTransmitterExt1::Reponse(const ConnectionIdentity, 
        //!       const std::string &, const Payload) to respond this request if needed
        virtual void Request(const ConnectionIdentity id, const std::string &receiver, Payload &payload) = 0;

		//! \brief This is how you receive command-based request from the sender
		//!        application. 
		//! \param id			 This identifies the sender. You'll need to pass this to RequestServiceTransmitterExt1::Reponse to send a response.
		//! \param receiverName  The name of the registered receiver which received this command
		//! \param command		 The command sent by the sender
		//! \parma payload 		 The arbitrary binary data from sender.
        //! \param senderExpectation    Contains the expectation from the sender on whether you need to repsonse; 
        //!                             and if need, the expected successful response code and response timeout
        //! \note You should use RequestServiceTransmitterExt1::Reponse(const CommandBasedConnectionIdentity, 
        //!       const std::string &, const std::string&, UnsignedInt, const Payload)
        //!       to respond this request if needed
		virtual void Request(const CommandBasedConnectionIdentity id, 
							 const std::string & receiverName,
							 const std::string & command, 
							 const Payload& payload, 
							 const SenderExpectation& senderExpectation) = 0;

							 
        //! \brief Callback function from smf::RequestServiceTransmitter::Reponse
        //! Called if SMF can't send a response
        //! \param receiver     The receiver name
        //! \param identifier   This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
        //! \param reason       Reason of failure.  Refer to ArsMessage.h for possible failure reasons
        virtual void ReportFailure(         const std::string &receiver, 
                                            UnsignedInt identifier,
                                            UnsignedInt reason) = 0;


        //! \brief Callback function from smf::RequestServiceTransmitter::RequestConnectionInfo
        //! \param receiver     The receiver name
        //! \param identifier   This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
        //! \param ConnectionInfomation This is the connection information.
        virtual void ReportConnectionInformation(
                                            const std::string &receiver, 
                                            UnsignedInt identifier,
                                            const ConnectionInformation&) = 0;

        virtual ~RequestServiceReceiverExt1(){}
    };
}

#endif
