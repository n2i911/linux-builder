ifneq ($(KERNELRELEASE),)

# kbuild part of makefile

obj-m += t_procfs.o

else

# normal makefile

target = t_procfs.ko

include $(mk_dir)/module.mk

endif
