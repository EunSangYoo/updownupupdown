#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

#define AC_DOWN (342)
#define AC_UP (379)

static int my_dev;
static DECLARE_WAIT_QUEUE_HEAD(my_wait);
static int my_dev;

static int VolIntFlag = 0;
static int LockFlag = 0;


irqreturn_t touch_handler(int data, void* ptr)
{
   
	VolIntFlag++;

	if( VolIntFlag == 2 )
	{
		if( data == 342 )
		{
            LockFlag  = 0xaa;
	        wake_up_interruptible(&my_wait);
		}

		printk("touch me!\n");
        VolIntFlag  = 0;
	}
	return IRQ_HANDLED;
}



int touch_open(struct inode *inode, struct file *filp)
{
	printk("my_open()\n");
	return 0;
}

int touch_close(struct inode *inode, struct file *filp)
{
	printk("my_close()\n");
	return 0;
}

ssize_t touch_read(struct file *filep, char __user *buff, size_t size, loff_t *off)

{

	if( LockFlag != 0xaa )
        interruptible_sleep_on(&my_wait);

//	copy_to_user

	put_user(LockFlag, (int*)buff); // 궁금함
    LockFlag = 0;
	return sizeof(LockFlag);
}


static struct file_operations fops = {
	.open = touch_open,
	.release = touch_close,
	.read = touch_read,
};

static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "touch_device",
	.fops = &fops,
};
	

int jibin_init(void)
{
	int ret;
	unsigned long int falg =  IRQF_SHARED | IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING ;
	ret = request_irq( AC_DOWN , touch_handler, falg, "hing", &my_dev); // IVT에 interrupt를 등록하는 함수 
	misc_register(&misc);
	return 0;
}


void __exit jibin_exit(void)
{
	misc_deregister(&misc);
	free_irq( AC_DOWN ,&my_dev);
}


module_init(jibin_init);
module_exit(jibin_exit);
