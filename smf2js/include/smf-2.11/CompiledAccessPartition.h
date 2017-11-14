#ifndef COMPILEDACCESSPARTITION_H
#define COMPILEDACCESSPARTITION_H

#include "PartitionTypes.h"
#include "Reference.h"
#include "Error.h"

namespace smf {

	class FieldSearchOptimiser;

    class CompiledAccessPartition
    {
    public: // exceptions

        class ParameterNotFound; // exception base

        class PathNameNotWellFormed;
        class GroupNameNotFound;
        class FieldNameNotFound;
        class GroupArrayIndexOutOfBounds;
        class FieldArrayIndexOutOfBounds;
		class PartitionInvalidated;

    public:

        class DataPosition;

        typedef PartitionTypes::CharType CharType;
        typedef PartitionTypes::IndexType IndexType;
        typedef PartitionTypes::IntegerType IntegerType;
        typedef PartitionTypes::LengthType LengthType;
        typedef PartitionTypes::LongLengthType LongLengthType;
        typedef PartitionTypes::LongIndexType LongIndexType;
        typedef __int64 Integer64Type;
		typedef smf::BinaryType BinaryType;
		typedef double DoubleType;

        virtual DataPosition *FindGroup(const CharType* name, IndexType indxArray) const = 0;           //! for compiled interface
        virtual DataPosition *FindField(const CharType* name, IndexType indxArray, DataPosition* group,
										    FieldSearchOptimiser* fieldSearchOptimiser) const = 0;      //! for compiled interface

        virtual DataPosition *FindGroup(const CharType* name) const = 0;                                //! for compiled interface
        virtual DataPosition *FindField(const CharType* name, DataPosition* group,
                                            FieldSearchOptimiser* fieldSearchOptimiser) const = 0;      //! for compiled interface


		//virtual DataPosition *Find(const char* fullname) const = 0;

		virtual void DestroyDataPosition( DataPosition* dataPosition ) const = 0;

        virtual smf::Counter::Reference* Reference() const = 0;
        virtual void TestIsValid() const = 0;
		virtual const std::string &Name() const = 0;
		

    protected:

	    virtual ~CompiledAccessPartition() {}
	    CompiledAccessPartition() {}

    private:

	    CompiledAccessPartition(const CompiledAccessPartition&);
	    CompiledAccessPartition &operator=(const CompiledAccessPartition &);

    };

	//! Use this to access parameters in the partitions directly
    class CompiledAccessPartition::DataPosition
    {
    public:
        class StringSizeLimitExceeded;
		class BinarySizeLimitExceeded;
		class DataPositionInvalidated;

		//! \brief These functions can be used to check whether a DataPosition is valid and what data type it references 
		//! (string, binary, 32 bit integer, 64 bit integer or double).
		//! \return If IsNull() returns true this is not a valid DataPosition.
		//! \remark Include: CompiledAccessPartition.h
		//! \note These functions are thread safe.
	    virtual bool IsNull() const = 0;
		//! \brief These functions can be used to check whether a DataPosition is valid and what data type it references 
		//! (string, binary, 32 bit integer, 64 bit integer or double).
		//! \remark Include: CompiledAccessPartition.h
		//! \note These functions are thread safe.
	    virtual bool IsInteger() const = 0;
		//! \brief These functions can be used to check whether a DataPosition is valid and what data type it references 
		//! (string, binary, 32 bit integer, 64 bit integer or double).
		//! \remark Include: CompiledAccessPartition.h
		//! \note Notes: 64 bit integer can be treated as binary or int64.  
		//! IsBinary() and IsInteger64() will both return true for 64 bit integer type DataPosition.  
		//! Therefore you will need to check IsInteger64() first if you want to treat it as int64.
		//! These functions are thread safe.
	    virtual bool IsBinary() const = 0;
		//! \brief These functions can be used to check whether a DataPosition is valid and what data type it references 
		//! (string, binary, 32 bit integer, 64 bit integer or double).
		//! \remark Include: CompiledAccessPartition.h
		//! \note Notes: 64 bit integer can be treated as binary or int64.  
		//! IsBinary() and IsInteger64() will both return true for 64 bit integer type DataPosition.  
		//! Therefore you will need to check IsInteger64() first if you want to treat it as int64.
		//! These functions are thread safe.
	    virtual bool IsInteger64() const = 0;
		//! \brief These functions can be used to check whether a DataPosition is valid and what data type it references 
		//! (string, binary, 32 bit integer, 64 bit integer or double).
		//! \remark Include: CompiledAccessPartition.h
		//! \note Notes: 64 bit integer can be treated as binary or double.  
		//! IsBinary() and IsDouble() will both return true for 64 bit integer type DataPosition.  
		//! Therefore you will need to check IsDouble() first if you want to treat it as double.
		//! These functions are thread safe.
	    virtual bool IsDouble() const = 0;

