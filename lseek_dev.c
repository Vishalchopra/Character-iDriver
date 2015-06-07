#include"header.h"
#include"declaration.h"

loff_t lseek_dev(struct file *fil, loff_t offset, int pos)
{
	#ifdef DEBUB
	printf(KERN_INFO "Begin %s", __func__);
	#endif
	switch(pos)
	{
		case 0:
		#ifdef DEBUB
		printf(KERN_INFO "SEEK_BEGIN %s", __func__);
		#endif
		fil->f_pos = offset;
		break;

		case 1:
		#ifdef DEBUB
		printf(KERN_INFO "SEEK_CURR %s", __func__);
		#endif
		fil->f_pos = fil->f_pos + offset;
		break;

		case 2:
		#ifdef DEBUB
		printf(KERN_INFO "SEEK_END %s", __func__);
		#endif
		fil->f_pos = offset;
		break;
	}

	#ifdef DEBUB
	printf(KERN_INFO "END %s", __func__);
	#endif
	return 0;
}
