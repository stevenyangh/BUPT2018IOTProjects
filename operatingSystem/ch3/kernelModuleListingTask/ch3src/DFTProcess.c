#include <linux/sched.h>
#include <linux/sched/signal.h>

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/list.h>

void printTaskInfo(int depth, struct task_struct *task) {
  printk(KERN_INFO "%4d[%8d|%8d|%8ld|%16s]\n", depth, task->pid, task_ppid_nr(task), task->state, task->comm);
}

int DFTDisplay(int depth, struct task_struct *prevNode) {
  int count = 1;
  int i;
  
  printTaskInfo(depth, prevNode);
  
  struct task_struct *task;
  struct list_head *list;
  list_for_each(list, &prevNode->children) {
    task = list_entry(list, struct task_struct, sibling);
    count = count + DFTDisplay(depth + 1, task);
  }
  return count;
}


int dft_init(void)
{
  printk(KERN_INFO "Loading Module\n");
  int displayNum = DFTDisplay(0, &init_task);
  printk(KERN_INFO "%d processes\n", displayNum);
  return 0;
}


void dft_exit(void) {
  printk(KERN_INFO "Removing Module\n");
}

module_init( dft_init );
module_exit( dft_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DFTraverseProcess");
MODULE_AUTHOR("YAN_Haowen");