        virtual LengthType GetStringLimit() const = 0;
        virtual LongLengthType GetBinaryLimit() const = 0;

		//! \brief Use these functions to retrieve a value from a DataPosition.
		//! \param[out] value	The 64 bit integer value of the parameter in the partition.
		//! \return True if successful. 
		//! \exception smf::Error
		//! \remark Include: CompiledAccessPartition.h
		//! \note	These functions are thread safe. 
		//!			You have to use the corresponding function to access the parameter of the same type.  
		//!			For example, an smf::Error will be thrown if you try to access an integer parameter as a string.
		virtual bool QueryValue( smf::CompiledAccessPartition::Integer64Type& value ) const = 0;
		//! \brief Use these functions to retrieve a value from a DataPosition.
		//! \param[out] value	The double value of the parameter in the partition.
		//! \return True if successful. 
		//! \exception smf::Error
		//! \remark Include: CompiledAccessPartition.h
		//! \note	These functions are thread safe. 
		//!			You have to use the corresponding function to access the parameter of the same type.  
		//!			For example, an smf::Error will be thrown if you try to access an integer parameter as a string.
		virtual bool QueryValue( smf::CompiledAccessPartition::DoubleType& value ) const = 0;
		//! \brief Use these functions to retrieve a value from a DataPosition.
		//! \param[out]	out		The integer value of the parameter in the partition.
		//! \return True if successful. 
		//! \exception smf::Error
		//! \remark Include: CompiledAccessPartition.h
		//! \note	These functions are thread safe. 
		//!			You have to use the corresponding function to access the parameter of the same type.  
		//!			For example, an smf::Error will be thrown if you try to access an integer parameter as a string.
	    virtual bool QueryValue(CompiledAccessPartition::IntegerType& out) const = 0;
		//! \brief Use these functions to retrieve a value from a DataPosition.
		//! \param[out]	out		The binary value of the parameter in the partition.
		//!						Use GetBinaryLimit() to check the binary maximum size.
		//! \return True if successful. 
		//! \exception smf::Error
		//! \remark Include: CompiledAccessPartition.h
		//! \note	These functions are thread safe. 
		//!			You have to use the corresponding function to access the parameter of the same type.  
		//!			For example, an smf::Error will be thrown if you try to access an integer parameter as a string.
	    virtual bool QueryValue(CompiledAccessPartition::BinaryType& out) const = 0;
		//! \brief Use these functions to retrieve a value from a DataPosition.
		//! \param	strCopy			A buffer that will contain the string value on return. 
		//!							The buffer should be big enough to hold the entire string.
		//!							Use GetStringLimit() to check the string maximum size. 
		//! \param	sizeCopy		The size of the strCopy buffer.
		//! \param	sizeofData		The size of the string held in SMF.
		//!							If this is greater than the size of the strCopy buffer, 
		//!							you should retrieve the value again with a bigger buffer.
		//! \return True if successful. 
		//! \exception smf::Error
		//! \remark Include: CompiledAccessPartition.h
		//! \note	These functions are thread safe. 
		//!			You have to use the corresponding function to access the parameter of the same type.  
		//!			For example, an smf::Error will be thrown if you try to access an integer parameter as a string.
	    virtual bool QueryValue(CompiledAccessPartition::CharType* strCopy, 
		    CompiledAccessPartition::LengthType sizeCopy, 
            CompiledAccessPartition::LengthType& sizeofData) const = 0;

