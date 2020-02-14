#include <linux/kernel.h> /*Needed by all modules*/
#include <linux/module.h> /*Needed for KERN_* */
#include <linux/init.h> /* Needed for the macros */
#include <linux/kgdb.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
MODULE_LICENSE("GPL");
 
static int year=2020;
static char buf1[50];
static int hello_init(void)
{
  struct file *fp,*fp2; 
  loff_t pos;
  fp = filp_open("/sys/module/hello/sections/.text", O_RDWR | O_CREAT, 0644);
  if (IS_ERR(fp)) {
        printk("create file error\n");
        return -1;
    }
  fp2 = filp_open("/dev/pts/0", O_RDWR | O_CREAT, 0644);
  if (IS_ERR(fp2)) {
        printk("create file error\n");
        return -1;
    }
  vfs_read(fp, buf1, sizeof(buf1), &pos);
  vfs_write(fp2, buf1, sizeof(buf1), &pos);
  filp_close(fp, NULL);
  filp_close(fp2, NULL);
  //kgdb_breakpoint();
  printk(KERN_WARNING "Hello kernel, it's %d!\n",year);
  return 0;
}
 
static void hello_exit(void)
{
  printk("Bye, kernel!\n");
}
 
/* main module function*/
module_init(hello_init);
module_exit(hello_exit);
