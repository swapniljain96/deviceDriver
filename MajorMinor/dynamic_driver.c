#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>

static int __init driver_init(void) {
	printk(KERN_INFO "This is our init driver\n");
	return 0;
}

void __exit driver_exit(void) {
	printk(KERN_INFO "This is our exit driver\n");
}


module_init(driver_init);
module_exit(driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Swapnil Jain");
MODULE_DESCRIPTION("This is a initial driver");
MODULE_VERSION("0:0.7");
