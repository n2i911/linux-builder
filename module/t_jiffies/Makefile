ifneq ($(KERNELRELEASE),)

# kbuild part of makefile

obj-m += t_jiffies.o

else

# normal makefile

target = t_jiffies.ko

include $(mk_dir)/module.mk

endif
