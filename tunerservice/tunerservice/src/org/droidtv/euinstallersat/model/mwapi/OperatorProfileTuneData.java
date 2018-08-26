package org.droidtv.euinstallersat.model.mwapi;

import java.util.Arrays;
public class OperatorProfileTuneData {
		
    public int 	TuneDataLength;		
    public int 	TuneData[];		
    
    public OperatorProfileTuneData() {
    }
    
    public OperatorProfileTuneData (int param1, int param2[]) {
        
        this.TuneDataLength		= param1;
        this.TuneData			= Arrays.copyOf(param2,param2.length);;
    }
}
