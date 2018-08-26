package org.droidtv.euinstallersat.model.mwapi;

import java.util.Arrays;

public class OperatorSearchSettings {
		
    public int Unattended_Flag;
    public int Service_Type_Length;	
    public int Service_Type[];			
    public int Delivery_Cap_Length;	
    public int Delivery_Capability[];
    public int Application_Cap_Length;
    public int Application_Capability[];
    
    public OperatorSearchSettings() {
    }
    
    public OperatorSearchSettings (int param1, int param2, int param3[], int param4, 
                                   int param5[], int param6, int param7[]) {
    
        this.Unattended_Flag 		 = param1;
        this.Service_Type_Length 	 = param2;	
        this.Service_Type 			 = Arrays.copyOf(param3,param3.length);;
        this.Delivery_Cap_Length	 = param4;	
        this.Delivery_Capability	 = Arrays.copyOf(param5,param5.length);;
        this.Application_Cap_Length  = param6;
        this.Application_Capability  = Arrays.copyOf(param7,param7.length);;
    }
}
