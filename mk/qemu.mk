run-qemu:
	cd $(target_out_bin) && qemu-system-$(ARCH) $(QEMU_OPTIONS)
