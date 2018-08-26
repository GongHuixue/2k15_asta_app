package org.droidtv.euinstallertc.settings;

import java.util.ArrayList;

import android.content.Context;

public class ChannelFreqNumberTable {

	public class ChanFreqNumEntry {
		public int Frequency;
		public String ChannelName;
		public boolean ifQucikScanOnly;
		public String band;

		public ChanFreqNumEntry(String argBand, int argFreq, String channel,
				Boolean argQuickScanOnly) {
			this.Frequency = argFreq;
			this.ChannelName = channel;
			this.ifQucikScanOnly = argQuickScanOnly;
			this.band = argBand;
		}
	}

	private static final String TAG = ChannelFreqNumberTable.class.getName();
	private ArrayList<ChanFreqNumEntry> mFreqList;
	private final int DEVIATION = 100;
	private Context ctx;

	public ArrayList<ChanFreqNumEntry> getChannelFreqEntryList(
			boolean argIfQuickScan, String countryName) {
		// return (ArrayList<ChanFreqNumEntry>)
		// Collections.unmodifiableCollection(mFreqList);
		ArrayList<ChanFreqNumEntry> returnFreqList = new ArrayList<ChanFreqNumEntry>();
		for (int index = 0; index < mFreqList.size(); index++) {
			// show all the frequencies always AN-71899
			
			if (countryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ESTONIA))) {
				if(		mFreqList.get(index).ChannelName.equalsIgnoreCase("K60") ||
						mFreqList.get(index).ChannelName.equalsIgnoreCase("K61") ||
						mFreqList.get(index).ChannelName.equalsIgnoreCase("K62") ||
						mFreqList.get(index).ChannelName.equalsIgnoreCase("K63") ||
						mFreqList.get(index).ChannelName.equalsIgnoreCase("K64") ||
						mFreqList.get(index).ChannelName.equalsIgnoreCase("K65") ||
						mFreqList.get(index).ChannelName.equalsIgnoreCase("K66") ||
						mFreqList.get(index).ChannelName.equalsIgnoreCase("K67") ||
						mFreqList.get(index).ChannelName.equalsIgnoreCase("K68") ||
						mFreqList.get(index).ChannelName.equalsIgnoreCase("K69")){
					// ignore
					// TF515PHIALLMTK02-52(301520)
				}else{
					// for all other cases populate full list
					returnFreqList.add(mFreqList.get(index));
				}
			}else{
				// for all other cases populate full list
				returnFreqList.add(mFreqList.get(index));
			}
			
