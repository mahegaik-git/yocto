#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
#if 0
    char buffer[255];
    int dev = open("/dev/gpio-driver",O_RDWR);
    if(dev == -1)
    {
        printf("Error opening file path \n");
	return -1;
    }
    else
        printf("Success opening file path \n");
    //memcpy(dev,"Hello");    
    write(dev, "0x31", 1); 
    read(dev, buffer,1);
    printf("Data Read %s\n",buffer);
    close(dev);
#endif    
    return 0;
}
