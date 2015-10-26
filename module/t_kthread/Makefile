ifneq ($(KERNELRELEASE),)

# kbuild part of makefile

obj-m += t_kthread.o

else

# normal makefile

target = t_kthread.ko

include $(mk_dir)/module.mk

endif
