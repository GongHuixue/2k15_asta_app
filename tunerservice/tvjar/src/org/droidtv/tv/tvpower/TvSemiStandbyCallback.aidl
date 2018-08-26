/*
 *  Copyright(C) 2012 TP Vision Holding B.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of TP Vision Holding B.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of TP Vision Holding B.V.
 *
 */

package org.droidtv.tv.tvpower;

/** @hide */
interface TvSemiStandbyCallback {

	void onStartAction();
	
	void onStopAction();
	
	long onGetNextAlarm();
	
	void onAlarmFired();
	
}

