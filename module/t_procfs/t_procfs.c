#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL v2");

struct proc_dir_entry *pentry;
struct proc_dir_entry *centry;

static int test_proc_open(struct inode *inode, struct file *filp)
{
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);
    return 0;
}

static ssize_t test_proc_read(struct file *filp, char __user *buf, size_t count,
        loff_t *offset)
{
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);
    return 0;
}

static ssize_t test_proc_write(struct file *filp, const char __user *buf,
        size_t count, loff_t *offset)
{
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);
    return count;
}

static int test_proc_release(struct inode *inode, struct file *filp)
{
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);
    return 0;
}

struct file_operations fop = {
	.owner = THIS_MODULE,
    .open = test_proc_open,
    .read = test_proc_read,
    .write = test_proc_write,
    .release = test_proc_release,
};

static int __init t_procfs_init(void)
{
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);

    /*
     * /proc/test_procfs/test_procfs
     */
    pentry = proc_mkdir("test_procfs", NULL);
    centry = proc_create("test_procfs", S_IFREG | S_IRUGO, pentry, &fop);

    /*
     * symlink test_symlink link to file /proc/test_procfs/test_procfs
     */
    proc_symlink("test_symlink", NULL, "/proc/test_procfs/test_procfs");

    return 0;
}

static void __exit t_procfs_exit(void)
{
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);
    remove_proc_entry("test_procfs", pentry);
    remove_proc_entry("test_procfs", NULL);

    remove_proc_entry("test_symlink", NULL);

    return;
}

module_init(t_procfs_init);
module_exit(t_procfs_exit);