		//! \brief These functions can be used to write a value to the partition.
		//! \param value	The new double value to write in the partition.
		//! \return True if successful.
		//! \exception smf::Error
		//! \remark Include: CompiledAccessPartition.h
		//! \note Writing an integer value is thread safe and will not block.
		//! Writing a string value is thread safe but will block if another thread is also writing to the same partition.
		//! You have to use the corresponding function to access the parameter of the same type.  
		//! For example, an smf::Error will be thrown if you try to access an integer parameter as a string.
	    virtual bool PutValue(CompiledAccessPartition::DoubleType value) const = 0;
		//! \brief These functions can be used to write a value to the partition.
		//! \param value	The new 64 bit integer value to write in the partition.
		//! \return True if successful.
		//! \exception smf::Error
		//! \remark Include: CompiledAccessPartition.h
		//! \note Writing an integer value is thread safe and will not block.
		//! Writing a string value is thread safe but will block if another thread is also writing to the same partition.
		//! You have to use the corresponding function to access the parameter of the same type.  
		//! For example, an smf::Error will be thrown if you try to access an integer parameter as a string.
	    virtual bool PutValue(CompiledAccessPartition::Integer64Type value) const = 0;
		//! \brief These functions can be used to write a value to the partition.
		//! \param value	The new integer value to write in the partition.
		//! \return True if successful.
		//! \exception smf::Error
		//! \remark Include: CompiledAccessPartition.h
		//! \note Writing an integer value is thread safe and will not block.
		//! Writing a string value is thread safe but will block if another thread is also writing to the same partition.
		//! You have to use the corresponding function to access the parameter of the same type.  
		//! For example, an smf::Error will be thrown if you try to access an integer parameter as a string.
	    virtual bool PutValue(CompiledAccessPartition::IntegerType value) const = 0;
		//! \brief These functions can be used to write a value to the partition.
		//! \param value	The new binary value to write in the partition.
		//! \return True if successful.
		//! \exception smf::Error
		//! \remark Include: CompiledAccessPartition.h
		//! \note Writing an integer value is thread safe and will not block.
		//! Writing a string value is thread safe but will block if another thread is also writing to the same partition.
		//! You have to use the corresponding function to access the parameter of the same type.  
		//! For example, an smf::Error will be thrown if you try to access an integer parameter as a string.
	    virtual bool PutValue(const CompiledAccessPartition::BinaryType& value) const = 0;
		//! \brief These functions can be used to write a value to the partition.
		//! \param value	The new string value to write in the partition.
		//! \return True if successful.
		//! \exception smf::Error
		//! \remark Include: CompiledAccessPartition.h
		//! \note Writing an integer value is thread safe and will not block.
		//! Writing a string value is thread safe but will block if another thread is also writing to the same partition.
		//! You have to use the corresponding function to access the parameter of the same type.  
		//! For example, an smf::Error will be thrown if you try to access an integer parameter as a string.
	    virtual bool PutValue(const CompiledAccessPartition::CharType* value) const = 0;

	    virtual const CompiledAccessPartition* RetrievePartition()const = 0;

		//! \brief These functions can be used on a 32 bit integer type DataPosition to increment/decrement its value in a thread safe manner.
		//! \return The resulting incremented/decremented value.
		//! \remark	Include: CompiledAccessPartition.h
		//! \exception smf::Error 	An smf::Error will be thrown if you try to do this on DataPosition other than the 32 bit integer type.
	    virtual IntegerType IncValueLocked() const = 0;
		//! \brief These functions can be used on a 32 bit integer type DataPosition to increment/decrement its value in a thread safe manner.
		//! \return The resulting incremented/decremented value.
		//! \remark	Include: CompiledAccessPartition.h
		//! \exception smf::Error 	An smf::Error will be thrown if you try to do this on DataPosition other than the 32 bit integer type.
	    virtual IntegerType DecValueLocked() const = 0;
	    virtual IntegerType IncValue() const = 0;
	    virtual IntegerType DecValue() const = 0;

