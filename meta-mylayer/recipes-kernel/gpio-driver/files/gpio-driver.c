#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mahesh Gaikwad");
MODULE_DESCRIPTION("A simple gpio driver for setting a LED and reasing a button");
/** Buffer for data  */
static int buffer_pointer = 0;

/* Variables for device and device class */
static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

#define DRIVER_NAME "gpiodriver"
#define DRIVER_CLASS "MyModuleClass"
#define GPIO_OUTPUT_PIN 66 
#define GPIO_INPUT_PIN 67

/**
 * @brief Read data out of the buffer
 */
static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) {
	int to_copy, not_copied, delta;
	char tmp[3] = " \n";
	/* Get amount of data to copy */
	to_copy = min(count, sizeof(tmp));
	/* Read value of button */
	printk("Value of button: %d\n", gpio_get_value(GPIO_INPUT_PIN));
	tmp[0] = gpio_get_value(GPIO_INPUT_PIN) + '0';
	/* Copy data to user */
	not_copied = copy_to_user(user_buffer, &tmp, to_copy);
	/* Calculate data */
	delta = to_copy - not_copied;
	return delta;
}
/**
 * @brief Write data to buffer
 */
static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs) {
	int to_copy, not_copied, delta;
	char value, drive;	
	/* Get amount of data to copy */
	to_copy = min(count, sizeof(value));	
	/* Copy data to user */
	not_copied = copy_from_user(&value, user_buffer, to_copy);
	printk("Value : %d XValue : %x\n", value, value);
	drive = value - '0';
	printk("Drive : %d \n", drive);
        /* setting value of LED */	
	switch(drive) {
		case 0:
			gpio_set_value(GPIO_OUTPUT_PIN,0);
			break;
		case 1:
			gpio_set_value(GPIO_OUTPUT_PIN,1);
			break;
		default:
			printk("Drive : Invalid Input!");
			break;
	}
	/* Calculate data */
	delta = to_copy - not_copied;
	return delta;
}
/**
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("dev_nr - open was called!\n");
	return 0;
}

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("dev_nr - close was called!\n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.read = driver_read,
	.write = driver_write
};
#define MYMAJOR 50
/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init ModuleInit(void) {
	//int retval;
	printk("Registering Device\n");

	/* Allocate a device nr */

	if( alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0) {
		printk("Device Nr. could not be allocated!\n");
		return -1;
	}
	printk("gpiodriver - Device Nr. Major: %d, Minor: %d was registered!\n", my_device_nr >> 20, my_device_nr & 0xfffff);
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
	/* GPIO OUTPUT INIT */
	if(gpio_request(GPIO_OUTPUT_PIN, "BBB-GPIO-OUTPUT")) {
	        printk("Cannot allocate GPIO-%d for OUTPUT\n", GPIO_OUTPUT_PIN);
	        goto AddError;
	}
	/* set GPIO direction */
	if(gpio_direction_output(GPIO_OUTPUT_PIN, 0)) {
	        printk("Cannot set GPIO %d as output!\n", GPIO_OUTPUT_PIN);
	        goto GpioOutputError;
	}
	/* GPIO INPUT INIT */
	if(gpio_request(GPIO_INPUT_PIN, "BBB-GPIO-INPUT")) {
	        printk("Cannot allocate GPIO-%d for INPUT\n", GPIO_INPUT_PIN);
	        goto GpioOutputError;
	}
	/* set GPIO direction */
	if(gpio_direction_input(GPIO_INPUT_PIN)) {
	        printk("Cannot set GPIO %d as input!\n", GPIO_OUTPUT_PIN);
	        goto GpioInputError;
	}
	return 0;
GpioInputError:
	gpio_free(GPIO_INPUT_PIN);
GpioOutputError:
	gpio_free(GPIO_OUTPUT_PIN);
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
        gpio_set_value(GPIO_OUTPUT_PIN,0);
	gpio_free(GPIO_OUTPUT_PIN);
	gpio_free(GPIO_INPUT_PIN);
	cdev_del(&my_device);
	device_destroy(my_class, my_device_nr);
	class_destroy(my_class);
	unregister_chrdev_region(my_device_nr, 1);
	printk("Goodbye, Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);

