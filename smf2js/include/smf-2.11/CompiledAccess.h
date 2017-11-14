// Overview:
//  ControlAccess.h header contains definitions for the library to support
//  generated code for compiled-access of physical partition groups and their
//  fields.
//
// Description:
//  The FieldElement base class holds the underlying Partition::DataPosition
//  in common for both the IntegerElement and the StringElement classes. These
//  classes can be used as public data members that are bound to individual
//  fields in a physical partition. The StringHolder type is simply a wrapper
//  for a raw char *, along with its length, to allow simple assignment from
//  a StringElement. For handling repetition, the FieldArray class template
//  supports subscripted access of individual field elements, i.e., either
//  IntegerElement or StringElement values.
//
//  The GroupElement class is the common base class for all generated group
//  classes. It binds itself by name to the underlying Partition::DataPosition
//  of its initial element. Generated group classes expose their fields
//  as public data members of IntegerElement, StringElement or FieldArray of
//  these types. They bind their fields by name given the initial offset of
//  the group. For handling repetition, the GroupArray class template
//  supports subscripted access of individual group elements.
//
// Author:
//  Kevlin Henney, August 2003
//  Copyright Reuters Hong Kong Ltd
//
// Comments:
//  - The implementation is all inlined for convenience and consistency with
//    the generated code: the user of the compiled-access headers need only
//    include the generated headers and this one in their compile path,
//    without needing to worry about additional items for compilation and
//    linkage.
//  - The StringHolder type is a contender for a more general library role,
//    perhaps as part of the core domain model types. This would compensate
//    for the lack of an encapsulated string type in the system.
//  - Error handling is absent but commented. Exceptions are the preferred
//    mechanism for dealing with these error conditions.
//  - The element types currently use the same access mechanism via a
//    Partition::DataPosition, regardless of transaction state.

#ifndef COMPILEDACCESS_H
#define COMPILEDACCESS_H

#include "FieldSearchOptimiser.h"
#include "CompiledAccessPartition.h"
#include "CompiledAccessEntryPoint.h"
#include "CodingError.h"

namespace smf{
	class FieldElement
	{
	public: // Access

		smf::CompiledAccessPartition::DataPosition *Position() const
		{
			if (position == 0)
				throw smf::CodingError("FieldElement", "Null position");
			return position;
		}

	protected: // Construction

		FieldElement()
			: position(0)
		{
		}

		FieldElement(smf::CompiledAccessPartition::DataPosition *pos)
			:
		position(pos)
		{
		}

        FieldElement(
			smf::CompiledAccessPartition::DataPosition *group,
			const char *fieldName, 
			smf::FieldSearchOptimiser *searchOptimiser )
		: position(Lookup(group, fieldName, searchOptimiser))
		{
			if (position == 0 || position->IsNull())
			{
				smf::CodingError e("FieldElement ctor", 
					"Failed to lookup the position of ");
				e << fieldName;
				throw e;
			}
		}

		FieldElement(
			smf::CompiledAccessPartition::DataPosition *group,
			const char *fieldName, 
			smf::FieldSearchOptimiser *searchOptimiser,
			smf::CompiledAccessPartition::IndexType index )
		: position(Lookup(group, fieldName, index, searchOptimiser))
		{
			if (position == 0 || position->IsNull())
			{
				smf::CodingError e("FieldElement ctor", 
					"Failed to lookup the position of ");
				e << fieldName;
				throw e;
			}
		}

		virtual ~FieldElement()
		{
			if ( position )
			{
				const smf::CompiledAccessPartition* pCompiledAccessPartition = position->RetrievePartition( );
				if ( pCompiledAccessPartition )
				{
					pCompiledAccessPartition->DestroyDataPosition( position );
				}
				position = 0;
			}
		}

		FieldElement(const FieldElement &that)
			: position(0)
		{
			if (that.position)
				position = that.position->Clone();
		}

        FieldElement &operator=(const FieldElement &that)
		{
            if (position)
                position->Assign(that.position);
			else if (that.position)
				position = that.position->Clone();

			return *this;
		}

	private: // Construction support

