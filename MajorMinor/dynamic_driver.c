#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>

dev_t dev = 0;

static int __init driver_init(void) {
	printk(KERN_INFO "Kernel Module is Inserted Successfully \n");
	
	if((alloc_chrdev_region(&dev,0,1,"Dynamic Driver"))<0) {
		printk(KERN_INFO "Unable to allocate MAJOR:MINOR number:\n");
		return -1;
	}	
	printk(KERN_INFO "MAJOR : MINOR number of your device is: %d : %d \n",MAJOR(dev),MINOR(dev));
	return 0;
}

void __exit driver_exit(void) {
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO "Removed Kernel Module Successfully \n");
}

module_init(driver_init);
module_exit(driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Swapnil Jain");
MODULE_DESCRIPTION("This is a initial driver");
MODULE_VERSION("0:0.7");
