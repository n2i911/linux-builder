#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/completion.h>
#include <linux/delay.h>
#include <linux/init.h>

MODULE_LICENSE("GPL v2");

struct task_struct *ptask, *ctask;

DECLARE_COMPLETION(comp);

static int pthreadfn(void* data)
{
    int i = 0;
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);

    while(!kthread_should_stop()) {
        printk(KERN_DEBUG pr_fmt("%s, i: %d\n"), __func__, i++);

        if (i == 9) {
            i = 0;
            complete(&comp);
        }

        ssleep(1);
    }

    return 0;
}

static int cthreadfn(void* data)
{
    int i = 0;

    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);

    while(!kthread_should_stop()) {
        wait_for_completion(&comp);
        printk(KERN_DEBUG pr_fmt("%s, i: %d\n"), __func__, i++);
    }

    return 0;
}

static int __init t_completion_init(void)
{
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);

    ptask = kthread_create(pthreadfn, NULL, "%s", "Produce");
    ctask = kthread_create(cthreadfn, NULL, "%s", "Consume");

    wake_up_process(ptask);
    wake_up_process(ctask);

    return 0;
}

static void __exit t_completion_exit(void)
{
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);

    kthread_stop(ctask);
    kthread_stop(ptask);

    return;
}

module_init(t_completion_init);
module_exit(t_completion_exit);
