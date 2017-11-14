
#ifndef SMF_VECTORWRAPPER_H
#define SMF_VECTORWRAPPER_H

namespace smf{

	template <typename ItemType>
	class VectorWrapper{
	public:

		typedef ItemType Item; 

		VectorWrapper(){}
		virtual ~VectorWrapper(){}

		virtual const Item at(size_t index) const = 0;

		virtual size_t size() const = 0;

	protected:
		//do not allow the interface to be copied directly
		VectorWrapper(const VectorWrapper&){}
		VectorWrapper& operator=(const VectorWrapper&){
			return *this;
		}
	};

}
#endif