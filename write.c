#include"header.h"
#include"declaration.h"

ssize_t write_dev(struct file *filp, const char __user *ubuff, size_t size, loff_t *loff)
{
	int no_qs, qun_siz, ret, nocsw, noctw, lv, i;
	struct DEV *lsdev;
	struct Qset *lqset;
	lsdev = filp->private_data;
	//char buff[] = ubuff;
	#ifdef DEBUG
	printk(KERN_INFO "BEGIN.....%s\n", __func__);
	#endif
	ret = i = nocsw = 0;
	no_qs = size / (qset_size * quantum_size);/*Calculation of number of struct qset*/
	
	if(size % (qset_size * quantum_size) )
			no_qs++;

	lsdev->qset = create_structqset(no_qs); /*Function for the creation of the struct Qset*/
	
	create_qset(no_qs, lsdev->qset); /*Function for the create of the qset array*/

	qun_siz = size / quantum_size;
	if(size % quantum_size)
		qun_siz++;
	create_quantum(qun_siz, lsdev->qset);/*Function to create the quantum*/
	
	noctw = size;
	lqset = lsdev->qset;
	for(lv = 0; lv < qun_siz; lv++)
	{
		if(noctw > quantum_size)
			noctw = quantum_size;
		ret = copy_from_user(lqset->data[i], ubuff + nocsw, noctw);
		printk(KERN_INFO "nocsw ..%d noctw ..%d  i = %d\n", nocsw, noctw, i);
		#ifdef DEBUG
		printk(KERN_INFO "Wrote on the device is %s\n", (char *)lqset->data[i]);
		#endif
		i++;
		nocsw = nocsw + noctw - ret;
		noctw = size - nocsw; 
		if(i == qset_size)
		{
			/*if(!lqset->next)
			{
				#ifdef DEBUG
				printk(KERN_ERR "Next qset is not present ...%s\n", __func__);
				#endif
				goto OUT;
			}*/
			if(lqset->next != NULL)
			{
				i = 0;
				lqset = lqset->next;
			}
			//else
			//	goto OUT;
		}

	}
	#ifdef DEBUG
	printk(KERN_INFO "END.....%s\n", __func__);
	#endif
                       
	data_size = nocsw;
	lsdev->data_size = nocsw;
	#ifdef DEBUG
	printk(KERN_INFO "._siz....%d\n", data_size);
	#endif
	filp->f_pos = *loff;
	return nocsw;
//OUT:
//	data_size = nocsw;
//	return nocsw;
}

struct Qset *create_structqset(int fno_qs)
{
	int qv;
	struct Qset *lqset, *first;
	first = NULL;
	#ifdef DEBUG
	printk(KERN_INFO "BEGIN.....%s\n", __func__);
	#endif

	for(qv = 0; qv < fno_qs; qv++)
	{
		if(qv == 0)
		{
			first = lqset = kmalloc(sizeof(struct Qset), GFP_KERNEL);
			if(!lqset)
			{
				#ifdef DEBUG
				printk(KERN_ERR "kmalloc failed ...%s\n", __func__);
				#endif
				goto OUT;
			}
			memset(lqset, '\0', sizeof(struct Qset));
		}
		else
		{
			lqset->next = kmalloc(sizeof(struct Qset), GFP_KERNEL);
			if(!lqset)
			{
				#ifdef DEBUG
				printk(KERN_ERR "kmalloc failed ...%s\n", __func__);
				#endif
				goto OUT;
			}
			memset(lqset->next, '\0', sizeof(struct Qset));
		}
		if(lqset->next)
 			lqset = lqset->next;
	}
	#ifdef DEBUG
	printk(KERN_INFO "END.....%s\n", __func__);
	#endif
	return first;
OUT:
	return 0;
}

int create_qset(int fno_qs1, struct Qset *lqset)
{
	int qv;
	#ifdef DEBUG
	printk(KERN_INFO "BEGIN.....%s\n", __func__);
	printk(KERN_INFO "%d fno_qs1 %s\n",fno_qs1, __func__);
	#endif
	for(qv = 0; qv < fno_qs1; qv++)
	{
		printk(KERN_INFO "%d no. of qset create %s\n", qv,__func__);
		lqset->data = kmalloc(sizeof(void *) * qset_size, GFP_KERNEL);
		if(!lqset->data)
		{
			#ifdef DEBUG
			printk(KERN_ERR "kmalloc failed ...%s\n", __func__);
			#endif
			goto OUT;
		}
		memset(lqset->data, '\0', sizeof(void *) * qset_size);
		if(lqset->next)
			lqset = lqset->next;
	}
	#ifdef DEBUG
	printk(KERN_INFO "End.....%s\n", __func__);
	#endif
	return 0;
OUT:
	return -1;
}                                  


int create_quantum(int qun_siz, struct Qset *lsdev)
{
	int qv, i;
	i = 0;
	for(qv = 0; qv < qun_siz; qv++)
	{
		lsdev->data[i] = kmalloc(quantum_size, GFP_KERNEL);
		if(!lsdev->data[i])
		{
			#ifdef DEBUG
			printk(KERN_ERR "kmalloc failed ...%s\n", __func__);
			#endif
		}
		i++;
		if(i == qset_size)
		{
			i = 0;
			lsdev = lsdev->next;
			if(!lsdev)
			{
				#ifdef DEBUG
				printk(KERN_ERR "kmalloc failed ...%s\n", __func__);
				#endif
				goto OUT;
			}
		}
	}
	return 0;
OUT:
	return -1;
}
