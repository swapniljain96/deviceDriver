#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

int valueX=7,arr[7];
int cb_valueX = 0;
char *name;

module_param(valueX,int,S_IWUSR|S_IRUSR);
module_param(name,charp,S_IWUSR|S_IRUSR);
module_param_array(arr,int,NULL,S_IWUSR|S_IRUSR);

//-------------------- module_param_cb()------------------------------------

int notify_param(const char *val,const struct kernel_param *kp) {
	int res = param_set_int(val,kp);
	if(res == 0) {
		printk(KERN_INFO "Callback function is Called !!\n");
		printk(KERN_INFO "New value of cb_valueX is: %d\n",cb_valueX);
		return 0;
	}
	return -1;
}

const struct kernel_param_ops my_param_ops = 
{
	.set = &notify_param,
	.get = &param_get_int,
};
module_param_cb ( cb_valueX, &my_param_ops, &cb_valueX, S_IRUGO|S_IWUSR );

//--------------------------------------------------------------------------


static int __init driver_init(void) {
	int i;
	printk(KERN_INFO "Kernel Module is Loaded Successfully \n");
	printk(KERN_INFO "valueX : %d\n",valueX);
	printk(KERN_INFO "Name : %s \n",name);
	printk(KERN_INFO "cb_valueX : %d \n",cb_valueX);
	for ( i=0;i<(sizeof(arr)/sizeof(int));i++) {
		printk(KERN_INFO "Array value: [%d]: %d \n",i,arr[i]);
	}
	return 0;
}

void __exit driver_exit(void) {
	printk(KERN_INFO "Kernel Module is Removed Successfully \n");
}

module_init(driver_init);
module_exit(driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Swapnil Jain");
MODULE_DESCRIPTION("This is a initial driver");
MODULE_VERSION("0:0.7");
