#include "_euinsstub_mtxtstub.h"
#include "stub.h"
#include <cutils/log.h>

/* Interfaces from IHsvTxtVpsData.id */

typedef   unsigned int top_notification_state;
#include <CGfxNativeWindow.h>
TRACESYMBOL(m, "comps/euinsstub_mtxtdummy")

#define CHECK_GFX()   {if(GfxNative == 0) { __android_log_print(ANDROID_LOG_DEBUG, "CHsvtxtPlfsvc_m_Priv"," GfxNative is NULL"); return 0;}}
IGfxANWabs *GfxNative;
CEuInstallerStub_mtxtstub_Priv *TxtplfHandle;


	 
 
class PumpCRunnable:public IRunnable
{
private:
    bool m_replace;
    //char m_name[32]; tbd
    void (*m_func) (int , unsigned int);
    IThread *m_l;
    char    *pumpName;
public:
    PumpCRunnable(void (*func) (int , unsigned int), bool replace, char* name, IThread *l)
    {
        m_func = func;
        m_replace = replace;
        m_l = l;
        pumpName = strdup(name);
    }
    virtual ~PumpCRunnable(){}
    virtual void Run(IParams *p)
    {
        (*m_func)((static_cast<Params*>(p))->P1(),(static_cast<Params*>(p))->P2());
    }
    virtual void PumpSend(int p1, unsigned int p2, unsigned int after)
    {
		if(m_l)
		m_l->Post(static_cast<IRunnable*>(this),m_replace,static_cast<IParams *>(new Params(p1,p2, pumpName)),after);
    }
	
};

class PumpCFactory
{
private:
    std::vector<PumpCRunnable*> m_pumps;
public:
    Pump PmpCreate(IThread* pen, void (*func) (int , unsigned int), bool replace, char *name)
    {
         PumpCRunnable *pmp = new PumpCRunnable(func, replace, name, pen);
         m_pumps.push_back(pmp);
		// __android_log_print(ANDROID_LOG_DEBUG, "CHsvtxtPlfsvc_m_Priv","PmpCreate p = %x func =%x",pmp,func);
         return (Pump) pmp;
    }
    void PmpSend(Pump p, int p1, Nat32 p2)
    {
	//__android_log_print(ANDROID_LOG_DEBUG, "CHsvtxtPlfsvc_m_Priv","pmpsend p = %x p1=%d",p,p1);
        ((PumpCRunnable*)p)->PumpSend(p1,p2,0);
    }
    void PmpSendAfter(Pump p, int p1, Nat32 p2, unsigned int msecs)
    {
		//__android_log_print(ANDROID_LOG_DEBUG, "CHsvtxtPlfsvc_m_Priv","pmpsendafter p = %x p1=%d,msec=%d",p,p1,msecs);
        ((PumpCRunnable*)p)->PumpSend(p1,p2,msecs);
    }
    ~PumpCFactory()
    {
        for(unsigned int i = 0; i < m_pumps.size(); i++)
            delete m_pumps[i];
    }
};


static PumpCFactory *pmpfac; // = new PumpCFactory();

static CTvMwCore	*CoreInstance;
void CEuInstallerStub_mtxtstub_Priv::SetMwCoreInstance (CTvMwCore *Core)
{
	__android_log_print(ANDROID_LOG_DEBUG,"CEuInstallerStub_mtxtstub_Priv","Alive.. Setting MW Core Instance in TXT %x ", Core);
	CoreInstance = Core;
}

void CEuInstallerStub_mtxtstub_Priv::pow_Init( void )
{
               int retval = 0;
               __android_log_print(ANDROID_LOG_DEBUG, "CEuInstallerStub_mtxtstub_Priv","pow_Init");
               pmpfac = new PumpCFactory();
               retval = hsvtxt__pow_Init();
               __android_log_print(ANDROID_LOG_DEBUG, "CEuInstallerStub_mtxtstub_Priv"," %d",retval);
                                             
}

void CEuInstallerStub_mtxtstub_Priv::pow_TurnOn( void )
{
               __android_log_print(ANDROID_LOG_DEBUG, "CEuInstallerStub_mtxtstub_Priv","pow_TurnOn");
               hsvtxt__pow_TurnOn();
               //pctlN_OnPageArrived( 0x101, 2 ); 
               //mode2_SetMode(0);
                              
}

void CEuInstallerStub_mtxtstub_Priv::pow_TurnOff( void )
{
               hsvtxt__pow_TurnOff();
}


int cpp_log(const char *fmt, ...)
{
  ALOGV(fmt);
  return 0;
}



void CEuInstallerStub_mtxtstub_Priv::Settxtplfhandle( CEuInstallerStub_mtxtstub_Priv* txtplfhandle)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "CEuInstallerStub_mtxtstub_Priv","Settxtplfhandle");
	TxtplfHandle = txtplfhandle;
	
}
void CEuInstallerStub_mtxtstub_Priv::SetGfxhandle( IGfxANWabs* gfxhandle)
{
	//__android_log_print(ANDROID_LOG_DEBUG, "CEuInstallerStub_mtxtstub_Priv","SetGfxhandle");
	GfxNative = gfxhandle;
	
}

int CEuInstallerStub_mtxtstub_Priv::vps_RequestDataFields ( Nat8 field_bit_vector, VpsCbFn cb_fn, Bool cb_on_every_update )
{
	return txbcs__vps_RequestDataFields(field_bit_vector,cb_fn,cb_on_every_update) ;
}

void CEuInstallerStub_mtxtstub_Priv::vps_UnRequestDataFields ( int request_id )
{
	txbcs__vps_UnRequestDataFields(request_id) ;
}

Bool CEuInstallerStub_mtxtstub_Priv::vps_IsDataFieldsAvailable ( Nat8  field_bit_vector )
{
	return txbcs__vps_IsDataFieldsAvailable(field_bit_vector);
}

Bool CEuInstallerStub_mtxtstub_Priv::vps_GetPilCode ( PilCode*  ptr_pil_code )
{
	return txbcs__vps_GetPilCode(ptr_pil_code);
}

Bool CEuInstallerStub_mtxtstub_Priv::vps_GetCountryNetworkIdentificationCode ( Nat16*  ptr_cni )
{
	return txbcs__vps_GetCountryNetworkIdentificationCode(ptr_cni);
}

Bool CEuInstallerStub_mtxtstub_Priv::vps_GetProgramType ( Nat8*  ptr_ptype )
{
	return txbcs__vps_GetProgramType(ptr_ptype);
}

Bool CEuInstallerStub_mtxtstub_Priv::vps_GetProgramControlStatus ( Nat8*  ptr_ps )
{
	return txbcs__vps_GetProgramControlStatus(ptr_ps);
}

Bool CEuInstallerStub_mtxtstub_Priv::vps_GetDistinctionBits( Nat8* ptr_dist_bits )
{
	return txbcs__vps_GetDistinctionBits(ptr_dist_bits);
}

/* Interfaces from IHsvTxtPacket830Data.id */
int CEuInstallerStub_mtxtstub_Priv::p830_RequestDataFields ( Nat16 field_bit_vector, Packet830CbFn cb_fn, Bool cb_on_every_update )
{
	return txbcs__p830_RequestDataFields(field_bit_vector,cb_fn,cb_on_every_update);
}

void CEuInstallerStub_mtxtstub_Priv::p830_UnRequestDataFields ( int request_id )
{
	txbcs__p830_UnRequestDataFields(request_id);
}

Bool CEuInstallerStub_mtxtstub_Priv::p830_IsDataFieldsAvailable ( Nat16  field_bit_vector )
{
	return txbcs__p830_IsDataFieldsAvailable(field_bit_vector);
}

Bool CEuInstallerStub_mtxtstub_Priv::p830_GetStatusMessage ( String  msg_string)
{
	return txbcs__p830_GetStatusMessage(msg_string);
}

Bool CEuInstallerStub_mtxtstub_Priv::p830_GetInitialPage ( PageNr* ptr_pn, Subcode* ptr_sc )
{
	return  txbcs__p830_GetInitialPage(ptr_pn, ptr_sc);
}

Bool CEuInstallerStub_mtxtstub_Priv::p830_GetUTCDate ( Mjd* ptr_mjd )
{
	return  txbcs__p830_GetUTCDate(ptr_mjd);
}

Bool CEuInstallerStub_mtxtstub_Priv::p830_GetUTCTime ( Time*  ptr_time )
{
	return  txbcs__p830_GetUTCTime(ptr_time);
}

Bool CEuInstallerStub_mtxtstub_Priv::p830_GetTimeOffset ( Int8*  ptr_time_offset )
{
	return txbcs__p830_GetTimeOffset(ptr_time_offset);
}

Bool CEuInstallerStub_mtxtstub_Priv::p830_GetNetworkIdentificationCode ( Nat16*  ptr_ni )
{
	return  txbcs__p830_GetNetworkIdentificationCode(ptr_ni);
}

Bool CEuInstallerStub_mtxtstub_Priv::p830_GetPilCode ( PilCode*  ptr_pil_code )
{
	return txbcs__p830_GetPilCode(ptr_pil_code);
}

Bool CEuInstallerStub_mtxtstub_Priv::p830_GetCountryNetworkIdentificationCode ( Nat16* ptr_cni )
{
	return txbcs__p830_GetCountryNetworkIdentificationCode(ptr_cni);
}

Bool CEuInstallerStub_mtxtstub_Priv::p830_GetLabelInfo ( LabelInfo*  ptr_li )
{
	return txbcs__p830_GetLabelInfo(ptr_li);
}

Bool CEuInstallerStub_mtxtstub_Priv::p830_GetProgramControlInfo ( ProgramControlInfo*  ptr_pci )
{
	return txbcs__p830_GetProgramControlInfo(ptr_pci);
}

