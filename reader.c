#include<stdio.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char *argv[])
{
	int fd, count, len, pos, whence;
	printf("Begin.......\n");
	char ch[1024];
	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		perror("open");
	}
	printf("Enter the whence:\n");
	scanf("%d", &whence);
	printf("Enter the position\n");
	scanf("%d", &pos);
	lseek(fd, pos, whence);
	count = read(fd, ch, 1024);
	printf("The read open with the file descriptor: %d\n", fd);
	
	printf("The number of bytes read %d   %d\n", count, strlen(ch));
	printf("Data read is : %s\n", ch);
	
	printf("Enter the whence:\n");
	scanf("%d", &whence);
	printf("Enter the position\n");
	scanf("%d", &pos);
	lseek(fd, pos, whence);
	count = read(fd, ch, 1024);
	printf("The number of bytes read %d   %d\n", count, strlen(ch));
	printf("Data read is : %s\n", ch);
	printf("End\n");
	close(fd);
	return 0;	
}
