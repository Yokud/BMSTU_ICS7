KPATH := /lib/modules/$(shell uname -r)/build
MDIR := $(shell pwd)

obj-m += hook_functions.o
EXTRA_CFLAGS=-I$(PWD)/inc

all:
	make -C $(KPATH) M=$(MDIR) modules

clean:
	make -C $(KPATH) M=$(MDIR) clean

load:
	sudo insmod monitor.ko

unload:
	sudo rmmod monitor.ko

info:
	modinfo monitor.ko

logs:
	sudo dmesg | grep "hook functions: "
