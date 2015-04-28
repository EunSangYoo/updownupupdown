#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <utils/StrongPointer.h>
#include <utils/String16.h>
#include <stdio.h>

#include "IHanaService.h"

using namespace android;

int main(int argc, char **argv)
{
	sp<IServiceManager> sm = defaultServiceManager();
	sp<IBinder> p;
	p = sm->getService(String16("hana.service"));

	sp<IHanaService> hana;
	hana = interface_cast<IHanaService>(p);

	if(strcmp(argv[1], "print") == 0){
		// temp = hana->getBrightness();
		// printf("current Brightness : %d\n", temp);
	}else{
		int x, y;
		sscanf(argv[1], "%d", &x);
		sscanf(argv[2], "%d", &y);
		hana->hanaTouch(x, y);
	}

	return 0;
}
