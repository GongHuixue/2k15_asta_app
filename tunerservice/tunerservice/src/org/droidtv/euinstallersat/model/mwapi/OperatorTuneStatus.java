package org.droidtv.euinstallersat.model.mwapi;

import java.util.Arrays;

public class OperatorTuneStatus {
		
    public int 	Descriptor_Number;		
    public int 	Signal_Strength;		
    public int 	Signal_Quality;			
    public int 	Status;					
    public int 	Descriptor_Loop_Length;	
    public int 	Descriptor_Loop[];
    
    public OperatorTuneStatus() {
    }
    
    public OperatorTuneStatus (int param1, int param2, int param3, int param4, int param5, int param6[]) {    
        this.Descriptor_Number			= param1;
        this.Signal_Strength			= param2;
        this.Signal_Quality				= param3;
        this.Status						= param4;	
        this.Descriptor_Loop_Length  	= param5;
        this.Descriptor_Loop			= Arrays.copyOf(param6,param6.length);
    }
}