		virtual bool IsEqual(const CompiledAccessPartition::CharType* str) const = 0;
		virtual bool IsEqual(CompiledAccessPartition::IntegerType i) const = 0;
		virtual bool IsEqual(CompiledAccessPartition::Integer64Type i) const = 0;
		virtual bool IsEqual(const CompiledAccessPartition::BinaryType& value) const = 0;
		virtual bool IsEqual(const CompiledAccessPartition::DoubleType value) const = 0;

        virtual CompiledAccessPartition::DataPosition *Clone() const = 0;
        virtual void Assign(CompiledAccessPartition::DataPosition*) = 0;

    protected:
	    DataPosition() {}
	    virtual ~DataPosition() {}
    private:
	    DataPosition(const DataPosition &);
	    DataPosition &operator=(const DataPosition &);
    };

    class CompiledAccessPartition::ParameterNotFound
        : public smf::Error
    {
        public:
            ParameterNotFound( const char* error )
                : smf::Error( "Could not find the parameter: " )
            {
                ( *this ) << error;
            }
            virtual ~ParameterNotFound( void )
            { }
    };

    class CompiledAccessPartition::PathNameNotWellFormed
        : public CompiledAccessPartition::ParameterNotFound
    {
        public:
            PathNameNotWellFormed( const char* error )
                : CompiledAccessPartition::ParameterNotFound( "Path name not well formed: " )
            {
                ( *this ) << error;
            }
            virtual ~PathNameNotWellFormed( void )
            { }
    };

    class CompiledAccessPartition::GroupNameNotFound
        : public CompiledAccessPartition::ParameterNotFound
    {
        public:
            GroupNameNotFound( const char* error )
                : CompiledAccessPartition::ParameterNotFound( "Group name not found: " )
            {
                ( *this ) << error;
            }
            virtual ~GroupNameNotFound( void )
            { }
    };

    class CompiledAccessPartition::FieldNameNotFound
        : public CompiledAccessPartition::ParameterNotFound
    {
        public:
            FieldNameNotFound( const char* error )
                : CompiledAccessPartition::ParameterNotFound( "Field name not found: " )
            {
                ( *this ) << error;
            }
            virtual ~FieldNameNotFound( void )
            { }
    };

    class CompiledAccessPartition::GroupArrayIndexOutOfBounds
        : public CompiledAccessPartition::ParameterNotFound
    {
        public:
            GroupArrayIndexOutOfBounds( const char* error )
                : CompiledAccessPartition::ParameterNotFound( error )
            { }
            virtual ~GroupArrayIndexOutOfBounds( void )
            { }
    };

    class CompiledAccessPartition::FieldArrayIndexOutOfBounds
        : public CompiledAccessPartition::ParameterNotFound
    {
        public:
            FieldArrayIndexOutOfBounds( const char* error )
                : CompiledAccessPartition::ParameterNotFound( error )
            { }
            virtual ~FieldArrayIndexOutOfBounds( void )
            { }
    };

	class CompiledAccessPartition::PartitionInvalidated
		: public smf::Error
	{
		public:
			PartitionInvalidated( const char* partition)
				: smf::Error("Partition has been unloaded: ")
			{
				( *this ) << partition;
			}
			virtual ~PartitionInvalidated( void )
			{ }
	};

    class CompiledAccessPartition::DataPosition::StringSizeLimitExceeded
        : public smf::Error
    {
        public:
            StringSizeLimitExceeded( void )
                : smf::Error( "String length exceeded limit." )
            { }
            virtual ~StringSizeLimitExceeded( void )
            { }
    };

	class CompiledAccessPartition::DataPosition::BinarySizeLimitExceeded
        : public smf::Error
    {
        public:
            BinarySizeLimitExceeded( void )
                : smf::Error( "Binary length exceeded limit." )
            { }
            virtual ~BinarySizeLimitExceeded( void )
            { }
    };

	class CompiledAccessPartition::DataPosition::DataPositionInvalidated
        : public smf::Error
    {
        public:
            DataPositionInvalidated( void )
                : smf::Error( "DataPosition has been invalidated." )
            { }
            virtual ~DataPositionInvalidated( void )
            { }
    };

}

#endif
