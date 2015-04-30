#include "HanaTouch.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <jni.h>

JNIEXPORT jint JNICALL Java_net_pocketmagic_android_mycursoroverlay_SensorService_touch_1check
(JNIEnv *env, jobject obj){
	int ret;
	int status;

	pid_t pid;
	pid = fork();

	if( pid == 0 )
	{
		ret = execl("/data/JungClient","/data/JungClient","touch",(char*)0);
	}

	wait(&status);
	return status;


}


