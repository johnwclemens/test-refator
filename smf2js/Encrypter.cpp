#pragma comment(lib, "crypt32")

#include <cassert>

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <wincrypt.h>

#include "Encrypter.h"

#define MAXIMUM_BUFFER_SIZE 1024
#define ENCRYPT_NULL_INDICATOR (BYTE)'N'
#define ENCRYPT_CHAR_INDICATOR (BYTE)'A'

#define ARRAY_LENGTH(array) (sizeof(array)/sizeof((array)[0]))

smf2js::Encrypter::Encrypter(void) 
{
	//_hProv = AcquireCryptoServiceContent();
	_hKey = GenerateCryptoKey();
}

smf2js::Encrypter::~Encrypter(void) { }

HCRYPTPROV smf2js::Encrypter::AcquireCryptoServiceContent()
{
	//---------------------------------------------------------------
    // Get a handle to the default PROV_RSA_FULL provider.
	HCRYPTPROV hProv = NULL;
	if(CryptAcquireContext(&hProv, 0, MS_DEF_PROV, PROV_RSA_FULL, 0)) 
    {
        //_tprintf(TEXT("CryptAcquireContext succeeded.\n"));
    }
    else
    {
        if (GetLastError() == NTE_BAD_KEYSET)
        {
            // No default container was found. Attempt to create it.
            if(CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET)) 
            {
                //_tprintf(TEXT("CryptAcquireContext succeeded.\n"));
            }
            else
            {
                MyHandleError(TEXT("Could not create the default ")
                    TEXT("key container.\n"));
            }
        }
        else
        {
            MyHandleError(TEXT("A general error running ")
                TEXT("CryptAcquireContext"));
        }
    }
	return hProv;
}

HCRYPTKEY smf2js::Encrypter::GenerateCryptoKey()
{
	HCRYPTPROV hProv = AcquireCryptoServiceContent();
	HCRYPTHASH hHash = NULL;
	HCRYPTKEY hKey = NULL;
	//-----------------------------------
	// Generate Crypto Key
	if (!CryptCreateHash(hProv, CALG_MD5, hKey, 0, &hHash))
	{
		MyHandleError(TEXT("CryptCreateHash failed")
			TEXT("CryptCreateHash"));
	}
	BYTE PASSWORD_TO_DERIVE_KEY[] = { 0xba, 0xe5, 0x80, 0x4b, 0x3f, 0x3f, 0x3f, 0x90, 0xf8, 0xee, 0x5d, 0x51, 0xff, 0x74, 0x3a, 0xf5, 0x41, 0x56, 0x57, 0x55, 0x68, 0xc5, 0x40, 0xbf, 0x64, 0x61, 0x30, 0x25, 0x4e, 0x21, 0x52, 0x50, 0xf1, 0x41, 0xf9, 0x57, 0xb1, 0x4a, 0x9d, 0x41, 0x57, 0x8b, 0xf0, 0x3f, 0x3f, 0x00 };
	//{'∫', 'Â','Ä','K','?','?','?','ê¯','Ó',']','Q','ˇ','t',
	//	':','ı','A','V','W','U','h','≈','@','ø','d','a','0','%','N','!','R','P','Ò','A','˘',
	//	'W','±','J','ùA','W','ã','','?','?'};

	int arrayLen = ARRAY_LENGTH(PASSWORD_TO_DERIVE_KEY);
	if (!CryptHashData(hHash, PASSWORD_TO_DERIVE_KEY, arrayLen, 0))
	{
		MyHandleError(TEXT("CryptHashData failed")
			TEXT("CryptHashData"));
	}
	if (!CryptDeriveKey(hProv, CALG_RC4, hHash, (DWORD)40 << 16, &hKey))
	{
		MyHandleError(TEXT("CryptDeriveKey failed")
			TEXT("CryptDeriveKey"));
	}
	//-----------------------------------
	return hKey;
}

BYTE* smf2js::Encrypter::Encrypt(std::string data)
{
	BYTE scramble[MAXIMUM_BUFFER_SIZE];
	DWORD length = data.length();
	memcpy(scramble, "\0", MAXIMUM_BUFFER_SIZE);
	memcpy(scramble, data.c_str(), length + 1);

	//HCRYPTKEY hKey = GenerateCryptoKey();

	if (!CryptEncrypt(_hKey, NULL, TRUE, 0, scramble, &length, MAXIMUM_BUFFER_SIZE))
	{
		MyHandleError(TEXT("CryptEncrypt failed")
			TEXT("CryptEncrypt"));
	}

	return PackEncryptedContent(scramble, length);
}

BYTE* smf2js::Encrypter::Decrypt(BYTE* scramble)
{
	//HCRYPTPROV hProv = AcquireCryptoServiceContent();
	//HCRYPTKEY hKey = GenerateCryptoKey();

	BYTE* result = UnpackEncryptedContent(scramble);
	int index = 0;
	for(; result[index] != '\0'; ++index) { }
	DWORD length = index;

	if (!CryptDecrypt(_hKey, NULL, true, 0, result, &length))
	{
		MyHandleError(TEXT("CryptDecrypt failed")
			TEXT("CryptDecrypt"));
	}

	return result;
}

BYTE* smf2js::Encrypter::PackEncryptedContent(BYTE* scramble, int length)
{
	BYTE* result = new BYTE[length * 2 + 2];
	memcpy(result, "\0", (length * 2 + 2));

	int sourceIndex = 0;
	int destinationIndex = 0;
	for (; sourceIndex < length; ++sourceIndex, destinationIndex += 2)
	{
		if (scramble[sourceIndex] == '\0')
		{
			// Assign N to indicate null
			result[destinationIndex] = ENCRYPT_NULL_INDICATOR;
			result[destinationIndex + 1] = ENCRYPT_NULL_INDICATOR;
		}
		else
		{
			// Assign N to indicate null
			result[destinationIndex] = ENCRYPT_CHAR_INDICATOR;
			result[destinationIndex + 1] = scramble[sourceIndex];
		}
	}

	return result;
}

BYTE* smf2js::Encrypter::UnpackEncryptedContent(BYTE* scramble)
{
	int index = 0;
	for(; scramble[index] != '\0'; ++index) { }
	BYTE* result = new BYTE[(index / 2)];
	memcpy(result, "\0", (index / 2));

	int len = index;
	int sourceIndex = 0;
	int destinationIndex = 0;
	
	for (; sourceIndex + 1 < len; sourceIndex += 2, ++destinationIndex)
	{
		if (scramble[sourceIndex] == ENCRYPT_NULL_INDICATOR)
			result[destinationIndex] = 0;
		else if(scramble[sourceIndex] == ENCRYPT_CHAR_INDICATOR)
			result[destinationIndex] = scramble[sourceIndex + 1];
	}

	return result;
}

//-------------------------------------------------------------------
// This example uses the function MyHandleError, a simple error
// handling function to print an error message and exit 
// the program. 
// For most applications, replace this function with one 
// that does more extensive error reporting.

void smf2js::Encrypter::MyHandleError(LPTSTR psz)
{
    _ftprintf(stderr, TEXT("An error occurred in the program. \n"));
    _ftprintf(stderr, TEXT("%s\n"), psz);
    _ftprintf(stderr, TEXT("Error number %x.\n"), GetLastError());
    _ftprintf(stderr, TEXT("Program terminating. \n"));
    exit(1);
} // End of MyHandleError.