			/*if (argIfQuickScan) {
				// Log.d(TAG, " frequency band:" + mFreqList.get(index).band + " name:" + mFreqList.get(index).ChannelName);
				// quick frequency scan: S-II only scanned in case of Norway
				if (mFreqList.get(index).band.equalsIgnoreCase("S-I")) {
					// S-I: only handled in case of full frequency scan
				} else if (mFreqList.get(index).band
						.equalsIgnoreCase("VHF-III")) {
					if (mFreqList.get(index).ifQucikScanOnly == true) {
						returnFreqList.add(mFreqList.get(index));
					} else {
						// 8 MHz: only handled in case of full frequency scan
					}
				}else if (mFreqList.get(index).band.equalsIgnoreCase("S-II")) {
					// quick frequency scan: S-II only scanned in case of Norway
					if (countryName.equalsIgnoreCase(ctx
							.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY))) {
						if (mFreqList.get(index).ifQucikScanOnly == true) {
							returnFreqList.add(mFreqList.get(index));
						} else {
							// 8 MHz: only handled in case of full frequency
							// scan
						}
					}
				} else if (mFreqList.get(index).band.equalsIgnoreCase("S-III")) {
					// quick frequency scan: S-III only scanned in case of
					// Norway
					if (countryName.equalsIgnoreCase(ctx
							.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY))) {
						returnFreqList.add(mFreqList.get(index));
					}
				} else if (mFreqList.get(index).band.equalsIgnoreCase("UHF")) {
					if (mFreqList.get(index).ifQucikScanOnly == true) {
						returnFreqList.add(mFreqList.get(index));
					} else {
						// 8 MHz: only handled in case of full frequency scan
					}
				}
			} else {
				// full frequency scan
				returnFreqList.add(mFreqList.get(index));
			}*/
		}

		return returnFreqList;
	}

	public ChannelFreqNumberTable(Context argCtx) {
		mFreqList = new ArrayList<ChanFreqNumEntry>();
		ctx = argCtx;
		initializeList();
	}

	public void initializeList() {

		mFreqList.add(new ChanFreqNumEntry("S-I", 107500, "S1", false));
		mFreqList.add(new ChanFreqNumEntry("S-I", 114000, "D1", true));
		mFreqList.add(new ChanFreqNumEntry("S-I", 114500, "S2", true));
		mFreqList.add(new ChanFreqNumEntry("S-I", 121500, "S3", true));
		mFreqList.add(new ChanFreqNumEntry("S-I", 122000, "D2", true));
		mFreqList.add(new ChanFreqNumEntry("S-I", 128500, "S4", true));
		mFreqList.add(new ChanFreqNumEntry("S-I", 130000, "D3", true));
		mFreqList.add(new ChanFreqNumEntry("S-I", 135500, "S5", true));
		mFreqList.add(new ChanFreqNumEntry("S-I", 138000, "D4", true));
		mFreqList.add(new ChanFreqNumEntry("S-I", 142500, "S6", true));
		mFreqList.add(new ChanFreqNumEntry("S-I", 146000, "D5", true));
		mFreqList.add(new ChanFreqNumEntry("S-I", 149500, "S7", true));
		mFreqList.add(new ChanFreqNumEntry("S-I", 154000, "D6", true));
		mFreqList.add(new ChanFreqNumEntry("S-I", 156500, "S8", true));
		mFreqList.add(new ChanFreqNumEntry("S-I", 162000, "D7", true));
		mFreqList.add(new ChanFreqNumEntry("S-I", 163500, "S9", true));
		mFreqList.add(new ChanFreqNumEntry("S-I", 170000, "D8", true));
		mFreqList.add(new ChanFreqNumEntry("S-I", 170500, "S10", true));

		mFreqList.add(new ChanFreqNumEntry("VHF-III", 177500, "K5", false));
		mFreqList.add(new ChanFreqNumEntry("VHF-III", 178000, "D9", true));
		mFreqList.add(new ChanFreqNumEntry("VHF-III", 184500, "K6", false));
		mFreqList.add(new ChanFreqNumEntry("VHF-III", 186000, "D10", true));
		mFreqList.add(new ChanFreqNumEntry("VHF-III", 191500, "K7", false));
		mFreqList.add(new ChanFreqNumEntry("VHF-III", 194000, "D11", true));
		mFreqList.add(new ChanFreqNumEntry("VHF-III", 198500, "K8", false));
		mFreqList.add(new ChanFreqNumEntry("VHF-III", 202000, "D12", true));
		mFreqList.add(new ChanFreqNumEntry("VHF-III", 205500, "K9", false));
		mFreqList.add(new ChanFreqNumEntry("VHF-III", 210000, "D13", true));
		mFreqList.add(new ChanFreqNumEntry("VHF-III", 212500, "K10", false));
		mFreqList.add(new ChanFreqNumEntry("VHF-III", 218000, "D14", true));
		mFreqList.add(new ChanFreqNumEntry("VHF-III", 219500, "K11", false));
		mFreqList.add(new ChanFreqNumEntry("VHF-III", 226000, "D15", true));
		mFreqList.add(new ChanFreqNumEntry("VHF-III", 226500, "K12", false));

		mFreqList.add(new ChanFreqNumEntry("S-II", 233500, "S11", false));
		mFreqList.add(new ChanFreqNumEntry("S-II", 234000, "D16", true));
		mFreqList.add(new ChanFreqNumEntry("S-II", 240500, "S12", false));
		mFreqList.add(new ChanFreqNumEntry("S-II", 242000, "D17", true));
		mFreqList.add(new ChanFreqNumEntry("S-II", 247500, "S13", false));
		mFreqList.add(new ChanFreqNumEntry("S-II", 250000, "D18", true));
		mFreqList.add(new ChanFreqNumEntry("S-II", 254500, "S14", false));
		mFreqList.add(new ChanFreqNumEntry("S-II", 258000, "D19", true));
		mFreqList.add(new ChanFreqNumEntry("S-II", 261500, "S15", false));
		mFreqList.add(new ChanFreqNumEntry("S-II", 266000, "D20", true));
		mFreqList.add(new ChanFreqNumEntry("S-II", 268500, "S16", false));
		mFreqList.add(new ChanFreqNumEntry("S-II", 274000, "D21", true));
		mFreqList.add(new ChanFreqNumEntry("S-II", 275500, "S17", false));
		mFreqList.add(new ChanFreqNumEntry("S-II", 282000, "D22", true));
		mFreqList.add(new ChanFreqNumEntry("S-II", 282500, "S18", false));
		mFreqList.add(new ChanFreqNumEntry("S-II", 289500, "S19", false));
		mFreqList.add(new ChanFreqNumEntry("S-II", 290000, "D23", true));
		mFreqList.add(new ChanFreqNumEntry("S-II", 296500, "S20", false));
		mFreqList.add(new ChanFreqNumEntry("S-II", 298000, "D24", true));

		mFreqList.add(new ChanFreqNumEntry("S-III", 306000, "S21", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 314000, "S22", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 322000, "S23", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 330000, "S24", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 338000, "S25", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 346000, "S26", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 354000, "S27", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 362000, "S28", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 370000, "S29", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 378000, "S30", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 386000, "S31", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 394000, "S32", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 402000, "S33", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 410000, "S34", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 418000, "S35", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 426000, "S36", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 434000, "S37", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 442000, "S38", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 450000, "S39", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 458000, "S40", true));
		mFreqList.add(new ChanFreqNumEntry("S-III", 466000, "S41", true));

		mFreqList.add(new ChanFreqNumEntry("UHF", 474000, "K21", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 482000, "K22", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 490000, "K23", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 498000, "K24", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 506000, "K25", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 514000, "K26", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 522000, "K27", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 530000, "K28", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 538000, "K29", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 546000, "K30", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 554000, "K31", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 562000, "K32", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 570000, "K33", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 578000, "K34", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 586000, "K35", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 594000, "K36", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 602000, "K37", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 610000, "K38", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 618000, "K39", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 626000, "K40", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 634000, "K41", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 642000, "K42", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 650000, "K43", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 658000, "K44", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 666000, "K45", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 674000, "K46", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 682000, "K47", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 690000, "K48", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 698000, "K49", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 706000, "K50", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 714000, "K51", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 722000, "K52", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 730000, "K53", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 738000, "K54", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 746000, "K55", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 754000, "K56", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 762000, "K57", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 770000, "K58", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 778000, "K59", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 786000, "K60", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 794000, "K61", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 802000, "K62", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 810000, "K63", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 818000, "K64", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 826000, "K65", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 834000, "K66", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 842000, "K67", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 850000, "K68", true));
		mFreqList.add(new ChanFreqNumEntry("UHF", 858000, "K69", true));
	}

	public String getChannelName(int argFreq) {
		String chName = null;
		ChanFreqNumEntry freqEntry;
		for (int index = 0; index < mFreqList.size(); index++) {
			freqEntry = mFreqList.get(index);

			if (((freqEntry.Frequency - DEVIATION) <= argFreq)
					&& ((freqEntry.Frequency + DEVIATION) >= argFreq)) {
				chName = freqEntry.ChannelName;
				break;
			}
		}
		return chName;
	}

	public int getFrequency(int argFreq) {
		int chfreq = 0;
		ChanFreqNumEntry freqEntry;
		for (int index = 0; index < mFreqList.size(); index++) {
			freqEntry = mFreqList.get(index);

			if (((freqEntry.Frequency - DEVIATION) <= argFreq)
					&& ((freqEntry.Frequency + DEVIATION) >= argFreq)) {
				chfreq = freqEntry.Frequency;
				break;
			}
		}
		return chfreq;
	}
}
