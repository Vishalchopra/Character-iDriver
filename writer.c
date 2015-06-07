#include<stdio.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char *argv[])
{
	int fd, count, len;
	char ch[] = "vish chopra1111111111111abc1111111111111111111111111";

	fd = open(argv[1], O_WRONLY);
	if(fd < 0)
	{
		perror("open");
	}
	len = strlen(ch);
	printf("len = %d\n", len);
	printf("Begin.......\n");
	count = write(fd, ch, len);
	printf("The writer open with the file descriptor: %d\n", fd);
	
	printf("The number of bytes wrote %d\n", count);
	
	
	printf("End\n");
	close(fd);
	return 0;	
}
