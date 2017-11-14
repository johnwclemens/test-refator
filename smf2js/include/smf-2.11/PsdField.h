#ifndef PSDFIELD_H
#define PSDFIELD_H

#pragma warning (disable : 4786)
#include <string>



// This is used when requesting values using the field name. 
// It contains just the field name
namespace smf{
	class PsdField
	{
	public:


		PsdField();

		PsdField(const std::string& name, unsigned int len) ;

		PsdField(const std::string& name);

		PsdField(const char* name);

		unsigned int FieldLength() const;

		const char* FieldName() const;

	private:
		std::string fieldname;
	};
}

#endif
