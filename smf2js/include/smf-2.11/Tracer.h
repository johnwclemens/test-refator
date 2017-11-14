
#ifndef TRACER_H
#define TRACER_H

namespace smf{
	class Tracer{

	public:
		Tracer(){
			whereLastUsed = "";
		}
		void LastUsed(const char* where){
			whereLastUsed = where;
		}

		const char* LastUsed(){
			return whereLastUsed;
		}
		virtual ~Tracer(){}
	private:
		const char* whereLastUsed;
	};
}
#endif