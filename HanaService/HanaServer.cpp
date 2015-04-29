#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <utils/StrongPointer.h>
#include <utils/String16.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define EVENT_BUF_NUM 64
#define MOVE_TRES 300

#define EVENT_TYPE 3
#define EVENT_CODE_X 53
#define EVENT_CODE_Y 54

#define event_count(read_bytes) (read_bytes / sizeof(struct input_event))

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

int numOfTouch(size_t read_bytes, struct input_event *event_buf)
{
	int num = 0;
	for (unsigned int i = 0; i < event_count(read_bytes); i++) {
		if (event_buf[i].type == EVENT_TYPE &&
				(event_buf[i].code == EVENT_CODE_X || event_buf[i].code == EVENT_CODE_Y)) {
			num++;
		}
	}
	return (num> 0 ? num / 2 : 0);
}

time_t timeDiff(struct timeval past_time, struct timeval cur_time)
{
	time_t usec;
	usec = cur_time.tv_sec - past_time.tv_sec;
	usec *= 1000000;
	usec += cur_time.tv_usec - past_time.tv_usec;

	return usec;
}

bool isExceedTime(struct timeval cur_time, struct timeval past_time)
{
	time_t usec = timeDiff(past_time, cur_time);
	if (usec > 1000000)
		return true;
	return false;
}

void trackingOneTouch(bool *check, size_t read_bytes, struct input_event* event_buf, int trackingCount)
{
	static int x = 0, y = 0;

	for (unsigned int i = 0; i < event_count(read_bytes); i++) {
		if (event_buf[i].type == EVENT_TYPE) {
			switch (event_buf[i].code) {
				case EVENT_CODE_X:
					x = event_buf[i].value;
					if (x > 2000 && y < 700) {
						printf("click top\n");
						check[0] = true;
					}
					break;
				case EVENT_CODE_Y:
					y = event_buf[i].value;
					if (x < 500 && y > 1700) {
						printf("click buttom\n");
						check[1] = true;
					}
					break;
			}
		}
	}

	if (check[0] && check[1]) {
		check[0] = check[1] = false;
		x = y = 0;
		if (fork() == 0) {
			printf("oneFinger Fork\n");
			execlp("sh", "sh", "/data/turnoff.sh", (char*)0);
		}
	}
}

void trackingTwoTouch(size_t read_bytes, struct input_event* event_buf, int trackingCount)
{
	static int x = 0, y = 0;
	static int savedX = 0, savedY = 0;
	static int forkCount = 0;
	int check[2] = {0,}; 

	for(unsigned int i = 0; i < event_count(read_bytes); i++) {
		if (event_buf[i].type == EVENT_TYPE) {
			switch(event_buf[i].code) {
				case EVENT_CODE_X:
					printf(" x : %d     ", event_buf[i].value);
					x = event_buf[i].value;
					check[0] = 1;
					break;
				case EVENT_CODE_Y:
					printf(" y : %d     ", event_buf[i].value);
					if( trackingCount == 0) {
						y = event_buf[i].value;
						savedY = y;
						if(fork()==0){
							printf("i'm child\n");
							forkCount = 0;
							execlp("input","input", "keyevent", "25", (char*)0);
						}
					}
					else{
						bool success = false;
						if( y < event_buf[i].value ){
							if (event_buf[i].value - savedY - MOVE_TRES > 0) {
								success = true;
								printf("move down    ");

								if(fork()==0){
									if (forkCount == 0)
										sleep(1);
									printf("i'm child\n");
									forkCount++;
									execlp("input","input", "keyevent", "25", (char*)0);
								}
							}
						}
						else {
							if (savedY - event_buf[i].value - MOVE_TRES > 0) {
								success = true;
								printf("move up ");	
								if(fork()==0){
									if (forkCount == 0)
										sleep(1);
									printf("i'm child\n");
									forkCount++;
									execlp("input","input", "keyevent", "24", (char*)0);
								}
							}
						}
						y = event_buf[i].value;
						if (success) {
							savedY = y;
						}
					}
					check[1] = 1;
					break;
			}
		}

		if(check[0] && check[1]) {
			printf("\n");
			break;
		}
	}
}

void touchRecognize()
{
	int event_fd;
	size_t read_bytes;
	struct input_event event_buf[64];
	int trackingCount = 0;
	bool firstTouch= false;
	int touchCount = 0;
	bool checkForOneTouch[2] = {false, false};
	struct timeval past_time;

	event_fd = open("/dev/input/event0", O_RDONLY);

	gettimeofday(&past_time, NULL);

	while(1){
		read_bytes = read(event_fd, event_buf, (sizeof(struct input_event) * 64));
		struct timeval cur_time;
		gettimeofday(&cur_time, NULL);

		if( isExceedTime(cur_time, past_time) ) {
			printf("Exeed!!\n");
			firstTouch = true;
			past_time = cur_time;
		}

		if ( firstTouch ){
			touchCount = numOfTouch(read_bytes, event_buf);

			trackingCount = 0;
			firstTouch = false;

			printf("touchCount : %d\n", touchCount);

			switch (touchCount) {
				case 1:
					checkForOneTouch[0] = checkForOneTouch[1] = false;
					break;
				case 2:
					break;
				case 3:
					{
						if(fork()==0){
							execlp("sh", "sh", "/data/screenshot.sh", (char*)0);
						}
						continue;
					}
				case 4:
					{
						if(fork()==0){
							execlp("input", "input", "keyevent", "26", (char*)0);
						}
						continue;
					}
					break;
				default: break;
			}
		}

		if( !firstTouch ) {
			switch (touchCount) {
				case 1:
					trackingOneTouch(checkForOneTouch, read_bytes, event_buf, trackingCount);
					break;
				case 2:
					trackingTwoTouch(read_bytes, event_buf, trackingCount);
					break;
			}
		}
		trackingCount++;
	}
	close(event_fd);
	exit(0);
}

int main()
{
	// asDaemon();
	sp<IServiceManager> sm = defaultServiceManager();
	sm->addService( String16("hana.service"), new HanaService , false );

	ProcessState::self() -> startThreadPool();
	touchRecognize();
	return 0;
}
