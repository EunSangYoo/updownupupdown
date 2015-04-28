#include "hana.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

JNIEXPORT void JNICALL Java_net_pocketmagic_android_mycursoroverlay_Input_hanaInput
(JNIEnv *env, jobject obj, jint x, jint y){
	char xbuff[10];
	char ybuff[10];
	pid_t pid = fork();

	sprintf(xbuff, "%d\0", x);
	sprintf(ybuff, "%d\0", y);

	if (pid == 0) {
		execl("/data/HanaClient", "/data/HanaClient", xbuff, ybuff, (char *)0);
	}

}

