LOCAL_PATH := $(call my-dir)

# cocos2dx-soomla-common
include $(CLEAR_VARS)

COCOS2D_JAVASCRIPT = $(filter %-DCOCOS2D_JAVASCRIPT=1,$(APP_CPPFLAGS))

LOCAL_MODULE := cocos2dx_soomla_common_static
LOCAL_MODULE_FILENAME := libcocos2dxsoomlacommon

CORE_SRC_LIST := $(wildcard $(LOCAL_PATH)/Soomla/*.cpp)
CORE_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/domain/*.cpp)
CORE_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/data/*.cpp)
CORE_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/rewards/*.cpp)
ifneq '$(COCOS2D_JAVASCRIPT)' ''
CORE_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/jsb/*.cpp)
endif


LOCAL_SRC_FILES := $(CORE_SRC_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/Soomla
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/data
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/domain
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/rewards
ifneq '$(COCOS2D_JAVASCRIPT)' ''
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/jsb
endif

ifneq '$(COCOS2D_JAVASCRIPT)' ''
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += spidermonkey_static
LOCAL_WHOLE_STATIC_LIBRARIES += scriptingcore-spidermonkey
endif
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += jansson_static


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/data
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/domain
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/rewards
ifneq '$(COCOS2D_JAVASCRIPT)' ''
LOCAL_EXPORT_C_INCLUDES += $$(LOCAL_PATH)/Soomla/jsb
endif

include $(BUILD_STATIC_LIBRARY)
ifneq '$(COCOS2D_JAVASCRIPT)' ''
$(call import-module,CocosDenshion/android)
$(call import-module,external/chipmunk)
$(call import-module,scripting/javascript/spidermonkey-android)
$(call import-module,scripting/javascript/bindings)
endif
$(call import-module,external/jansson)
