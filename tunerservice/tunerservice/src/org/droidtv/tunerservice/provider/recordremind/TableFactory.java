package org.droidtv.tunerservice.provider.recordremind;

import org.droidtv.tunerservice.provider.recordremind.tables.ParentVersionTbl;
import org.droidtv.tunerservice.provider.recordremind.tables.RecordingTbl;
import org.droidtv.tunerservice.provider.recordremind.tables.VersionTbl;
import org.droidtv.tv.provider.IRecordingsContract;


public class TableFactory {

	public static ItblHandler getTableInstance(String tableName) {

		if (tableName.equalsIgnoreCase(IRecordingsContract.ParentVersion)) {
			return (ItblHandler) new ParentVersionTbl();
		} else if (tableName.equalsIgnoreCase(IRecordingsContract.RECORDINGS_TABLE)) {
			return (ItblHandler) new RecordingTbl();
		} else if (tableName.equalsIgnoreCase(IRecordingsContract.Version)) {
			return (ItblHandler) new VersionTbl();
		} else {
			return null;
		}
	}
}
