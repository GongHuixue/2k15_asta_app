LOCAL_PATH := $(call my-dir)

ifneq ($(AOSP_BUILD_SAT),)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_CERTIFICATE := platform
LOCAL_LDLIBS := -llog  
LOCAL_MODULE := libsatInstallerjni

LOCAL_C_INCLUDES := bionic external/stlport/stlport  \
		    $(LOCAL_PATH)/inc/dd \
		    $(LOCAL_PATH)/inc/intf \
		    $(LOCAL_PATH)/inc \
		    $(TOP)/device/tpvision/common/plf/tvserver/common \
		    $(TOP)/external/sqlite/dist \
		    $(LOCAL_PATH)/installation/prod/s2installer \
		    $(LOCAL_PATH)/installation/prod/s2installermw \
		    $(LOCAL_PATH)/installation/prod/s2installermw/src \
            	    $(LOCAL_PATH)/installation/comp/hsvdvbsopprofile \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsopprofile/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbscanal \
		    $(LOCAL_PATH)/installation/comp/hsvdvbscanal/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsdigiturk \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsdigiturk//src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsfransat \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsfransat/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsgeneric \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsgeneric/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsins \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsins/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsm7 \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsm7/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsn/ \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsn/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbspol \
		    $(LOCAL_PATH)/installation/comp/hsvdvbspol/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsrussia \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsrussia/src \
			$(LOCAL_PATH)/installation/comp/hsvdvbsfreesat \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsastra \
   		    $(LOCAL_PATH)/installation/comp/hsvdvbsastra/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbstricolor \
		    $(LOCAL_PATH)/installation/comp/hsvsatfe \
		    $(LOCAL_PATH)/installation/comp/hsvsatfe/src \
		    $(LOCAL_PATH)/installation/comp/hsvpgdat/ \
		    $(LOCAL_PATH)/installation/comp/hsvpgdat/src \
	        $(LOCAL_PATH)/installation/comp/sdm/hsvdvbbat \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbfnt	\
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbfst \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbnit \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbsdt \
   		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbsgt \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbsi \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvsimplempeg \
			$(LOCAL_PATH)/installation/comp/sdm/hsvdvbsdm \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbcamnit \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbpostcode\
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbtot \
		    $(LOCAL_PATH)/installation/comp/util/hsvutil \
		    $(LOCAL_PATH)/installation/comp/util/hsvstrmwlk \
		    $(LOCAL_PATH)/installation/prod/euinstallermw \
		    $(TOP)/device/tpvision/common/plf/tvplayer/av/api/include \
	      	$(TOP)/device/tpvision/common/plf/tvplayer/av/include
 
 
 LOCAL_SRC_FILES :=   installation/comp/hsvdvbsdigiturk/src/hsvdvbsdigiturk_mSort.cpp\
			installation/comp/hsvdvbsdigiturk/src/hsvdvbsdigiturk_mAcq.cpp\
			installation/comp/hsvdvbsdigiturk/src/hsvdvbsdigiturk_mPow.cpp\
			installation/comp/hsvdvbsdigiturk/src/hsvdvbsdigiturk_mScan.cpp\
			installation/comp/hsvdvbsopprofile/src/hsvdvbsopprofile_mAcq.cpp\
			installation/comp/hsvdvbsopprofile/src/hsvdvbsopprofile_mScan.cpp\
			installation/comp/hsvdvbsopprofile/src/hsvdvbsopprofile_mSort.cpp\
			installation/comp/hsvdvbsfransat/src/hsvdvbsfransat_mAcq.cpp\
			installation/comp/hsvdvbsfransat/src/hsvdvbsfransat_mBckgnd.cpp\
			installation/comp/hsvdvbsfransat/src/hsvdvbsfransat_mSort.cpp\
			installation/comp/hsvdvbsfransat/src/hsvdvbsfransat_mScan.cpp\
			installation/comp/hsvdvbsfreesat/src/hsvdvbsfreesat_mAcq.cpp\
			installation/comp/hsvdvbsfreesat/src/hsvdvbsfreesat_mBckgnd.cpp\
			installation/comp/hsvdvbsfreesat/src/hsvdvbsfreesat_mScan.cpp\
			installation/comp/hsvdvbsfreesat/src/hsvdvbsfreesat_mSort.cpp\
			installation/comp/hsvdvbsfreesat/src/hsvdvbsfreesat_mSettings.cpp\
			installation/comp/hsvdvbsm7/src/hsvdvbsm7_mSort.cpp\
			installation/comp/hsvdvbsm7/src/hsvdvbsm7_mAcq.cpp\
			installation/comp/hsvdvbsm7/src/hsvdvbsm7_mScan.cpp\
			installation/comp/hsvdvbscanal/src/hsvdvbscanal_mSort.cpp\
			installation/comp/hsvdvbscanal/src/hsvdvbscanal_mAcq.cpp\
			installation/comp/hsvdvbscanal/src/hsvdvbscanal_mScan.cpp\
			installation/comp/hsvdvbsrussia/src/hsvdvbsrussia_mSort.cpp\
			installation/comp/hsvdvbsrussia/src/hsvdvbsrussia_mAcq.cpp\
			installation/comp/hsvdvbsrussia/src/hsvdvbsrussia_mScan.cpp\
			installation/comp/hsvdvbstricolor/src/hsvdvbstricolor_mSort.cpp\
			installation/comp/hsvdvbstricolor/src/hsvdvbstricolor_mAcq.cpp\
			installation/comp/hsvdvbstricolor/src/hsvdvbstricolor_mScan.cpp\
			installation/comp/hsvdvbstricolor/src/hsvdvbstricolor_msettings.cpp\
			installation/comp/hsvdvbsn/src/hsvdvbsn_mSort.cpp\
			installation/comp/hsvdvbsn/src/hsvdvbsn_mScan.cpp\
			installation/comp/hsvdvbsn/src/hsvdvbsn_mAcq.cpp\
			installation/comp/hsvdvbspol/src/hsvdvbspol_mAcq.cpp\
			installation/comp/hsvdvbspol/src/hsvdvbspol_mSort.cpp\
			installation/comp/hsvdvbspol/src/hsvdvbspol_mScan.cpp\
			installation/comp/hsvdvbsgeneric/src/hsvdvbsgeneric_mAcq.cpp\
			installation/comp/hsvdvbsgeneric/src/hsvdvbsgeneric_m.cpp\
			installation/comp/hsvdvbsgeneric/src/hsvdvbsgeneric_mSort.cpp\
			installation/comp/hsvdvbsgeneric/src/hsvdvbsgeneric_mScan.cpp\
			installation/comp/hsvdvbsgeneric/src/hsvdvbsgeneric_mBckgnd.cpp\
			installation/comp/hsvdvbsgeneric/src/hsvdvbsgeneric_mSrt.cpp\
			installation/comp/hsvdvbsins/src/hsvdvbsins_mprescan.cpp \
			installation/comp/hsvdvbsins/src/hsvdvbsins_msatipprescan.cpp \
			installation/comp/hsvdvbsins/src/hsvdvbsins_mpredefinedlistcopy.cpp \
			installation/comp/hsvdvbsins/src/hsvdvbsins_mutil.cpp \
			installation/comp/hsvdvbsins/src/hsvdvbsins_mprescanparser.cpp\
			installation/comp/hsvdvbsins/src/hsvdvbsins_mpow.cpp\
			installation/comp/hsvdvbsins/src/hsvdvbsins_mroute.cpp\
			installation/comp/hsvdvbsins/src/hsvdvbsins_m.cpp\
			installation/comp/hsvdvbsins/src/hsvdvbsins_mminiprescan.cpp \
			installation/comp/hsvdvbsins/src/hsvdvbsins_mpackageparser.cpp\
			installation/comp/hsvdvbsins/src/hsvdvbsins_mremovesat.cpp\
			installation/comp/hsvdvbsins/src/hsvdvbsins_msettings.cpp\
			installation/comp/hsvdvbsins/src/hsvdvbsins_msigstr.cpp\
			installation/comp/sdm/hsvdvbnit/src/hsvdvbnit_m.cpp\
			installation/comp/sdm/hsvdvbsdt/src/hsvdvbsdt_m.cpp\
			installation/comp/sdm/hsvdvbsgt/src/hsvdvbsgt_m.cpp\
			installation/comp/sdm/hsvdvbfnt/src/hsvdvbfnt_m.cpp\
			installation/comp/sdm/hsvdvbbat/src/hsvdvbbat_m.cpp\
			installation/comp/sdm/hsvdvbfst/src/hsvdvbfst_m.cpp\
			installation/comp/sdm/hsvdvbsi/src/hsvdvbsi_m.cpp\
			installation/comp/sdm/hsvdvbsi/src/hsvdvbsi_mtab.cpp\
			installation/comp/sdm/hsvdvbsi/src/hsvdvbsi_mdt.cpp\
			installation/comp/sdm/hsvsimplempeg/src/hsvsimplempeg_m.cpp\
			installation/comp/sdm/hsvdvbpostcode/src/hsvdvbpostcode_m.cpp\
			installation/comp/sdm/hsvdvbsdm/src/hsvdvbsdm_mstrapi.cpp\
			installation/comp/sdm/hsvdvbsdm/src/hsvdvbsdm_m.cpp\
			installation/comp/sdm/hsvdvbcamnit/src/hsvdvbcamnit_m.cpp\
			installation/comp/sdm/hsvdvbtot/src/hsvdvbtot_m.cpp\
			installation/comp/util/hsvutil/src/hsvutil_mwchar.cpp\
			installation/comp/util/hsvutil/src/hsvutil_gpimwchar.cpp\
			installation/comp/util/hsvutil/src/hsvutil_mhuffdec.cpp\
			installation/comp/hsvsatfe/src/hsvsatfe_msilabs.cpp\
			installation/comp/hsvpgdat/src/hsvpgdat_mpgdat.cpp\
			installation/comp/hsvpgdat/src/hsvpgdat_mpgdb.cpp\
			installation/comp/hsvpgdat/src/hsvpgdat_m.cpp\
			installation/comp/hsvdvbsastra/src/hsvdvbsastra_mScan.cpp\
			installation/comp/hsvdvbsastra/src/hsvdvbsastra_mAcq.cpp\
			installation/comp/hsvdvbsastra/src/hsvdvbsastra_mSort.cpp\
			installation/comp/hsvdvbsastra/src/hsvdvbsastra_mBckgnd.cpp\
			installation/prod/s2installermw/src/dvbsmw_mpow.cpp\
			src/satinstallerstub_mdummy.cpp\
			src/CS2Installer.cpp \
			src/SatInstallerJNI.cpp \
			src/SatInstaller.cpp \
			src/CS2Logger.cpp
			
			
					
