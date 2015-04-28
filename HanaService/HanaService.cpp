#include "HanaService.h"
#include <fcntl.h>
#include <unistd.h>

namespace android {

	void HanaService::hanaTouch(uint32_t x, uint32_t y){
		printf("HANATouch x : %d, y: %d\n", x, y);

		char sx[10];
		char sy[10];
	
		sprintf(sx, "%d", x);
		sprintf(sy, "%d", y);
		sx[strlen(sx)] = 0;
		sy[strlen(sy)] = 0;

		if(fork() == 0){
			execlp("input","input", "tap", sx, sy, (char*)0);
		}
	}

}; // namespace android
