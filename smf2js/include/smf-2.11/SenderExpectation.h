#ifndef SENDEREXPECTATION_H
#define SENDEREXPECTATION_H

namespace smf
{
    class SenderExpectation
    {
    public:
	    //! \return true if the sender expected there is a response from the receiver.
	    virtual bool RepsonseExpected() const = 0;
		
	    //! \return the response timeout that the sender expected. This value is valid only if
        //!         ResponseExpected() is true. Receiver should respond within this timeout.
	    virtual unsigned int ResponseTimeoutInMsec() const = 0;
		
	    //! \return the expected response code that represents a successful execution. This value is valid only if
        //!         ResponseExpected() is true. Receiver should respond with this code if the execution of the command succeed.
	    virtual unsigned int ExpectedSuccessRepsonseCode() const  = 0;

        virtual ~SenderExpectation() {}

    };
}

#endif /*SENDEREXPECTATION_H*/