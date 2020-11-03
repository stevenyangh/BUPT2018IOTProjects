#include <linux/sched.h>
#include <linux/sched/signal.h>

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>



void printTaskInfo(struct task_struct *task) {
  printk(KERN_INFO "%6d|%8ld|%s\n", task->pid, task->state, task->comm);
}

int lt_init(void)
{
  printk(KERN_INFO "Loading Module\n");
  struct task_struct *task;
  printk(KERN_INFO " pid  | status | name");

  for_each_process(task) {
    printTaskInfo(task);
  }
  return 0;
}

void lt_exit(void) {
  printk(KERN_INFO "Removing Module\n");
}

module_init( lt_init );
module_exit( lt_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LinearTraverseProcess");
MODULE_AUTHOR("YAN_Haowen");
