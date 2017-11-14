#ifndef STATSFACTORY_H
#define STATSFACTORY_H

#include <vector>
#include <map>
#include <string>


namespace smf{


	// create the data model and partition
	// Integer and String wrap the data position
	class StatsMemory{
	public:
		class Integer;
		class String;
		class NullInteger;
		class NullString;

		virtual Integer* GetInteger(unsigned int index, const char*  groupName, const char* statsName) = 0;
		virtual String* GetString(unsigned int index, const char* groupName, const char* statsName) = 0;
		virtual void Destroy(Integer*) = 0;
		virtual void Destroy(String*) = 0;

		virtual bool SafeToDestroy() = 0;

		virtual ~StatsMemory() {}
	protected:
		StatsMemory() {}
	private:
		StatsMemory(const StatsMemory&);
		StatsMemory& operator=(const StatsMemory&);
	};

	//Integer and String are not thread safe (except the interlocked functions of Integer)
	class StatsMemory::Integer{
	public:
		virtual bool IsNull() = 0;
		virtual unsigned int inclocked() = 0; 
		virtual unsigned int declocked() = 0; 
		virtual void inc() = 0;
		virtual void dec() = 0;
		virtual void assign(unsigned int) = 0;
		virtual unsigned int retrieve () = 0;

		virtual ~Integer(){}
	};
	
	class StatsMemory::String{
	public:
		virtual bool IsNull() = 0;
		virtual void assign(const char*) = 0;
		virtual const char* retrieve () = 0;

		virtual ~String(){}
	};

	class StatsMemory::NullInteger:
		public StatsMemory::Integer
	{
	public:
		
		bool IsNull() ;
		unsigned int inclocked();
		unsigned int declocked(); 
		void inc();
		void dec();
		void assign(unsigned int);
		unsigned int retrieve ();

		~NullInteger(){}
	
	};
		
	class StatsMemory::NullString:
		public StatsMemory::String
	{
	public:
	
		bool IsNull() ;
		void assign(const char*);
		const char* retrieve ();

		~NullString(){}
	
	};

	class StatsFactory{
	public:
		struct Element{
			std::string groupName;
			std::string name;
			bool isInteger;
			unsigned int size;
		};

		//use to add non-default grouping 
		// by default there is only 1 group
		struct Group{
			std::string name;
			unsigned int arraySize;
		};
		typedef std::vector<Element> Elements;
		typedef std::vector<Group> Groups;

		virtual StatsMemory* Create(const char* name, const Elements&, const Groups&) = 0;
		virtual StatsMemory* Create(const char* name) = 0;
		virtual void Destroy(StatsMemory*) = 0;

		virtual ~StatsFactory() {}
	protected:

		StatsFactory() {}
	private:
		StatsFactory(const StatsFactory&);
		StatsFactory& operator=(const StatsFactory&);
	};
}

#endif
