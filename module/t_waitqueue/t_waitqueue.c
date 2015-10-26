#include <linux/module.h>
#include <linux/wait.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/init.h>

MODULE_LICENSE("GPL v2");

wait_queue_head_t waitq;
static struct task_struct *p, *c;

int condition = 0;

char data[] = "wait queue";

static int pthreadfn(void *data)
{
    /*
     * user context
     */
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);
    do {
        msleep(2000);
        printk(KERN_DEBUG pr_fmt("%s, wake up c\n"), __func__);
        condition = 1;
        wake_up(&waitq);
    } while(!kthread_should_stop());
    return 0;
}

static int cthreadfn(void *data)
{
    /*
     * user context
     */
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);
    do {
        wait_event(waitq, condition);
        printk(KERN_DEBUG pr_fmt("%s, condition = 1\n"), __func__);
        condition = 0;
    } while(!kthread_should_stop());
    return 0;
}

static int __init t_waitqueue_init(void)
{
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);

    /*
     * initial wait queue
     */
    init_waitqueue_head(&waitq);

    /*
     * Just create a thread, but not yet running
     */
    p = kthread_create(pthreadfn, data, "produce_kthread");

    if (IS_ERR(p)) {
        goto error;
    }

    c = kthread_create(cthreadfn, data, "consume_kthread");

    if (IS_ERR(c)) {
        goto error;
    }

    /*
     * Wake up a specific process
     */
    wake_up_process(p);

    /*
     * Wake up a specific process
     */
    wake_up_process(c);

    return 0;

error:
    return -1;
}

static void __exit t_waitqueue_exit(void)
{
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);

    /*
     * stop a thread created by kthread_create()
     */
    kthread_stop(p);

    /*
     * stop a thread created by kthread_create()
     */
    kthread_stop(c);

    return;
}

module_init(t_waitqueue_init);
module_exit(t_waitqueue_exit);
