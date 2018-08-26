LOCAL_PATH := $(call my-dir)

ifneq ($(AOSP_BUILD_TC),)


include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_CERTIFICATE := platform
LOCAL_LDLIBS := -llog  
LOCAL_MODULE    := libtcinstallerjni

LOCAL_C_INCLUDES := bionic external/stlport/stlport  \
		    $(LOCAL_PATH)/inc/dd \
		    $(LOCAL_PATH)/inc/intf \
		    $(LOCAL_PATH)/inc \
		    $(TOP)/device/tpvision/common/plf/tvserver/common \
		    $(TOP)/external/sqlite/dist \
		    $(LOCAL_PATH)/installation/prod/euinstaller \
		    $(LOCAL_PATH)/installation/prod/euinstaller/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbtins \
		    $(LOCAL_PATH)/installation/comp/hsvdvbtins/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbcins \
		    $(LOCAL_PATH)/installation/comp/hsvdvbcins/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbcamins \
		    $(LOCAL_PATH)/installation/comp/hsvdvbcamins/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbtmpegins \
		    $(LOCAL_PATH)/installation/comp/hsvdvbtmpegins/src \
			$(LOCAL_PATH)/installation/comp/hsvacidec \
			$(LOCAL_PATH)/installation/comp/hsvprins \
			$(LOCAL_PATH)/installation/comp/svpaci \
			$(LOCAL_PATH)/installation/comp/svpats \
		    $(LOCAL_PATH)/installation/comp/hsveuins \
		    $(LOCAL_PATH)/installation/comp/hsveuins/src \
		    $(LOCAL_PATH)/installation/comp/hsvziggo \
		    $(LOCAL_PATH)/installation/comp/hsvziggo/src \
			$(LOCAL_PATH)/installation/comp/hsvcanaldigital \
		    $(LOCAL_PATH)/installation/comp/hsvcanaldigital/src \
		    $(LOCAL_PATH)/installation/comp/hsvfe \
		    $(LOCAL_PATH)/installation/comp/hsvfe/src \
		    $(LOCAL_PATH)/installation/comp/hsvpgdat/ \
		    $(LOCAL_PATH)/installation/comp/hsvpgdat/src \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbcamsdm \
	        $(LOCAL_PATH)/installation/comp/sdm/hsvdvbeit \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbsdm	\
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbsi \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbtdt \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbtot \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvmpeg \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbsdt \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbnit \
		    $(LOCAL_PATH)/installation/comp/util/hsvutil \
		    $(LOCAL_PATH)/installation/prod/euinstallermw \
		    $(TOP)/device/tpvision/common/plf/tvplayer/av/api/include \
	      	    $(TOP)/device/tpvision/common/plf/tvplayer/av/include \
                    $(TOP)/device/tpvision/common/plf/tvserver/common \
                    $(TOP)/device/tpvision/common/plf/tvserver/TvMw/inc/intf\
 $(TOP)/device/tpvision/common/app/txt/jni/txtMiddleware/inc/intf\
  $(TOP)/device/tpvision/common/app/txt/jni/txtMiddleware/inc/dd
 
 LOCAL_SRC_FILES :=  installation/comp/sdm/hsvdvbsdt/src/hsvdvbsdt_m.cpp \
		     installation/comp/hsvziggo/src/hsvziggo_mBackground.cpp \
		     installation/comp/sdm/hsvdvbnit/src/hsvdvbnit_m.cpp \
		     installation/comp/hsvziggo/src/hsvziggo_mDtr.cpp \
		     installation/comp/hsvziggo/src/hsvziggo_mInstall.cpp \
		     installation/comp/hsvziggo/src/hsvziggo_mPreInstall.cpp \
		     installation/comp/hsvziggo/src/hsvziggo_mRoute.cpp \
			 installation/comp/hsvcanaldigital/src/hsvcanaldigital_mDtr.cpp \
		     installation/comp/hsvcanaldigital/src/hsvcanaldigital_mInstall.cpp \
		     installation/comp/hsvcanaldigital/src/hsvcanaldigital_mPreInstall.cpp \
		     installation/comp/hsvcanaldigital/src/hsvcanaldigital_mRoute.cpp \
			 installation/comp/hsvcanaldigital/src/hsvcanaldigital_mBackground.cpp \
		     installation/comp/hsvfe/src/hsvfe_m.cpp \
		     installation/comp/hsveuins/src/hsveuins_mconflicts.cpp \
		     installation/comp/hsveuins/src/hsveuins_mDbookConflicts.cpp \
		     installation/comp/hsveuins/src/hsveuins_mDbookSort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mfinsort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mfreqctl.cpp \
		     installation/comp/hsveuins/src/hsveuins_mitasort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mlitesort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mnorsort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mpegsort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mpow.cpp \
		     installation/comp/hsveuins/src/hsveuins_mroute.cpp \
		     installation/comp/hsveuins/src/hsveuins_msigstr.cpp \
		     installation/comp/hsveuins/src/hsveuins_msort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mSortRoute.cpp \
		     installation/comp/hsveuins/src/hsveuins_msysctl.cpp \
		     installation/comp/hsveuins/src/hsveuins_mcabsort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mcamsort.cpp \
		     installation/comp/hsveuins/src/hsveuins_madvpgitr.cpp \
		     installation/comp/hsveuins/src/hsveuins_mapmeasort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mhungarysort.cpp \
 		     installation/comp/hsveuins/src/hsveuins_mblizoosort.cpp \
		     installation/comp/hsveuins/src/hsveuins_m.cpp	\
		     installation/comp/hsvdvbtmpegins/src/hsvdvbtmpegins_m.cpp \
		     installation/comp/hsvdvbtmpegins/src/hsvdvbtmpegins_mdigacq.cpp \
		     installation/comp/hsvdvbcins/src/hsvdvbcins_m.cpp \
		     installation/comp/hsvdvbcins/src/hsvdvbcins_msettings.cpp \
		     installation/comp/hsvdvbcins/src/hsvdvbcins_mquick.cpp \
		     installation/comp/hsvdvbcins/src/hsvdvbcins_mprescan.cpp \
		     installation/comp/hsvdvbcins/src/hsvdvbcins_mgrid.cpp \
		     installation/comp/hsvdvbcins/src/hsvdvbcins_mfull.cpp \
		     installation/comp/hsvdvbtins/src/hsvdvbtins_mBackground.cpp \
		     installation/comp/hsvdvbtins/src/hsvdvbtins_mcountry.cpp \
		     installation/comp/hsvdvbtins/src/hsvdvbtins_mRoute.cpp \
		     installation/comp/hsvdvbtins/src/hsvdvbtins_msettings.cpp \
		     installation/comp/hsvdvbtins/src/hsvdvbtins_mQuick.cpp \
		     installation/comp/hsvdvbtins/src/hsvdvbtins_mDtr.cpp \
		     installation/comp/hsvdvbtins/src/hsvdvbtins_mFull.cpp \
		     installation/comp/hsvdvbcamins/src/hsvdvbcamins_mScan.cpp \
		     installation/comp/hsvdvbcamins/src/hsvdvbcamins_mSettings.cpp \
		     installation/comp/hsvpgdat/src/hsvpgdat_m.cpp \
		     installation/comp/hsvpgdat/src/hsvpgdat_mpgdat.cpp \
		     installation/comp/hsvpgdat/src/hsvpgdat_mpgdb.cpp \
		     installation/prod/euinstallermw/src/euinsmw_mpow.cpp \
		     installation/comp/util/hsvutil/src/hsvutil_gpimwchar.cpp \
		     installation/comp/util/hsvutil/src/hsvutil_mhuffdec.cpp \
		     installation/comp/util/hsvutil/src/hsvutil_mwchar.cpp \
		     installation/comp/sdm/hsvdvbsi/src/hsvdvbsi_mdt.cpp \
		     installation/comp/sdm/hsvdvbsi/src/hsvdvbsi_mtab.cpp \
		     installation/comp/sdm/hsvdvbsi/src/hsvdvbsi_m.cpp \
		     installation/comp/sdm/hsvdvbeit/src/hsvdvbeit_m.cpp \
		     installation/comp/sdm/hsvdvbcamsdm/src/hsvdvbcamsdm_m.cpp \
		     installation/comp/sdm/hsvdvbtdt/src/hsvdvbtdt_m.cpp \
		     installation/comp/sdm/hsvmpeg/src/hsvmpeg_m.cpp \
		     installation/comp/sdm/hsvdvbtot/src/hsvdvbtot_m.cpp \
		     installation/comp/hsvziggo/src/hsvziggo_mDataAcq.cpp \
			 installation/comp/hsvcanaldigital/src/hsvcanaldigital_mDataAcq.cpp \
		     installation/comp/hsvdvbcins/src/hsvdvbcins_mDataAcq.cpp \
		     installation/comp/hsvdvbtins/src/hsvdvbtins_mDataAcq.cpp \
		     installation/comp/hsvdvbcamins/src/hsvdvbcamins_mDataAcq.cpp \
		     installation/comp/sdm/hsvdvbsdm/src/hsvdvbsdm_m.cpp	\
		     installation/comp/sdm/hsvdvbsdm/src/hsvdvbsdm_mstrapi.cpp \
			 installation/comp/hsveuins/src/hsveuins_mstub.cpp \
			 installation/comp/hsveuins/src/hsveuins_mdiv.cpp \
			 installation/comp/hsveuins/src/hsveuins_macids.cpp \
			 installation/comp/hsveuins/src/hsveuins_msysset.cpp \
			 installation/comp/hsvprins/src/hsvprins_m.cpp \
			 installation/comp/hsvprins/src/hsvprins_maci.cpp \
			 installation/comp/hsvprins/src/hsvprins_msettings.cpp \
			 installation/comp/hsvacidec/src/hsvacidec_m.cpp \
			 installation/comp/svpaci/src/svpaci_m.cpp \
			 installation/comp/svpaci/src/svpaci_mdiv.cpp \
			 installation/comp/svpats/src/svpats_m.cpp \
		     ./src/euinsstub_mdummy.cpp \
			 ./src/euinsstub_mtxtstub.cpp \
		     ./src/CTvInstallTC.cpp \
		     ./src/NativeEuInstallerJNI.cpp \
			 ./src/CTCLogger.cpp \
		     ./src/NativeEuInstaller.cpp 
			 
					
