#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <utils/StrongPointer.h>
#include <utils/String16.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "IHanaService.h"

using namespace android;

int main(int argc, char **argv)
{

	int ret;

	sp<IServiceManager> sm = defaultServiceManager();
	sp<IBinder> p;
	p = sm->getService(String16("jung.service"));

	sp<IHanaService> hana;
	hana = interface_cast<IHanaService>(p);


	if( !strcmp(argv[1],"touch" ) )
	{
		printf("jeong touch\n");
		ret = hana->touch_check();
		if( ret == -1 )
		{
			exit(99);
		}
		else
		{
			exit(ret);
		}
	}
	else if( !strcmp(argv[1],"pattern" ) )
	{
		ret = hana->lock_check();
		if( ret == -1 )
		{
			exit(99);
		}
		else
		{
			exit(ret);
		}
	}

	return 99;
}