        static smf::CompiledAccessPartition::DataPosition *Lookup(
			smf::CompiledAccessPartition::DataPosition *group,
			const char *fieldName, 
			smf::FieldSearchOptimiser *searchOptimiser)
		{
			const smf::CompiledAccessPartition *partition = group->RetrievePartition();
			if (partition == 0)
				throw smf::CodingError("FieldElement Lookup", 
					"Null partition pointer held by the group data position");
			return partition->FindField(fieldName, group, searchOptimiser);
		}

		static smf::CompiledAccessPartition::DataPosition *Lookup(
			smf::CompiledAccessPartition::DataPosition *group,
			const char *fieldName, 
			smf::CompiledAccessPartition::IndexType index,
			smf::FieldSearchOptimiser *searchOptimiser)
		{
			const smf::CompiledAccessPartition *partition = group->RetrievePartition();
			if (partition == 0)
				throw smf::CodingError("FieldElement Lookup", 
					"Null partition pointer held by the group data position");
			return partition->FindField(fieldName, index, group, searchOptimiser);
		}

	private: // Representation

		smf::CompiledAccessPartition::DataPosition *position;

	};

	class IntegerElement : public FieldElement
	{
	public: // Construction

		IntegerElement()
		{
		}

		IntegerElement(smf::CompiledAccessPartition::DataPosition *pos)
			:
		FieldElement(pos)
		{
		}

		IntegerElement(
			smf::CompiledAccessPartition::DataPosition *group,
			const char *fieldName,  
			smf::FieldSearchOptimiser *searchOptimiser)
		: FieldElement(group, fieldName, searchOptimiser)
		{
			// Also need to check for correct type
		}

		IntegerElement(
			smf::CompiledAccessPartition::DataPosition *group,
			const char *fieldName,  
			smf::FieldSearchOptimiser *searchOptimiser,
			smf::CompiledAccessPartition::IndexType index )
		: FieldElement(group, fieldName, searchOptimiser, index)
		{
			// Also need to check for correct type
		}

	public: // Conversion

		bool operator == (smf::CompiledAccessPartition::IntegerType rhs)const
		{
			return Position()->IsEqual(rhs);
		}
		bool operator != (smf::CompiledAccessPartition::IntegerType rhs)const
		{
			return !Position()->IsEqual(rhs);
		}

		const IntegerElement &operator=(
			smf::CompiledAccessPartition::IntegerType rhs)const
		{
			//PR: should we try to output the name as well?			############################
			// Not yet transaction aware
			if(!Position()->PutValue(rhs))
			{
				smf::CodingError e("IntegerElement::operator=", "Failed to PutValue(");
				e << rhs << ")";
				throw e;
			}
			return *this;
		}

		operator smf::CompiledAccessPartition::IntegerType() const
		{
			smf::CompiledAccessPartition::IntegerType result = 0;
			if(!Position()->QueryValue(result))
			{
				throw smf::CodingError("IntegerElement::operator IntergerType()", 
					"Failed to QueryValue()");
			}
			return result;
		}

		smf::CompiledAccessPartition::IntegerType Increment() const
		{		
			return Position()->IncValue();
		}

		smf::CompiledAccessPartition::IntegerType LockedIncrement() const
		{
			return Position()->IncValueLocked();
		}

		smf::CompiledAccessPartition::IntegerType Decrement() const
		{
			return Position()->DecValue();
		}

		smf::CompiledAccessPartition::IntegerType LockedDecrement() const
		{
			return Position()->DecValueLocked();
		}
	};

	class StringElement : public FieldElement
	{
	public: // Construction

		StringElement()
		{
		}
		StringElement(smf::CompiledAccessPartition::DataPosition *pos)
			:
		FieldElement(pos)
		{
		}

        StringElement(
			smf::CompiledAccessPartition::DataPosition *group,
			const char *fieldName,  
			smf::FieldSearchOptimiser *searchOptimiser )
		: FieldElement(group, fieldName, searchOptimiser)
		{
			// Also need to check for correct type
		}

		StringElement(
			smf::CompiledAccessPartition::DataPosition *group,
			const char *fieldName,  
			smf::FieldSearchOptimiser *searchOptimiser,
			smf::CompiledAccessPartition::IndexType index )
		: FieldElement(group, fieldName, searchOptimiser, index)
		{
			// Also need to check for correct type
		}

