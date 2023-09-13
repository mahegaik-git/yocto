/*
   I2C Sample codde for MCP23017 R/W
   Mahesh R Gaikwad
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "i2c-dev.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
	char *end;
	int res, i2cbus, address, size, file;
	int daddress;
	int key = -1;

	char filename[20];

	i2cbus   = 1;
	address  = 0x27;
	daddress = 19;   //register to write to LED
	size = I2C_SMBUS_BYTE;

	sprintf(filename, "/dev/i2c-%d", i2cbus);
	file = open(filename, O_RDWR);
	if (file<0) {
  	    if (errno == ENOENT) {
	        printf("Error: Could not open file /dev/i2c-1");
 	    } 
	    else {
	            printf("Error: Could not open file");
		    if (errno == EACCES)
		        printf("Run as root?\n");
	    }
	    exit(1);
	}

	if (ioctl(file, I2C_SLAVE, address) < 0) {
    	        printf("Error: Could not set address to 0x27");
		return -errno;
	}
	//res = i2c_smbus_write_byte(file, daddress);
	//res = i2c_smbus_write_byte_data(file,daddress,value);
	key = i2c_smbus_read_byte_data(file, daddress);
	printf("KEY-READ %x",key);
	//if (key < 0) {
	//	printf("Warning - write failed\n");
	//}
	exit(0);
}
