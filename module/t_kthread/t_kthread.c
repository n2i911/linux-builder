#include <linux/module.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL v2");

static struct task_struct *p;
char data[] = "1234567890";

struct timer_list timer;
struct work_struct workq;

void workq_callback(struct work_struct *work)
{
    /*
     * user context
     */
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);

    /*
     * stop a thread created by kthread_create()
     */
    kthread_stop(p);

    return;
}

void timer_callback(unsigned long data)
{
    /*
     * interrupt context
     */
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);

#if 0
    /*
     * Why this call will cause oops
     * ANS: kthread_stop() will wait for the termination of thread by
     *      the completion Mechanism, which will 'sleep'
     *
     *      And 'sleep' is not allowed within interrupt context
     */

    /*
     * stop a thread created by kthread_create()
     */
    kthread_stop(p);
#endif

    schedule_work(&workq);

    return;
}

static int threadfn(void *data)
{
    /*
     * user context
     */
    unsigned long i = 0;

    char *buf = kmalloc(strlen(data) + 1, GFP_KERNEL);
    memset(buf, '\0', strlen(data) + 1);
    strncpy(buf, data, strlen(data) + 1);

    printk(KERN_DEBUG pr_fmt("%s, data: %s\n"), __func__, buf);

    /*
     * should this kthread return now?
     */
    do {
        printk(KERN_DEBUG pr_fmt("%s, %lu\n"), __func__, i++);
        ssleep(1);
    } while(!kthread_should_stop());

    return 0;
}

static int __init t_kthread_init(void)
{
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);

    /*
     * Just create a thread, but not yet running
     */
    p = kthread_create(threadfn, data, "test_kthread");

    if (IS_ERR(p)) {
        goto error;
    }

    /*
     * initial workqueue
     */
    INIT_WORK(&workq, workq_callback);

    /*
     * initial the timer
     */
    init_timer(&timer);
    timer.function = timer_callback;
    timer.expires = jiffies + (10 * HZ);

    /*
     * Wake up a specific process
     */
    wake_up_process(p);

    /*
     * start a timer
     */
    add_timer(&timer);

#if 0
    /*
     * Don't sleep to much within init function
     */
    set_current_state(TASK_UNINTERRUPTIBLE );
    schedule_timeout(5 * HZ);

    /*
     * stop a thread created by kthread_create()
     */
    kthread_stop(p);
#endif

    return 0;

error:
    printk(KERN_DEBUG pr_fmt("%s, error\n"), __func__);
    return PTR_ERR(p);
}

static void __exit t_kthread_exit(void)
{
    printk(KERN_DEBUG pr_fmt("%s\n"), __func__);

#if 0
    /*
     * stop a thread created by kthread_create()
     */
    kthread_stop(p);
#endif

    flush_scheduled_work();

    /*
     * don't forget remove the timer
     */
    del_timer_sync(&timer);

    return;
}

module_init(t_kthread_init);
module_exit(t_kthread_exit);
