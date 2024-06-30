#include <linux/module.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/delay.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mahesh Gaikwad");
MODULE_DESCRIPTION("Lcd Driver : 16X2 JHD162A driver");
/** Buffer for data  */
//static int buffer_pointer = 0;

/* Variables for device and device class */
static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

#define DRIVER_NAME "lcddriver"
#define DRIVER_CLASS "MyModuleClass"

//#define GPIO_OUTPUT_PIN 66 -> Used for LED in gpiodriver
//#define GPIO_INPUT_PIN 67

/* LCD char buffer */
static char lcd_buffer[17];

/* Pinout for LCD Display */
unsigned int gpios[] = {
	69, /* Enable Pin */
	61, /* Register Select Pin */
	68, /* Data Pin 0*/
	45, /* Data Pin 1*/
	44, /* Data Pin 2*/
	26, /* Data Pin 3*/
	47, /* Data Pin 4*/
	46, /* Data Pin 5*/
	27, /* Data Pin 6*/
	65, /* Data Pin 7*/
};

#define REGISTER_SELECT gpios[1]

/**
 * @brief generates a pulse on the enable signal
 */
void lcd_enable(void) {
	gpio_set_value(gpios[0], 1);
	msleep(5);
	gpio_set_value(gpios[0], 0);
}

/**
 * @brief set the 8 bit data bus
 * @param data: Data to set
 */
void lcd_send_byte(char data) {
	int i;
	for(i=0; i<8; i++)
		gpio_set_value(gpios[i+2], ((data) & (1<<i)) >> i);
	lcd_enable();
	msleep(5);
}

/**
 * @brief send a command to the LCD
 *
 * @param data: command to send
 */
void lcd_command(uint8_t data) {
 	gpio_set_value(REGISTER_SELECT, 0);	/* RS to Instruction */
	lcd_send_byte(data);
}


/**
 * @brief send a data to the LCD
 *
 * @param data: data to send
 */
void lcd_data(uint8_t data) {
 	gpio_set_value(REGISTER_SELECT, 1);	/* RS to data */
	lcd_send_byte(data);
}

/**
 * @brief Write data to buffer
 */
static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs) {
	int to_copy, not_copied, delta;
	int i;
	/* Get amount of data to copy */
	to_copy = min(count, sizeof(lcd_buffer));	
	/* Copy data to user */
	not_copied = copy_from_user(&lcd_buffer, user_buffer, to_copy);
	/* Calculate data */
	delta = to_copy - not_copied;
	/* Set the new data to the display */
	lcd_command(0x1);
	for(i=0;i<to_copy;i++)	{
		lcd_data(lcd_buffer[i]);
	}
	return delta;
}
/**
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("lcd-driver - open was called!\n");
	return 0;
}

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("lcd-driver - close was called!\n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.write = driver_write
};
#define MYMAJOR 50
/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init ModuleInit(void) {
	//int retval;
	int i;
	char *names[] = {"ENABLE_PIN", "REGISTER_SELECT", "DATA_PIN0", "DATA_PIN1", "DATA_PIN2", "DATA_PIN3", "DATA_PIN4", "DATA_PIN5", "DATA_PIN6", "DATA_PIN7"};
	printk("Registering LCD Driver-9\n");
	char test[] = "Hello LCD!";

	/* Allocate a device nr */

	if( alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0) {
		printk("Device Nr. could not be allocated!\n");
		return -1;
	}
	printk("lcd-driver - Device Nr. Major: %d, Minor: %d was registered!\n", my_device_nr >> 20, my_device_nr & 0xfffff);
	/* Create device class */
	if((my_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
	//if((my_class = class_create(DRIVER_CLASS)) == NULL) {
		printk("Device class can not created!\n");
		goto ClassError;
	}
	/* Create Device File */
	if(device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME) == NULL) {
		printk("Can not create device file!\n");
		goto FileError;
	}
	/* Initialize device file */
	cdev_init(&my_device, &fops);

	/* Regisering device to kernel */
	if(cdev_add(&my_device, my_device_nr, 1) == -1) {
                printk("Registering of device to kernel failed!\n");
	        goto AddError;
	}
	/* Initialize GPIOs */
	printk("lcd-driver - GPIO Init\n");
	for(i=0; i<10; i++) {
		if(gpio_request(gpios[i], names[i])) {
			printk("lcd-driver - Error Init GPIO %d\n", gpios[i]);
			goto GpioInitError;
		}
	}

	printk("lcd-driver - Set GPIOs to output\n");
	for(i=0; i<10; i++) {
		if(gpio_direction_output(gpios[i], 0)) {
			printk("lcd-driver - Error setting GPIO %d to output\n", i);
			goto GpioDirectionError;
		}
	}
	
	//blinkall();
	//return 0;
	/* Init the display */
	lcd_command(0x38);	/* Set the display for 8 bit data interface */
	msleep(5);
	lcd_command(0x0c);	/* Set the display for 8 bit data interface */
	msleep(1);
	lcd_command(0x0f);	/* Set the display for 8 bit data interface */
	msleep(1);
	lcd_command(0x01);	/* Set the display for 8 bit data interface */
	msleep(1000);	
	char text[] = "Hello World!";
	//for(i=0; i<sizeof(text)-1;i++)
	//	lcd_data(text[i]);
	lcd_data(0x41);
	lcd_data(0x42);
	lcd_data(0x43);
	lcd_data(0x31);
	lcd_data(0x32);
	lcd_data(0x33);		
	return 0;
GpioDirectionError:
	i=9;
GpioInitError:
	for(;i>=0; i--)
		gpio_free(gpios[i]);
AddError:
	device_destroy(my_class, my_device_nr);
FileError:
	class_destroy(my_class);
ClassError:
	unregister_chrdev_region(my_device_nr, 1);
	return -1;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
 
static void __exit ModuleExit(void) {
        int i;
        lcd_command(0x1); /* Clear the lcd */
	for(i=0; i<10; i++) {
		gpio_set_value(gpios[i],0);
		gpio_free(gpios[i]);
	}
	cdev_del(&my_device);
	device_destroy(my_class, my_device_nr);
	class_destroy(my_class);
	unregister_chrdev_region(my_device_nr, 1);
	printk("Goodbye, Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);

