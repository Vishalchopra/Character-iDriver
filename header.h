#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/uaccess.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/cdev.h>
#include<linux/moduleparam.h>

extern dev_t dev;
extern unsigned int majorno, nod, minorno, quantum_size, data_size, qset_size, device_size;

#ifndef MAJORNO
#define MAJORNO 0
#endif

#ifndef MINORNO
#define MINORNO 0
#endif

#ifndef DEBUG
#define DEBUG 
#endif

#ifndef NOD
#define NOD 1
#endif

#ifndef DEVICE_SIZE
#define DEVICE_SIZE 1024
#endif

#ifndef DATA_SIZE
#define DATA_SIZE 0
#endif

#ifndef QUANTUM_SIZE
#define QUANTUM_SIZE 1
#endif

#ifndef QSET_SIZE
#define QSET_SIZE 8
#endif

#define DNAME "vishchopra"
MODULE_LICENSE("GPL");
MODULE_AUTHOR("vishchopra");
MODULE_DESCRIPTION("Initialization");
