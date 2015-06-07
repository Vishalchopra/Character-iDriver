#include"header.h"
#include"declaration.h"

static void __exit exit_ker_pro(void)
{
	int dvar;
	#ifdef DEBUG
	printk("Exit from the kernel %d\n", nod);
	#endif
	for(dvar = 0; dvar < nod; dvar++)
	{
		cdev_del(&sdev[dvar].c_dev);
	}
		kfree(sdev);
	unregister_chrdev_region(dev, nod);

	#ifdef DEBUG
	printk(KERN_INFO "Unregister : THE END:\n");
	#endif
	
//	return 0;
}

module_exit(exit_ker_pro);
