package org.droidtv.tunerservice.epgnownext;

public interface IEpgNowNextData {
	 String getNowEventName();
	 String getNextEventName();
     int getNowEventId();
	 int getNextEventId();
	 int getNowPresetId();
	 int getNextPresetId();
	 int getNowVersion();
	 int getNextVersion();
	 int getNowStartTime();
	 int getNextStartTime();
	 int getNowEndTime();
	 int getNextEndTime();
	 String getNowShortInfo();
	 String getNextShortInfo();
	 String getNowExtendedInfo();
	 String getNextExtendedInfo();
	 String getNowLanguageid();
	 String getNextLanguageid();
	 int getNowTargetIndex();
	 int getNextTargetIndex();
	 int getNowGenre();
	 int getNextGenre();
	 boolean getNowScrambledStatus();
	 boolean getNextScrambledStatus();
	 int getNowRating();
	 int getNextRating();
	 String getNowGuidanceinfo();
	 String getNextGuidanceinfo();
	 int getNowLinkType();
	 int getNextLinkType();
	 int getHeatMap();
	 int getNowNextDataChannelId();
}
