LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
				   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
				   $(LOCAL_PATH)/../../../Classes/MenuScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/Debug/GLES-Render.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GameSpecific/GCGameLayerPlatformer.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GameSpecific/Invaders/GCObjGroupInvader.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GameSpecific/Invaders/GCObjInvader.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GameSpecific/Items/GCObjGroupItem.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GameSpecific/Items/GCObjItem.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GameSpecific/Platforms/GCObjGroupPlatform.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GameSpecific/Platforms/GCObjPlatform.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GameSpecific/Player/GCObjGroupProjectilePlayer.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GameSpecific/Player/GCObjPlayer.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GameSpecific/Player/GCObjProjectilePlayer.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GCCocosInterface/GB2ShapeCache-x.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GCCocosInterface/GCCallFuncStatic.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GCCocosInterface/GCCocosHelpers.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GCCocosInterface/GCObjSprite.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GCCocosInterface/GCObjSpritePhysics.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GCCocosInterface/GCObjTileLayer.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GCCocosInterface/IGCGameLayer.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GCCocosInterface/LevelLoader/GCLevelLoader_Ogmo.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GCCocosInterface/pugixml-1.2/pugixml.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GCObject/GCObject.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GCObject/GCObjectGroup.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GCObject/GCObjectManager.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/GCObject/GCObjGroupDefault.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamerCamp/Win32Input/GCKeyboardManager.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
