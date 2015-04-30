LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := hana.c
LOCAL_MODULE := hana
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := HanaTouch.c
LOCAL_MODULE := HanaTouch
include $(BUILD_SHARED_LIBRARY)
