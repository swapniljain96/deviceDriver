#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>


int8_t writebuf[1024];
int8_t readbuf[1024];

int main() {
	int fd;
	int option;
	fd = open("/dev/swapnil_device",O_RDWR);
	if (fd < 0) {
		printf("Cannot open device file !!!\n");
		return 0;
	}

	while(1) {
	printf("\n\nPlease select option\n");	
	printf("1. Read\n2. Write\n3. Exit\n");
	scanf("%d",&option);
	switch(option) {
		case 1: printf("Data Reading...");
			 read(fd,readbuf,1024);
			 printf("Done !!\n");
			 printf("Data is: %s\n",readbuf);
			 break;
		case 2: printf("Enter the string to write into the driver: ");
			 scanf(" %[^\t\n]s",writebuf);
			 printf("Writing Data...");
			 write(fd,writebuf,strlen(writebuf+1));
			 printf("Done !!\n");
			 break;
		case 3: close(fd);
			 exit(1);
			 break;
		default: printf("Invalid option");
			 break;
	  }
	}
	close(fd);
}
