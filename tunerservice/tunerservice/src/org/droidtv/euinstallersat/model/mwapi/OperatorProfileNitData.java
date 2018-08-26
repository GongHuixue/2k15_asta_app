package org.droidtv.euinstallersat.model.mwapi;

import java.util.Arrays;
public class OperatorProfileNitData {
		
    public int 	NitStatus;
    public int	NitDataLength;
    public int 	NitData[];	
	
    public OperatorProfileNitData() {
    }
    
    public OperatorProfileNitData(int param1, int param2, int param3[]) {
        
        this.NitStatus		= param1;
        this.NitDataLength	= param2;
        this.NitData		= Arrays.copyOf(param3,param3.length);
    }
}
