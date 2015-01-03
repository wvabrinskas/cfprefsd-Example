#import "tweakHeader.h"

%ctor { //this is a function of theos that is called when a dynamic libray is first loaded into substrate

    //BUNDLE_ID is the bundle id you gave your tweak when you created it using theos, it generally is com.something.tweakname
    
    BOOL fileExists = [[NSFileManager defaultManager] fileExistsAtPath:@"/var/mobile/Library/Preferences/BUNDLE_ID.plist"]; 
    
    if (!fileExists) { //check if the plist exists, if it doesn't then create it. 
        
        NSMutableDictionary *tempDict = [[NSMutableDictionary alloc] initWithDictionary:@{@"enabled" : [NSNumber numberWithBool:YES]}]; //create an entry called enabled, that we will set to YES that way when we check later if it is enabled it will be set to YES for first time users. 
        
        [tempDict writeToFile:@"/var/mobile/Library/Preferences/BUNDLE_ID.plist" atomically:YES]; //write to file
        
        
    }
    
}

%hook someClass

-(void)onLoadMethodOfSomeClass {

    PreferencesChangedCallback(); //on load method create your preferences objects

    %orig; //call original function of method


}

-(void)someMethodOfSomeClass {

    BOOL enabled = [[rootObj objectForKey:@"enabled"] boolValue]; // get the bool value of the dictionary key "enabled", this will be a YES or NO value

    if (enabled) {

        //do something if enabled

    } else {

        //do something if not enabled

    }

    %orig; 

}

%end