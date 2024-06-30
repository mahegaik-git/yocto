#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    int dev = open("/dev/mydevice",O_RDONLY);
    if(dev == -1)
    {
        printf("Error opening file path \n");
	return -1;
    }
    else
        printf("Success opening file path \n");
    close(dev);
    return 0;
}
