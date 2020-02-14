obj-m := hello.o 表示编译成模块，后面写对应文件名称加.o

安装模块命令 insmod ./hello.ko

删除 rmmod ./hello.ko

用命令 tail /var/log/kern.log查看日志

出现的问题

1.用 ide 可能报找不到#include <linux/kernel.h> 等头文件

确实 include里面没有

这个没关系 因为有内核源码先查看内核版本
```
root@ubuntu:~/Desktop# uname -r
4.2.0-27-generic
```

再写 makefile 文件时用$(shell uname -r) 就可以了

add-symbol-file

kgdb_breakpoint()

#ifndef __PARISC_KGDB_H__
#define __PARISC_KGDB_H__

#define BREAK_INSTR_SIZE        4
#define PARISC_KGDB_COMPILED_BREAK_INSN    0x3ffc01f
#define PARISC_KGDB_BREAK_INSN        0x3ffa01f


#define NUMREGBYTES            sizeof(struct parisc_gdb_regs)
#define BUFMAX                4096

#define CACHE_FLUSH_IS_SAFE        1

#ifndef __ASSEMBLY__

static inline void arch_kgdb_breakpoint(void)
{
    asm(".word %0" : : "i"(PARISC_KGDB_COMPILED_BREAK_INSN) : "memory");
}


static inline void barrier(void)
{
    asm volatile("" : : : "memory");
}

static inline void
atomic_inc(atomic_t *v)
{
    atomic_add(1, v);
}


typedef struct {
    int counter;
} atomic_t;

atomic_t            kgdb_setting_breakpoint;

noinline void kgdb_breakpoint(void)
{
    atomic_inc(&kgdb_setting_breakpoint);
    wmb(); /* Sync point before breakpoint */
    arch_kgdb_breakpoint();
    wmb(); /* Sync point after breakpoint */
    atomic_dec(&kgdb_setting_breakpoint);
}






#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
static char buf[] = "你好";
static char buf1[10];
 
int __init hello_init(void)
{
    struct file *fp;
    mm_segment_t fs;
    loff_t pos;
    printk("hello enter\n");
    fp = filp_open("/home/niutao/kernel_file", O_RDWR | O_CREAT, 0644);
    if (IS_ERR(fp)) {
        printk("create file error\n");
        return -1;
    }
    fs = get_fs();
    set_fs(KERNEL_DS);
    pos = 0;
    vfs_write(fp, buf, sizeof(buf), &pos);
    pos = 0;
    vfs_read(fp, buf1, sizeof(buf), &pos);
    printk("read: %s\n", buf1);
    filp_close(fp, NULL);
    set_fs(fs);
    return 0;
}
void __exit hello_exit(void)
{
    printk("hello exit\n");
}
 
module_init(hello_init);
module_exit(hello_exit);
 
MODULE_LICENSE("GPL");

