#include "header.h"
#include "declaration.h"
#include "filopertion.h"

struct DEV *sdev;
struct cdev c_dev;
dev_t dev;
int ret_reg;
unsigned int majorno, minorno, nod, quantum_size, qset_size, device_size, data_size;

module_param(nod, int, S_IRUGO);
module_param(quantum_size, int, S_IRUGO);
module_param(qset_size, int, S_IRUGO);

void init_dev_parameter(void)
{
	majorno = MAJOR(dev);
	minorno = MINOR(dev);
	majorno = MAJORNO;
	minorno = MINORNO;
	//quantum_size = QUANTUM_SIZE;
	//qset_size = QSET_SIZE;
	device_size = DEVICE_SIZE;
	data_size = DATA_SIZE;
	
}
static int __init start_ker_pro(void)
{
	int dvar;
	printk(KERN_INFO "I'M in......\n");
	init_dev_parameter();
	if(majorno)
	{
		register_chrdev_region(majorno, nod, DNAME );	
	}
	else
	{
		ret_reg = alloc_chrdev_region(&dev, minorno, nod, DNAME);
		if(ret_reg == -1)
		{
			printk(KERN_ERR "wrong wrong");
			goto OUT;
		}
	}
	#ifdef DEBUG
	printk(KERN_INFO "major number %d\n", majorno);
	#endif 
	
	#ifdef DEBUG
	printk(KERN_INFO "node = %d\n", nod);
	#endif 
	
	sdev = kmalloc(sizeof(struct DEV) * nod, GFP_KERNEL);
	printk(KERN_INFO "The size is \n" );
	memset(sdev, '\0', sizeof(struct DEV) * nod);


	for(dvar = 0; dvar < nod; dvar++)
	{
		cdev_init(&sdev[dvar].c_dev, &fops);
		sdev[dvar].c_dev.owner = THIS_MODULE;
		sdev[dvar].c_dev.ops = &fops;
		sdev[dvar].quantum_size = quantum_size;
		sdev[dvar].qset_size = qset_size;
		sdev[dvar].device_size = device_size;
		sdev[dvar].data_size = data_size;

		if( cdev_add(&sdev[dvar].c_dev, dev, nod) != 0)
		{
			#ifdef DEBUG
			printk(KERN_INFO "There some error in cdev_add\n");
			#endif 
		}
	
	}
	return 0;
OUT:
	#ifdef DEBUG
	printk(KERN_INFO "There some error please fix this\n");
	#endif 
	return -1;
}

module_init(start_ker_pro);
