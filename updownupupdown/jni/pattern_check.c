#include "pattern_check.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <jni.h>

JNIEXPORT jint JNICALL Java_com_lge_updownupupdown_BootSvc_pattern_1check(JNIEnv *env, jobject obj)
{
	int ret;
	int status;

    pid_t pid;
	pid = fork();

	if( pid == 0 )
	{
	    ret = execl("/data/JungClient","/data/JungClient","pattern",(char*)0);
	}

	wait(&status);
	return status;
}
