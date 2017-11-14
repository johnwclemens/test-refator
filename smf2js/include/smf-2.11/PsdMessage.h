#ifndef PSDMESSAGE_H
#define PSDMESSAGE_H

namespace smf{
	struct BinaryHolder{
		const void* data;
		unsigned int dataSize;
	};

	
#ifdef _WIN32
	typedef __int64 Integer64Type;
#else
	typedef long long Integer64Type;
#endif

	typedef double DoubleType;


	class PsdMessage
	{
	public:
		enum
		{
			ValueTypeSize = 2,
			FailureReasonSize = sizeof(unsigned short)
		};

		enum ValueType
		{
			Null,
			String,
			Integer,
			Binary,
			Integer64,
			Double
		};
		
		enum DataTypeVersion
		{
			Version0, // Support Integer, String and Binary
			Version1,  // Support Integer64 and Double, extension of Version0

			LastSupportedVersion = Version1
		};

		enum MessageType
		{
			QueryPartitions,
			QuerySchema,
			QueryValuesByName,
			QueryValuesByHandle,
			UpdateValuesByName,
			UpdateValuesByHandle,
			QueryHandlesByName,
			ReportPartitions,
			ReportSchema,
			ReportValuesByName,
			ReportHandlesByName,
			ReportValuesByHandle,
			ReportSuccessfulUpdate,
			ReportFailedUpdateByName,
			ReportFailedUpdateByHandle,
			ReportGeneralFailure,

            QueryTableValues,			
            UpdateTableValues,			
            ReportTableValues,			
            ReportFailedTableQuery,
            ReportSuccessfulTableUpdate,
            ReportFailedTableUpdate,

			LastTableMessageType,

            QueryMetadata,
            ReportMetadata,
            ReportMetadataError,

			QueryTableValuesWithComp,
			UpdateTableValuesWithComp,
			ReportTableValuesWithComp,

			// 8 message type to support resizable array
			QueryArraySizesByName,			
			QueryArrayCapacitiesByName,			
			QueryBulkArraySizes,
			QueryBulkArrayCapacities,
			ReportArraySizesByName,			
			ReportArrayCapacitiesByName,			
			ReportBulkArraySizes,
			ReportBulkArrayCapacities,

			LastTableMessageTypeWithComp,

            // message type to support non-transactional query
			QueryValuesByNameNonTransactional,
			QueryValuesByHandleNonTransactional,
            QueryTableValuesNonTransactional,
			QueryTableValuesWithCompNonTransactional,

			// support parameter subscription
			Subscribe,
			Unsubscribe,
			SubscriptionSuccessful,
			SubscriptionFailed,
			UnsubscribeSuccessful,
			UnsubscribeFailed,
            ReportValuesByNameComp,

			//support dynamic load/unload partition
			DynamicReloadPartition,
			DynamicReloadPartitionSuccess,
			DynamicReloadPartitionFailed,
			
            LastMessageType,

			FirstMessageType = QueryPartitions, 
			FirstTableMessageType = QueryTableValues, 
			FirstTableMessageTypeWithComp = QueryTableValuesWithComp
		};

		enum
		{
			NumberOfMessageTypes = LastMessageType - FirstMessageType,
			NumberOfTableMessageTypes = LastTableMessageType - FirstTableMessageType,
			NumberOfTablemessageTypesWithComp = LastTableMessageTypeWithComp - FirstTableMessageTypeWithComp
		};

		virtual ~PsdMessage() {}

		enum FailureReason
		{
			Success,
			UnclassifiedFailure,
			InvalidFieldName,
			UnknownFieldName,
			FieldNotModifiable,
			ArrayIndexOutOfBounds,
			TypeMismatch,
			StringTooLong,
			TransactionInProgress,
			TransactionAcrossPartitions,
			PathNameNotWellFormed,
			PathIteratorError,
			NullHandle,
			InvalidHandle,//!< the handle is incorrect 
			UnknownHandle,
			HandlesNotSupportedForThisPartition,//!< check the config file ...
			CodingError, //!< smf has detected a problem with its own code
			FieldValueTooBig,
			InvalidUpdate,
			MissedMessage, //!< this is originated at the client side 
			UnknownGroupName,
			ServerOverloaded,
			TransactionSeqNumMismatched,
			SizeMismatch,
			TransactionTimeout,
			TransactionSizeExceededMaxSize,
			UnsupportedMessageType,
			UnknownMessage,
			TotalMessageSizeTooBig,
			TransactionalReadFailure,
			ZeroLengthString,
			ZeroLengthBinary,//<= obsolete; zero length binary is 
 			BinaryTooLong,
            MetadataNotSupported,
            MetadataFormatNotSupported,
            MetadataUnavailable,
			RegistryReadError,
			RegistryWriteError,
			RegistryAccessDenied,
			RegistryNotSupported,			
			TooManySubscriptions, // for parameter subscription
			SubscriberNotFound,	  // for parameter subscription
            EmptySubscriptionParameters,	// for parameter subscription

			//for dynamic load/unload partition
			PartitionNotFound,
			PartitionCheckFailed,          
			PartitionAttributeNotMatch,
			PsdInternalError,
			PsdCapacityLimitReached,
			PartitionAlreadyExist,
			PartitionNotLoaded,
			UnloadSMFPartitionNotAllowed,
			HandleMapOverflow,
			PartitionReplaceFailed,
			PartitionUnloadFail

		};

		


		unsigned int static PsdIdentifier(){
			return (*(unsigned int*)"PSD\0") & 0xFFFFFFFF;
		}
		static unsigned int Version(){
			return (*(unsigned int *)"0001") & 0xFFFFFFFF;
		}
		static unsigned int BulkPsdVersion(){
			return (*(unsigned int *)"0002") & 0xFFFFFFFF;
		}
		static unsigned int SecondaryTypeVersion(){
			return (*(unsigned int *)"0003") & 0xFFFFFFFF;
		}
		static unsigned int BulkCompTypeVersion(){
			return (*(unsigned int *)"0004") & 0xFFFFFFFF;
		}

		static unsigned int NonTransactionalQueryVersion(){
			return (*(unsigned int *)"0005") & 0xFFFFFFFF;
		}

		static unsigned int ParameterSubscriptionVersion(){
			return (*(unsigned int *)"0006") & 0xFFFFFFFF;
		}
	};

	class VariableType
	{
	public:
		explicit VariableType(Integer64Type v)
			: type(PsdMessage::Integer64), int64Value(v), doubleValue(0)
		{ }
		
		explicit VariableType(DoubleType v)
			: type(PsdMessage::Double), int64Value(0), doubleValue(v)
		{ }
		
		PsdMessage::ValueType Type()const { return type; }

		Integer64Type ValueAsInteger64()const { return int64Value; }
		DoubleType ValueAsDouble()const { return doubleValue; }
	
	private:
		PsdMessage::ValueType type;
		Integer64Type int64Value;
		DoubleType doubleValue;
	};
}

#endif