LOCAL_CFLAGS := -DAOSP_BUILD_TC
LOCAL_SHARED_LIBRARIES := libTvMiddlewareCore libutils libstlport libbinder libcutils libsqlite libandroid libandroid_runtime libtvplayerps
LOCAL_STATIC_LIBRARIES := libtxtlegacy

else
LOCAL_PATH := $(NDK_ROOT)
include $(CLEAR_VARS)
LOCAL_MODULE := libsqlite-ndk-prebuilt  
LOCAL_SRC_FILES := ../../../TPVision_NDK_Addons\android-ndk-r8d\lib\libsqlite.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libTvMiddlewareCore-ndk-prebuilt
LOCAL_SRC_FILES := ../../../TPVision_NDK_Addons\android-ndk-r8d\lib\libTvMiddlewareCore.so  
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)

LOCAL_PATH := ./jni

LOCAL_MODULE_TAGS := optional
LOCAL_CERTIFICATE := platform
LOCAL_MODULE := libtcinstallerjni

LOCAL_C_INCLUDES := bionic external/stlport/stlport  \
		    $(LOCAL_PATH)/inc/dd \
		    $(LOCAL_PATH)/inc/intf \
		    $(LOCAL_PATH)/inc \
		    $(TOP)/device/tpvision/common/plf/tvserver/common \
		    $(TOP)/external/sqlite/dist \
		    $(LOCAL_PATH)/installation/prod/euinstaller \
		    $(LOCAL_PATH)/installation/prod/euinstaller/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbtins \
		    $(LOCAL_PATH)/installation/comp/hsvdvbtins/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbcins \
		    $(LOCAL_PATH)/installation/comp/hsvdvbcins/src \
		    $(LOCAL_PATH)/installation/comp/hsvdvbtmpegins \
		    $(LOCAL_PATH)/installation/comp/hsvdvbtmpegins/src \
		    $(LOCAL_PATH)/installation/comp/hsveuins \
		    $(LOCAL_PATH)/installation/comp/hsveuins/src \
		    $(LOCAL_PATH)/installation/comp/hsvziggo \
		    $(LOCAL_PATH)/installation/comp/hsvziggo/src \
		    $(LOCAL_PATH)/installation/comp/hsvcanaldigital \
		    $(LOCAL_PATH)/installation/comp/hsvcanaldigital/src \
		    $(LOCAL_PATH)/installation/comp/hsvfe \
		    $(LOCAL_PATH)/installation/comp/hsvfe/src \
		    $(LOCAL_PATH)/installation/comp/hsvpgdat/ \
		    $(LOCAL_PATH)/installation/comp/hsvpgdat/src \
	        $(LOCAL_PATH)/installation/comp/sdm/hsvdvbeit \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbsdm	\
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbsi \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbtdt \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbtot \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvmpeg \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbsdt \
		    $(LOCAL_PATH)/installation/comp/sdm/hsvdvbnit \
		    $(LOCAL_PATH)/installation/comp/util/hsvutil \
		    $(LOCAL_PATH)/installation/prod/euinstallermw \
		    $(TOP)/device/tpvision/common/plf/tvplayer/av/api/include \
	      	$(TOP)/device/tpvision/common/plf/tvplayer/av/include \
	      	$(LOCAL_PATH)/installation/comp/hsvacidec \
	      	$(LOCAL_PATH)/installation/comp/hsvprins \
	      	$(LOCAL_PATH)/installation/comp/svpaci \
	      	$(LOCAL_PATH)/installation/comp/svpats
	      	
		    
 LOCAL_SRC_FILES := installation/comp/sdm/hsvdvbsdt/src/hsvdvbsdt_m.cpp \
		     installation/comp/hsvziggo/src/hsvziggo_mBackground.cpp \
			 installation/comp/hsvcanaldigital/src/hsvcanaldigital_mBackground.cpp \
		     installation/comp/sdm/hsvdvbnit/src/hsvdvbnit_m.cpp \
		     installation/comp/hsvziggo/src/hsvziggo_mDtr.cpp \
		     installation/comp/hsvziggo/src/hsvziggo_mInstall.cpp \
		     installation/comp/hsvziggo/src/hsvziggo_mPreInstall.cpp \
		     installation/comp/hsvziggo/src/hsvziggo_mRoute.cpp \
			 installation/comp/hsvcanaldigital/src/hsvcanaldigital_mDtr.cpp \
		     installation/comp/hsvcanaldigital/src/hsvcanaldigital_mInstall.cpp \
		     installation/comp/hsvcanaldigital/src/hsvcanaldigital_mPreInstall.cpp \
		     installation/comp/hsvcanaldigital/src/hsvcanaldigital_mRoute.cpp \
		     installation/comp/hsvfe/src/hsvfe_m.cpp \
		     installation/comp/hsveuins/src/hsveuins_mconflicts.cpp \
		     installation/comp/hsveuins/src/hsveuins_mDbookConflicts.cpp \
		     installation/comp/hsveuins/src/hsveuins_mDbookSort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mfinsort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mfreqctl.cpp \
		     installation/comp/hsveuins/src/hsveuins_mitasort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mlitesort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mnorsort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mpegsort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mpow.cpp \
		     installation/comp/hsveuins/src/hsveuins_mroute.cpp \
		     installation/comp/hsveuins/src/hsveuins_msigstr.cpp \
		     installation/comp/hsveuins/src/hsveuins_msort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mSortRoute.cpp \
		     installation/comp/hsveuins/src/hsveuins_msysctl.cpp \
		     installation/comp/hsveuins/src/hsveuins_mcabsort.cpp \
		     installation/comp/hsveuins/src/hsveuins_madvpgitr.cpp \
		     installation/comp/hsveuins/src/hsveuins_mapmeasort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mhungarysort.cpp \
		     installation/comp/hsveuins/src/hsveuins_mblizoosort.cpp \
		     installation/comp/hsveuins/src/hsveuins_m.cpp	\
		     installation/comp/hsvdvbtmpegins/src/hsvdvbtmpegins_m.cpp \
		     installation/comp/hsvdvbtmpegins/src/hsvdvbtmpegins_mdigacq.cpp \
		     installation/comp/hsvdvbcins/src/hsvdvbcins_m.cpp \
		     installation/comp/hsvdvbcins/src/hsvdvbcins_msettings.cpp \
		     installation/comp/hsvdvbcins/src/hsvdvbcins_mquick.cpp \
		     installation/comp/hsvdvbcins/src/hsvdvbcins_mprescan.cpp \
		     installation/comp/hsvdvbcins/src/hsvdvbcins_mgrid.cpp \
		     installation/comp/hsvdvbcins/src/hsvdvbcins_mfull.cpp \
		     installation/comp/hsvdvbtins/src/hsvdvbtins_mBackground.cpp \
		     installation/comp/hsvdvbtins/src/hsvdvbtins_mcountry.cpp \
		     installation/comp/hsvdvbtins/src/hsvdvbtins_mRoute.cpp \
		     installation/comp/hsvdvbtins/src/hsvdvbtins_msettings.cpp \
		     installation/comp/hsvdvbtins/src/hsvdvbtins_mQuick.cpp \
		     installation/comp/hsvdvbtins/src/hsvdvbtins_mDtr.cpp \
		     installation/comp/hsvdvbtins/src/hsvdvbtins_mFull.cpp \
		     installation/comp/hsvpgdat/src/hsvpgdat_m.cpp \
		     installation/comp/hsvpgdat/src/hsvpgdat_mpgdat.cpp \
		     installation/comp/hsvpgdat/src/hsvpgdat_mpgdb.cpp \
		     installation/prod/euinstallermw/src/euinsmw_mpow.cpp \
		     installation/comp/util/hsvutil/src/hsvutil_gpimwchar.cpp \
		     installation/comp/util/hsvutil/src/hsvutil_mhuffdec.cpp \
		     installation/comp/util/hsvutil/src/hsvutil_mwchar.cpp \
		     installation/comp/sdm/hsvdvbsi/src/hsvdvbsi_mdt.cpp \
		     installation/comp/sdm/hsvdvbsi/src/hsvdvbsi_mtab.cpp \
		     installation/comp/sdm/hsvdvbsi/src/hsvdvbsi_m.cpp \
		     installation/comp/sdm/hsvdvbeit/src/hsvdvbeit_m.cpp \
		     installation/comp/sdm/hsvdvbtdt/src/hsvdvbtdt_m.cpp \
		     installation/comp/sdm/hsvmpeg/src/hsvmpeg_m.cpp \
		     installation/comp/sdm/hsvdvbtot/src/hsvdvbtot_m.cpp \
		     installation/comp/hsvziggo/src/hsvziggo_mDataAcq.cpp \
			 installation/comp/hsvcanaldigital/src/hsvcanaldigital_mDataAcq.cpp \
		     installation/comp/hsvdvbcins/src/hsvdvbcins_mDataAcq.cpp \
		     installation/comp/hsvdvbtins/src/hsvdvbtins_mDataAcq.cpp \
		     installation/comp/sdm/hsvdvbsdm/src/hsvdvbsdm_m.cpp	\
		     installation/comp/sdm/hsvdvbsdm/src/hsvdvbsdm_mstrapi.cpp \
			 installation/comp/hsveuins/src/hsveuins_mstub.cpp \
			 installation/comp/hsveuins/src/hsveuins_mdiv.cpp \
			 installation/comp/hsveuins/src/hsveuins_macids.cpp \
			 installation/comp/hsveuins/src/hsveuins_msysset.cpp \
			 installation/comp/hsvprins/src/hsvprins_m.cpp \
			 installation/comp/hsvprins/src/hsvprins_maci.cpp \
			 installation/comp/hsvprins/src/hsvprins_msettings.cpp \
			 installation/comp/hsvacidec/src/hsvacidec_m.cpp \
			 installation/comp/svpaci/src/svpaci_m.cpp \
			 installation/comp/svpaci/src/svpaci_mdiv.cpp \
			 installation/comp/svpats/src/svpats_m.cpp \
		     ./src/euinsstub_mdummy.cpp \
			 ./src/euinsstub_mtxtstub.cpp \
		     ./src/CTvInstallTC.cpp \
		     ./src/NativeEuInstallerJNI.cpp \
		     ./src/NativeEuInstaller.cpp 

LOCAL_LDLIBS := -llog 
LOCAL_SHARED_LIBRARIES := libTvMiddlewareCore-ndk-prebuilt \
                          libsqlite-ndk-prebuilt 

endif		
					

include $(BUILD_SHARED_LIBRARY)
