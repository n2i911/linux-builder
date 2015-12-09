build-rootfs: $(busybox_version) $(target_rootfs)

$(busybox_version):
	mkdir -p $(target_out_bin)
	mkdir -p $(target_out_rootfs)
	mkdir -p $(target_out_busybox)
	cp -f config/busybox_config $(target_out_busybox)/.config
	make -C $(busybox_dir) O=$(target_out_busybox) oldconfig
	make -C $(target_out_busybox) CONFIG_PREFIX=$(target_out_rootfs) install

$(target_rootfs): $(target_out_rootfs) $(target_out_busybox)/.config
	cp -raf $(rootfs_dir)/* $(target_out_rootfs)
	cp -ra $(target_out_ext_modules)/*.ko $(target_out_rootfs)/lib/modules/
	cd $(target_out_bin) && genromfs -v \
		-V "ROM Disk" \
		-f $(target_rootfs) \
		-x placeholder \
		-d $(target_out_rootfs) 1> romfs.map 2>&1
	cd $(target_out_bin) && env PATH=$(root_dir)/tool:$(PATH) geninitrd
