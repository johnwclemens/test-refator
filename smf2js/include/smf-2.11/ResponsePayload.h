#ifndef RESPONSEPAYLOAD_H
#define RESPONSEPAYLOAD_H

#include "ArsPayload.h"
#include "Error.h"

namespace smf {

    class ResponsePayload
    {
    public:
	    class IndexOutOfBounds;

	    explicit ResponsePayload(const ArsPayload &payload);
	    unsigned int PayloadSize() const;
	    char& operator[] (unsigned int index) const;
	    bool operator==(const ResponsePayload& that) const;
	    bool operator!=(const ResponsePayload& that) const;
	    operator const ArsPayload() const;
    private:
		ResponsePayload(const ResponsePayload&);
		ResponsePayload &operator=(const ResponsePayload&);


	    const ArsPayload &payload;
    };

    class ResponsePayload::IndexOutOfBounds : public Error
	{
	public:
		IndexOutOfBounds();
	};
}

#endif
