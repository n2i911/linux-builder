#include <linux/module.h>
#include <linux/jiffies.h>
#include <linux/init.h>

MODULE_LICENSE("GPL v2");

static int __init t_jiffies_init(void)
{
    printk(KERN_DEBUG pr_fmt("%lu\n"), jiffies);
    return 0;
}

static void __exit t_jiffies_exit(void)
{
    printk(KERN_DEBUG pr_fmt("%lu\n"), jiffies);
    return;
}

module_init(t_jiffies_init);
module_exit(t_jiffies_exit);
