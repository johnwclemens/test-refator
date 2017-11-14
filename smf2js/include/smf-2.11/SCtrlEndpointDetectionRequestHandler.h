#ifndef SCTRL_ENDPOINT_DETECTION_REQUEST_HANDLER_H
#define SCTRL_ENDPOINT_DETECTION_REQUEST_HANDLER_H

#include "Types.h"
#include "Error.h"

namespace smf {

    class SCtrlEndpointDetectionResponseHandler;
    class ServiceChannel;

    //! This interface is for the remote client to subscribe for the Heartbeat messages.
    //!
    class SCtrlEndpointDetectionRequestHandler
    {
    public:
        
		class SizeLimitExceedsAllocationLimit : public Error
		{
		public:
			SizeLimitExceedsAllocationLimit(const char* details) : Error(details)
			{
			}
		};

		class CouldNotGetBuffer : public Error
		{
		public:
			CouldNotGetBuffer(unsigned int size)
				: Error("Could not get a message buffer from the request service - ")
			{
				(*this) << " size requested " << size;
			}
		};

		class CouldNotHandleRequest : public Error
		{
		public:
			CouldNotHandleRequest()
				: Error("SCtrlEndpointDetectionRequestHandler could not handle "
                    "request because the queue of the client service is full")
			{
				  
			}
		};

		class ConnectionDropped : public Error
		{
		public:
			ConnectionDropped() 
				: Error("The connection to the server has been closed or dropped")
			{
			}
		};

    public:

        SCtrlEndpointDetectionRequestHandler(void) { }

        virtual ~SCtrlEndpointDetectionRequestHandler(void) { }

    public:

        //! \brief      Use this function to subscribe to SMF for the Heartbeat 
        //!             messages.
        //! \param      identifier  This is an identifier defined by the 
        //!                         application. SMF does not use it; SMF will
        //!                         pass this back to you when reporting 
        //!                         whether the subscription was accepted or 
        //!                         not through your 
        //!                         SCtrlEndpointDetectionResponseHandler
        //!                         implementation.
        //! \remark     Include: SCtrlEndpointDetectionRequestHandler.h,
        //!             SCtrlEndpointDetectionResponseHandler.h, Error.h
        //! \exception  smf::Error  See SCtrlEndpointDetectionRequestHandler.h
        //!                         for a list of specific exceptions.
        //! \note       This subscribe function is thread safe.
        //! \post       Scuccessful and failure subscription will be sent to 
        //!             smf::SCtrlEndpointDetectionResponseHandler::ReportSuccess and
        //!             smf::SCtrlEndpointDetectionResponseHandler::ReportFailure
        //!             respectively.
        //!             Once successfully subscribed, you will be sent all 
        //!             heartbeats through your SCtrlEndpointSubscriberResponseHandler
        //!             implementation through the
        //!             smf::SCtrlEndpointDetectionResponseHandler::ReportHeartbeat
        //!             function.
        virtual void Subscribe(UnsignedInt identifier) = 0;

        //! \brief  Use this function to unsubscribe to SMF for the Heartbeat 
        //!         messages.
        //! \param  identifier  This is an identifier supplied by you, SMF
        //!                     will pass it back to you when the subscribe is
        //!                     successed or not.
        //! \post       Scuccessful and failure unsubscription will be sent to 
        //!             smf::SCtrlEndpointDetectionResponseHandler::ReportSuccess and
        //!             smf::SCtrlEndpointDetectionResponseHandler::ReportFailure
        //!             respectively.
        virtual void UnSubscribe(UnsignedInt identifier) = 0;
    };

};
#endif //SCTRL_ENDPOINT_DETECTION_REQUEST_HANDLER_H
