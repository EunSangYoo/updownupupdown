TARGET = pattern_check
obj-m = $(TARGET).o
PWD = $(shell pwd)
KDIR = /usr/src/tegra

default:
	make -C $(KDIR) SUBDIRS=$(PWD) modules
#	adb push $(TARGET).ko /data

clean:
	make -C $(KDIR) SUBDIRS=$(PWD) clean
#	adb shell rmmod /data/$(TARGET).ko