Bool CEuInstallerStub_mtxtstub_Priv::p830_GetProgramType ( Nat8*  ptr_ptype )
{
	return txbcs__p830_GetProgramType(ptr_ptype);
}

/* Interfaces from IHsvTxtPresent.id */
Bool CEuInstallerStub_mtxtstub_Priv::txtpre_WstPresent(void)
{
	return TRUE;
}

Bool CEuInstallerStub_mtxtstub_Priv::txtpre_VpsPresent(void)
{
	return TRUE;
}

/* Interfaces from IHsvTxtPageConvert.id */
void CEuInstallerStub_mtxtstub_Priv::cnv_ConfInit( TxtPageConfigStruct* pcs )
{
	txdscnv__cnv_ConfInit(pcs);
}

void CEuInstallerStub_mtxtstub_Priv::cnv_SetConfWindowId( TxtPageConfigStruct* pcs, TWindowId window_id )
{
	txdscnv__cnv_SetConfWindowId(pcs,window_id);
}

TWindowId CEuInstallerStub_mtxtstub_Priv::cnv_GetConfWindowId( TxtPageConfigStruct* pcs )
{
	return txdscnv__cnv_GetConfWindowId(pcs);
}

void CEuInstallerStub_mtxtstub_Priv::cnv_SetConfPageHandle( TxtPageConfigStruct* pcs, TxtPageHandle hnd )
{
	txdscnv__cnv_SetConfPageHandle(pcs,hnd);
}

TxtPageHandle CEuInstallerStub_mtxtstub_Priv::cnv_GetConfPageHandle( TxtPageConfigStruct* pcs )
{
	return txdscnv__cnv_GetConfPageHandle(pcs);
}

void CEuInstallerStub_mtxtstub_Priv::cnv_SetConfPresentation( TxtPageConfigStruct* pcs, int presentation )
{
	txdscnv__cnv_SetConfPresentation(pcs,presentation);
}

int CEuInstallerStub_mtxtstub_Priv::cnv_GetConfPresentation( TxtPageConfigStruct* pcs )
{
	return txdscnv__cnv_GetConfPresentation(pcs);
}

void CEuInstallerStub_mtxtstub_Priv::cnv_SetConfSupRow24( TxtPageConfigStruct* pcs, Bool sup_row_24 )
{
	txdscnv__cnv_SetConfSupRow24(pcs,sup_row_24);
}

Bool CEuInstallerStub_mtxtstub_Priv::cnv_GetConfSupRow24( TxtPageConfigStruct* pcs )
{
	return txdscnv__cnv_GetConfSupRow24(pcs);
}

void CEuInstallerStub_mtxtstub_Priv::cnv_SetConfSupHeader( TxtPageConfigStruct* pcs, Bool sup_header )
{
	txdscnv__cnv_SetConfSupHeader(pcs,sup_header);
}

Bool CEuInstallerStub_mtxtstub_Priv::cnv_GetConfSupHeader( TxtPageConfigStruct* pcs )
{
	return txdscnv__cnv_GetConfSupHeader(pcs);
}

void CEuInstallerStub_mtxtstub_Priv::cnv_SetConfSupPicture( TxtPageConfigStruct* pcs, Bool sup_picture )
{
	txdscnv__cnv_SetConfSupPicture(pcs,sup_picture);
}

Bool CEuInstallerStub_mtxtstub_Priv::cnv_GetConfSupPicture( TxtPageConfigStruct* pcs )
{
	return txdscnv__cnv_GetConfSupPicture(pcs);
}

void CEuInstallerStub_mtxtstub_Priv::cnv_SetConfSupSidePanels( TxtPageConfigStruct* pcs, Bool sup_side_pan )
{
	txdscnv__cnv_SetConfSupSidePanels(pcs,sup_side_pan);
}

Bool CEuInstallerStub_mtxtstub_Priv::cnv_GetConfSupSidePanels( TxtPageConfigStruct* pcs )
{
	return txdscnv__cnv_GetConfSupSidePanels(pcs);
}

void CEuInstallerStub_mtxtstub_Priv::cnv_SetConfSupRowAttribs( TxtPageConfigStruct* pcs, Bool sup_row_attribs )
{
	txdscnv__cnv_SetConfSupRowAttribs(pcs,sup_row_attribs);
}

Bool CEuInstallerStub_mtxtstub_Priv::cnv_GetConfSupRowAttribs( TxtPageConfigStruct* pcs )
{
	return txdscnv__cnv_GetConfSupRowAttribs(pcs);
}

void CEuInstallerStub_mtxtstub_Priv::cnv_ConfigureTextPageConversion( TxtPageConfigStruct* pcs )
{
	txdscnv__cnv_ConfigureTextPageConversion(pcs);
}

void CEuInstallerStub_mtxtstub_Priv::cnv_StartTextPageConversion( Bool New )
{
	txdscnv__cnv_StartTextPageConversion(New);
}

void CEuInstallerStub_mtxtstub_Priv::cnv_TerminateTextPageConversion ( void )
{
	txdscnv__cnv_TerminateTextPageConversion();
}

void CEuInstallerStub_mtxtstub_Priv::cnv_SetRevealState( Bool rev_state )
{
	txdscnv__cnv_SetRevealState(  rev_state );;
}

Bool CEuInstallerStub_mtxtstub_Priv::cnv_GetRevealState( void )
{
	return txdscnv__cnv_GetRevealState();
}

Bool CEuInstallerStub_mtxtstub_Priv::cnv_GetPageWidthOffset ( TxtPageHandle hnd,  int * width, int * offset )
{
	return txdscnv__cnv_GetPageWidthOffset(  hnd, width,offset );
}

Bool CEuInstallerStub_mtxtstub_Priv::cnv_GetPagePon( void )
{
	return txdscnv__cnv_GetPagePon();
}

void CEuInstallerStub_mtxtstub_Priv::cnv_SetRollingHeader( int mode, int magazine )
{
	 txdscnv__cnv_SetRollingHeader(  mode,  magazine );
}

void CEuInstallerStub_mtxtstub_Priv::cnv_SetRollingTime( int mode )
{
	txdscnv__cnv_SetRollingTime(  mode );
}

void CEuInstallerStub_mtxtstub_Priv::cnv_SetHeaderInitialPosition(Nat8 topleftrow, Nat8 topleftcol)
{
	txdscnv__cnv_SetHeaderInitialPosition( topleftrow, topleftcol );
}

void CEuInstallerStub_mtxtstub_Priv::cnv_HoldConversion( Bool convhold_state )
{
	 txdscnv__cnv_HoldConversion( convhold_state );
}

void CEuInstallerStub_mtxtstub_Priv::cnv_ResetUpdateCounter( void )
{
	txdscnv__cnv_ResetUpdateCounter( );
}

void CEuInstallerStub_mtxtstub_Priv::cnv_IncrementUpdateCounter( void )
{
	txdscnv__cnv_IncrementUpdateCounter(  );
}

/* Interfaces from IHsvTxtPacket0.id */
Bool acipage_present_temp = 0; 

void CEuInstallerStub_mtxtstub_Priv::pkt0_GetLatestHeader      ( TxtPacket0 *pkt0ptr, Nat8 mag )
{
 //__android_log_print(ANDROID_LOG_DEBUG, "testfunc","%s %d ",__FUNCTION__,__LINE__);
   txsto__pkt0_GetLatestHeader( pkt0ptr, mag );
}

void testfunc()
{
TxtPageHandle handle = NOHND;
PacketId    pkt = NOPKT;
	Nat8 *pkt_data = NULL;
	
handle = txsto__str_OpenPageForRead(0x1be,0x3f7f);

if(handle != NOHND)
	{	
		acipage_present_temp = 1;
		__android_log_print(ANDROID_LOG_DEBUG, "testfunc PAGE FOUND","%s %d ",__FUNCTION__,__LINE__);
		for(pkt =0;pkt<=29;pkt++)
		{
			//PrintfNotice("pkt %d ",pkt);
			pkt_data = (PageLinkCache[handle].packets[pkt]->data);//txsto__str_GetPacket(handle,pkt);
			
			if(pkt_data == NULL)
			{
				continue;
			}
					
			{
				//__android_log_print(ANDROID_LOG_DEBUG, "testfunc","pkt_data 0x%x 0x%x 0x%x 0x%x 0x%x",pkt_data[0],pkt_data[1],pkt_data[2],pkt_data[3],pkt_data[4]);
			}
			/*if(NULL!= strnstr(pkt_data, rated_seq, 44))
			{
				//PrintfNotice("%s %d ",__FUNCTION__,__LINE__);
				Retval = TRUE;
				break;
			}
*/			
		}
		txsto__str_ClosePage(handle);		
	}
	//__android_log_print(ANDROID_LOG_DEBUG, "testfunc","%s %d ",__FUNCTION__,__LINE__);
}

Bool CEuInstallerStub_mtxtstub_Priv::pkt0_GetLatestTime        ( Time *time_ptr )
{
	return  txsto__pkt0_GetLatestTime( time_ptr );
}

