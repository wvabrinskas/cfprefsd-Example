
//NOTE: THIS IS FOR ARC (Automatic Reference Counting) SETUPS ONLY, IF YOU DON'T KNOW WHAT THAT IS OR HOW TO ENABLE IT ADD THIS LINE: "ADDITIONAL_OBJCFLAGS = -fobjc-arc" (no quotes) UNDER THE ARCHS FLAG IN YOUR MAKEFILE. YOU NEED TO REMOVE ALL "release" CALLS WHEN YOU SET YOUR PROJECT TO ARC

static NSMutableDictionary *rootObj; // create a mutable dictionary called rootObj



static void syncPreferences() { //call this to force syncronize your prefs when you change them
    
    CFStringRef appID = CFSTR("BUNDLE_ID_HERE");
    
    CFPreferencesSynchronize(appID, kCFPreferencesCurrentUser, kCFPreferencesAnyHost);
    
    
}

static void savePrefs (id key, id value) { //call this to save a prefs value to plist
    
    
    CFPreferencesSetValue ((__bridge CFStringRef)key,(__bridge CFStringRef)value, CFSTR("BUNDLE_ID_HERE"), kCFPreferencesCurrentUser , kCFPreferencesAnyHost);
    
    syncPreferences();

}

static void PreferencesChangedCallback() { // call this on tweak load to initialize the dictionary and then call it when you need to reference the plist
    
    syncPreferences();
    
    CFStringRef appID = CFSTR("BUNDLE_ID_HERE");
    
    CFArrayRef keyList = CFPreferencesCopyKeyList(appID, kCFPreferencesCurrentUser, kCFPreferencesAnyHost);
    
    if (!keyList) {
        
        NSLog(@"There's been an error getting the key list!");
        return;
        
    }
    
    rootObj = (NSMutableDictionary *)CFBridgingRelease(CFPreferencesCopyMultiple(keyList, appID, kCFPreferencesCurrentUser, kCFPreferencesAnyHost));
    
    if (!rootObj) {
        
        NSLog(@"There's been an error getting the preferences dictionary!");
        
    }
    
    CFRelease(keyList);
    
}
