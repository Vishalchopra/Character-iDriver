#include "header.h"
#include "declaration.h"

int close_dev(struct inode *inod, struct file *fop)
{
	#ifdef DEBUG
	printk(KERN_INFO "Begin......%s\n", __func__);
	#endif 

	#ifdef DEBUG
	printk(KERN_INFO "End......%s\n", __func__);
	#endif 

	return 0;
}	
