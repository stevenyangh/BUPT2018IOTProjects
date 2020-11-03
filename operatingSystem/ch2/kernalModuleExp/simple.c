#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

struct birthday
{
    int day;
    int month;
    int year;
    struct list_head list;
};

static LIST_HEAD(birthday_list); 

/* This function is called when the module is loaded. */
int simple_init(void) {
    printk(KERN_INFO "Loading Module\n");
    struct birthday *person;
    
    person = kmalloc(sizeof(*person), GFP_KERNEL);
    person->day = 2;
    person->month = 8;
    person->year = 1995;
    INIT_LIST_HEAD(&person->list);
    list_add_tail(&person->list, &birthday_list);
    
    person = kmalloc(sizeof(*person), GFP_KERNEL);
    person->day = 27;
    person->month = 2;
    person->year = 2000;
    list_add_tail(&person->list, &birthday_list);
    
    person = kmalloc(sizeof(*person), GFP_KERNEL);
    person->day = 11;
    person->month = 9;
    person->year = 2005;
    list_add_tail(&person->list, &birthday_list);
    
    person = kmalloc(sizeof(*person), GFP_KERNEL);
    person->day = 26;
    person->month = 12;
    person->year = 2007;
    list_add_tail(&person->list, &birthday_list);
    
    person = kmalloc(sizeof(*person), GFP_KERNEL);
    person->day = 7;
    person->month = 3;
    person->year = 2004;
    list_add_tail(&person->list, &birthday_list);
    
    struct birthday *ptr;
    printk(KERN_INFO "+--------------------+\n");
    printk(KERN_INFO "|  list of birthdays |\n");
    printk(KERN_INFO "+--------------------+\n");
    printk(KERN_INFO "| year | month | day |\n");
    list_for_each_entry(ptr, &birthday_list, list) {
	printk(KERN_INFO "| %4d | %2d    | %2d  |\n", ptr->year, ptr->month, ptr->day);
    }
    printk(KERN_INFO "+--------------------+\n");
    
    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
    struct birthday *ptr, *next;

    printk(KERN_INFO "free node:\n");
    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
	printk(KERN_INFO "{%d, %d, %d}\n", ptr->year, ptr->month, ptr->day);
	list_del(&ptr->list);
	kfree(ptr);
    }
    
    printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

