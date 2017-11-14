#pragma once

#include <iostream>

namespace smf2js
{
	class Encrypter
	{
	public:
		Encrypter(void);
		virtual ~Encrypter(void);

		BYTE* Encrypt(std::string data);
		BYTE* Decrypt(BYTE* scramble);

	private:
		//---------------------------------------------------------------
		// Declare and initialize variables.
		LPBYTE _pEncryptedData;

		const char* _szPassword;
		DWORD _dwPasswordLen;

		HCRYPTPROV AcquireCryptoServiceContent();
		HCRYPTKEY GenerateCryptoKey();

		HCRYPTPROV _hProv;
		HCRYPTKEY _hKey;

		BYTE* PackEncryptedContent(BYTE* scramble, int length);
		BYTE* UnpackEncryptedContent(BYTE* scramble);

		void MyHandleError(LPTSTR psz);
	};
}

