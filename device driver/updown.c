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
#define PATTERN_SIZE (5)

typedef enum
{
	UP = 0x1111,
	DOWN = 0x2222,

}Lock_Pattern_st;

static int temp;
static int my_dev;
static DECLARE_WAIT_QUEUE_HEAD(my_wait);

static Lock_Pattern_st Lock_Pattern[PATTERN_SIZE] = { UP, DOWN, UP, UP, DOWN };
static Lock_Pattern_st Input_Pattern[PATTERN_SIZE];
static int my_dev;

static int TimerIntFlag = 0;
static int InputCnt = 0;
static int LockFlag = 0;

static struct timer_list my_timer;

void my_timer_handler(unsigned long data);

irqreturn_t my_handler(int data, void* ptr)
{
   
	int i;
	TimerIntFlag++;

	if( TimerIntFlag == 2 )
	{
		mod_timer( &my_timer, jiffies + HZ );
		if( data == 342 )
		{
	        Input_Pattern[InputCnt] = DOWN;
		}
		else if( data == 379 )
		{
	        Input_Pattern[InputCnt] = UP;
		}

        TimerIntFlag  = 0;
		InputCnt++;
	}

	if( InputCnt == PATTERN_SIZE )
	{
		
		for( i = 0; i< PATTERN_SIZE ; i ++)
		{
            if( Lock_Pattern[i] != Input_Pattern[i] )
			{
				printk("Pattern Fail!\n\n");
		        InputCnt = 0;
	            return IRQ_HANDLED;
			}
		}

        InputCnt = 0;
		LockFlag = 0xaa;
	    printk("Pattern Success!\n\n");
	    wake_up_interruptible(&my_wait);
	}

	return IRQ_HANDLED;
}


void my_timer_handler(unsigned long data)
{
    TimerIntFlag  = 0;
	InputCnt = 0;
    printk("Time expire!! \n");
}


int my_open(struct inode *inode, struct file *filp)
{
	printk("my_open()\n");
	return 0;
}

int my_close(struct inode *inode, struct file *filp)
{
	printk("my_close()\n");
	return 0;
}

ssize_t my_read(struct file *filep, char __user *buff, size_t size, loff_t *off)
{

	if( LockFlag != 0xaa )
        interruptible_sleep_on(&my_wait);

	put_user(LockFlag, (int*)buff); // 궁금함
    LockFlag = 0;
	return sizeof(LockFlag);
}


static struct file_operations fops = {
	.open = my_open,
	.release = my_close,
	.read = my_read,
};

static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "updown_device",
	.fops = &fops,
};
	

int my_init(void)
{
	int ret;
	unsigned long int falg =  IRQF_SHARED | IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING ;
	ret = request_irq( AC_DOWN , my_handler, falg, "AC_DOWN", &my_dev); // IVT에 interrupt를 등록하는 함수 
	ret = request_irq( AC_UP , my_handler, falg, "AC_UP", &my_dev); // IVT에 interrupt를 등록하는 함수 ,, list형식으로 연결되어 있음

	init_timer(&my_timer);
	my_timer.expires = jiffies + HZ; // 5*Hz = 5s
    my_timer.function = my_timer_handler;
	my_timer.data = 0;
	add_timer(&my_timer);
	misc_register(&misc);
	return 0;
}


void __exit my_exit(void)
{
	misc_deregister(&misc);
	free_irq( AC_DOWN ,&my_dev);
	free_irq( AC_UP, &my_dev);
}


module_init(my_init);
module_exit(my_exit);
