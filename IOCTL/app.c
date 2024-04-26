#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>

#define WR_VALUE _IOW('r','w',int32_t*)
#define RD_VALUE _IOR('r','r',int32_t*)

int main() {
	int fd;
	int32_t value,number;
	printf("\nOpening Driver.\n");
	fd = open("/dev/swapnil_device",O_RDWR);
	if(fd < 0) {
		printf("Cannot open device file\n");
		return -1;
	}
	printf("Enter value of to send\n");
	scanf("%d",&number);
	printf("Writing value to Driver\n");
	ioctl(fd,WR_VALUE,(int32_t*) &number);

	printf("Reading value from Driver\n");
	ioctl(fd,RD_VALUE,(int32_t*)&value);
	printf("Value is: %d\n",value);

	printf("Closing Driver !!\n");
	close(fd);
}
