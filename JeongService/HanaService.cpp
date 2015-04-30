#include "HanaService.h"
#include <fcntl.h>
#include <unistd.h>

namespace android {

	int HanaService::lock_check(){

		int ret;
		int fd;
		int buff;

		fd = open("/dev/updown_device", O_RDONLY);

		if( fd < 0 )
		{
	        return -1;	
		}
		else
		{
            ret = read( fd, &buff, sizeof(buff));
		    close(fd);
		    return buff;

		}
	}

	int HanaService::touch_check(){

		int ret;
		int fd;
		int buff;

		fd = open("/dev/touch_device", O_RDONLY);

		if( fd < 0 )
		{
	        return -1;	
		}
		else
		{
            ret = read( fd, &buff, sizeof(buff));
		    close(fd);
		    return buff;
		}
	}

}; // namespace android
