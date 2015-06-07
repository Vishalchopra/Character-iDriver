//extern struct file_operations ofs;

//extern int quantum_size, qset_size, device_size, data_size, majorno, minorno;
struct Qset
{
	struct Qset *next;
	void **data;
};
struct DEV
{
	struct Qset *qset;
	int quantum_size, qset_size, device_size, data_size;
	struct cdev c_dev;
};

extern struct DEV *sdev;

int open_dev(struct inode *, struct file *);
int close_dev(struct inode *, struct file *);
ssize_t write_dev(struct file*, const char __user *, size_t, loff_t *);
ssize_t reader_dev(struct file*, char __user *, size_t, loff_t *);
loff_t lseek_dev(struct file*, loff_t, int);
struct Qset* create_structqset(int);
int create_qset(int, struct Qset *);
int create_quantum(int, struct Qset *);
//int write_to_quantum(struct Qset *, const char __user *);
