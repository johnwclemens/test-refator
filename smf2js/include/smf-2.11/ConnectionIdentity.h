
#ifndef CONNECTIONIDENTITY_H
#define CONNECTIONIDENTITY_H

namespace smf {

    class ConnectionIdentity
    {
    public:
	    ConnectionIdentity();
	    ConnectionIdentity(	unsigned int proxy, 
					    unsigned int key, 
					    unsigned int check,
					    unsigned int id);
	    unsigned int MessageId()const;
	    unsigned int Proxy()const;
	    unsigned int Key()const;
	    unsigned int Check()const;
    private:
	    unsigned int	proxy, 
					    key, 
					    check,
					    messageId;
    };
	
	class CommandBasedConnectionIdentity 
	{
	public:
		CommandBasedConnectionIdentity();
		CommandBasedConnectionIdentity(unsigned int proxy,
						unsigned int key,
						unsigned int check,
							   unsigned int id);
		const ConnectionIdentity & GetConnectionIdentity() const;
	private:
		ConnectionIdentity id;
	};
}

#endif
