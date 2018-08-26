package org.droidtv.tunerservice.interfaces;

import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;

import android.os.Bundle;

public interface IPowerEvents {
	abstract public void onPowerChangeStart(PowerStates from,PowerStates to, Bundle extras);
	abstract public void onPowerChangeEnd(PowerStates from,PowerStates to, Bundle extras);
}