/* Interfaces from IHsvTxtDisplayDriver.id */
TWindowId CEuInstallerStub_mtxtstub_Priv::dsdrv_OpenWindow( int PadType, Nat8 TopLeftRow, Nat8 TopLeftColumn, Nat8 BottomRightRow, Nat8 BottomRightColumn )
{
	return txdsdrv__dsdrv3_OpenWindow(  PadType,  TopLeftRow,  TopLeftColumn,  BottomRightRow,  BottomRightColumn );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv_ClearWindow( TWindowId handl, int colour )
{
	txdsdrv__dsdrv3_ClearWindow(handl,colour);
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv_CloseWindow( TWindowId handl )
{
	 txdsdrv__dsdrv3_CloseWindow( handl );;
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv_SetScreenRowColour(Nat8 row, int colour, Bool left)
{
	 txdsdrv__dsdrv3_SetScreenRowColour( row,  colour,  left );;
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv_SetScreenTopBottomColour( int colour, Bool tb, Bool left )
{
	txdsdrv__dsdrv3_SetScreenTopBottomColour(  colour,  tb,  left );;
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv_WriteString(TWindowId handl,Nat8 row,Nat8 col,Nat8 len,Nat32* string )
{
	txdsdrv__dsdrv3_WriteString(  handl,  row,  col,  len, string );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv_InitAttrCharacterCode( Nat32* cc )
{
	txdsdrv__dsdrv3_InitAttrCharacterCode( cc );;
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv_SetConvRowForeAndBackgroundClutSelection( Nat8 row, Bool fgClutSel, Bool bgClutSel, Bool left )
{
	txdsdrv__dsdrv3_SetConvRowForeAndBackgroundClutSelection(  row,  fgClutSel,  bgClutSel,  left );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv_SetRowForeAndBackgroundClutSelection( Nat8 row, Bool fgClutSel, Bool bgClutSel, Bool left )
{
	txdsdrv__dsdrv3_SetRowForeAndBackgroundClutSelection(  row,  fgClutSel, bgClutSel,  left );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv_SetScreenRowHeight( Nat8 row, int rh, Bool left)
{
	txdsdrv__dsdrv3_SetScreenRowHeight(  row,  rh,  left );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv_SetRowsDoubleHeight( int start, Nat8 nr_rows, Bool dh )
{
	txdsdrv__dsdrv3_SetRowsDoubleHeight(  start,  nr_rows,  dh );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv_SetRowDisplayEnable( Nat8 row, Bool enb, Bool left )
{
	txdsdrv__dsdrv3_SetRowDisplayEnable(  row,  enb,  left );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv_SetRowBoxEnable( Nat8 row, Bool enb, Bool left )
{
	txdsdrv__dsdrv3_SetRowBoxEnable(  row,  enb, left );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv_SetAttrBackgroundColour( Nat32* cc, int bg )
{
     txdsdrv__dsdrv3_SetAttrBackgroundColour(  cc,  bg );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv_SetAttrForegroundColour( Nat32* cc, int fg )
{
    txdsdrv__dsdrv3_SetAttrForegroundColour( cc, fg );
 }

void CEuInstallerStub_mtxtstub_Priv::dsdrv_SetAttrFontAndCharacter( Nat32* cc, Font font, Language lng, int ch )
{
	txdsdrv__ixrdsdrv2_SetConversionFontAndCharacter(  cc,  font,  lng,  ch );
}

/* Interfaces from ITxtDisplayDriver3.id */
TWindowId CEuInstallerStub_mtxtstub_Priv::dsdrv3_OpenWindow( int PadType, Nat8 TopLeftRow, Nat8 TopLeftColumn, Nat8 BottomRightRow, Nat8 BottomRightColumn )
{
	return  txdsdrv__dsdrv3_OpenWindow(  PadType,  TopLeftRow,  TopLeftColumn,  BottomRightRow,  BottomRightColumn );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_ClearWindow( TWindowId handl, int colour )
{
	txdsdrv__dsdrv3_ClearWindow(  handl,  colour );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_WriteCharacter( TWindowId hand, Nat8 row, Nat8 col, Nat32 cc)
{
	txdsdrv__dsdrv3_WriteCharacter(  hand,  row,  col,  cc );
}

Nat32 CEuInstallerStub_mtxtstub_Priv::dsdrv3_ReadCharacter( TWindowId handl, Nat8 row, Nat8 col )
{
	return  txdsdrv__dsdrv3_ReadCharacter(  handl,  row,  col );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_WriteString(TWindowId handl,Nat8 row,Nat8 col,Nat8 len,Nat32* string )
{
	txdsdrv__dsdrv3_WriteString(  handl,  row,  col,  len,  string );
}

Nat8 CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetWindowStartRow( TWindowId handl )
{
	return txdsdrv__dsdrv3_GetWindowStartRow(  handl );
}

Nat8 CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetWindowStartColumn( TWindowId handl )
{
	return txdsdrv__dsdrv3_GetWindowStartColumn(  handl );
}

Nat8 CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetWindowEndRow( TWindowId handl )
{
	return txdsdrv__dsdrv3_GetWindowEndRow(  handl );
}

Nat8 CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetWindowEndColumn( TWindowId handl )
{
	return txdsdrv__dsdrv3_GetWindowEndColumn(  handl );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_CloseWindow( TWindowId handl )
{
	 txdsdrv__dsdrv3_CloseWindow( handl );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_ChangeWindowCoordinates( TWindowId handl, Nat8 TopLeftRow, Nat8 TopLeftColumn, Nat8 BottomRightRow, Nat8 BottomRightColumn )
{
	txdsdrv__dsdrv3_ChangeWindowCoordinates(  handl,  TopLeftRow,  TopLeftColumn,  BottomRightRow,  BottomRightColumn );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_InitAttrCharacterCode( Nat32* cc )
{
	txdsdrv__dsdrv3_InitAttrCharacterCode(  cc );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetAttrUnderlineSeparate( Nat32* cc, Bool us )
{
	txdsdrv__dsdrv3_SetAttrUnderlineSeparate( cc,  us );
}

Bool CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetAttrUnderlineSeparate( Nat32 cc )
{
	return txdsdrv__dsdrv3_GetAttrUnderlineSeparate(  cc );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetAttrFontAndCharacter( Nat32* cc, Font font, Language lng, int ch )
{
	 txdsdrv__ixrdsdrv2_SetConversionFontAndCharacter(  cc,  font,  lng,  ch );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetAttrDoubleHeight( Nat32* cc, Bool dh )
{
	txdsdrv__dsdrv3_SetAttrDoubleHeight(  cc, dh );
}

Bool CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetAttrDoubleHeight( Nat32 cc )
{
	return txdsdrv__dsdrv3_GetAttrDoubleHeight( cc );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetAttrDoubleWidth( Nat32* cc, Bool dw )
{
	txdsdrv__dsdrv3_SetAttrDoubleWidth( cc, dw );
}

Bool CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetAttrDoubleWidth( Nat32 cc )
{
	return txdsdrv__dsdrv3_GetAttrDoubleWidth(  cc );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetAttrFlashMode( Nat32* cc, Nat8 fm )
{
	txdsdrv__dsdrv3_SetAttrFlashMode( cc, fm );
}

Nat8 CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetAttrFlashMode( Nat32 cc )
{
	return txdsdrv__dsdrv3_GetAttrFlashMode( cc );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetAttrFlashPhase( Nat32* cc, Nat8 fp )
{
	txdsdrv__dsdrv3_SetAttrFlashPhase( cc, fp );
}

Nat8 CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetAttrFlashPhase( Nat32 cc )
{
	return txdsdrv__dsdrv3_GetAttrFlashPhase(  cc );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetAttrBox( Nat32* cc, Bool box )
{
	txdsdrv__dsdrv3_SetAttrBox( cc, box );
}

Bool CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetAttrBox( Nat32 cc )
{
	return txdsdrv__dsdrv3_GetAttrBox(  cc );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetAttrForegroundColour( Nat32* cc, int fg )
{
	 txdsdrv__dsdrv3_SetAttrForegroundColour( cc, fg );
}

int CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetAttrForegroundColour( Nat32 cc )
{
	return  txdsdrv__dsdrv3_GetAttrForegroundColour(  cc );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetAttrBackgroundColour( Nat32* cc, int bg )
{
	txdsdrv__dsdrv3_SetAttrBackgroundColour( cc,  bg );
}

int CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetAttrBackgroundColour( Nat32 cc )
{
	return  txdsdrv__dsdrv3_GetAttrBackgroundColour(  cc );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetConversionCurrentPosition( TWindowId handl,  Nat8 row, Nat8 col )
{
	txdsdrv__ixrdsdrv2_SetConversionCurrentPosition(  handl,  row,  col );
}

Nat8 CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetConversionCurrentRow( TWindowId handl )
{
	return  txdsdrv__ixrdsdrv2_GetConversionCurrentRow( handl );
}

Nat8 CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetConversionCurrentColumn( TWindowId handl )
{
	return txdsdrv__dsdrv3_GetConversionCurrentColumn( handl );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetConversionLanguageContext( TWindowId  handl, Language lng )
{
	txdsdrv__dsdrv3_SetConversionLanguageContext(  handl,  lng );
}

Language CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetConversionLanguageContext( TWindowId handl )
{
	return txdsdrv__dsdrv3_GetConversionLanguageContext(  handl );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetConversionUnderlineSeparate( TWindowId handl, Bool ul_sep )
{
	txdsdrv__dsdrv3_SetConversionUnderlineSeparate(  handl,  ul_sep );
}

Bool CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetConversionUnderlineSeparate( TWindowId handl )
{
	return   txdsdrv__dsdrv3_GetConversionUnderlineSeparate(  handl );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_WriteConversionCharacter( TWindowId handl, int charcode, TConvAttrUnion ca )
{
	 txdsdrv__ixrdsdrv2_WriteConversionCharacter(  handl,  charcode,  ca );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_WriteConversionAccentedCharacter( TWindowId handl, int charcode, int accentcode, TConvAttrUnion ca )
{
	txdsdrv__dsdrv3_WriteConversionAccentedCharacter(  handl,  charcode,  accentcode, ca );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetConversionAttributes( TWindowId handl, TConvAttrUnion ca )
{
	txdsdrv__dsdrv3_SetConversionAttributes(  handl,  ca );
}

Bool CEuInstallerStub_mtxtstub_Priv::dsdrv3_ConversionIsOnLeftSide( TWindowId handl )
{
	return  txdsdrv__dsdrv3_ConversionIsOnLeftSide( handl );
}
/*
void CEuInstallerStub_mtxtstub_Priv::dsdrv3_CopyConvAttributes( TConvAttrUnion* ca1, TConvAttrUnion* ca2 )
{
	return 0;
}*/

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetConvRowDisplayEnable( Nat8 row, Bool enb, Bool left )
{
	 txdsdrv__dsdrv3_SetConvRowDisplayEnable( row, enb, left );
}
/*
void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetConvRowNewsflashSubtitleEnable( Nat8 row, Bool enb, Bool left )
{
	return 0;
}*/

Nat32* CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetConvRowAttributesPointer( Nat8 row, Bool left )
{
	return  txdsdrv__dsdrv3_GetConvRowAttributesPointer(  row,  left );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetConvRowForeAndBackgroundColBank( Nat8 row, Bool fgColBank, Bool bgColBank, Bool left )
{
	txdsdrv__dsdrv3_SetConvRowForeAndBackgroundColBank(  row,  fgColBank,  bgColBank,  left );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetConvRowForeAndBackgroundClutSelection( Nat8 row, Bool fgClutSel, Bool bgClutSel, Bool left )
{
	txdsdrv__dsdrv3_SetConvRowForeAndBackgroundClutSelection(  row,  fgClutSel,  bgClutSel,  left );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetScreenTopBottomColour( int colour, Bool tb, Bool left )
{
	 txdsdrv__dsdrv3_SetScreenTopBottomColour(  colour,  tb,  left );
}

int CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetScreenTopBottomColour( Bool tb, Bool left )
{
	return  txdsdrv__dsdrv3_GetScreenTopBottomColour(  tb,  left );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetScreenRowColour(Nat8 row, int colour, Bool left)
{
	txdsdrv__dsdrv3_SetScreenRowColour(  row,  colour, left );
}

int CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetScreenRowColour( Nat8 row, Bool left )
{
	return  txdsdrv__dsdrv3_GetScreenRowColour(  row, left );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetScreenRowHeight( Nat8 row, int rh, Bool left)
{
	txdsdrv__dsdrv3_SetScreenRowHeight(  row,  rh,  left );
}

int CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetScreenRowHeight( Nat8 row, Bool left )
{
	return  txdsdrv__dsdrv3_GetScreenRowHeight(  row,  left );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetRowsDoubleHeight( int start, Nat8 nr_rows, Bool dh )
{
	txdsdrv__dsdrv3_SetRowsDoubleHeight(  start,  nr_rows,  dh );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetRowDisplayEnable( Nat8 row, Bool enb, Bool left )
{
	txdsdrv__dsdrv3_SetRowDisplayEnable(  row,  enb,  left );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetRowBoxEnable( Nat8 row, Bool enb, Bool left )
{
	 txdsdrv__dsdrv3_SetRowBoxEnable(  row,  enb,  left );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetRowNewsflashSubtitleEnable( Nat8 row, Bool enb, Bool left )
{
	txdsdrv__dsdrv3_SetRowNewsflashSubtitleEnable(  row,  enb,  left );
}

Bool CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetRowNewsflashSubtitleEnable( Nat8 row, Bool left )
{
	return txdsdrv__dsdrv3_GetRowNewsflashSubtitleEnable(  row,  left );
}

Nat32* CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetRowAttributesPointer( Nat8 row, Bool left )
{
	return txdsdrv__dsdrv3_GetRowAttributesPointer(  row, left );
}

Nat8 CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetRowForegroundColBank( Nat8 row, Bool left )
{
	return  txdsdrv__dsdrv3_GetRowForegroundColBank(  row,  left );
}

Nat8 CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetRowBackgroundColBank( Nat8 row, Bool left )
{
	return txdsdrv__dsdrv3_GetRowBackgroundColBank(  row, left );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetRowForeAndBackgroundColBank( Nat8 row, Bool fgColBank, Bool bgColBank, Bool left )
{
	 txdsdrv__dsdrv3_SetRowForeAndBackgroundColBank(  row,  fgColBank,  bgColBank,  left );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetRowForeAndBackgroundClutSelection( Nat8 row, Bool fgClutSel, Bool bgClutSel, Bool left )
{
	txdsdrv__dsdrv3_SetRowForeAndBackgroundClutSelection(  row,  fgClutSel,  bgClutSel,  left );
}

Bool CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetRemapRowClutArea( Nat8 row, Bool fg, Bool left )
{
	return  txdsdrv__dsdrv3_GetRemapRowClutArea(  row,  fg,  left );
}

void CEuInstallerStub_mtxtstub_Priv::dsdrv3_SetRamPalette( int start, int count, Nat32 *rgba )
{
	 txdsdrv__dsdrv3_SetRamPalette(  start,  count,  rgba );
}

Nat32 CEuInstallerStub_mtxtstub_Priv::dsdrv3_GetBodyPadHeaderId()
{
	//TraceNotice (m, "%s %d",__FUNCTION__,__LINE__);
	return txdsdrv__dsdrv3_GetBodyPadHeaderId(  );
}

Bool CEuInstallerStub_mtxtstub_Priv::dsdrv3_ReadGfxCharacter( TWindowId handl, Nat32 row, Nat32 col, Nat32 *charbits, Nat32 *charcol, Nat32 *charctrl )
{
	return  txdsdrv__dsdrv3_ReadGfxCharacter(  handl,  row,  col,  charbits,  charcol,  charctrl );
}

/* Interfaces from IHsvTxtPageRequest.id */
int CEuInstallerStub_mtxtstub_Priv::req_RequestPage( PageNr page, Subcode subcode, FncReceived fnc, int tag )
{
	return txsto__req_RequestPage(  page,  subcode,  fnc,  tag );
}

void CEuInstallerStub_mtxtstub_Priv::req_UnRequestPage( PageNr page, Subcode subcode, FncReceived fnc )
{
	if(page > 0x7ff)
	{
		__android_log_print(ANDROID_LOG_DEBUG, "req_UnRequestPage invalid page","%s %d  page %d ",__FUNCTION__,__LINE__,page);
	}
	else{
	
	 txsto__req_UnRequestPage(  page,  subcode,  fnc );
	 }
}

void CEuInstallerStub_mtxtstub_Priv::req_SuggestPage( PageNr page )
{
	txsto__req_SuggestPage( page );
}

void CEuInstallerStub_mtxtstub_Priv::req_UnSuggestPage( PageNr page )
{
	txsto__req_UnSuggestPage(  page );
}

Bool CEuInstallerStub_mtxtstub_Priv::req_SetType(PageNr page, PageType ptype, Bool priority, FncCallBack func)
{
	return  txsto__req_SetType(  page,  ptype,  priority,  func );
}

/* Interfaces from IHsvTxtPageAccess.id */
TxtPageHandle CEuInstallerStub_mtxtstub_Priv::acc_OpenPageForRead( PageNr page, Subcode subcode)
{
	return txsto__str_OpenPageForRead(page,subcode);
}

void CEuInstallerStub_mtxtstub_Priv::acc_ClosePage( TxtPageHandle hnd )
{
	txsto__str_ClosePage(hnd);
}

Nat8 * CEuInstallerStub_mtxtstub_Priv::acc_GetPacket( TxtPageHandle hnd, PacketNumber pkt_num )
{
	return (PageLinkCache[hnd].packets[pkt_num]->data);
}

/* Interfaces from IHsvTxtDecode.id */
void CEuInstallerStub_mtxtstub_Priv::dec_DecodeOddParity(Nat8 *src, Nat8 *dst, Nat8 *old, int size )
{
	txdec__dec_DecodeOddParity(src,dst,old,size);
}

/* Interfaces from IHsvTextDisplay.id */
Nat32 CEuInstallerStub_mtxtstub_Priv::gfxtxt_CreateHeader( int NoOfClutEntries )
{
	return  txtgfxdsp__gfxtxt2_CreateHeader(  NoOfClutEntries );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_DeleteHeader( Nat32 headerId )
{
	 txtgfxdsp__gfxtxt2_DeleteHeader(  headerId );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_TruncateHeader( Nat32 headerId, int sections )
{
	  txtgfxdsp__gfxtxt2_TruncateHeader(  headerId,  sections );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_ResetHeader( Nat32 headerId )
{
	txtgfxdsp__gfxtxt2_ResetHeader( headerId );
}

Nat32 CEuInstallerStub_mtxtstub_Priv::gfxtxt_CreateString( Nat32 headerId, int maxChar, Nat32 ul_x, Nat32 ul_y )
{
	return   txtgfxdsp__gfxtxt2_CreateString(  headerId,  maxChar,  ul_x,  ul_y );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_RepositionString( Nat32 stringId, Nat8 window, Nat16 pos, Nat32 ul_x, Nat32 ul_y ) //added
{
	txtgfxdsp__gfxtxt2_RepositionString(  stringId,  window,  pos,  ul_x,  ul_y );
}

Nat32 CEuInstallerStub_mtxtstub_Priv::gfxtxt_CreateFiller( Nat32 headerId, Nat32 ul_x, Nat32 ul_y, Nat32 lr_x, Nat32 lr_y, Nat8 clutIndex )
{
	return  txtgfxdsp__gfxtxt2_CreateFiller(  headerId,  ul_x,  ul_y,  lr_x,  lr_y,  clutIndex );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_RepositionFiller( Nat32 fillerId, Nat32 ul_x, Nat32 ul_y, Nat32 lr_x, Nat32 lr_y) //added
{
	txtgfxdsp__gfxtxt2_RepositionFiller(  fillerId,  ul_x,  ul_y,  lr_x,  lr_y );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetFillerColor( Nat32 fillerId, Nat8 clutIndex )
{
	txtgfxdsp__gfxtxt2_SetFillerColor(  fillerId, clutIndex );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_Configure( Nat32 multipleId, Nat32 Font, Nat32 width, Nat32 ht, Nat32 fntSize, Nat32 controlBits )  //modified - imp
{
	txtgfxdsp__gfxtxt2_Configure(  multipleId,  Font,  width,  ht,  fntSize,  controlBits );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_GetBounds(Nat32 multipleId, Nat32 *ul_x, Nat32 *ul_y, Nat32 *lr_x, Nat32 *lr_y ) //added - imp
{
	txtgfxdsp__gfxtxt2_GetBounds(  multipleId,  ul_x,  ul_y, lr_x,  lr_y );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetVisibility( Nat32 multipleId, Bool visible )
{
	 txtgfxdsp__gfxtxt2_SetVisibility(  multipleId,  visible );
}

Nat32 CEuInstallerStub_mtxtstub_Priv::gfxtxt_PackColors(Nat8 border, Nat8 flash, Nat8 back, Nat8 fore ) //modified, added border - imp
{
	return ((Nat32)( (((border)&0xff)<<24) | (((flash)&0xff)<<16) | (((back)&0xff)<<8) | ((fore)&0xff) ));
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetBorderColor( Nat32 *pCharCol, Nat8 border ) //added - imp
{
	((*pCharCol) |= ((border&0xff)<<24));
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetForeColor( Nat32 *pCharCol, Nat8 fore )
{
	((*pCharCol) |= (fore&0xff));
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetBackColor( Nat32 *pCharCol, Nat8 back )
{
		((*pCharCol) |= ((back&0xff)<<8));
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetFlashColor( Nat32 *pCharCol, Nat8 flash )
{
		((*pCharCol) |= ((flash&0xff)<<16));
}

Nat8 CEuInstallerStub_mtxtstub_Priv::gfxtxt_GetBorderColor( Nat32 charCol ) //added - imp
{
	return (((charCol) & 0xff000000)>>24);
}

Nat8 CEuInstallerStub_mtxtstub_Priv::gfxtxt_GetForeColor( Nat32 charCol )
{
	return 	((charCol) & 0xff);
}

Nat8 CEuInstallerStub_mtxtstub_Priv::gfxtxt_GetBackColor( Nat32 charCol )
{
	return (((charCol) & 0xff00)>>8);
}

Nat8 CEuInstallerStub_mtxtstub_Priv::gfxtxt_GetFlashColor( Nat32 charCol )
{
	return (((charCol) & 0xff0000)>>16);
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_AddCharacter( Nat32 stringId, Nat32 charBits, Nat32 charCol, Nat32 fntSize, Nat32 charCtrl ) //modified, added fntSize - imp
{
	return;
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_ModifyCharacters( Nat32 stringId, Nat32 charNum, Nat32 charBits, Nat32 CharCol, Nat32 fntSize, Nat32 borderstyle, Nat32 CharCtrl ) //modified, added fntSize - imp
{
	 txtgfxdsp__gfxtxt2_ModifyCharacters(  stringId,  charNum,  charBits,  CharCol,  fntSize,  borderstyle,  CharCtrl );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_CopyCharacters( Nat32 srcStringId, Nat32 dstStringId, Nat32 attrib )
{
	 txtgfxdsp__gfxtxt2_CopyCharacters(  srcStringId,  dstStringId,  attrib );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_GetCharacter(Nat32 stringId, Nat32 charNum, Nat32 *CharBits, Nat32 *CharCol, Nat32 *CharCtrl, Nat32 *FntSize ) //modified, added fntsize - imp
{
	 txtgfxdsp__gfxtxt2_GetCharacter(  stringId,  charNum,  CharBits, CharCol, CharCtrl ,FntSize);
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_GetCharacterAdvance(Nat32 CharBits, Nat32 CharCol, Nat32 CharCtrl, Nat32 *width, Nat32 *height ) //added - imp
{
	txtgfxdsp__gfxtxt2_GetCharacterAdvance(  CharBits,  CharCol,  CharCtrl,  width, height );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetCursor( Nat32 headerId, Nat32 ul_x, Nat32 ul_y, Nat32 lr_x, Nat32 lr_y )
{
	 txtgfxdsp__gfxtxt2_SetCursor(  headerId,  ul_x,  ul_y,  lr_x,  lr_y );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetCursorVisiblity( Nat32 headerId, Bool onoff ) //added
{
	return;
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetCursorBorderColors( Nat32 headerId, int innerBox, int outerBox ) //added
{
	return;
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetColor( Nat32 headerId, int start, Nat8 noOfEntries, Nat32 *pColor )
{
	 txtgfxdsp__gfxtxt2_SetColor(  headerId,  start,  noOfEntries,  pColor );
}

Nat32 CEuInstallerStub_mtxtstub_Priv::gfxtxt_GetColor( Nat32 headerId, int clutindex )
{
	return  txtgfxdsp__gfxtxt2_GetColor(  headerId,  clutindex );
}

Nat32 CEuInstallerStub_mtxtstub_Priv::gfxtxt_PackARGB( Nat8 alpha, Nat8 red, Nat8 green, Nat8 blue )
{
	return  txtgfxdsp__gfxtxt2_PackARGB(  alpha,  red,  green,  blue );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_UnPackARGB( Nat32 value, Nat8 *pAlpha, Nat8 *pRed, Nat8 *pGreen, Nat8 *pBlue )
{
	txtgfxdsp__gfxtxt2_UnPackARGB(  value,  pAlpha,  pRed,  pGreen,  pBlue );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetFlash( Bool onoff ) //added
{
	 txtgfxdsp__gfxtxt2_SetFlash(  onoff );
}

Nat32 CEuInstallerStub_mtxtstub_Priv::gfxtxt_StoreBitmaps( Nat32 headerId, Nat32 size, Nat32 *pInput, Nat8 inputType, Nat32 bitMapId )
{
	return txtgfxdsp__gfxtxt2_StoreBitmaps(  headerId,  size,  pInput,  inputType,  bitMapId );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_Draw( void )
{
	txtgfxdsp__gfxtxt2_Draw();
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_DrawTextPad( Nat8 window, Nat16 pos )
{
	//TraceNotice (m, "%s %d",__FUNCTION__,__LINE__);
	 txtgfxdsp__gfxtxt2_DrawTextPad(  window,  pos );}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_Scroll(Nat8 window, Nat16 pos, Nat8 UpDown ) //added
{
	 txtgfxdsp__gfxtxt2_Scroll(  window,  pos,  UpDown );
}

Bool CEuInstallerStub_mtxtstub_Priv::gfxtxt_Register( int clientId )
{
	return  txtgfxdsp__gfxtxt2_Register( clientId );
}

Bool CEuInstallerStub_mtxtstub_Priv::gfxtxt_UnRegister( int clientId )
{
	return  txtgfxdsp__gfxtxt2_UnRegister(  clientId );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetDisplayVisibility( Bool onOff )
{
	txtgfxdsp__gfxtxt2_SetDisplayVisibility(  onOff );
}

Bool CEuInstallerStub_mtxtstub_Priv::gfxtxt_GetDisplayVisibility( void )
{
	return  txtgfxdsp__gfxtxt2_GetDisplayVisibility( );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_AttachTextPad( Nat8 window, int pos, Nat32 headerId )
{
	txtgfxdsp__gfxtxt2_AttachTextPad(  window,  pos,  headerId );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_DetachTextPad( Nat8 window, Nat16 pos )
{
	  txtgfxdsp__gfxtxt2_DetachTextPad(  window,  pos );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_ScrollSetUp( Nat32 headerId, Nat8 ScrollIncr ) //added
{
	 txtgfxdsp__gfxtxt2_ScrollSetUp( headerId, ScrollIncr );
}

Bool CEuInstallerStub_mtxtstub_Priv::gfxtxt_GetRevealMode( Nat8 window )
{
	return  txtgfxdsp__gfxtxt2_GetRevealMode( window );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetRevealMode( Nat8 window, Bool mode )
{
	 txtgfxdsp__gfxtxt2_SetRevealMode(  window, mode );;
}

Bool CEuInstallerStub_mtxtstub_Priv::gfxtxt_GetMixMode( Nat8 window )
{
	return  txtgfxdsp__gfxtxt2_GetMixMode( window );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetMixedMode( Nat8 window, Bool mode )
{
	 txtgfxdsp__gfxtxt2_SetMixedMode( window, mode );
}

Nat8 CEuInstallerStub_mtxtstub_Priv::gfxtxt_GetPageMode( void )
{
	return  txtgfxdsp__gfxtxt2_GetPageMode();
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetPageMode( Nat8 mode )
{
	txtgfxdsp__gfxtxt2_SetPageMode( mode );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_RowMapInit( void )
{
	 txtgfxdsp__gfxtxt2_RowMapInit( );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_RowMapInitPlain( void )
{
	txtgfxdsp__gfxtxt2_RowMapInitPlain( );
}

Nat32 CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetUpRowMapEntry( Nat16 txtPadRow, Bool dispEn, Bool doubleHt, Bool showBottom )
{
	return  txtgfxdsp__gfxtxt2_SetUpRowMapEntry(  txtPadRow,  dispEn,  doubleHt,  showBottom );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetRowMapEntry( Nat8 window, Nat16 pos, Nat16 canvasRow, Nat32 rowEntry )
{
	 txtgfxdsp__gfxtxt2_SetRowMapEntry(  window,  pos,  canvasRow,  rowEntry );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetRowMapRange( Nat8 window, Nat16 pos, Nat16 canvasRowStart, Nat16 rowCount, Nat32 rowEntry )
{
	 txtgfxdsp__gfxtxt2_SetRowMapRange(  window,  pos,  canvasRowStart,  rowCount,  rowEntry );
}

void CEuInstallerStub_mtxtstub_Priv::gfxtxt_SetFillerMap( Nat8 window, Nat16 topEndRow, Nat16 bottomStartRow)
{
	  txtgfxdsp__gfxtxt2_SetFillerMap(  window,  topEndRow,  bottomStartRow );
}

void CEuInstallerStub_mtxtstub_Priv::plfvbintf_onWstData(int wsttype,const int nrLines,int * const pLines,const int sizeFirstBuffer,const int sizeSecondBuffer,int * const firstBuffer,int * const secondBuffer)
{
__android_log_print(ANDROID_LOG_DEBUG, "CHsvtxtPlfsvc_m_Priv","plfvbintf_onWstData called");
	//if( sizeFirstBuffer > 0)
	//writeData(sizeFirstBuffer,(unsigned char *)firstBuffer);
	
	txvbi__vbislN_OnWstData (wsttype, nrLines, pLines, sizeFirstBuffer, sizeSecondBuffer, firstBuffer, secondBuffer);	
	
}

void CEuInstallerStub_mtxtstub_Priv::plfvbintf_onWstNoData( void )
{
    __android_log_print(ANDROID_LOG_DEBUG, "CHsvtxtPlfsvc_m_Priv","plfvbintf_onWstNoData called");
	txvbi__vbislN_OnWstNoData();
}

void CEuInstallerStub_mtxtstub_Priv::plfvbintf_onVpsData(const int size,int * const buffer)
{
	//txvbi__vbislN_onVpsData(size, buffer );
}

void CEuInstallerStub_mtxtstub_Priv::plfvbintf_onVpsNoData( void )
{
//	txvbi__vbislN_onVpsNoData ();
}

/*IEnable dcu */
void CEuInstallerStub_mtxtstub_Priv::dcu_Enable(void)
{
    __android_log_print(ANDROID_LOG_DEBUG, "CHsvtxtPlfsvc_m_Priv","dcu_Enable called");
	TxtplfHandle->plfvbi_Enable();
	txvbi__dcu_Enable();
}
void CEuInstallerStub_mtxtstub_Priv::dcu_Disable(void)
{
	TxtplfHandle->plfvbi_Disable();
	txvbi__dcu_Disable();
}

/*IEnable dsenb*/
void CEuInstallerStub_mtxtstub_Priv::dsenb_Enable(void)
{
 txdscnv__pow_TurnOn( );
}
void CEuInstallerStub_mtxtstub_Priv::dsenb_Disable(void)
{
  txdscnv__pow_TurnOff();
}
/*IHsvTsvChannelName chlname*/
Bool CEuInstallerStub_mtxtstub_Priv::chlname_GetCurrentChannelLabel ( String label )
{
	return txsvc__chlname_GetCurrentChannelLabel( label );
}



void cpp_topN_OnTopUpdate(  Nat16 notify )
{
	return;
}

void cpp_tranN_OnTransmissionChanged (void)
{
	return;
}

void cpp_mode2N_OnModeChanged(int mode)
{
	return;
}

void cpp_wsrN_OnSearchPage( PageNr page_in_search )
{
	return;
}

void cpp_wsrN_OnStartSearchInTransmission( void )
{
	return;
}

void cpp_wsrN_OnEndOfSearch( Bool word_found )
{
	return;
}

void cpp_wnavN_OnExitHypertext ( void )
{
	return;
}

void cpp_ponN_OnPonChanged(void)
{
	return;
}

void cpp_pctlN_OnPageArrived     ( PageNr pg, Subcode subcd )
{
	return;
}

void cpp_pctlN_OnPageDropped     ( PageNr pg )
{
	return;
}

void cpp_pctlN_OnSubcodeArrived  ( Subcode subcd )
{
	return;
}

void cpp_pctlN_OnPageDisplayed   ( Int16 pg )
{
	return;
}

Pump cpp_pmp_PmpCreateEx ( PumpEngine pen, PumpFunc func, Bool replace, char* name )
{
	Pump pmp;
	
	//pmp = pmpfac->PmpCreate(TxtplfHandle->pen->PumpEngine(), func, replace, name ) ;
	pmp = pmpfac->PmpCreate(CoreInstance->sundry->PumpEngine(), func, replace, name ) ;
	
	//__android_log_print(ANDROID_LOG_DEBUG, "CEuInstallerStub_mtxtstub_Priv","TxtplfHandle = %x pmp = %x ",TxtplfHandle,pmp);
	return pmp;

}

void       cpp_pmp_PmpSend     ( Pump pmp, int param1, Nat32 param2 )
{
	__android_log_print(ANDROID_LOG_DEBUG, "CEuInstallerStub_mtxtstub_Priv","TxtplfHandle = %x cpp_pmp_PmpSend event = %d ",TxtplfHandle,param1);

pmpfac->PmpSend( pmp,param1,  param2 );
	return;
}
void       cpp_pmp_PmpSendAfter( Pump pmp, int param1, Nat32 param2, int msecs )
{
	__android_log_print(ANDROID_LOG_DEBUG, "CEuInstallerStub_mtxtstub_Priv","TxtplfHandle = %x cpp_pmp_PmpSendAfter event = %d ",TxtplfHandle,param1);

pmpfac->PmpSendAfter( pmp,param1,  param2,  msecs );
	return;
}

Bool       cpp_pmp_PenTaskHasLock( PumpEngine pen )
{
	return FALSE;
}

STimer cpp_tmr_Create   ( Function ntf )
{
	STimer retval = 0;
	return retval;
}
void   cpp_tmr_FireOnce ( STimer tmr, Int32 seconds)
{
	return;
}
void cpp_tmr_FireEvery( STimer tmr, Int32 seconds)
{
	return;
}
void   cpp_tmr_Cancel   ( STimer tmr)
{
	return;
}
void   cpp_tmr_Delete   ( STimer tmr)
{
	return;
}
Bool   cpp_tmr_State    ( STimer tmr, Int32 * remaining, Int32 * reload )
{
	return FALSE;
}
Semaphore cpp_rtk_SemCreate( void )
{
	Semaphore retval = 0;
	return retval;
}

void cpp_rtk_SemDelete( Semaphore sem )
{
	return;
}

void cpp_rtk_SemAcquire( Semaphore sem )
{
	return;
}

void cpp_rtk_SemRelease( Semaphore sem )
{
	return;
}

Bool cpp_rtk_SemAcquireNoWait( Semaphore sem )
{
	return FALSE;
}

void cpp_SetClock(int Time)
{
return;
}
int cpp_sysset_GetMenuLanguage(void )
{
	return 0;
}
int cpp_sysset_GetInstallCountry(void)
{
	return 0;
}

Bool cpp_GetNvmLevel25Processing(void)
{
	return FALSE;
}

int cpp_vbisl_EnableAutoSlicing(int winid,Bool enable,Nat32 * retval)
{
	//TraceNotice (m, "EnableAutoSlicing called from Teletext library");
		return TxtplfHandle->plfvbi_EnableAutoSlicing( winid,enable,retval);
//return 1;//TxtplfHandle->vbisl->EnableAutoSlicing( winid,enable,retval);
}
 int cpp_vbisl_SetSlicermode(int winid,Nat32 subscriptions,Nat32 * retval)
 {
	//TraceNotice (m, "SetSlicerMode called from Teletext library");	
	return TxtplfHandle->plfvbi_SetSlicermode(winid,0x0C, retval); 
	// TxtplfHandle->vbisl->SetSlicermode(winid,subscriptions, retval);
 }
 
 
  FResult cpp_gfxacc3_Register(int gfxclientId,Nat32 buffWidth,Nat32 buffHeight,
                Nat32 buffFmtClass,Nat32 buffFmtType,Nat32 clutSize,Nat8 backBuffers,
                int colorKey,Nat32 clearColor,int srfHnd)
				{
					CHECK_GFX()
					return GfxNative->gfxacc->Register(gfxclientId,buffWidth,buffHeight,buffFmtClass,buffFmtType,clutSize,backBuffers,
									colorKey,clearColor,srfHnd);
				}
    	 FResult cpp_gfxacc3_UnRegister(int gfxclientId)
		 {
			CHECK_GFX()
			return GfxNative->gfxacc->UnRegister(gfxclientId);
		 }
    	 FResult cpp_gfxacc3_GetPlaneId(int gfxclientId,int * pPlaneId)
		 {
			CHECK_GFX()
			return GfxNative->gfxacc->GetPlaneId(gfxclientId, pPlaneId);
		 }
    	 FResult cpp_gfxacc3_GetSurfaceHnd(int gfxclientId,int * pSrfHnd)
		 {
			CHECK_GFX()
			return GfxNative->gfxacc->GetSurfaceHnd(gfxclientId,pSrfHnd);
		 }
    	 FResult cpp_gfxacc3_GetClutHnd(int gfxclientId,int * pClutHnd)
		 {
			CHECK_GFX()
			return GfxNative->gfxacc->GetClutHnd(gfxclientId,pClutHnd);
		 }
    	 FResult cpp_gfxacc3_ScreenUpdate(int gfxclientId,Bool partial,int ul_x,int ul_y,
                int lr_x,int lr_y)
		{
			CHECK_GFX()
			return GfxNative->gfxacc->ScreenUpdate(gfxclientId,partial,ul_x,ul_y,
                lr_x,lr_y);
		 }
    	 FResult cpp_gfxacc3_GetWindowId(int gfxclientId,Nat32 * pwndId)
		 {
			CHECK_GFX()
			return GfxNative->gfxacc->GetWindowId(gfxclientId,pwndId);
		 }
    	 FResult cpp_gfxacc3_RequestFocus(int gfxclientId)
		 {
		 CHECK_GFX()
			return GfxNative->gfxacc->RequestFocus(gfxclientId);
		
		 }
    	 FResult cpp_gfxacc3_SetVisibility(int gfxclientId,Bool visible)
		 {
		 //__android_log_print(ANDROID_LOG_DEBUG, "CHsvtxtPlfsvc_m_Priv","ClearSurface");
				// GfxNative->gfxacc->ClearSurface(0xff,0xff,0xff,0xff);								
				CHECK_GFX()
				return GfxNative->gfxacc->SetVisibility(gfxclientId,visible);
		 }
    	 FResult cpp_gfxacc3_GetVisiblity(int gfxclientId,Bool * pVisibility)
		 {
			CHECK_GFX()
			return GfxNative->gfxacc->GetVisiblity(gfxclientId,pVisibility);
		 }
    	 FResult cpp_gfxacc3_ScreenUpdateNoNotify(int gfxclientId,Bool partial,int ul_x,
                int ul_y,int lr_x,int lr_y)
		{
			CHECK_GFX()
			return GfxNative->gfxacc->ScreenUpdateNoNotify(gfxclientId,partial, ul_x,
                ul_y,lr_x,lr_y);
		 }
    	 FResult cpp_gfxacc3_GetDfbParams(int gfxclientId,Address * dfb_ptr,
                Address * Surface)
				{
				CHECK_GFX()
			return GfxNative->gfxacc->GetDfbParams( gfxclientId, dfb_ptr,
                Surface);
		 }
    	 FResult cpp_gfxacc3_GetDfbParamsEx(int gfxclientId,Address * dfb_ptr,
                Address * Surface,Address * DFbWindow)
				{
				CHECK_GFX()
			return GfxNative->gfxacc->GetDfbParamsEx( gfxclientId, dfb_ptr,
                Surface,DFbWindow);
		 }
    	 FResult cpp_gfxacc3_ClearSurface(Nat8 r,Nat8 g,Nat8 b,Nat8 a)
		 {
		 CHECK_GFX()
			return GfxNative->gfxacc->ClearSurface(r,g,b,a);
		 }
    	 FResult cpp_gfxacc3_EnableMouseCursor(int gfxclientId,int cursorId,Bool enable)
		 {
		 CHECK_GFX()
			return GfxNative->gfxacc->EnableMouseCursor(gfxclientId,cursorId,enable);
		 }
    	 FResult cpp_gfxacc3_EnableMouseCursorEx(int gfxclientId,int cursorId,
                Bool enable,Bool hidden)
		{
			return 0;//GfxNative->gfxacc->EnableMouseCursorEx(gfxclientId,cursorId,enable,hidden);
		}
    	 FResult cpp_gfxacc3_SetWindowAssociation(int gfxclientId,int ParentId)
		 {
		 CHECK_GFX()
			return GfxNative->gfxacc->SetWindowAssociation(gfxclientId,ParentId);
		}
    	 FResult cpp_gfxacc3_SetMouseCursorPosition(int gfxclientId,int pos_x,int pos_y)
		 {
			return 0;
			// GfxNative->gfxacc->SetMouseCursorPosition(gfxclientId,pos_x,pos_y);
		}
		
		 FResult cpp_gfxsrf_CreateSurface(Nat32 PixClass,Nat32 PixType,Nat32 Width,
    	        Nat32 Height,Nat32 Stride,int BackBuffers,Nat8 MemType,int * pSrfHnd,
    	        Address * pBufferptrList)
		{
		CHECK_GFX()
			return GfxNative->gfxsurf->CreateSurface(PixClass,PixType,Width,
    	         Height, Stride, BackBuffers, MemType,pSrfHnd,pBufferptrList);
		}
    	  FResult cpp_gfxsrf_GetSurfaceAttributes(int srfHnd,Nat32 * PixClass,
                Nat32 * PixType,Nat32 * Width,Nat32 * Height,Nat32 * Stride,
                int * BackBuffers,Nat8 * MemType)
		{
		CHECK_GFX()
			return GfxNative->gfxsurf->GetSurfaceAttributes(srfHnd,PixClass,PixType,Width,Height,Stride,
                BackBuffers,MemType);
		}
    	 FResult cpp_gfxsrf_GetBufferAddress(int buffHnd,Address * pBuffAdd)
		 {
		 CHECK_GFX()
			return GfxNative->gfxsurf->GetBufferAddress(buffHnd,pBuffAdd);
		}
    	  FResult cpp_gfxsrf_DestroySurface(int srfHnd)
			{
			CHECK_GFX()
				return 	GfxNative->gfxsurf->DestroySurface(srfHnd);
			}
    	  FResult cpp_gfxsrf_Lock(int srfHnd,Nat8 BufferId,int * pBuffHnd)
		  {
		  CHECK_GFX()
				return 	GfxNative->gfxsurf->Lock(srfHnd,BufferId,pBuffHnd);
		  }
    	 FResult cpp_gfxsrf_UnLock(int * pbuffHnd)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxsurf->UnLock(pbuffHnd);				
		  }
    	  FResult cpp_gfxsrf_Flip(int srfHnd,FunctionIntInt FlipCallBack,Nat32 cookie)
		  {
		  CHECK_GFX()
				return 	GfxNative->gfxsurf->Flip(srfHnd,FlipCallBack,cookie);
		  }
    	 FResult cpp_gfxsrf_FlipNoNotify(int srfHnd,FunctionIntInt FlipCallBack,Nat32 cookie)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxsurf->FlipNoNotify(srfHnd,FlipCallBack,cookie);
		  }
    	 FResult cpp_gfxsrf_Blit(int srcbuff,int src_ul_x,int src_ul_y,int src_lr_x,
                int src_lr_y,int dstbuff,int dst_ul_x,int dst_ul_y,int dst_lr_x,
                int dst_lr_y,FunctionIntInt BlitCallBack,Nat32 cookie)
				{
				CHECK_GFX()
				return 	GfxNative->gfxsurf->Blit( srcbuff, src_ul_x, src_ul_y, src_lr_x,
                 src_lr_y, dstbuff, dst_ul_x, dst_ul_y, dst_lr_x,
                 dst_lr_y, BlitCallBack, cookie);
		  }
    	 FResult cpp_gfxsrf_CopyBlit(int srcbuffHnd,int src_rec_x,int src_rec_y,
                int src_rec_w,int src_rec_h,int dstbuffHnd,int dst_rec_x,
                int dst_rec_y,FunctionIntInt BlitCallBack,Nat32 cookie)
				{
				CHECK_GFX()
				return 	GfxNative->gfxsurf->CopyBlit( srcbuffHnd, src_rec_x, src_rec_y,
                 src_rec_w, src_rec_h, dstbuffHnd, dst_rec_x,
                 dst_rec_y, BlitCallBack, cookie);
		  }
    	 FResult cpp_gfxsrf_SetDirtyRectangle(int srfHnd,Bool partial,int ul_x,int ul_y,
                int lr_x,int lr_y)
				{
				CHECK_GFX()
				return 	GfxNative->gfxsurf->SetDirtyRectangle( srfHnd, partial, ul_x, ul_y,
                 lr_x, lr_y);
		  }
    	  Bool cpp_gfxsrf_IsCopyBlitSupported(void)
		  {
		  CHECK_GFX()
				return 	GfxNative->gfxsurf->IsCopyBlitSupported();
		  }
    	 FResult cpp_gfxsrf_SetClut(int srfHnd,int clutHnd)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxsurf->SetClut( srfHnd, clutHnd);
		  }
    	 FResult cpp_gfxsrf_GetClut(int srfHnd,int * pClutHnd)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxsurf->GetClut( srfHnd,pClutHnd);
		  }
    	 Nat32 cpp_gfxsrf_GetPixClass(int srfHnd)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxsurf->GetPixClass(srfHnd);
		  }
    	 Nat32 cpp_gfxsrf_GetPixType(int srfHnd)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxsurf->GetPixType(srfHnd);
		  }
    	  Nat32 cpp_gfxsrf_GetWidth(int srfHnd)
		  {
		  CHECK_GFX()
				return 	GfxNative->gfxsurf->GetWidth(srfHnd);
		  }
    	 Nat32 cpp_gfxsrf_GetHeight(int srfHnd)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxsurf->GetHeight(srfHnd);
		  }
    	 Nat32 cpp_gfxsrf_GetStride(int srfHnd)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxsurf->GetStride(srfHnd);
		  }
    	 int cpp_gfxsrf_GetNoOfBackBuffers(int srfHnd)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxsurf->GetNoOfBackBuffers(srfHnd);
		  }
    	 Nat8 cpp_gfxsrf_GetMemoryType(int srfHnd)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxsurf->GetMemoryType(srfHnd);
		  }
    	 FResult cpp_gfxsrf_Set3DGfxOption(int gfxclientId,int value)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxsurf->Set3DGfxOption(gfxclientId,value);
		  }


		 FResult cpp_gfxpln_GetBgSupported(int planeId,Bool * pbgSupp)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->GetBgSupported( planeId,pbgSupp);
		 }
		 
    	 FResult cpp_gfxpln_SetBgColor(int planeId,Nat32 bgcolor)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->SetBgColor(planeId,bgcolor);
		 }
    	 FResult cpp_gfxpln_GetBgColor(int planeId,Nat32 * pbgColor)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->GetBgColor(planeId,pbgColor);
		 }
    	 FResult cpp_gfxpln_SetVisibility(int planeId,Bool visible)
		 {
			CHECK_GFX()
				return 	GfxNative->gfxpln->SetVisibility(planeId,visible);
		 }
    	 FResult cpp_gfxpln_GetVisiblity(int planeId,Bool * pVisibility)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->GetVisiblity(planeId,pVisibility);
		 }
    	 FResult cpp_gfxpln_GetBlendFactorRange(int planeId,Nat32 * pMinBlendFactor,
                Nat32 * pMaxBlendFactor)
				{
				CHECK_GFX()
				return 	GfxNative->gfxpln->GetBlendFactorRange(planeId,pMinBlendFactor,
                pMaxBlendFactor);
		 }
    	 FResult cpp_gfxpln_GetBlendFactor(int planeId,Nat32 * pblendFactor)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->GetBlendFactor(planeId,pblendFactor);
		 }
		 
    	 FResult cpp_gfxpln_SetBlendFactor(int planeId,Nat32 blendFactor)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->SetBlendFactor(planeId,blendFactor);
		 }
    	 FResult cpp_gfxpln_SetPlaneSizeAndPosition(int planeId,Nat32 width,
                Nat32 height,int posX,int posY)
				{
				CHECK_GFX()
				return 	GfxNative->gfxpln->SetPlaneSizeAndPosition(planeId,width,
                 height,posX,posY);
		 }
    	 FResult cpp_gfxpln_GetPlaneSizeAndPosition(int planeId,Nat32 * pWidth,
                Nat32 * pHeight,int * pPosX,int * pPosY)
				{
				CHECK_GFX()
				return 	GfxNative->gfxpln->GetPlaneSizeAndPosition(planeId,pWidth,
                 pHeight,pPosX,pPosY);
		 }
    	 FResult cpp_gfxpln_GetMinimumPlaneSize(int planeId,Nat32 * pWidth,Nat32 * pHeight)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->GetMinimumPlaneSize(planeId,pWidth,pHeight);
		 }
    	 FResult cpp_gfxpln_GetMaximumPlaneSize(int planeId,Nat32 * pWidth,Nat32 * pHeight)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->GetMaximumPlaneSize(planeId,pWidth,pHeight);
		 }
    	 FResult cpp_gfxpln_GetMinimumViewRegionSize(int planeId,Nat32 * pWidth,
                Nat32 * pHeight)
				 {
				 CHECK_GFX()
				return 	GfxNative->gfxpln->GetMinimumViewRegionSize(planeId,pWidth,pHeight);
		 }
    	 FResult cpp_gfxpln_SetDstViewRegionSizeAndPosition(int planeId,
                Nat32 width,Nat32 Height,int posX,int posY)
				{
				CHECK_GFX()
				return 	GfxNative->gfxpln->SetDstViewRegionSizeAndPosition( planeId,
                 width, Height, posX, posY);
		 }
    	 FResult cpp_gfxpln_GetDstViewRegionSizeAndPosition(int planeId,
                Nat32 * pWidth,Nat32 * pHeight,int * pPosX,int * pPosY)
				{
				CHECK_GFX()
				return 	GfxNative->gfxpln->GetDstViewRegionSizeAndPosition( planeId,
                pWidth,pHeight,pPosX,pPosY);
		 }
    	 FResult cpp_gfxpln_SetSrcViewRegionSizeAndPosition(int planeId,
                Nat32 width,Nat32 height,int posX,int posY)
				{
				CHECK_GFX()
				return 	GfxNative->gfxpln->SetSrcViewRegionSizeAndPosition( planeId,
                 width, height, posX, posY);
		 }
    	 FResult cpp_gfxpln_GetSrcViewRegionSizeAndPosition(int planeId,
                Nat32 * pWidth,Nat32 * pHeight,int * pPosX,int * pPosY)
		{
			CHECK_GFX()
				return 	GfxNative->gfxpln->GetSrcViewRegionSizeAndPosition( planeId,
                 pWidth, pHeight, pPosX, pPosY);
		 }
    	 FResult cpp_gfxpln_GetSupportedScaleModes(int planeId,Nat32 * pScaleModes)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->GetSupportedScaleModes(planeId,pScaleModes);
		 }
    	 FResult cpp_gfxpln_GetScaleRange(int planeId,Nat32 scaleMode,
                Nat32 * pMinWidthPercentage,Nat32 * pMinHeightPercentage,
                Nat32 * pMaxWidthPercentage,Nat32 * pMaxHeigthPercentage)
				{
				CHECK_GFX()
				return 	GfxNative->gfxpln->GetScaleRange( planeId, scaleMode,
                 pMinWidthPercentage,pMinHeightPercentage,
                pMaxWidthPercentage, pMaxHeigthPercentage);
		 }
    	 FResult cpp_gfxpln_SetScaleMode(int planeId,Nat32 scaleMode)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->SetScaleMode(planeId,scaleMode);
		 }
    	 FResult cpp_gfxpln_GetScaleMode(int planeId,Nat32 * pScaleMode)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->GetScaleMode(planeId,pScaleMode);
		 }
    	 FResult cpp_gfxpln_GetPanoramaMidScaleRange(int planeId,
                Nat32 * pMinMidScaleFactor,Nat32 * pMaxMidScaleFactor)
				{
				CHECK_GFX()
				return 	GfxNative->gfxpln->GetPanoramaMidScaleRange(planeId,
                pMinMidScaleFactor, pMaxMidScaleFactor);
		 }
    	 FResult cpp_gfxpln_SetPanoramaMidScaleFactor(int planeId,
                Nat32 MidScaleFactor)
				{
				CHECK_GFX()
				return 	GfxNative->gfxpln->SetPanoramaMidScaleFactor( planeId,
                 MidScaleFactor);
		 }
    	 FResult cpp_gfxpln_GetPanoramaMidScaleFactor(int planeId,
                Nat32 * pMidScaleFactor)
				{
				CHECK_GFX()
				return 	GfxNative->gfxpln->GetPanoramaMidScaleFactor(planeId,
                pMidScaleFactor);
		 }
    	 FResult cpp_gfxpln_GetSupportedFormatClasses(int planeId,
                Nat32 * pFmtClass)
				{
				CHECK_GFX()
				return 	GfxNative->gfxpln->GetSupportedFormatClasses(planeId,
                pFmtClass);
		 }
    	 FResult cpp_gfxpln_GetSupportedFormatTypes(int planeId,Nat32 fmtclass,
                Nat32 * pFmtType)
				{
				CHECK_GFX()
				return 	GfxNative->gfxpln->GetSupportedFormatTypes(planeId,fmtclass,
                pFmtType);
		 }
    	 FResult cpp_gfxpln_GetSupportedNumberOfColorKeys(int planeId,Nat32 * pNoOfKeys)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->GetSupportedNumberOfColorKeys( planeId,pNoOfKeys);
		 }
    	 FResult cpp_gfxpln_GetSupportedColorKeyTypes(int planeId,Nat32 * pkeyTypes)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->GetSupportedColorKeyTypes( planeId,pkeyTypes);
		 }
    	 FResult cpp_gfxpln_SetColorKey(int planeId,Nat32 keyNr,Nat32 keytype,
                Nat32 lowerColor,Nat32 UpperColor)
				{
				CHECK_GFX()
				return 	GfxNative->gfxpln->SetColorKey( planeId, keyNr, keytype,
                 lowerColor, UpperColor);
		 }
    	 FResult cpp_gfxpln_GetColorKey(int planeId,Nat32 keyNr,Nat32 * pkeytype,
                Nat32 * plowerColor,Nat32 * pUpperColor)
		{
		CHECK_GFX()
				return 	GfxNative->gfxpln->GetColorKey( planeId, keyNr, pkeytype,
                 plowerColor, pUpperColor);
		 }
    	 FResult cpp_gfxpln_SetColorKeyActivation(int planeId,Nat32 keyNr,Bool enable)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->SetColorKeyActivation( planeId, keyNr, enable);
		 }
    	 FResult cpp_gfxpln_GetColorKeyActivation(int planeId,Nat32 keyNr,Bool * actStatus)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->GetColorKeyActivation( planeId, keyNr,actStatus);
		 }
    	 FResult cpp_gfxpln_AttachSurface(int planeId,int srfHnd)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->AttachSurface(planeId,srfHnd);
		 }
    	 FResult cpp_gfxpln_DetachSurface(int planeId,int srfHnd)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->DetachSurface(planeId,srfHnd);
		 }
    	 FResult cpp_gfxpln_GetAlignment(int planeId,Nat32 * palign)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->GetAlignment(planeId,palign);
		 }
    	 FResult cpp_gfxpln_SetTransitionParameters(int planeId,Nat32 msec)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->SetTransitionParameters(planeId,msec);
		 }
    	 FResult cpp_gfxpln_Lock(int planeId,int * pLockId)
		 {
		 CHECK_GFX()
			return 	GfxNative->gfxpln->Lock(planeId,pLockId);		 
		 }
		 
    	 FResult cpp_gfxpln_UnLock(int planeId,int lockId)
		 {
		 CHECK_GFX()
		 return 	GfxNative->gfxpln->UnLock(planeId,lockId);		 
		 }
    	 FResult cpp_gfxpln_RegisterCallBack(int planeId,FunctionIntInt fn,Nat32 cookie)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->RegisterCallBack(planeId,fn,cookie);
		 }
    	 FResult cpp_gfxpln_PlaneUpdate(int planeId)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->PlaneUpdate(planeId);
		 }
    	 void cpp_gfxpln_LockLayerBuffer(int planeId)
		 {
			if(GfxNative)
				 GfxNative->gfxpln->LockLayerBuffer(planeId);
		 }
    	 void cpp_gfxpln_UnlockLayerBuffer(int planeId)
		 {
		 if(GfxNative)
				 GfxNative->gfxpln->UnlockLayerBuffer( planeId);
		 }
    	 void cpp_gfxpln_SetLayerFormat(int planeId,Nat32 fmtclass,Nat32 fmttype)
		 {
			if(GfxNative)
				 GfxNative->gfxpln->SetLayerFormat(planeId,fmtclass,fmttype);
		 }
    	 void cpp_gfxpln_GetLayerFormat(int planeId,Nat32 * pfmtclass,Nat32 * pfmttype)
		 {
		 if(GfxNative)
				 GfxNative->gfxpln->GetLayerFormat( planeId, pfmtclass, pfmttype);
		 }
    	 Bool cpp_gfxpln_IsLayerModeSupported(int planeId,Nat32 layermode)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->IsLayerModeSupported( planeId, layermode);
		 }
    	 FResult cpp_gfxpln_SetGraphicLayerMode(int planeId,Nat32 layermode)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->SetGraphicLayerMode( planeId, layermode);
		 }
    	 Nat32 cpp_gfxpln_GetGraphicLayerMode(int planeId)
		 {
		 CHECK_GFX()
				return 	GfxNative->gfxpln->GetGraphicLayerMode( planeId);
		 }
