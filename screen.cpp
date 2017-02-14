#include "readWrite.h"
void print(bool gState, bool aState) {
	system("cls");
	std::cout << "press <F1> to toggle on <F3> to toggle off godmode: " << (bool) gState << std::endl;
	std::cout << "press <F2> to toggle on <F4> unlimited ammo: " << (bool)aState << std::endl;
}