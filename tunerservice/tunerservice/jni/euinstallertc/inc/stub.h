#ifdef __cplusplus
extern "C" {
#endif
typedef unsigned int Nat32;
typedef unsigned short Nat16;
typedef unsigned char Nat8;

int cpp_log(const char *fmt, ...);
extern Nat32 hsvtxt__pow_Init(void);
extern void hsvtxt__pow_TurnOn();
extern void hsvtxt__pow_TurnOff();
extern Bool cpp_txbcs__p830_GetPilCode( Nat32 * ptr_pil_code );
extern int txbcs__vps_RequestDataFields( Nat8 field_bit_vector, VpsCbFn cb_fn, Bool cb_on_every_update );
extern void txbcs__vps_UnRequestDataFields ( int request_id );
extern void cpp_ponN_OnPonChanged( void );
extern void cpp_wnavN_OnExitHypertext ( void );
extern void cpp_wsrN_OnSearchPage( PageNr page_in_search );
extern void cpp_wsrN_OnStartSearchInTransmission( void );
extern void cpp_wsrN_OnEndOfSearch( Bool word_found );
extern void cpp_pctlN_OnPageArrived( PageNr pg, Subcode subcd );
extern void cpp_pctlN_OnPageArrived     ( PageNr pg, Subcode subcd );
extern void cpp_pctlN_OnPageDropped     ( PageNr pg );
extern void cpp_pctlN_OnSubcodeArrived  ( Subcode subcd );
extern void cpp_pctlN_OnPageDisplayed   ( PageNr pg );
extern void cpp_tranN_OnTransmissionChanged (void) ;
extern void cpp_topN_OnTopUpdate( Nat16 notify );
extern STimer cpp_tmr_Create   ( Function ntf );
extern void   cpp_tmr_FireOnce ( STimer tmr, Int32 seconds);
extern void cpp_tmr_FireEvery( STimer tmr, Int32 seconds);
extern void   cpp_tmr_Cancel   ( STimer tmr);
extern void   cpp_tmr_Delete   ( STimer tmr);
extern Bool   cpp_tmr_State    ( STimer tmr, Int32 * remaining, Int32 * reload );
extern Semaphore cpp_rtk_SemCreate( void );
extern void cpp_rtk_SemDelete( Semaphore sem );
extern void cpp_rtk_SemAcquire( Semaphore sem );
extern void cpp_rtk_SemRelease( Semaphore sem );
extern Bool cpp_rtk_SemAcquireNoWait( Semaphore sem );
extern void cpp_SetClock(int Time);
extern int cpp_sysset_GetMenuLanguage(void );
extern int cpp_sysset_GetInstallCountry(void);
extern Pump cpp_pmp_PmpCreateEx ( PumpEngine pen, PumpFunc func, Bool replace, char* name );
extern void       cpp_pmp_PmpSend     ( Pump pmp, int param1, Nat32 param2 );
extern void       cpp_pmp_PmpSendAfter( Pump pmp, int param1, Nat32 param2, int msecs );
extern Bool       cpp_pmp_PenTaskHasLock( PumpEngine pen );

extern FResult cpp_gfxacc3_Register(int gfxclientId,Nat32 buffWidth,Nat32 buffHeight,
		Nat32 buffFmtClass,Nat32 buffFmtType,Nat32 clutSize,Nat8 backBuffers,
		int colorKey,Nat32 clearColor,int srfHnd);
extern FResult cpp_gfxacc3_UnRegister(int gfxclientId);
extern FResult cpp_gfxacc3_GetPlaneId(int gfxclientId,int * pPlaneId);
extern FResult cpp_gfxacc3_GetSurfaceHnd(int gfxclientId,int * pSrfHnd);
extern FResult cpp_gfxacc3_GetClutHnd(int gfxclientId,int * pClutHnd);
extern FResult cpp_gfxacc3_ScreenUpdate(int gfxclientId,Bool partial,int ul_x,int ul_y,
		int lr_x,int lr_y);
extern FResult cpp_gfxacc3_GetWindowId(int gfxclientId,Nat32 * pwndId);
extern FResult cpp_gfxacc3_RequestFocus(int gfxclientId);
extern FResult cpp_gfxacc3_SetVisibility(int gfxclientId,Bool visible);
extern FResult cpp_gfxacc3_GetVisiblity(int gfxclientId,Bool * pVisibility);
extern FResult cpp_gfxacc3_ScreenUpdateNoNotify(int gfxclientId,Bool partial,int ul_x,
		int ul_y,int lr_x,int lr_y);
extern FResult cpp_gfxacc3_GetDfbParams(int gfxclientId,Address * dfb_ptr,
		Address * Surface);
extern FResult cpp_gfxacc3_GetDfbParamsEx(int gfxclientId,Address * dfb_ptr,
		Address * Surface,Address * DFbWindow);
extern FResult cpp_gfxacc3_ClearSurface(Nat8 r,Nat8 g,Nat8 b,Nat8 a);
extern FResult cpp_gfxacc3_EnableMouseCursor(int gfxclientId,int cursorId,Bool enable);

extern FResult cpp_gfxsrf_CreateSurface(Nat32 PixClass,Nat32 PixType,Nat32 Width,
		Nat32 Height,Nat32 Stride,int BackBuffers,Nat8 MemType,int * pSrfHnd,
		Address * pBufferptrList);
extern  FResult cpp_gfxsrf_GetSurfaceAttributes(int srfHnd,Nat32 * PixClass,
		Nat32 * PixType,Nat32 * Width,Nat32 * Height,Nat32 * Stride,
		int * BackBuffers,Nat8 * MemType);
extern FResult cpp_gfxsrf_GetBufferAddress(int buffHnd,Address * pBuffAdd);
extern  FResult cpp_gfxsrf_DestroySurface(int srfHnd);
extern  FResult cpp_gfxsrf_Lock(int srfHnd,Nat8 BufferId,int * pBuffHnd);
extern FResult cpp_gfxsrf_UnLock(int * pbuffHnd);
extern  FResult cpp_gfxsrf_Flip(int srfHnd,FunctionIntInt FlipCallBack,Nat32 cookie);
extern FResult cpp_gfxsrf_FlipNoNotify(int srfHnd,FunctionIntInt FlipCallBack,Nat32 cookie);
extern FResult cpp_gfxsrf_Blit(int srcbuff,int src_ul_x,int src_ul_y,int src_lr_x,
		int src_lr_y,int dstbuff,int dst_ul_x,int dst_ul_y,int dst_lr_x,
		int dst_lr_y,FunctionIntInt BlitCallBack,Nat32 cookie);
extern FResult cpp_gfxsrf_CopyBlit(int srcbuffHnd,int src_rec_x,int src_rec_y,
		int src_rec_w,int src_rec_h,int dstbuffHnd,int dst_rec_x,
		int dst_rec_y,FunctionIntInt BlitCallBack,Nat32 cookie);
extern FResult cpp_gfxsrf_SetDirtyRectangle(int srfHnd,Bool partial,int ul_x,int ul_y,
		int lr_x,int lr_y);
extern  Bool cpp_gfxsrf_IsCopyBlitSupported(void);
extern FResult cpp_gfxsrf_SetClut(int srfHnd,int clutHnd);
extern FResult cpp_gfxsrf_GetClut(int srfHnd,int * pClutHnd);
extern Nat32 cpp_gfxsrf_GetPixClass(int srfHnd);
extern Nat32 cpp_gfxsrf_GetPixType(int srfHnd);
extern  Nat32 cpp_gfxsrf_GetWidth(int srfHnd);
extern Nat32 cpp_gfxsrf_GetHeight(int srfHnd);
extern Nat32 cpp_gfxsrf_GetStride(int srfHnd);
extern int cpp_gfxsrf_GetNoOfBackBuffers(int srfHnd);
extern Nat8 cpp_gfxsrf_GetMemoryType(int srfHnd);
extern FResult cpp_gfxsrf_Set3DGfxOption(int gfxclientId,int value);


extern FResult cpp_gfxpln_GetBgSupported(int planeId,Bool * pbgSupp);
extern FResult cpp_gfxpln_SetBgColor(int planeId,Nat32 bgcolor);
extern FResult cpp_gfxpln_GetBgColor(int planeId,Nat32 * pbgColor);
extern FResult cpp_gfxpln_SetVisibility(int planeId,Bool visible);
extern FResult cpp_gfxpln_GetVisiblity(int planeId,Bool * pVisibility);
extern FResult cpp_gfxpln_GetBlendFactorRange(int planeId,Nat32 * pMinBlendFactor,
		Nat32 * pMaxBlendFactor);
extern FResult cpp_gfxpln_GetBlendFactorRangeGetBlendFactor(int planeId,Nat32 * pblendFactor);
extern FResult cpp_gfxpln_SetBlendFactor(int planeId,Nat32 blendFactor);
extern FResult cpp_gfxpln_SetPlaneSizeAndPosition(int planeId,Nat32 width,
		Nat32 height,int posX,int posY);
extern FResult cpp_gfxpln_GetPlaneSizeAndPosition(int planeId,Nat32 * pWidth,
		Nat32 * pHeight,int * pPosX,int * pPosY);
extern FResult cpp_gfxpln_GetMinimumPlaneSize(int planeId,Nat32 * pWidth,Nat32 * pHeight);
extern FResult cpp_gfxpln_GetMaximumPlaneSize(int planeId,Nat32 * pWidth,Nat32 * pHeight);
extern FResult cpp_gfxpln_GetMinimumViewRegionSize(int planeId,Nat32 * pWidth,
		Nat32 * pHeight);
extern FResult cpp_gfxpln_SetDstViewRegionSizeAndPosition(int planeId,
		Nat32 width,Nat32 Height,int posX,int posY);
extern FResult cpp_gfxpln_GetDstViewRegionSizeAndPosition(int planeId,
		Nat32 * pWidth,Nat32 * pHeight,int * pPosX,int * pPosY);
extern FResult cpp_gfxpln_SetSrcViewRegionSizeAndPosition(int planeId,
		Nat32 width,Nat32 height,int posX,int posY);
extern FResult cpp_gfxpln_GetSrcViewRegionSizeAndPosition(int planeId,
		Nat32 * pWidth,Nat32 * pHeight,int * pPosX,int * pPosY);
extern FResult cpp_gfxpln_GetSupportedScaleModes(int planeId,Nat32 * pScaleModes);
extern FResult cpp_gfxpln_GetScaleRange(int planeId,Nat32 scaleMode,
		Nat32 * pMinWidthPercentage,Nat32 * pMinHeightPercentage,
		Nat32 * pMaxWidthPercentage,Nat32 * pMaxHeigthPercentage);
extern FResult cpp_gfxpln_SetScaleMode(int planeId,Nat32 scaleMode);
extern FResult cpp_gfxpln_GetScaleMode(int planeId,Nat32 * pScaleMode);
extern FResult cpp_gfxpln_GetPanoramaMidScaleRange(int planeId,
		Nat32 * pMinMidScaleFactor,Nat32 * pMaxMidScaleFactor);
extern FResult cpp_gfxpln_SetPanoramaMidScaleFactor(int planeId,
		Nat32 MidScaleFactor);
extern FResult cpp_gfxpln_GetPanoramaMidScaleFactor(int planeId,
		Nat32 * pMidScaleFactor);
extern FResult cpp_gfxpln_GetSupportedFormatClasses(int planeId,
		Nat32 * pFmtClass);
extern FResult cpp_gfxpln_GetSupportedFormatTypes(int planeId,Nat32 fmtclass,
		Nat32 * pFmtType);
extern FResult cpp_gfxpln_GetSupportedNumberOfColorKeys(int planeId,Nat32 * pNoOfKeys);
extern FResult cpp_gfxpln_GetSupportedColorKeyTypes(int planeId,Nat32 * pkeyTypes);
extern FResult cpp_gfxpln_SetColorKey(int planeId,Nat32 keyNr,Nat32 keytype,
		Nat32 lowerColor,Nat32 UpperColor);
extern FResult cpp_gfxpln_GetColorKey(int planeId,Nat32 keyNr,Nat32 * pkeytype,
		Nat32 * plowerColor,Nat32 * pUpperColor);
extern FResult cpp_gfxpln_SetColorKeyActivation(int planeId,Nat32 keyNr,Bool enable);
extern FResult cpp_gfxpln_GetColorKeyActivation(int planeId,Nat32 keyNr,Bool * actStatus);
extern FResult cpp_gfxpln_AttachSurface(int planeId,int srfHnd);
extern FResult cpp_gfxpln_DetachSurface(int planeId,int srfHnd);
extern FResult cpp_gfxpln_GetAlignment(int planeId,Nat32 * palign);
extern FResult cpp_gfxpln_SetTransitionParameters(int planeId,Nat32 msec);
extern FResult cpp_gfxpln_gfxpln_Lock(int planeId,int * pLockId);
extern FResult cpp_gfxpln_gfxpln_UnLock(int planeId,int lockId);
extern FResult cpp_gfxpln_RegisterCallBack(int planeId,FunctionIntInt fn,Nat32 cookie);
extern FResult cpp_gfxpln_PlaneUpdate(int planeId);
extern void LockLayerBuffer(int planeId);
extern void cpp_gfxpln_UnlockLayerBuffer(int planeId);
extern void cpp_gfxpln_SetLayerFormat(int planeId,Nat32 fmtclass,Nat32 fmttype);
extern void cpp_gfxpln_GetLayerFormat(int planeId,Nat32 * pfmtclass,Nat32 * pfmttype);
extern Bool cpp_gfxpln_IsLayerModeSupported(int planeId,Nat32 layermode);
extern FResult cpp_gfxpln_SetGraphicLayerMode(int planeId,Nat32 layermode);
extern Nat32 cpp_gfxpln_GetGraphicLayerMode(int planeId);
extern void cpp_gfxpln_LockLayerBuffer(int planeId);
extern void cpp_gfxpln_UnlockLayerBuffer(int planeId);
extern	 FResult cpp_gfxpln_Lock(int planeId,int * pLockId);
extern FResult cpp_gfxpln_UnLock(int planeId,int lockId);
extern     	 FResult cpp_gfxpln_GetBlendFactor(int planeId,Nat32 * pblendFactor);
extern Bool cpp_GetNvmLevel25Processing(void);
extern 	 int cpp_vbisl_SetSlicermode(int winid,Nat32 subscriptions,Nat32 * retval);
extern  int cpp_vbisl_EnableAutoSlicing(int winid,Bool enable,Nat32 * retval);
/* Function prototypes */
extern int txbcs__div_RollHdrUpdateFreq;
extern void stub__pmp_PmpSend( Pump pmp, int param1, Nat32 param2 );
extern int txbcs__div_RollHdrBgCol;
extern void * txbcs__div_PacketPoolStart;
extern Bool stub__rtk_SemAcquireNoWait( Semaphore sem );
extern int stub__rtk_PrioNormal;
extern int txbcs__div_RollHdrFgCol;
extern int txbcs__div_MaxDrcsTypeBlocks;
extern Bool txbcs__p830_GetPilCode( PilCode * ptr_pil_code );
extern Bool txbcs__p830_GetStatusMessage( String msg_string );
extern Semaphore stub__rtk_SemCreate( void );
extern int txbcs__div_SemCeilingPriority;
extern int txbcs__div_MaxConcealTypeBlocks;
extern Pump stub__pmp_PmpCreateEx( PumpEngine pen, PumpFunc func, Bool replace, char * name );
extern Bool stub__pmp_PenTaskHasLock( PumpEngine pen );
extern int txbcs__p830_RequestDataFields( Nat16 field_bit_vector, Packet830CbFn cb_fn, Bool cb_on_every_update );
extern void stub__pmp_PmpSendAfter( Pump pmp, int param1, Nat32 param2, int msecs );
extern Bool txbcs__p830_GetProgramType( Nat8 * ptr_ptype );
extern Bool txbcs__p830_GetUTCDate( Mjd * ptr_mjd );
extern void stub__rtk_SemAcquire( Semaphore sem );
extern Bool txbcs__p830_GetCountryNetworkIdentificationCode( Nat16 * ptr_cni );
extern Bool txbcs__p830_GetNetworkIdentificationCode( Nat16 * ptr_ni );
extern void txbcs__p830_UnRequestDataFields( int request_id );
extern int stub__rtk_PrioHighest;
extern int stub__rtk_PrioLowest;
extern int stub__rtk_PrioAboveNormal;
extern int stub__rtk_PrioHigh;
extern int txbcs__div_RollTimeUpdateFreq;
extern int stub__rtk_PrioLow;
extern Nat32 txbcs__div_PacketPoolSize;
extern Bool txbcs__p830_GetLabelInfo( LabelInfo * ptr_li );
extern void stub__rtk_SemRelease( Semaphore sem );
extern Nat32 txbcs__div_BundleDataBufferSize;
extern void stub__rtk_SemDelete( Semaphore sem );
extern int txbcs__div_MaxCallBacks;
extern int stub__rtk_PrioBelowNormal;
extern int txbcs__div_MaxWinTypeBlocks;
extern void * txbcs__div_PacketPoolBase;
extern Bool txbcs__p830_GetTimeOffset( Int8 * ptr_time_offset );
extern PumpEngine stub__high_PumpEngine;
extern void txbcs__p830N_OnPacket830( Nat8 * received_buffer );
extern Bool txbcs__p830_GetUTCTime( Time * ptr_time );
extern Nat8 * txbcs__div_BundleDataBufferBase;
extern Nat8 txbcs__div_MaxAitPages;
extern Bool txbcs__p830_GetInitialPage( PageNr * ptr_pn, Subcode * ptr_sc );
extern Bool txbcs__p830_IsDataFieldsAvailable( Nat16 field_bit_vector );
extern int txbcs__div_MaxOpenPages;
extern Bool txbcs__p830_GetProgramControlInfo( ProgramControlInfo * ptr_pci );
extern int txbcs__div_iVersion;

/* Function prototypes */
extern int txbcs__div_RollHdrBgCol;
extern void * txbcs__div_PacketPoolStart;
extern Bool stub__rtk_SemAcquireNoWait( Semaphore sem );
extern int stub__rtk_PrioNormal;
extern Bool txbcs__vps_GetCountryNetworkIdentificationCode( Nat16 * ptr_cni );
extern int txbcs__div_MaxDrcsTypeBlocks;
extern int txbcs__vps_RequestDataFields( Nat8 field_bit_vector, VpsCbFn cb_fn, Bool cb_on_every_update );
extern Semaphore stub__rtk_SemCreate( void );
extern int txbcs__div_MaxConcealTypeBlocks;
extern Bool txbcs__vps_GetDistinctionBits( Nat8 * ptr_dist_bits );
extern void stub__rtk_SemAcquire( Semaphore sem );
extern void txbcs__vpsN_OnEnd( void );
extern void txbcs__vps_UnRequestDataFields( int request_id );
extern int stub__rtk_PrioHighest;
extern int stub__rtk_PrioLowest;
extern int stub__rtk_PrioAboveNormal;
extern int stub__rtk_PrioHigh;
extern int stub__rtk_PrioLow;
extern Bool txbcs__vps_GetProgramType( Nat8 * ptr_ptype );
extern Nat32 txbcs__div_PacketPoolSize;
extern Bool txbcs__pre_VpsPresent( void );
extern void txbcs__vpsN_OnPacket( Nat8 NEAR * data );
extern Bool txbcs__vps_IsDataFieldsAvailable( Nat8 field_bit_vector );
extern Bool txbcs__pre_WstPresent( void );
extern void stub__rtk_SemRelease( Semaphore sem );
extern Nat32 txbcs__div_BundleDataBufferSize;
extern void stub__rtk_SemDelete( Semaphore sem );
extern int txbcs__div_MaxCallBacks;
extern Bool txbcs__vps_GetProgramControlStatus( Nat8 * ptr_ps );
extern int stub__rtk_PrioBelowNormal;
extern int txbcs__div_MaxWinTypeBlocks;
extern void * txbcs__div_PacketPoolBase;
extern Bool txbcs__vps_GetPilCode( PilCode * ptr_pil_code );
extern void txbcs__vpsN_OnBegin( void );
extern int txbcs__div_RollTimeUpdateFreq;
extern Nat8 * txbcs__div_BundleDataBufferBase;
extern Nat8 txbcs__div_MaxAitPages;
extern int txbcs__div_RollHdrFgCol;
extern int txbcs__div_SemCeilingPriority;
extern int txbcs__div_MaxOpenPages;
extern int txbcs__div_RollHdrUpdateFreq;
extern int txbcs__div_iVersion;

extern void txdscnv__cnv_ConfInit( TxtPageConfigStruct * pcs );
extern void txdscnv__cnv_SetConfWindowId( TxtPageConfigStruct * pcs, TWindowId window_id );
extern TWindowId txdscnv__cnv_GetConfWindowId( TxtPageConfigStruct * pcs );
extern void txdscnv__cnv_SetConfPageHandle( TxtPageConfigStruct * pcs, TxtPageHandle hnd );
extern TxtPageHandle txdscnv__cnv_GetConfPageHandle( TxtPageConfigStruct * pcs );
extern void txdscnv__cnv_SetRevealState( Bool rev_state );
extern Bool txdscnv__cnv_GetRevealState( void );
extern Bool txdscnv__cnv_GetPageWidthOffset( TxtPageHandle hnd, int * width, int * offset );
extern Bool txdscnv__cnv_GetPagePon( void );
extern void txdscnv__cnv_SetRollingHeader( int mode, int magazine );
extern void txdscnv__cnv_SetRollingTime( int mode );
extern void txdscnv__cnv_SetHeaderInitialPosition( Nat8 topleftrow, Nat8 topleftcol );
extern void txdscnv__cnv_HoldConversion( Bool convhold_state );
extern void txdscnv__cnv_ResetUpdateCounter( void );
extern void txdscnv__cnv_IncrementUpdateCounter( void );
extern void txsto__pkt0_GetLatestHeader( TxtPacket0 * pkt0ptr, Nat8 mag );
extern Bool txsto__pkt0_GetLatestTime( Time * time_ptr );
extern TWindowId txdsdrv__dsdrv3_OpenWindow( int PadType, Nat8 TopLeftRow, Nat8 TopLeftColumn, Nat8 BottomRightRow, Nat8 BottomRightColumn );
extern void txdsdrv__dsdrv3_ClearWindow( TWindowId handl, int colour );
extern void txdsdrv__dsdrv3_CloseWindow( TWindowId handl );
extern void txdscnv__cnv_SetConfPresentation(TxtPageConfigStruct* pcs, int presentation);
extern void txdsdrv__dsdrv3_SetScreenRowColour( Nat8 row, int colour, Bool left );
extern void txdsdrv__dsdrv3_SetScreenTopBottomColour( int colour, Bool tb, Bool left );
extern int txdscnv__cnv_GetConfPresentation( TxtPageConfigStruct * pcs );
extern void txdscnv__cnv_SetConfSupRow24( TxtPageConfigStruct * pcs, Bool sup_row_24 );
extern Bool txdscnv__cnv_GetConfSupRow24( TxtPageConfigStruct * pcs );
extern void txdscnv__cnv_SetConfSupHeader( TxtPageConfigStruct * pcs, Bool sup_header );
extern Bool txdscnv__cnv_GetConfSupHeader( TxtPageConfigStruct * pcs );
extern void txdscnv__cnv_SetConfSupPicture( TxtPageConfigStruct * pcs, Bool sup_picture );
extern Bool txdscnv__cnv_GetConfSupPicture( TxtPageConfigStruct * pcs );
extern void txdscnv__cnv_SetConfSupSidePanels( TxtPageConfigStruct * pcs, Bool sup_side_pan );
extern Bool txdscnv__cnv_GetConfSupSidePanels( TxtPageConfigStruct * pcs );
extern void txdscnv__cnv_SetConfSupRowAttribs( TxtPageConfigStruct * pcs, Bool sup_row_attribs );
extern void txdscnv__cnv_ConfigureTextPageConversion( TxtPageConfigStruct * pcs );
extern void txdscnv__cnv_StartTextPageConversion( Bool stat );
extern void txdscnv__cnv_TerminateTextPageConversion( void );
extern void txdsdrv__dsdrv3_CloseWindow( TWindowId handl );
extern Bool txdscnv__cnv_GetConfSupRowAttribs( TxtPageConfigStruct * pcs );
extern void txdsdrv__dsdrv3_CloseWindow( TWindowId handl );
extern TxtPageHandle txsto__str_OpenPageForRead( PageNr page, Subcode subcode );
extern void txsto__str_ClosePageWrite( TxtPageHandle hnd );
extern void txdec__dec_DecodeOddParity( Nat8 * src, Nat8 * dst, Nat8 * old, int size );
extern void txsto__str_ClosePageWrite( TxtPageHandle hnd );
extern void txsto__str_ClosePage( TxtPageHandle hnd );
extern void txdsdrv__dsdrv3_WriteString( TWindowId handl, Nat8 row, Nat8 col, Nat8 len, Nat32 * string );
extern void txdsdrv__dsdrv3_InitAttrCharacterCode( Nat32 * cc );
extern void txdsdrv__dsdrv3_SetConvRowForeAndBackgroundClutSelection( Nat8 row, Bool fgClutSel, Bool bgClutSel, Bool left );
extern void txdsdrv__dsdrv3_SetRowForeAndBackgroundClutSelection( Nat8 row, Bool fgClutSel, Bool bgClutSel, Bool left );
extern void txdsdrv__dsdrv3_SetScreenRowHeight( Nat8 row, int rh, Bool left );
extern void txdsdrv__dsdrv3_SetRowsDoubleHeight( int start, Nat8 nr_rows, Bool dh );
extern void txdsdrv__dsdrv3_SetRowDisplayEnable( Nat8 row, Bool enb, Bool left );
extern void txdsdrv__dsdrv3_SetRowBoxEnable( Nat8 row, Bool enb, Bool left );
extern void txdsdrv__dsdrv3_SetAttrBackgroundColour( Nat32 * cc, int bg );
extern void txdsdrv__dsdrv3_SetAttrForegroundColour( Nat32 * cc, int fg );
extern void txdsdrv__ixrdsdrv2_SetConversionFontAndCharacter( Nat32 * cc, Font font, Language lng, int ch );
extern TWindowId txdsdrv__dsdrv3_OpenWindow( int PadType, Nat8 TopLeftRow, Nat8 TopLeftColumn, Nat8 BottomRightRow, Nat8 BottomRightColumn );
extern void txdsdrv__dsdrv3_ClearWindow( TWindowId handl, int colour );
extern void txdsdrv__dsdrv3_WriteCharacter( TWindowId hand, Nat8 row, Nat8 col, Nat32 cc );
extern Nat32 txdsdrv__dsdrv3_ReadCharacter( TWindowId handl, Nat8 row, Nat8 col );
extern void txdsdrv__dsdrv3_WriteString( TWindowId handl, Nat8 row, Nat8 col, Nat8 len, Nat32 * string );
extern Nat8 txdsdrv__dsdrv3_GetWindowStartRow( TWindowId handl );
extern Nat8 txdsdrv__dsdrv3_GetWindowStartColumn( TWindowId handl );
extern Nat8 txdsdrv__dsdrv3_GetWindowEndRow( TWindowId handl );
extern Nat8 txdsdrv__dsdrv3_GetWindowEndColumn( TWindowId handl );
extern void txdsdrv__dsdrv3_CloseWindow( TWindowId handl );
extern void txdsdrv__dsdrv3_ChangeWindowCoordinates( TWindowId handl, Nat8 TopLeftRow, Nat8 TopLeftColumn, Nat8 BottomRightRow, Nat8 BottomRightColumn );
extern void txdsdrv__dsdrv3_InitAttrCharacterCode( Nat32 * cc );
extern void txdsdrv__dsdrv3_SetAttrUnderlineSeparate( Nat32 * cc, Bool us );
extern Bool txdsdrv__dsdrv3_GetAttrUnderlineSeparate( Nat32 cc );
extern void txdsdrv__ixrdsdrv2_SetConversionFontAndCharacter( Nat32 * cc, Font font, Language lng, int ch );
extern void txdsdrv__dsdrv3_SetAttrDoubleHeight( Nat32 * cc, Bool dh );
extern Bool txdsdrv__dsdrv3_GetAttrDoubleHeight( Nat32 cc );
extern void txdsdrv__dsdrv3_SetAttrDoubleWidth( Nat32 * cc, Bool dw );
extern Bool txdsdrv__dsdrv3_GetAttrDoubleWidth( Nat32 cc );
extern void txdsdrv__dsdrv3_SetAttrFlashMode( Nat32 * cc, Nat8 fm );
extern Nat8 txdsdrv__dsdrv3_GetAttrFlashMode( Nat32 cc );
extern void txdsdrv__dsdrv3_SetAttrFlashPhase( Nat32 * cc, Nat8 fp );
extern Nat8 txdsdrv__dsdrv3_GetAttrFlashPhase( Nat32 cc );
extern void txdsdrv__dsdrv3_SetAttrBox( Nat32 * cc, Bool box );
extern Bool txdsdrv__dsdrv3_GetAttrBox( Nat32 cc );
extern void txdsdrv__dsdrv3_SetAttrForegroundColour( Nat32 * cc, int fg );
extern int txdsdrv__dsdrv3_GetAttrForegroundColour( Nat32 cc );
extern void txdsdrv__dsdrv3_SetAttrBackgroundColour( Nat32 * cc, int bg );
extern int txdsdrv__dsdrv3_GetAttrBackgroundColour( Nat32 cc );
extern void txdsdrv__ixrdsdrv2_SetConversionCurrentPosition( TWindowId handl, Nat8 row, Nat8 col );
extern Nat8 txdsdrv__ixrdsdrv2_GetConversionCurrentRow( TWindowId handl );
extern Nat8 txdsdrv__dsdrv3_GetConversionCurrentColumn( TWindowId handl );
extern void txdsdrv__dsdrv3_SetConversionLanguageContext( TWindowId handl, Language lng );
extern Language txdsdrv__dsdrv3_GetConversionLanguageContext( TWindowId handl );
extern void txdsdrv__dsdrv3_SetConversionUnderlineSeparate( TWindowId handl, Bool ul_sep );
extern Bool txdsdrv__dsdrv3_GetConversionUnderlineSeparate( TWindowId handl );
extern void txdsdrv__ixrdsdrv2_WriteConversionCharacter( TWindowId handl, int charcode, TConvAttrUnion ca );
extern void txdsdrv__dsdrv3_WriteConversionAccentedCharacter( TWindowId handl, int charcode, int accentcode, TConvAttrUnion ca );
extern void txdsdrv__dsdrv3_SetConversionAttributes( TWindowId handl, TConvAttrUnion ca );
extern Bool txdsdrv__dsdrv3_ConversionIsOnLeftSide( TWindowId handl );
extern void txdsdrv__dsdrv3_SetConvRowDisplayEnable( Nat8 row, Bool enb, Bool left );
extern Nat32 * txdsdrv__dsdrv3_GetConvRowAttributesPointer( Nat8 row, Bool left );
extern void txdsdrv__dsdrv3_SetConvRowForeAndBackgroundColBank( Nat8 row, Bool fgColBank, Bool bgColBank, Bool left );
extern Nat32 txtgfxdsp__gfxtxt2_CreateHeader( int NoOfClutEntries );
extern void txdsdrv__dsdrv3_SetConvRowForeAndBackgroundClutSelection( Nat8 row, Bool fgClutSel, Bool bgClutSel, Bool left );
extern void txdsdrv__dsdrv3_SetScreenTopBottomColour( int colour, Bool tb, Bool left );
extern int txdsdrv__dsdrv3_GetScreenTopBottomColour( Bool tb, Bool left );
extern void txdsdrv__dsdrv3_SetScreenRowColour( Nat8 row, int colour, Bool left );
extern int txdsdrv__dsdrv3_GetScreenRowColour( Nat8 row, Bool left );
extern void txdsdrv__dsdrv3_SetScreenRowHeight( Nat8 row, int rh, Bool left );
extern int txdsdrv__dsdrv3_GetScreenRowHeight( Nat8 row, Bool left );
extern void txdsdrv__dsdrv3_SetRowsDoubleHeight( int start, Nat8 nr_rows, Bool dh );
extern void txdsdrv__dsdrv3_SetRowDisplayEnable( Nat8 row, Bool enb, Bool left );
extern void txdsdrv__dsdrv3_SetRowBoxEnable( Nat8 row, Bool enb, Bool left );
extern void txdsdrv__dsdrv3_SetRowNewsflashSubtitleEnable( Nat8 row, Bool enb, Bool left );
extern Bool txdsdrv__dsdrv3_GetRowNewsflashSubtitleEnable( Nat8 row, Bool left );
extern Nat32 * txdsdrv__dsdrv3_GetRowAttributesPointer( Nat8 row, Bool left );
extern Nat8 txdsdrv__dsdrv3_GetRowForegroundColBank( Nat8 row, Bool left );
extern Nat8 txdsdrv__dsdrv3_GetRowBackgroundColBank( Nat8 row, Bool left );
extern void txdsdrv__dsdrv3_SetRowForeAndBackgroundColBank( Nat8 row, Bool fgColBank, Bool bgColBank, Bool left );
extern void txdsdrv__dsdrv3_SetRowForeAndBackgroundClutSelection( Nat8 row, Bool fgClutSel, Bool bgClutSel, Bool left );
extern Bool txdsdrv__dsdrv3_GetRemapRowClutArea( Nat8 row, Bool fg, Bool left );
extern void txdsdrv__dsdrv3_SetRamPalette( int start, int count, Nat32 * rgba );
extern Nat32 txdsdrv__dsdrv3_GetBodyPadHeaderId( void );
extern Bool txdsdrv__dsdrv3_ReadGfxCharacter( TWindowId handl, Nat32 row, Nat32 col, Nat32 * charbits, Nat32 * charcol, Nat32 * charctrl );
extern int txsto__req_RequestPage( PageNr page, Subcode subcode, FncReceived fnc, int tag );
extern void txsto__req_UnRequestPage( PageNr page, Subcode subcode, FncReceived fnc );
extern void txsto__req_SuggestPage( PageNr page );
extern void txsto__req_UnSuggestPage( PageNr page );
extern Bool txsto__req_SetType( PageNr page, PageType ptype, Bool priority, FncCallBack func );
extern void txtgfxdsp__gfxtxt2_DeleteHeader( Nat32 headerId );
extern void txtgfxdsp__gfxtxt2_TruncateHeader( Nat32 headerId, int sections );
extern void txtgfxdsp__gfxtxt2_ResetHeader( Nat32 headerId );
extern Nat32 txtgfxdsp__gfxtxt2_CreateString( Nat32 headerId, int maxChar, Nat32 ul_x, Nat32 ul_y );
extern void txtgfxdsp__gfxtxt2_RepositionString( Nat32 stringId, Nat8 window, Nat16 pos, Nat32 ul_x, Nat32 ul_y );
extern Nat32 txtgfxdsp__gfxtxt2_CreateFiller( Nat32 headerId, Nat32 ul_x, Nat32 ul_y, Nat32 lr_x, Nat32 lr_y, Nat8 clutIndex );
extern void txtgfxdsp__gfxtxt2_RepositionFiller( Nat32 fillerId, Nat32 ul_x, Nat32 ul_y, Nat32 lr_x, Nat32 lr_y );
extern void txtgfxdsp__gfxtxt2_SetFillerColor( Nat32 fillerId, Nat8 clutIndex );
extern void txtgfxdsp__gfxtxt2_Configure( Nat32 multipleId, Nat32 Font, Nat32 width, Nat32 ht, Nat32 fntSize, Nat32 controlBits );
extern void txtgfxdsp__gfxtxt2_GetBounds( Nat32 multipleId, Nat32 * ul_x, Nat32 * ul_y, Nat32 * lr_x, Nat32 * lr_y );
extern void txtgfxdsp__gfxtxt2_SetVisibility( Nat32 multipleId, Bool visible );
extern Nat32 * txdsdrv__dsdrv3_GetConvRowAttributesPointer( Nat8 row, Bool left );
extern void txtgfxdsp__gfxtxt2_ModifyCharacters( Nat32 stringId, Nat32 charNum, Nat32 charBits, Nat32 CharCol, Nat32 fntSize, Nat32 borderstyle, Nat32 CharCtrl );
extern void txtgfxdsp__gfxtxt2_CopyCharacters( Nat32 srcStringId, Nat32 dstStringId, Nat32 attrib );
extern void txtgfxdsp__gfxtxt2_GetCharacterAdvance( Nat32 CharBits, Nat32 CharCol, Nat32 CharCtrl, Nat32 * width, Nat32 * height );
extern void txtgfxdsp__gfxtxt2_GetCharacterAdvance( Nat32 CharBits, Nat32 CharCol, Nat32 CharCtrl, Nat32 * width, Nat32 * height );
extern void txtgfxdsp__gfxtxt2_SetCursor( Nat32 headerId, Nat32 ul_x, Nat32 ul_y, Nat32 lr_x, Nat32 lr_y );
extern void txtgfxdsp__gfxtxt2_SetColor( Nat32 headerId, int start, Nat8 noOfEntries, Nat32 * pColor );
extern Nat32 txtgfxdsp__gfxtxt2_GetColor( Nat32 headerId, int clutindex );
extern Nat32 txtgfxdsp__gfxtxt2_PackARGB( Nat8 alpha, Nat8 red, Nat8 green, Nat8 blue );
extern void txtgfxdsp__gfxtxt2_UnPackARGB( Nat32 value, Nat8 * pAlpha, Nat8 * pRed, Nat8 * pGreen, Nat8 * pBlue );
extern void txtgfxdsp__gfxtxt2_SetFlash( Bool onoff );
extern Nat32 txtgfxdsp__gfxtxt2_StoreBitmaps( Nat32 headerId, Nat32 size, Nat32 * pInput, Nat8 inputType, Nat32 bitMapId );
extern void txtgfxdsp__gfxtxt2_Draw( void );
extern void txtgfxdsp__gfxtxt2_DrawTextPad( Nat8 window, Nat16 pos );
 extern void txtgfxdsp__gfxtxt2_Scroll( Nat8 window, Nat16 pos, Nat8 UpDown );
 extern Bool txtgfxdsp__gfxtxt2_Register( int clientId );
extern Bool txtgfxdsp__gfxtxt2_UnRegister( int clientId );
extern void txtgfxdsp__gfxtxt2_SetDisplayVisibility( Bool onOff );
extern Bool txtgfxdsp__gfxtxt2_GetDisplayVisibility( void );
extern void txtgfxdsp__gfxtxt2_AttachTextPad( Nat8 window, int pos, Nat32 headerId );
extern void txtgfxdsp__gfxtxt2_DetachTextPad( Nat8 window, Nat16 pos );
extern void txtgfxdsp__gfxtxt2_ScrollSetUp( Nat32 headerId, Nat8 ScrollIncr );
extern Bool txtgfxdsp__gfxtxt2_GetRevealMode( Nat8 window );
extern void txtgfxdsp__gfxtxt2_SetRevealMode( Nat8 window, Bool mode );
extern Bool txtgfxdsp__gfxtxt2_GetMixMode( Nat8 window );
extern void txtgfxdsp__gfxtxt2_SetMixedMode( Nat8 window, Bool mode );
extern Nat8 txtgfxdsp__gfxtxt2_GetPageMode( void );
extern void txtgfxdsp__gfxtxt2_SetPageMode( Nat8 mode );
extern void txtgfxdsp__gfxtxt2_RowMapInit( void );
extern void txtgfxdsp__gfxtxt2_RowMapInitPlain( void );
extern Nat32 txtgfxdsp__gfxtxt2_SetUpRowMapEntry( Nat16 txtPadRow, Bool dispEn, Bool doubleHt, Bool showBottom );
extern void txtgfxdsp__gfxtxt2_SetRowMapEntry( Nat8 window, Nat16 pos, Nat16 canvasRow, Nat32 rowEntry );
extern void txtgfxdsp__gfxtxt2_SetRowMapRange( Nat8 window, Nat16 pos, Nat16 canvasRowStart, Nat16 rowCount, Nat32 rowEntry );
extern void txtgfxdsp__gfxtxt2_SetFillerMap( Nat8 window, Nat16 topEndRow, Nat16 bottomStartRow );
extern void txdscnv__pow_TurnOn( void );
extern void txdscnv__pow_TurnOff( void );
extern Bool txsvc__chlname_GetCurrentChannelLabel( String label );
extern void txtgfxdsp__gfxtxt2_GetCharacterAdvance( Nat32 CharBits, Nat32 CharCol, Nat32 CharCtrl, Nat32 * width, Nat32 * height );
extern void txtgfxdsp__gfxtxt2_RowMapInit( void );
extern void txtgfxdsp__gfxtxt2_GetCharacter( Nat32 stringId, Nat32 charNum, Nat32 * CharBits, Nat32 * CharCol, Nat32 * CharCtrl, Nat32 * FntSize );
extern void txvbi__vbislN_OnWstData (int wsttype,const int nrLines,int * const pLines,const int sizeFirstBuffer,const int sizeSecondBuffer,int * const firstBuffer,int * const secondBuffer);
extern void txvbi__vbislN_OnWstNoData(void);
extern void txvbi__vbislN_onVpsData(const int size,int * const buffer);
extern void txvbi__vbislN_onVpsNoData(void);

extern void txvbi__dcu_Enable( void );
extern void txvbi__dcu_Disable( void );

 
 
 

#ifdef __cplusplus
}

#endif