LOCAL_CFLAGS := -DAOSP_BUILD_SAT
LOCAL_SHARED_LIBRARIES := libTvMiddlewareCore libutils libstlport libbinder libcutils libsqlite   libandroid_runtime libtvplayerps libandroid

else
LOCAL_PATH := $(NDK_ROOT)
include $(CLEAR_VARS)
LOCAL_MODULE := libsqlite-ndk-prebuilt  
LOCAL_SRC_FILES := ../../TPVision_NDK_Addons\android-ndk-r8d\lib\libsqlite.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libTvMiddlewareCore-ndk-prebuilt
LOCAL_SRC_FILES := ../../TPVision_NDK_Addons\android-ndk-r8d\lib\libTvMiddlewareCore.so  
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_PATH := ./jni
LOCAL_MODULE_TAGS := optional
LOCAL_CERTIFICATE := platform
LOCAL_MODULE := libsatInstallerjni

LOCAL_C_INCLUDES := bionic external/stlport/stlport  \
		    $(LOCAL_PATH)/inc/dd \
		    $(LOCAL_PATH)/inc/intf \
		    $(LOCAL_PATH)/inc \
		    $(TOP)/device/tpvision/common/plf/tvserver/common \
		    $(TOP)/external/sqlite/dist \
		    $(LOCAL_PATH)/installation/prod/s2installer \
		    $(LOCAL_PATH)/installation/prod/s2installermw \
		    $(LOCAL_PATH)/installation/prod/s2installermw/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsopprofile \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsopprofile/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbscanal \
		    $(LOCAL_PATH)/installation/comp/hsvdvbscanal/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsdigiturk \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsdigiturk//src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsfransat \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsfransat/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsgeneric \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsgeneric/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsins \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsins/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsm7 \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsm7/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsn/ \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsn/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbspol \
		    $(LOCAL_PATH)/installation/comp/hsvdvbspol/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsrussia \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsrussia/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbsfreesat \
   		    $(LOCAL_PATH)/installation/comp/hsvdvbsastra \
		    $(LOCAL_PATH)/installation/comp/hsvdvbstricolor \
		    $(LOCAL_PATH)/installation/comp/hsvdvbstricolor/src \
		    $(LOCAL_PATH)/installation/comp/hsvsatfe \
		    $(LOCAL_PATH)/installation/comp/hsvsatfe/src \
		    $(LOCAL_PATH)/installation/comp/hsvpgdat/ \
		    $(LOCAL_PATH)/installation/comp/hsvpgdat/src \
	        $(LOCAL_PATH)/installation/comp/sdm/hsvdvbbat \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbfnt	\
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbfst \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbnit \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbsdt \
   		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbsgt \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbsi \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvsimplempeg \
			$(LOCAL_PATH)/installation/comp/sdm/hsvdvbsdm \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbcamnit \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbpostcode\
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbtot \
		    $(LOCAL_PATH)/installation/comp/util/hsvutil \
		    $(LOCAL_PATH)/installation/comp/util/hsvstrmwlk \
		    $(LOCAL_PATH)/installation/prod/euinstallermw \
		    $(TOP)/device/tpvision/common/plf/tvplayer/av/api/include \
	      	$(TOP)/device/tpvision/common/plf/tvplayer/av/include
 
 
 LOCAL_SRC_FILES :=   installation/comp/hsvdvbsdigiturk/src/hsvdvbsdigiturk_mSort.cpp\
			installation/comp/hsvdvbsdigiturk/src/hsvdvbsdigiturk_mAcq.cpp\
			installation/comp/hsvdvbsdigiturk/src/hsvdvbsdigiturk_mPow.cpp\
			installation/comp/hsvdvbsdigiturk/src/hsvdvbsdigiturk_mScan.cpp\
			installation/comp/hsvdvbsopprofile/src/hsvdvbsopprofile_mAcq.cpp\
			installation/comp/hsvdvbsopprofile/src/hsvdvbsopprofile_mScan.cpp\
			installation/comp/hsvdvbsopprofile/src/hsvdvbsopprofile_mSort.cpp\
			installation/comp/hsvdvbsfransat/src/hsvdvbsfransat_mAcq.cpp\
			installation/comp/hsvdvbsfransat/src/hsvdvbsfransat_mBckgnd.cpp\
			installation/comp/hsvdvbsfransat/src/hsvdvbsfransat_mSort.cpp\
			installation/comp/hsvdvbsfransat/src/hsvdvbsfransat_mScan.cpp\
			installation/comp/hsvdvbsm7/src/hsvdvbsm7_mSort.cpp\
			installation/comp/hsvdvbsm7/src/hsvdvbsm7_mAcq.cpp\
			installation/comp/hsvdvbsm7/src/hsvdvbsm7_mScan.cpp\
			installation/comp/hsvdvbscanal/src/hsvdvbscanal_mSort.cpp\
			installation/comp/hsvdvbscanal/src/hsvdvbscanal_mAcq.cpp\
			installation/comp/hsvdvbscanal/src/hsvdvbscanal_mScan.cpp\
			installation/comp/hsvdvbsrussia/src/hsvdvbsrussia_mSort.cpp\
			installation/comp/hsvdvbsrussia/src/hsvdvbsrussia_mAcq.cpp\
			installation/comp/hsvdvbsrussia/src/hsvdvbsrussia_mScan.cpp\
			installation/comp/hsvdvbstricolor/src/hsvdvbstricolor_mSort.cpp\
			installation/comp/hsvdvbstricolor/src/hsvdvbstricolor_mAcq.cpp\
			installation/comp/hsvdvbstricolor/src/hsvdvbstricolor_mScan.cpp\
			installation/comp/hsvdvbstricolor/src/hsvdvbstricolor_msettings.cpp\
			installation/comp/hsvdvbsn/src/hsvdvbsn_mSort.cpp\
			installation/comp/hsvdvbsn/src/hsvdvbsn_mScan.cpp\
			installation/comp/hsvdvbsn/src/hsvdvbsn_mAcq.cpp\
			installation/comp/hsvdvbspol/src/hsvdvbspol_mAcq.cpp\
			installation/comp/hsvdvbspol/src/hsvdvbspol_mSort.cpp\
			installation/comp/hsvdvbspol/src/hsvdvbspol_mScan.cpp\
			installation/comp/hsvdvbsfreesat/src/hsvdvbsfreesat_mAcq.cpp\
			installation/comp/hsvdvbsfreesat/src/hsvdvbsfreesat_mBckgnd.cpp\
			installation/comp/hsvdvbsfreesat/src/hsvdvbsfreesat_mScan.cpp\
			installation/comp/hsvdvbsfreesat/src/hsvdvbsfreesat_mSort.cpp\
			installation/comp/hsvdvbsfreesat/src/hsvdvbsfreesat_mSettings.cpp\
			installation/comp/hsvdvbsgeneric/src/hsvdvbsgeneric_mAcq.cpp\
			installation/comp/hsvdvbsgeneric/src/hsvdvbsgeneric_m.cpp\
			installation/comp/hsvdvbsgeneric/src/hsvdvbsgeneric_mSort.cpp\
			installation/comp/hsvdvbsgeneric/src/hsvdvbsgeneric_mScan.cpp\
			installation/comp/hsvdvbsgeneric/src/hsvdvbsgeneric_mBckgnd.cpp\
			installation/comp/hsvdvbsgeneric/src/hsvdvbsgeneric_mSrt.cpp\
			installation/comp/hsvdvbsins/src/hsvdvbsins_mprescan.cpp \
			installation/comp/hsvdvbsins/src/hsvdvbsins_msatipprescan.cpp \
			installation/comp/hsvdvbsins/src/hsvdvbsins_mpredefinedlistcopy.cpp \
			installation/comp/hsvdvbsins/src/hsvdvbsins_mutil.cpp \
			installation/comp/hsvdvbsins/src/hsvdvbsins_mprescanparser.cpp\
			installation/comp/hsvdvbsins/src/hsvdvbsins_mpow.cpp\
			installation/comp/hsvdvbsins/src/hsvdvbsins_mroute.cpp\
			installation/comp/hsvdvbsins/src/hsvdvbsins_m.cpp\
			installation/comp/hsvdvbsins/src/hsvdvbsins_mminiprescan.cpp \
			installation/comp/hsvdvbsins/src/hsvdvbsins_mpackageparser.cpp\
			installation/comp/hsvdvbsins/src/hsvdvbsins_mremovesat.cpp\
			installation/comp/hsvdvbsins/src/hsvdvbsins_msettings.cpp\
			installation/comp/hsvdvbsins/src/hsvdvbsins_msigstr.cpp\
			installation/comp/sdm/hsvdvbnit/src/hsvdvbnit_m.cpp\
			installation/comp/sdm/hsvdvbsdt/src/hsvdvbsdt_m.cpp\
			installation/comp/sdm/hsvdvbsgt/src/hsvdvbsgt_m.cpp\
			installation/comp/sdm/hsvdvbfnt/src/hsvdvbfnt_m.cpp\
			installation/comp/sdm/hsvdvbbat/src/hsvdvbbat_m.cpp\
			installation/comp/sdm/hsvdvbfst/src/hsvdvbfst_m.cpp\
			installation/comp/sdm/hsvdvbpostcode/src/hsvdvbpostcode_m.cpp\
			installation/comp/sdm/hsvdvbsi/src/hsvdvbsi_m.cpp\
			installation/comp/sdm/hsvdvbsi/src/hsvdvbsi_mtab.cpp\
			installation/comp/sdm/hsvdvbsi/src/hsvdvbsi_mdt.cpp\
			installation/comp/sdm/hsvsimplempeg/src/hsvsimplempeg_m.cpp\
			installation/comp/sdm/hsvdvbsdm/src/hsvdvbsdm_mstrapi.cpp\
			installation/comp/sdm/hsvdvbsdm/src/hsvdvbsdm_m.cpp\
			installation/comp/sdm/hsvdvbcamnit/src/hsvdvbcamnit_m.cpp\
			installation/comp/sdm/hsvdvbtot/src/hsvdvbtot_m.cpp\
			installation/comp/util/hsvutil/src/hsvutil_mwchar.cpp\
			installation/comp/util/hsvutil/src/hsvutil_gpimwchar.cpp\
			installation/comp/util/hsvutil/src/hsvutil_mhuffdec.cpp\
			installation/comp/hsvsatfe/src/hsvsatfe_msilabs.cpp\
			installation/comp/hsvpgdat/src/hsvpgdat_mpgdat.cpp\
			installation/comp/hsvpgdat/src/hsvpgdat_mpgdb.cpp\
			installation/comp/hsvpgdat/src/hsvpgdat_m.cpp\
			installation/comp/hsvdvbsastra/src/hsvdvbsastra_mScan.cpp\
			installation/comp/hsvdvbsastra/src/hsvdvbsastra_mAcq.cpp\
			installation/comp/hsvdvbsastra/src/hsvdvbsastra_mSort.cpp\
			installation/comp/hsvdvbsastra/src/hsvdvbsastra_mBckgnd.cpp\
			installation/prod/s2installermw/src/dvbsmw_mpow.cpp\
			src/satinstallerstub_mdummy.cpp\
			src/CS2Installer.cpp \
			src/SatInstallerJNI.cpp \
			src/SatInstaller.cpp 
			
LOCAL_LDLIBS := -llog 
LOCAL_LDLIBS += -landroid
LOCAL_SHARED_LIBRARIES := libTvMiddlewareCore-ndk-prebuilt \
						  libsqlite-ndk-prebuilt 
		
endif		
					

include $(BUILD_SHARED_LIBRARY)
