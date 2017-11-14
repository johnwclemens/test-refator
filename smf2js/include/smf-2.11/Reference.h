
#ifndef REFERENCE_H
#define REFERENCE_H


namespace smf{
	class Counter{
	public:
		class Reference;

		Counter(Reference* r);
		~Counter();

	private:
		Counter();
		Counter(const Counter&);
		Counter& operator=(const Counter&);

		Reference *ref;

	};


	class Counter::Reference{

	public:
		virtual bool WaitClear(unsigned int) = 0;
	protected:
		
		Reference();
		virtual void inc() = 0;
		virtual void dec() = 0;
		virtual ~Reference();

	private:
		Reference(const Reference&);
		Reference& operator =(const Reference&);

		friend class Counter;
	};
}


#endif