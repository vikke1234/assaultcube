#include "readWrite.h"
#include <stdlib.h>
//offsets:
//health = F8
//ammo = 150
//ground level = 5c
//name =225
//


//struct for different player stats
typedef struct playerData {
	int * base = (int *)0x00509b74;
	
	int health;
	int* healthAddr;

	int ammo, *ammoAddr = 0;

	bool godmode = false;
	bool unlimitedAmmo = false;
}playerData_t;

int main() {

	DWORD procID;
	HANDLE handle;
	DWORD healthOff =  0xf8;
	DWORD ammoOff = 0x150;
	playerData_t *data, dat;
	data = &dat;
	HWND hwnd;
	if (!(hwnd = FindWindowA(NULL, "AssaultCube"))) {
		std::cout << "error: cannot find window";
		exit(-1);
	}
	
	else {
		//opens the process
		GetWindowThreadProcessId(hwnd, &procID);
		handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
	}
	if (!procID) {
		std::cout << "error: cannot find the process id";
		exit(-1);
	}
	else {
		int val = HEALTH;
		DWORD player = readMem(handle, data->base);
		std::cout << std::hex << player + 0x150;
		// finds the players memory address
		data->healthAddr = reinterpret_cast<int*>(player + healthOff);
		data->ammoAddr = reinterpret_cast<int*> (player + ammoOff);
		//finds the health of the player
		
		print(data->godmode, data->unlimitedAmmo);
		while (true) {
			data->health = readMem(handle, (LPCVOID)data->healthAddr);
			data->ammo = readMem(handle, (LPCVOID)data->ammoAddr);
#ifdef DEBUG
			system("cls");
			std::cout << "base: 0x" << data->base << std::endl;
			std::cout << "player: 0x" << player << std::endl;
			std::cout << "healthAddr: 0x" << std::hex << data->healthAddr << std::endl;
			std::cout << "base: 0x" << data->base << std::endl;
			std::cout << "health: " << data->health << std::endl;

#endif
			if (GetAsyncKeyState(VK_F1)){
				data->godmode = true;
				print(data->godmode, data->unlimitedAmmo);
			}
			else if (GetAsyncKeyState(VK_F2)) {
				data->unlimitedAmmo = true;
				print(data->godmode, data->unlimitedAmmo);
			}
			else if (GetAsyncKeyState(VK_F3)) {
				data->godmode = false;
				print(data->godmode, data->unlimitedAmmo);
			}
			else if (GetAsyncKeyState(VK_F4)){
				data->unlimitedAmmo = false;
				print(data->godmode, data->unlimitedAmmo);
			}


			if (data->godmode) {
				if (!(writeMem(handle, (LPVOID)data->healthAddr, HEALTH)))
					std::cout << "error, could not write to address: ";
					std::cout << std::hex << data->healthAddr << std::endl;

			}
			if (data -> unlimitedAmmo)
				writeMem(handle, (LPVOID)data->ammoAddr, AMMO);
			


			Sleep(5);
		}
	}
	return 0;
}

