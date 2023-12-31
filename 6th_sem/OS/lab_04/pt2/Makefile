KVERSION = $(shell uname -r)
KDIR = /lib/modules/$(KVERSION)/build
PWD = $(shell pwd)
TARGET1 = fortune
TARGET2 = seqfile
obj-m := $(TARGET1).o $(TARGET2).o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean

disclean: clean
	@rm -f *.ko *.symvers *.mod

ins_fortune:
	sudo insmod fortune.ko

ins_seqfile: 
	sudo insmod seqfile.ko

remove:
	sudo rmmod fortune.ko
	sudo rmmod seqfile.ko

info:
	modinfo fortune.ko
	modinfo seqfile.ko

log:
	sudo dmesg | tail -100



