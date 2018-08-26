package org.droidtv.euinstallersat.util;

import org.droidtv.euinstallersat.model.mwapi.MwDataTypes;
import android.util.Log;


public class BouquetIdMapping
{
	private static final String TAG = "BouquetIdMapping";
	private static BouquetIdMapping m_instance = null;
	
	int[][] m_bouquetIdArray = new int[][]{
			
				{0,		org.droidtv.ui.strings.R.string.MAIN_BOUQUET_NO_SORTING},								/* No sorting */
				{1,		org.droidtv.ui.strings.R.string.MAIN_BOUQUET_AUSTRIA},									/* Austrian List */
				{2,		org.droidtv.ui.strings.R.string.MAIN_BOUQUET_GERMANY_FTA},								/* German FTA List */
				{3,		org.droidtv.ui.strings.R.string.MAIN_BOUQUET_GERMANY_HD_PLUS},							/* German HD+ */
				{4,		org.droidtv.ui.strings.R.string.MAIN_BOUQUET_CYFRA_PLUS},								/* Cyfra+ */
				{5,		org.droidtv.ui.strings.R.string.MAIN_BOUQUET_CYFROWY_POLSAT},							/* Cyfrowy Polsat */
				{6,		org.droidtv.ui.strings.R.string.MAIN_BOUQUET_N_ITI_NEOVISION},							/* N-ITI Neovision */
				{7,		org.droidtv.ui.strings.R.string.MAIN_BOUQUET_SWISS_FRENCH},							/* Swiss French List */
				{8,		org.droidtv.ui.strings.R.string.MAIN_BOUQUET_SWISS_GERMAN},							/* Swiss german */
				{9,		org.droidtv.ui.strings.R.string.MAIN_BOUQUET_POLAND_SMART_HD},							/* Polska: SMART HD+  */
				{28,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_DIGITURK_EUTELSAT_W3A_7E},				/* Digiturk Eutelsat */
				{10,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_DIGITURK_EUTELSAT_W3A_7E_MDU4},			/* Digiturk EutelSat MDU4 */
				{27,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_DIGITURK_TURKSAT_42E},					/* Digiturk Turksat 42E */
				{12,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_DSMART_TURKSAT_42E_HOTBIRD_13E},			/* D-smart Turksat hotbird */
				{13,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_DSMART_TURKSAT_42E},						/* D-smart turksat */
				{14,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_CANAL_DIGITAL},							/* Canal digital norway */
				{15,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_CANAL_DIGITAL},							/* Canal digital sweden */
				{16,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_CANAL_DIGITAL},							/* Canal digital finland */
				{17,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_CANAL_DIGITAL},							/* canal digital denmark */
				{29,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_RUSSIA_NTV_PLUS},							/* NTV+ */
				{30,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_TURKEY_TURKSAT}, 							/* Turkey Turksat FTA */
				{MwDataTypes.FREESAT_PACKAGE_ID,    	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_FREESAT       },                          /* Freesat */
				{MwDataTypes.ASTRALCN_PACKAGE_ID, 		org.droidtv.ui.strings.R.string.MAIN_BOUQUET_ASTRA_LCN },    /* Astra LCN */
				{MwDataTypes.TRICOLOR_SD_PACKAGE_ID,	org.droidtv.ui.strings.R.string.MAIN_WI_SAT_BOUQUET_TRICOLOUR_SD		},						/* Russia Tricolor HD*/
				{MwDataTypes.TRICOLOR_HD_PACKAGE_ID,	org.droidtv.ui.strings.R.string.MAIN_WI_SAT_BOUQUET_TRICOLOUR_HD	},
				/* M7 packages */
				{MwDataTypes.CANALDIGITAAL_SD_BOUQUET_ID,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_THE_NETHERLANDS_CANAL_DIGITAL_SD},
				{MwDataTypes.CANALDIGITAAL_HD_BOUQUET_ID,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_THE_NETHERLANDS_CANAL_DIGITAL_HD},
				{MwDataTypes.TVVLAANDEREN_SD_BOUQUET_ID,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_TV_VLAANDEREN_SD},
				{MwDataTypes.TVVLAANDEREN_HD_BOUQUET_ID,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_TV_VLAANDEREN_HD},
				{MwDataTypes.TELESAT_BEL_BOUQUET_ID,		org.droidtv.ui.strings.R.string.MAIN_BOUQUET_TELESAT_BELGIUM},
				{MwDataTypes.TELESAT_LUX_BOUQUET_ID,		org.droidtv.ui.strings.R.string.MAIN_BOUQUET_TELESAT_LUXEMBOURG},
				{MwDataTypes.AUSRTIA_BOUQUET_ID,			org.droidtv.ui.strings.R.string.MAIN_BOUQUET_AUSTRIASAT},
				{MwDataTypes.CZECH_REPUBLIC_BOUQUET_ID,		org.droidtv.ui.strings.R.string.MAIN_BOUQUET_SKYLINK_CS_LINK_CESKO},
				{MwDataTypes.SLOVAK_REPUBLIC_BOUQUET_ID,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_SKYLINK_CS_LINK_SLOVENSKO},
				{MwDataTypes.AUSTRIASAT_MAGYA_PACKAGE_ID,	org.droidtv.ui.strings.R.string.MAIN_BOUQUET_HELLO_HUNGARY}
				


			
	};
	
	
	public static BouquetIdMapping getInstance()
	{
		if (m_instance == null)
		{
			m_instance = new BouquetIdMapping();
		}
		return m_instance;
	}

	public int getPackageStringId(int p_bouquetId)
	{
		Log.d(TAG,"getPackageName entry");
		int l_idx;
		int l_id = org.droidtv.ui.strings.R.string.MAIN_BOUQUET_NO_SORTING;
		int l_pkgCount = m_bouquetIdArray.length;
		for(l_idx = 0; l_idx < l_pkgCount; l_idx ++ )
		{
			if(p_bouquetId == m_bouquetIdArray[l_idx][0])
			{
				l_id =  m_bouquetIdArray[l_idx][1];
				break;
			}
		}
		Log.d(TAG,"returning " + l_id);
		return l_id;
	}
	

}
