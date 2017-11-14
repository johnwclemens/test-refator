#ifndef FILETRANSFERSERVERFILENODE
#define FILETRANSFERSERVERFILENODE

#include <string>

namespace smf {
	class FileTransferServerFileNode
	{
	public:
		FileTransferServerFileNode();
		FileTransferServerFileNode(const std::string& name, bool bIsDirectory);
		FileTransferServerFileNode(const char* name, bool bIsDirectory);

		FileTransferServerFileNode(const std::string& name, bool bIsDirectory, unsigned int fileSize);
		FileTransferServerFileNode(const char* name, bool bIsDirectory, unsigned int fileSize);


		bool isFile() const;
		bool isDirectory() const;

		const char* FileName() const;
		unsigned int FileNameSize() const;
		unsigned int FileSize() const;

		~FileTransferServerFileNode();

		// All copyable: let the compiler generate the copy constructor
	private:
		std::string m_fileName;
		bool m_isDirectory;
		unsigned int fileSize;
	};
}

#endif
