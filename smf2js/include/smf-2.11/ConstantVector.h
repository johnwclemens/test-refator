
#ifndef CONSTANTVECTOR_H
#define CONSTANTVECTOR_H

#include "Error.h"
#include <vector>

namespace smf{
	template <typename VectorType>
	class ConstantVector
	{

	public:
		class IndexOutOfBounds:
			public smf::Error
		{
		public:
			IndexOutOfBounds(size_t size, size_t index):Error("A vector type was accessed beyonds it last element. ")
			{
				(*this) << "Size " << size << " Index " << index;
			}
		};

		typedef std::vector<VectorType> Types;
		typedef typename Types::const_iterator const_iterator;
		typedef typename Types::const_iterator iterator;

		ConstantVector(std::vector<VectorType>& v):
		types(v)
		{
			
		}

        ConstantVector(const std::vector<VectorType>& v):
        types(v)
        {
        
        }

		const VectorType& operator[](size_t index) const
		{
			if(index < types.size()){
				return types[index];
			}
			throw IndexOutOfBounds(types.size(), index);
		}

		size_t size()const{
			return types.size();
		}

		bool operator ==(const ConstantVector& rhs)const{
			return types == rhs.types;
		}
		bool operator !=(const ConstantVector& rhs)const{
			return types != rhs.types;
		}

		typename Types::const_iterator begin()const{
			return types.begin();
		}

		typename Types::const_iterator end()const{
			return types.end();
		}

		operator const Types() const
		{
			return types;
		}

	private:
		ConstantVector();
		ConstantVector(const ConstantVector&);
		ConstantVector& operator=(const ConstantVector&);

		const Types& types;
	};
}
#endif