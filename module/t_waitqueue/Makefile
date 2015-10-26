ifneq ($(KERNELRELEASE),)

# kbuild part of makefile

obj-m += t_waitqueue.o

else

# normal makefile

target = t_waitqueue.ko

include $(mk_dir)/module.mk

endif
