
#ifndef COMPILEDACCESSENTRYPOINTS_H
#define COMPILEDACCESSENTRYPOINTS_H

namespace smf{

    class FieldSearchOptimiser;
    class LogServiceRequestHandler;
    class Logger;
    class CompiledAccessPartition;
    class TransactionalView;
    class TransactionalUpdate;
	class DataPositionFactory;
	class PartitionPathIterator;
	class CompiledAccessPartitionExt1;
	class DataPositionFactoryExt1;

	namespace CompiledAccess{

		const char* LibName();

		//! \brief Use this function before calling CreateDataPositionFactory to check the SMF server is ready.
		//! check the SMF server is running - this is intended for use by user interface applications
		//! that need to report their status to the user
		//! \param timeout		This is the time to wait before returning. 
		//! \return				True if the server is ready.
		//! \remark				Include: Error.h, CompiledAccessEntryPoint.h
		//! \note				This function is thread safe and will block (up to the given timeout) until the server becomes ready.		
		bool TestServerAvailable(unsigned int timeout);

		//! \cond
		//Attach to a partition to read and write parameters
		//the transaction begin timeout specifies how long to wait trying to start
		//a transaction when another transaction is underway.
		enum{ 
			DontSetBeginTransactionTimeout = -1 // don't set the timeout by default 
		};
		//CompiledAccessPartition* OpenPartition(const char* partitionName);
		CompiledAccessPartition* OpenPartition(const char* partitionName, 
			unsigned int transactionBeginTimeout = DontSetBeginTransactionTimeout);

		CompiledAccessPartitionExt1* OpenPartitionExt1(const char* partitionName, 
			unsigned int transactionBeginTimeout = DontSetBeginTransactionTimeout);

        FieldSearchOptimiser* CreateSequentialSearchOptimiser();
        FieldSearchOptimiser* CreateFieldArraySearchOptimiser();
        void DestroySequentialSearchOptimiser(FieldSearchOptimiser*);
        void DestroyFieldArraySearchOptimiser(FieldSearchOptimiser*);
	//! \endcond

	//! \brief Before using PSD Direct service you need to set up an external logger (which is used to log audit trails to the server log where appropriate) and an internal logger. 
	//! See Opening a Log Service Request Channel for how to create an external logger and Getting a Pointer to the Internal Logger for how to create an internal logger.
	//! \param internalLogger A local logger created using smf::InternalLogger() function.  
	//! \remark Include: Logger.h, Error.h, CompiledAccessEntryPoint.h
	//! \note	These functions are thread safe, but you should only need to call them once during startup.
        void SetInternalLogger(Logger* internalLogger);

	//! \brief When you create the external logger, you should connect it to the SMF server on the local machine.
	//! \param serverLogger A LogServiceRequestHandler used to log audit trails into the server log file.
	//! \remark Include: Logger.h, Error.h, CompiledAccessEntryPoint.h
	//! \note	This should *not* be called by multiple threads.
	//! \note	These functions are thread safe, but you should only need to call them once during startup.
	void SetExternalLogger(LogServiceRequestHandler* serverLogger);

	//! \cond
	void ChangeMemoryUsage(long size);
	//! \endcond
	
	TransactionalView* CreateTransactionalViewer();
	void DestroyTransactionalViewer(TransactionalView* t);

        TransactionalUpdate* CreateTransactionalUpdater( void );
        void DestroyTransactionalUpdater( TransactionalUpdate* t );

	//! \cond
	//!Use wildcard search expression to clear parameters
	void ClearElements(const char* partition, const char* start);
	//! \endcond

	//!Set the StartTransaction timeout for a partition
	void SetStartTransactionTimeout(unsigned int timeoutInMs, const char* partition);


		//! \brief	Use this function to create a DataPositionFactory
		//!			A DataPosition is a C++ object that understands how to read and write to SMF parameters. 
		//!			You can create DataPositions through a DataPositionFactory.
		//!A data position factory can create data position pointers given a
		//!full field name /<group name>/[group index]/<field name>/[field index]
		//!e.g.	/SomeGroup/55/SomeField 
		//!		/SomeOtherGroup/SomeOtherField/23
		//!the timeout (msec) is how long to wait for a partition to become free when we try 
		//!to write data, using a data position, to the partition
		//! \param logger A local logger created using smf::InternalLogger() function. See Opening a Logger. 
		//!	\param timeout This is the time to wait for a partition to become free when we try to write to a string parameter.
		//! Note, writing a single integer value, in a non-transactional way will not have to wait. 
		//! \return A DataPositionFactory pointer that can be used to create DataPositions.
		//! \remark Include: DataPositionFactory.h, Logger.h, Error.h, CompiledAccessEntryPoint.h
		//! \post	Cleanup: You must clear up the object by calling DestroyDataPositionFactory 
		//!			(see Destroying a Data Position Factory). Note that you should clearup any DataPositions created by this factory before you destroy the factory itself.
		//! \exception smf::Error
		//! \note This function is thread safe.
		//! If the SMF has not been started, this function will wait forever for it to start. 
		//! It is recommended to call TestServerAvailable first (see Checking the Server is Ready).
		DataPositionFactory* CreateDataPositionFactory(Logger* logger, unsigned int timeout);

		//! \brief	Use this function to create a DataPositionFactoryExt1 which support resizable array
		//!			A DataPosition is a C++ object that understands how to read and write to SMF parameters. 
		//!			You can create DataPositions through a DataPositionFactory.
		//!A data position factory can create data position pointers given a
		//!full field name /<group name>/[group index]/<field name>/[field index]
		//!e.g.	/SomeGroup/55/SomeField 
		//!		/SomeOtherGroup/SomeOtherField/23
		//!the timeout (msec) is how long to wait for a partition to become free when we try 
		//!to write data, using a data position, to the partition
		//! \param logger A local logger created using smf::InternalLogger() function. See Opening a Logger. 
		//!	\param timeout This is the time to wait for a partition to become free when we try to write to a string parameter.
		//! Note, writing a single integer value, in a non-transactional way will not have to wait. 
		//! \return A DataPositionFactoryExt1 pointer that can be used to create DataPositions.
		//! \remark Include: DataPositionFactory.h, DataPositionFactoryExt1.h, Logger.h, Error.h, CompiledAccessEntryPoint.h
		//! \post	Cleanup: You must clear up the object by calling DestroyDataPositionFactory 
		//!			(see Destroying a Data Position Factory). Note that you should clearup any DataPositions created by this factory before you destroy the factory itself.
		//! \exception smf::Error
		//! \note This function is thread safe.
		//! If the SMF has not been started, this function will wait forever for it to start. 
		//! It is recommended to call TestServerAvailable first (see Checking the Server is Ready).
		DataPositionFactoryExt1* CreateDataPositionFactoryExt1(Logger* logger, unsigned int timeout);

		void DestroyDataPositionFactory(smf::DataPositionFactory* factory);


		PartitionPathIterator* CreatePartitionIterator( const char* PartitionName , const char* StartingPath );
		void DestroyPartitionIterator( PartitionPathIterator* pPartitionPathIterator );
    }
}

#endif
