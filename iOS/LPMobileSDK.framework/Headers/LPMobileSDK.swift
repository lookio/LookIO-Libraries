//
//  LPMobileSDK.swift
//  LookIO
//
//  Created by Omer Berger on 8/2/16.
//
//

import Foundation
import UIKit

public class LPMobileSDK{
    
    public class func  performSetup(){
        
        LIOLookIOManager.sharedLookIOManager().performSetupWithDelegate(nil)
    }
    
    public class func  performSetupWithDelegate(delegate:UIViewController?){
        
        LIOLookIOManager.sharedLookIOManager().performSetupWithDelegate(delegate as? protocol<LIOLookIOManagerDelegate>)
    }

    
}
