
#ifndef SMFRECORDER_H
#define SMFRECORDER_H

#include "StampedLogEntry.h"
#include "OutputStream.h"
#include <vector>

namespace smf{

	class Recorder
	{
	public: // construction and destruction

		Recorder()
			: recorder(0)
		{
		}

		Recorder(const Recorder &other)
			: recorder(other.recorder ? other.recorder->Clone() : 0)
		{
		}

		template<typename TargetType>
		Recorder(TargetType *target, 
				void (TargetType::*memberFunction)(smf::OutputStream& out, const StampedLogEntry& entry))
			: recorder(new BoundFunction<TargetType>(target, memberFunction))
		{
		}

		~Recorder()
		{
			delete recorder;
		}

	public: // assignment

		Recorder &operator=(const Recorder &rhs)
		{
			Recorder copy(rhs);
			std::swap(recorder, copy.recorder);
			return *this;
		}

	public: // query

		operator bool() const
		{
			return recorder != 0;
		}

	public: // execution

		void operator()(smf::OutputStream& out, const StampedLogEntry& entry) const
		{
			if(recorder)
				recorder->Execute(out, entry);
		}

	private: // types

		class Executable
		{
		public: // construction and destruction

			virtual Executable *Clone() const = 0;

			virtual ~Executable()
			{
			}

		public: // execution

			virtual void Execute(smf::OutputStream& out, const StampedLogEntry& entry) = 0;

		};


		template<typename TargetType>
		class BoundFunction : public Executable
		{
		public: // construction

			BoundFunction(TargetType *target, 
				void (TargetType::*memberFunction)(smf::OutputStream& out, const StampedLogEntry& entry))
				: target(target), memberFunction(memberFunction)
			{
			}

			virtual Executable *Clone() const
			{
				return new BoundFunction(*this);
			}

		public: // execution

			virtual void Execute(smf::OutputStream& out, const StampedLogEntry& entry)
			{
				(target->*memberFunction)(out, entry);
			}

		private: // representation

			TargetType *target;
			void (TargetType::*memberFunction)(smf::OutputStream& out, const StampedLogEntry& entry);

		};

	private: // representation

		Executable *recorder;

	};

	typedef std::vector<Recorder> Recorders;
}

#endif