#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>
#include<linux/slab.h>      //for kmalloc()
#include<linux/device.h>
#include<linux/uaccess.h>   //for copy_to/from_user
#include<linux/ioctl.h>
#include<linux/err.h>
 
#define WR_VALUE _IOW('r','w',int32_t*)
#define RD_VALUE _IOR('r','r',int32_t*)

int32_t value = 0;

dev_t dev = 0;
static struct class *dev_class;
static struct cdev swapnil_cdev;

/*these is init and exit functions*/
static int __init init_driver(void);
static void __exit exit_driver(void);

/*this is files operations functions*/
static int dev_open(struct inode *inode,struct file *file);
static int dev_release(struct inode *inode,struct file *file);
static ssize_t dev_read(struct file *filp,char __user *buf,size_t len,loff_t *off);
static ssize_t dev_write(struct file *filp,const char *buf,size_t len,loff_t *off);
static long dev_ioctl(struct file *file,unsigned int cmd,unsigned long agr);

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = dev_open,
	.read = dev_read,
	.write = dev_write,
	.unlocked_ioctl = dev_ioctl,
	.release = dev_release,
};


static int dev_open(struct inode *inode,struct file *file) {
	printk("Device File Opened !!");
	return 0;
}


static int dev_release(struct inode *inode,struct file *file) {
	printk("Device File Close !!");
	return 0;
}


static ssize_t dev_read(struct file *filep,char __user *buf,size_t len,loff_t *off) {
	printk("Read Function Called !! ");
	return 0;
}


static ssize_t dev_write(struct file *filep,const char *buf,size_t len,loff_t *off) {
	printk("Write Function Called !!");
	return len;
}

static long dev_ioctl(struct file *file,unsigned int cmd,unsigned long arg) {
	switch(cmd){
		case WR_VALUE:
		        if(copy_from_user(&value,(int32_t*) arg,sizeof(value))) {
				printk("Data Write Error !!\n");
			}
			printk("Value is: %d\n",value);
			break;
		case RD_VALUE:
		        if(copy_to_user((int32_t*) arg, &value,sizeof(value))) {
				printk("Data Read Error !!\n");
			}
			break;

		default	     :printk("Default");
			break;
	}
	return 0;
}


static int __init init_driver(void) {

	if(alloc_chrdev_region(&dev,0,1,"swapnil_dev") < 0) {
		printk("Major Minor number can't assign");
		return -1;
	}
	printk("Minor = %d Major = %d of your modules.",MAJOR(dev),MINOR(dev));

	/*This helps in creating/initialsing cdev structures */
	cdev_init(&swapnil_cdev,&fops);
	
	/*Adding character device in the system */
	if(cdev_add(&swapnil_cdev,dev,1) < 0) {
		printk("Cannot add char device to our system");
		goto r_class;
	}

	/*This will creata a dev_class*/
	if(IS_ERR(dev_class = class_create("swapnil_class"))) {
		printk("Cannot create the struct class");
		goto r_class;
	}
	
	/*this will create our device file in the system (found it by: ls /dev)*/
	if(IS_ERR(device_create(dev_class,NULL,dev,NULL,"swapnil_device"))) {
		printk("Cannot create the device");
		goto r_device;
	}

	printk("Device Module Inserted Successfully");
	return 0;
r_device:
	class_destroy(dev_class);
r_class:
	unregister_chrdev_region(dev,1);
	return -1;
}

static void __exit exit_driver(void) {
	device_destroy(dev_class,dev);
	class_destroy(dev_class);
	cdev_del(&swapnil_cdev);
	unregister_chrdev_region(dev,1);
	printk("Device Driver Removed !!");
}

module_init(init_driver);
module_exit(exit_driver);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Swapnil Jain");
MODULE_DESCRIPTION("This is sample IOCTL driver !!");
MODULE_VERSION("0:0.7");

