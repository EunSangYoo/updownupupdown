LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := pattern_check
LOCAL_SRC_FILES := pattern_check.c
include $(BUILD_SHARED_LIBRARY)
