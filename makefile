#
# This makefile would help to build the kernel, bootloader and root filesystem
#

root_dir := $(shell pwd)

include mk/version.mk
include mk/defs.mk
include mk/download.mk

.PHONY: all clean distclean run help

all: stamp-kernel stamp-uboot stamp-rootfs

# kernel
include mk/kernel.mk
stamp-kernel:
	make build-kernel
	touch $@

clean-kernel:
	make kernel-clean
	rm -rf stamp-kernel

distclean-kernel:
	rm -rf $(target_out_kernel) stamp-kernel

# u-boot
include mk/uboot.mk
stamp-uboot:
	make build-uboot
	touch $@

clean-uboot:
	make uboot-clean
	rm -rf stamp-uboot

distclean-uboot:
	rm -rf $(target_out_uboot) stamp-uboot

# root filesystem
include mk/rootfs.mk
stamp-rootfs:
	make build-rootfs
	touch $@

distclean-rootfs:
	rm -rf $(target_out_busybox) $(target_out_rootfs) stamp-rootfs

clean: distclean-kernel distclean-uboot distclean-rootfs
	rm -rf $(target_out)

distclean: clean
	rm -rf $(src_dir)

# Run with Qemu
include mk/qemu.mk
run: all
	make run-qemu

help:
	@echo ""
	@echo ""
	@echo "              linux-builder"
	@echo "=========================================="
	@echo "# kernel:"
	@echo "  make clearn-kernel; make stamp-kernel"
	@echo ""
	@echo "# uboot:"
	@echo "  make clean-uboot; make stamp-uboot"
	@echo ""
	@echo "# rootfs:"
	@echo "  make distclean-rootfs; make stamp-rootfs"
	@echo ""
	@echo "# run with QEMU:"
	@echo "  make run"
	@echo ""
	@echo "# rebuild all:"
	@echo "  make clean; make"
	@echo ""
	@echo "# remove source and rebuild all:"
	@echo "  make distclean; make"
	@echo ""
	@echo "# display help:"
	@echo "  make hlep"
	@echo ""