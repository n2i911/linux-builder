ifneq ($(KERNELRELEASE),)

# kbuild part of makefile

obj-m += t_completion.o

else

# normal makefile

target = t_completion.ko

include $(mk_dir)/module.mk

endif
