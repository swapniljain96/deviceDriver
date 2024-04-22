#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/device.h>
#include<linux/err.h>

dev_t dev = 0;
static struct class *dev_class;

static int __init automatic_driver_init(void) {
	printk(KERN_INFO "Kernel Module is Inserted Successfully \n");
	
	if((alloc_chrdev_region(&dev,0,1,"Automatic Driver")) <0) {
		printk("Unable to allocate Major:Minor number");
		return -1;
	}
	printk(KERN_INFO "MAJOR : MINOR number of your device is: %d : %d \n",MAJOR(dev),MINOR(dev));

	/* Creating struct Class*/
	dev_class = class_create("swapnil_class");
	if(IS_ERR(dev_class)) {
		printk("Cannot create the struct class for driver");
		goto r_class;
	}
	
	/*Creating Device*/
	if(IS_ERR(device_create(dev_class,NULL,dev,NULL,"swapnil_device"))) {
		printk("Cannot create the Device");
		goto r_device;
	}
	return 0;

r_device:
	class_destroy(dev_class);
r_class:
	unregister_chrdev_region(dev,1);
	return -1;
}

static void __exit automatic_driver_exit(void) {
	device_destroy(dev_class,dev);
	class_destroy(dev_class);
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO "Removed Kernel Module Successfully \n");
}

module_init(automatic_driver_init);
module_exit(automatic_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Swapnil Jain");
MODULE_DESCRIPTION("This is a initial driver");
MODULE_VERSION("0:0.7");
