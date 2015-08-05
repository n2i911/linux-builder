# This is only for kernel and u-boot
ARCH := arm
CROSS := arm-none-eabi-
VERVOSE := 0

# This is speific to kernel
MACH := vexpress

# This is speific to u-boot
BOARD := vexpress_ca9x4_defconfig

# This is speific to busybox
BUSYBOX_CROSS := arm-none-linux-gnueabi-

# source directory
src_dir := $(root_dir)/src
uboot_dir := $(src_dir)/$(uboot_version)
kernel_dir := $(src_dir)/$(kernel_version)
busybox_dir := $(src_dir)/$(busybox_version)

rootfs_dir := $(root_dir)/rootfs

# output directory
target_out := $(root_dir)/out
target_out_kernel := $(target_out)/$(kernel_version)
target_out_uboot := $(target_out)/$(uboot_version)
target_out_busybox := $(target_out)/$(busybox_version)
target_out_rootfs := $(target_out)/rootfs
target_out_bin := $(target_out)/bin

# config directory
config_dir := $(root_dir)/config

kernel_config := $(config_dir)/kernel/vexpress_initrd_kernel_config
busybox_config := $(config_dir)/busybox_config

# bin files
target_kernel := zImage
target_kernel_dtb := vexpress-v2p-ca9.dtb
target_uboot := u-boot.bin
target_rootfs := romfs.img
target_initrd := initrd.img

# This is speific to qemu
QMACH := vexpress-a9
QEMU_OPTIONS := -M $(QMACH) -kernel $(target_kernel) -initrd $(target_initrd) \
	-m 256 -nographic -localtime -append 'console=ttyAMA0 console=ttyS0' \
	-net none -dtb $(target_kernel_dtb)
