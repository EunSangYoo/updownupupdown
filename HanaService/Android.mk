LOCAL_PATH:= $(call my-dir)

svc_c_flags =	\
	-Wall -Wextra \

ifneq ($(TARGET_USES_64_BIT_BINDER),true)
ifneq ($(TARGET_IS_64_BIT),true)
svc_c_flags += -DBINDER_IPC_32BIT=1
endif
endif

include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := liblog libbinder libutils
LOCAL_SRC_FILES := HanaServer.cpp IHanaService.cpp HanaService.cpp
LOCAL_CFLAGS += $(svc_c_flags)
LOCAL_MODULE := HanaServer 
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := liblog libbinder libutils
LOCAL_SRC_FILES := HanaClient.cpp  IHanaService.cpp
LOCAL_CFLAGS += $(svc_c_flags)
LOCAL_MODULE := HanaClient
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

