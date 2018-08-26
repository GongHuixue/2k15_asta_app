package org.droidtv.tunerservice.services.sbyservice;

import android.os.Message;

public interface SSBYDefinitions {
	
	public static int ACTION_CLOCKCALIB	= 5;
	public static int ACTION_EMMUPDATE	= 6;
	
	public enum PStates{
		PSTATE_INIT(0),
		PSTATE_FULLON_TO_SEMI(1),
		PSTATE_BOOTING_TO_SEMI_ALARM(2),
		PSTATE_BOOTING_TO_SEMI_COLD(3),
		PSTATE_SEMI_TO_FULLON(4),
		PSTATE_DDR_TO_FULLON(5),
		PSTATE_SBY(6),
		PSTATE_FULLON(7);
			
		int value;
		PStates(int val){
			value = val;
		}
	}
	
	public enum ControlStates{
		MSTATE_INIT(0),
		MSTATE_WAITING(1),
		MSTATE_AVAILABLE(2),
		MSTATE_IDLE(3);
			
		int value;
		ControlStates(int val){
			value = val;
		}
	}
	
	public enum ClientStates{
		CSTATE_INIT(0),
		CSTATE_WAITING_TO_CONNECT(1),
		CSTATE_CONNECTED(2),
		CSTATE_INPROGRESS(3),
		CSTATE_STOPPING(4);
			
		int value;
		ClientStates(int val){
			value = val;
		}
	}
	
	public enum Events{
		EVENT_INIT(0),
		EVENT_POWERCHANGE_START(1),
		EVENT_POWERCHANGE_END(2),
		EVENT_CLIENT_CONNECTED(3),
		EVENT_CLIENT_DISCONNECTED(4),
		EVENT_CLIENT_COMPLETED(5),
		EVENT_MP_AVAILABLE(6),
		EVENT_MP_UNAVAILABLE(7),
		EVENT_FAC_AVAILABLE(8),
		EVENT_FAC_UNAVAILABLE(9),
		EVENT_ALARM_FIRED(10),
		EVENT_REQUEST_MPLAYER(11),
		EVENT_RELEASE_MPLAYER(12),
		EVENT_START_APP(13),
		EVENT_RELEASE_DSL(14),
		EVENT_REGISTER_ALARM(15),
		EVENT_LAST_SELECTION_DONE(16),
		EVENT_REQUEST_SBY(17),
		EVENT_MP_AVAILABLITY_CHANGED(18),
		EVENT_ALARM_REQUEST(19);
			
		int value;
		Events(int val){
			value = val;
		}
		public static Events getEvent(int what) {
			switch(what) {
				case 0: return EVENT_INIT;
				case 1: return EVENT_POWERCHANGE_START;
				case 2: return EVENT_POWERCHANGE_END;
				case 3: return EVENT_CLIENT_CONNECTED;
				case 4: return EVENT_CLIENT_DISCONNECTED;
				case 5: return EVENT_CLIENT_COMPLETED;
				case 6: return EVENT_MP_AVAILABLE;
				case 7: return EVENT_MP_UNAVAILABLE;
				case 8: return EVENT_FAC_AVAILABLE;
				case 9: return EVENT_FAC_UNAVAILABLE;
				case 10: return EVENT_ALARM_FIRED;
				case 11: return EVENT_REQUEST_MPLAYER;
				case 12: return EVENT_RELEASE_MPLAYER;
				case 13: return EVENT_START_APP;
				case 14: return EVENT_RELEASE_DSL;
				case 15: return EVENT_REGISTER_ALARM;
				case 16: return EVENT_LAST_SELECTION_DONE;
				case 17: return EVENT_REQUEST_SBY;
				case 18: return EVENT_MP_AVAILABLITY_CHANGED;
				case 19: return EVENT_ALARM_REQUEST;
			}
			return null;
		}
	}
	
	public interface PowerStateEventHandler {
		abstract void doAction(Events event, Message msg);
		abstract void onAllActionsCompleted();
	}
	
	public interface SSBYSessionHelperCallbacks {
		abstract public void onObserverSessionCreated();
		abstract public void onObserverSessionClosed();
		abstract public void onExtensionSessionTuned();
	}
	
	public interface SSBYClientDeathListener {
		abstract public void onSSBYClientDied(SSBYClient client);
	}
		
	public final String AlarmPendingIntent  = "org.droidtv.playtv.SbyServiceAlm";
	public final static String strClientid 	= "clientid";
	public final static String strAlarmid  	= "alarmid";
	public final static String strAlmScheme	= "semiStandby";
	public final static String strTimeinms	= "timeinms";
	
	public final static String strSSBYStore		= "SSBYStore";
	public final static String strSSBYLastAlarm	= "SSBYLastAlarm";
	public final static String strSSBYLastClient = "SSBYLastClient";
	
}
