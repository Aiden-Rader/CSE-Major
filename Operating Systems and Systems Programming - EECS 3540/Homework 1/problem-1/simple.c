/**
 * simple.c
 *
 * A simple kernel module.
 *
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gcd.h>  /* Added to print out greatest common divisor */
#include <linux/jiffies.h>  /* Added to get count of timer interruptions */
#include <linux/param.h>  /* Added to get HZ, didn't use <asm/param.h> due to it being outdated according to my terminal */


/* Added function prototype defintions to remove warnings when loading make file */
int simple_init(void);
void simple_exit(void);

/* This function is called when the module is loaded. */
int simple_init(void)
{
	printk(KERN_INFO "Loading Kernel Module\n");
       	printk(KERN_INFO "HZ = %d\n", HZ);
       	printk(KERN_INFO "jiffies = %lu\n", jiffies);
       	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
    printk(KERN_INFO "Removing Kernel Module\n");
	printk(KERN_INFO "GCD = %lu\n", gcd(3300, 24));
	printk(KERN_INFO "jiffies = %lu\n", jiffies);
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
