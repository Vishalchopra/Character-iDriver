INSTALLDIR= $(shell pwd)/modules
ifneq ($(KERNELRELEASE),)
	obj-m := vish_ch.o
	vish_ch-objs := init.o clean.o open_dev.o close_dev.o write.o reader_dev.o lseek_dev.o
else
KERNDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
		$(MAKE) -C $(KERNDIR) M=$(PWD) modules
			@rm -rf $(INSTALLDIR)
		@mkdir $(INSTALLDIR)
		@mv *.ko *.mod.c *.o .*.cmd $(INSTALLDIR)

clean:
		rm -rf $(INSTALLDIR)

endif

