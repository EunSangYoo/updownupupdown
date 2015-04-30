#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <utils/StrongPointer.h>
#include <utils/String16.h>
#include <sys/stat.h>
#include <stdio.h>

#include "HanaService.h"

using namespace android;
void asDaemon()
{
	if (fork() > 0) {
		exit(0);
	}

	umask(0);
	chdir("/");
	// for(int i = 0; i < 64; i++) close(i);
	setsid();
}

int main()
{
	asDaemon();
	sp<IServiceManager> sm = defaultServiceManager();
	sm->addService( String16("jung.service"), new HanaService , false );

	ProcessState::self() -> startThreadPool();
	IPCThreadState::self() -> joinThreadPool();
	return 0;
}
