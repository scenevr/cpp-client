LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

LOCAL_CLANG :=true

SDL_PATH := ../SDL2
SDL_TTF_PATH := ../SDL2TTF
GLM_PATH := ../glm
LITEHTML_PATH := ../litehtml
THREE_PATH := ../THREE
EASYWS_PATH := ../easywsclient
PUGI_PATH := ../pugixml

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
		$(LOCAL_PATH)/$(SDL2TTF)/include \
		$(LOCAL_PATH)/$(LITEHTML)/include \
    $(LOCAL_PATH)/$(THREE_PATH)/ \
    $(LOCAL_PATH)/$(EASYWS_PATH)/ \
    $(LOCAL_PATH)/$(PUGI_PATH)/

# Add your application source files here...
LOCAL_SRC_FILES := \
	$(SDL_PATH)/src/main/android/SDL_android_main.c \
	$(EASYWS_PATH)/easywsclient.cpp \
	$(PUGI_PATH)/pugixml.cpp \
	$(wildcard $(LOCAL_PATH)/*.cpp) \
	$(wildcard $(LOCAL_PATH)/elements/*.cpp) \
	vendor/sdl.cpp \
	vendor/stats.cpp

LOCAL_SHARED_LIBRARIES := SDL2 THREE SDL2_ttf

LOCAL_LDLIBS := -lGLESv1_CM -lEGL -lGLESv3 -llog

LOCAL_CPPFLAGS := -std=c++11 -frtti

LOCAL_STL=gnustl_static

# NDK_TOOLCHAIN_VERSION=clang
# NDK_TOOLCHAIN_VERSION=4.8

include $(BUILD_SHARED_LIBRARY)