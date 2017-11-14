#ifndef DURATION_ENTRY
#define DURATION_ENTRY

namespace smf
{

    class DurationEntry
    {
    public:
        DurationEntry(unsigned long long int totalMilliSeconds);
        ~DurationEntry(void);

        unsigned long long int Days() const;
        unsigned int Hours() const;
        unsigned int Minutes() const;
        unsigned int Seconds() const;
        unsigned int MilliSeconds() const;

        unsigned long long int TotalMilliSeconds() const;

    private:
        unsigned long long int _totalMilliSeconds;
    };

}

#endif