	public: // Conversion
		smf::CompiledAccessPartition::LengthType Limit()const
        {
            return Position()->GetStringLimit();
        }
		bool operator == (const smf::CompiledAccessPartition::CharType *rhs)const
		{
			return Position()->IsEqual(rhs);
		}
		bool operator != (const smf::CompiledAccessPartition::CharType *rhs)const
		{
			return !Position()->IsEqual(rhs);
		}

		bool Update(const smf::CompiledAccessPartition::CharType *rhs)const
		{
			if(!Position()->PutValue(rhs)){
				return false;
			}
			return true;

		}

	};

	class StringHolder
	{
	public: // Construction

		StringHolder(char *data, 
			smf::CompiledAccessPartition::LengthType bufferSize)
		: data(data), reserved(bufferSize), used(0)
		{
			//size_t datasize = strlen(data);
			//if (datasize != (smf::CompiledAccessPartition::LengthType)datasize)
			//{
			//    smf::CodingError e("StringHolder", "data size > max LengthType");
			//    e << ": data size: " << (long)datasize;
			//    throw e;
			//}

			//used = (smf::CompiledAccessPartition::LengthType)datasize;
		}

	public: // Conversion

		StringHolder &operator=(const StringElement &rhs)
		{
            return *this = rhs.Position();
        }

        StringHolder &operator=(smf::CompiledAccessPartition::DataPosition *position)
        {
			if(!position->QueryValue(data, reserved, used))
			{
				throw smf::CodingError("StringHolder::operator=", 
					"Failed to QueryValue()");
			}
			return *this;
		}

	public: // Access

		const char operator[](smf::CompiledAccessPartition::IndexType index) const
		{
			if (index >= size())
			{
				smf::CodingError error("StringHolder::const char operator[] const",
					"index out of bound");
				error << " size: " << size() << " index: " << index;
				throw error;
			}
			return data[index];
		}

		char &operator[](smf::CompiledAccessPartition::IndexType index)
		{
			if (index >= size())
			{
				smf::CodingError error("StringHolder::char &operator[]",
					"index out of bound");
				error << " size: " << size() << " index: " << index;
				throw error;
			}
			return data[index];
		}

		operator const char *() const
		{
			return data;
		}

		operator char *()
		{
			return data;
		}

	public: // Capacity

		smf::CompiledAccessPartition::LengthType capacity() const
		{
			return reserved;
		}

		smf::CompiledAccessPartition::LengthType size() const
		{
			return used;
		}

		bool empty() const
		{
			return used == 0;
		}

	private: // Representation

		char *data;
		smf::CompiledAccessPartition::LengthType reserved, used;
			// Invariant: reserved >= used && used == strlen(data)

	};

	template<typename CompiledField, 
		smf::CompiledAccessPartition::LengthType repetitionCount>
	class FieldArray
	{
	public: // Construction

		FieldArray()
		{
		}

		FieldArray(smf::CompiledAccessPartition::DataPosition *groupPosition,
			const char *fieldName, 
			smf::FieldSearchOptimiser *initialiser)
		{
			smf::FieldSearchOptimiser *searchOptimiser = 
				smf::CompiledAccess::CreateFieldArraySearchOptimiser();

			try
			{
				searchOptimiser->set(initialiser);

				for(smf::CompiledAccessPartition::IndexType at = 0; 
					at < repetitionCount; ++at)
				{
					elements[at] = CompiledField(groupPosition, 
						fieldName, searchOptimiser, at);
				}

				smf::CompiledAccessPartition::LongIndexType foundAt = 0;
				if(searchOptimiser->index(foundAt)){
					initialiser->found(foundAt);
				}
			}
			catch (...)
			{
				smf::CompiledAccess::DestroyFieldArraySearchOptimiser(searchOptimiser);
				throw;
			}

			smf::CompiledAccess::DestroyFieldArraySearchOptimiser(searchOptimiser);
		}

	public: // Access

		const CompiledField &operator[](
										size_t fieldIndex) const
		{
			if(fieldIndex >= repetitionCount)
			{
				smf::CodingError e("CompiledField::operator[]", "field index (");
				e << fieldIndex << ") >= array size (" << repetitionCount << ")";
				throw e;
			}
			return elements[fieldIndex];
		}

		CompiledField &operator[](
			smf::CompiledAccessPartition::IndexType fieldIndex)
		{
			if(fieldIndex >= repetitionCount)
			{
				smf::CodingError e("CompiledField::operator[]", "field index (");
				e << fieldIndex << ") >= array size (" << repetitionCount << ")";
				throw e;
			}
			return elements[fieldIndex];
		}

		
		size_t size() const
		{
			return repetitionCount;
		}

