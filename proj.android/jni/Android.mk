LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/PlayScene.cpp \
                   ../../Classes/ThirdPartyHelper.cpp \
                   ../../Classes/GameOverScene.cpp \
                   ../../Classes/jansson/dump.c \
                   ../../Classes/jansson/error.c \
                   ../../Classes/jansson/hashtable.c \
                   ../../Classes/jansson/load.c \
                   ../../Classes/jansson/memory.c \
                   ../../Classes/jansson/pack_unpack.c \
                   ../../Classes/jansson/strbuffer.c \
                   ../../Classes/jansson/strconv.c \
                   ../../Classes/jansson/utf.c \
                   ../../Classes/jansson/value.c \
                   ../../Classes/NDKHelper/NDKCallbackNode.cpp \
                   ../../Classes/NDKHelper/NDKHelper.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/NDKHelper \
					$(LOCAL_PATH)/../../Classes/jansson \

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
