#include "header.h"
#include "declaration.h"

struct DEV *lsdev;
int trim_dev(struct DEV *);
int open_dev(struct inode *inod, struct file *fop)
{
	lsdev = sdev;
	#ifdef DEBUG
	printk(KERN_INFO "Begin......%s\n", __func__);
	#endif 

	lsdev = container_of(inod->i_cdev,struct DEV, c_dev);
	if(!lsdev)
	{
		#ifdef DEBUG
		printk(KERN_ERR "error in container.%s\n", __func__);
		#endif 
		goto OUT;
	}

	trim_dev(lsdev);

	fop->private_data = lsdev;

	if((fop->f_flags & O_ACCMODE) == O_WRONLY)
	{
		trim_dev(sdev);	
	}
	#ifdef DEBUG
	printk(KERN_INFO "End......%s\n", __func__);
	#endif 

	return 0;

OUT:
	return -1;
}	

int trim_dev(struct DEV *lsdev)
{
	 if(!lsdev)
	{
		#ifdef DEBUG
		printk(KERN_INFO "Need not to trim %s\n", __func__);
		#endif 
		goto OUT;
	}
		#ifdef DEBUG
		printk(KERN_INFO "Need to trim %s\n", __func__);
		#endif 

OUT:
	return -1;
}