	private: // Representation

		CompiledField elements[repetitionCount];
	};

	class GroupElement
	{
	protected: // Construction

		GroupElement()
		: searchOptimiser(smf::CompiledAccess::CreateSequentialSearchOptimiser()), position(0)
		{
		}

        GroupElement(
			const char* partitionName, 
			const char *groupName )
		: searchOptimiser(smf::CompiledAccess::CreateSequentialSearchOptimiser()),
			position(0)
		{
			smf::CompiledAccessPartition* partition = 
				smf::CompiledAccess::OpenPartition(partitionName);
			position = partition->FindGroup(groupName);
			if(position == 0 || position->IsNull())
			{
				smf::CodingError e("GroupElement ctor", 
					"Failed to lookup the position of ");
				e << groupName;
				throw e;
			}
		}

		GroupElement(
			const char* partitionName, 
			const char *groupName, smf::CompiledAccessPartition::IndexType index )
		: searchOptimiser(smf::CompiledAccess::CreateSequentialSearchOptimiser()),
			position(0)
		{
			smf::CompiledAccessPartition* partition = 
				smf::CompiledAccess::OpenPartition(partitionName);
			position = partition->FindGroup(groupName, index);
			if(position == 0 || position->IsNull())
			{
				smf::CodingError e("GroupElement ctor", 
					"Failed to lookup the position of ");
				e << groupName;
				throw e;
			}
		}

		virtual ~GroupElement()
		{
			if ( position )
			{
				const smf::CompiledAccessPartition* pCompiledAccessPartition = position->RetrievePartition( );
				if ( pCompiledAccessPartition )
				{
					pCompiledAccessPartition->DestroyDataPosition( position );
				}
				position = 0;
			}
			if (searchOptimiser)
			{
				smf::CompiledAccess::DestroySequentialSearchOptimiser(searchOptimiser);
				searchOptimiser = 0;
			}
		}

		GroupElement(const GroupElement &that)
		: searchOptimiser(smf::CompiledAccess::CreateSequentialSearchOptimiser()), position(0)
		{
            if (that.position)
                position = that.position->Clone();
		}

        GroupElement &operator=(const GroupElement &that)
		{
            if (position)
                position->Assign(that.position);
            else if (that.position)
                position = that.position->Clone();
			// don't copy the search optimiser ptr
			return *this;
		}

	protected: // Access

		smf::CompiledAccessPartition::DataPosition *StartPosition() const
		{
			if (position == 0)
				throw smf::CodingError("GroupElement", "Null position");
			return position;
		}

		smf::FieldSearchOptimiser *SearchOptimiser()
		{
			return searchOptimiser;
		}

	private: // Representation

		smf::CompiledAccessPartition::DataPosition *position;
		smf::FieldSearchOptimiser *searchOptimiser;
	};

	template<typename CompiledGroup, 
		smf::CompiledAccessPartition::LengthType repetitionCount>
	class GroupArray
	{
	private:
		static const void ReportSize()
		{
			long size = sizeof(GroupArray<CompiledGroup, repetitionCount>);
			smf::CompiledAccess::ChangeMemoryUsage(size);
		}

		const void ClearSize()
		{
			long size = sizeof(GroupArray<CompiledGroup, repetitionCount>);
			smf::CompiledAccess::ChangeMemoryUsage(-size);
		}
	public: // Construction

		GroupArray()
		{
			for (smf::CompiledAccessPartition::IndexType at = 0; 
				at < repetitionCount; ++at)
			{
				elements[at] = CompiledGroup(at);
			}

			ReportSize();
		}

		virtual ~GroupArray()
		{
			ClearSize();
		}

	public: // Access

		const CompiledGroup &operator[](size_t groupIndex) const
		{
			if(groupIndex >= repetitionCount)
			{
				smf::CodingError e("CompiledGroup::operator[]", "group index (");
				e << groupIndex << ") >= array size (" << repetitionCount << ")";
				throw e;
			}
			return elements[groupIndex];
		}

		size_t size() const
		{
			return repetitionCount;
		}

	private: // Representation

		CompiledGroup elements[repetitionCount];

	};
}
#endif
