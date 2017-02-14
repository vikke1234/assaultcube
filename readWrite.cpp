#include "readWrite.h"

DWORD readMem(HANDLE processHandle, LPCVOID address) {
	DWORD buffer = 0;
	SIZE_T numberOfBytesToRead = sizeof(buffer);
	SIZE_T numberOfBytesActuallyRead;

	BOOL error = ReadProcessMemory(processHandle, address, &buffer,
		numberOfBytesToRead, &numberOfBytesActuallyRead);

	if (!error || numberOfBytesActuallyRead != numberOfBytesToRead) {
		std::cout << "readMem GetLastError: " << GetLastError() << std::endl;
		std::cout << buffer << std::endl;
		std::cout << "error reading memory" << std::endl;
	}
	

#ifdef DEBUG
	std::cout << "buffer: 0x" << std::hex << buffer << std::endl;
#endif

	return buffer;
	//returns a hex
}

BOOL writeMem(HANDLE handle, LPVOID address, int writeData) {
	BOOL error = WriteProcessMemory(handle, address, &writeData,
		sizeof(writeData), 0);

	if (!error) {
		
		std::cout << "writeMem GetLastError: " << GetLastError() << std::endl;
		std::cout << "address: 0x" << std::hex << address << std::endl;
	}
	return error;
}