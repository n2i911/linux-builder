#
# kernel modules
#
all_modules = t_jiffies t_waitqueue t_kthread t_procfs t_completion

modules: $(all_modules)

$(all_modules):
	make -C $(module_dir)/$@

modules.clean: $(all_modules:%=%.clean)

$(all_modules:%=%.clean): %.clean:
	make -C $(module_dir)/$* clean uninstall

.PHONY: modules $(all_modules) modules.clean $(all_modules:%=%.clean)
