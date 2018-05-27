LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
#TARGET_ARCH := arm
LOCAL_MODULE:= TestCpuFeature
LOCAL_SRC_FILES := TestCpuFeature.c

LOCAL_STATIC_LIBRARIES := cpufeatures
include $(BUILD_EXECUTABLE)
#include $(BUILD_SHARED_LIBRARY)
$(call import-module,android/cpufeatures)

