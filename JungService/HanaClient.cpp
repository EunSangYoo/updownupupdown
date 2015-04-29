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
#if 0

		ret = hana->lock_check();
		if( ret == -1 )
		{
			return ret;
		}
		else
		{
			exit(ret);
		}

		printf("%s\n",argv[1]);

#endif
	}
	else if( !strcmp(argv[1],"pattern" ) )
	{
		ret = hana->lock_check();
		if( ret == -1 )
		{
			return ret;
		}
		else
		{
			exit(ret);
		}
	}

}
