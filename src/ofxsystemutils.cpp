#include "ofxSystemUtils.h"

#ifdef TARGET_OSX
// ofSystemUtils.cpp is configured to build as
// objective-c++ so as able to use Cocoa dialog panels
// This is done with this compiler flag
//        -x objective-c++
// http://www.yakyak.org/viewtopic.php?p=1475838&sid=1e9dcb5c9fd652a6695ac00c5e957822#p1475838
// or by selecting
#include <Cocoa/Cocoa.h>
#endif

#ifdef TARGET_OSX

static NSString * getLastUserDir(){
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSString * file = [userDefaults stringForKey:@"current.dir"];
    NSString * result = (file == nil || [file isEqualToString:@""])? @"/Users":file;
    BOOL isDir;
    [[NSFileManager defaultManager] fileExistsAtPath:result isDirectory:&isDir];
    return isDir? result : [result stringByDeletingLastPathComponent];
}

static void setLastUserDir( NSString * dir ){
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    [userDefaults setValue:dir forKey:@"current.dir"];
    [userDefaults synchronize];
}


#endif


ofFileDialogResult ofxSystemSaveDialog(string defaultName, string windowMessage){
    {

#ifdef TARGET_OSX
        ofFileDialogResult result;

        NSOpenGLContext *context = [NSOpenGLContext currentContext];
        NSDictionary *error = nil;

        NSString * dir = [getLastUserDir() stringByReplacingOccurrencesOfString:@"\"" withString:@"\\\""];
        NSString * name = [[NSString stringWithUTF8String:defaultName.c_str()] stringByReplacingOccurrencesOfString:@"\"" withString:@"\\\""];
        NSString * msg = [[NSString stringWithUTF8String:windowMessage.c_str()] stringByReplacingOccurrencesOfString:@"\"" withString:@"\\\""];
        NSString * script = [NSString stringWithFormat:
                             @"tell app \"SystemUIServer\"\n"
                             @"    choose file name default location \"%@\" default name \"%@\" with prompt \"%@\"\n"
                             @"    set result to (the POSIX path of result)\n"
                             @"end tell", dir, name, msg];


        NSAppleScript* openFile = [[NSAppleScript alloc] initWithSource:script];
        NSString *absoluteFilePath = [[openFile executeAndReturnError: &error] stringValue];

        if(absoluteFilePath != NULL){
            result.filePath = string([absoluteFilePath UTF8String]);
            setLastUserDir(absoluteFilePath);
            NSLog(@"User selected %@\n",absoluteFilePath);
        }
        else{
            NSLog(@"User hit cancel\n");
            result.bSuccess = false;
        }

        //restore app window focus
        NSWindow * appWindow = (NSWindow *)ofGetCocoaWindow();
        if(appWindow) {
            [appWindow makeKeyAndOrderFront:nil];
        }

        [context makeCurrentContext];

        if( result.filePath.length() > 0 ){
            result.bSuccess = true;
            result.fileName = ofFilePath::getFileName(result.filePath);
        }
        return result;
    }
#else
    return ofSystemSaveDialog(defaultName, windowMessage);
#endif

}



ofFileDialogResult ofxSystemLoadDialog( string windowMessage ){
    {

#ifdef TARGET_OSX
        ofFileDialogResult result;

        NSOpenGLContext *context = [NSOpenGLContext currentContext];
        NSDictionary *error = nil;

        NSString * dir = [getLastUserDir() stringByReplacingOccurrencesOfString:@"\"" withString:@"\\\""];
        NSString * msg = [[NSString stringWithUTF8String:windowMessage.c_str()] stringByReplacingOccurrencesOfString:@"\"" withString:@"\\\""];
        NSString * script = [NSString stringWithFormat:
                             @"tell app \"SystemUIServer\"\n"
                             @"    choose file default location \"%@\" with prompt \"%@\"\n"
                             @"    set result to (the POSIX path of result)\n"
                             @"end tell", dir, msg];
        NSLog(script);

        NSAppleScript* openFile = [[NSAppleScript alloc] initWithSource:script];
        NSString *absoluteFilePath = [[openFile executeAndReturnError: &error] stringValue];

        if(absoluteFilePath != NULL){
            result.filePath = string([absoluteFilePath UTF8String]);
            setLastUserDir(absoluteFilePath);
            NSLog(@"User selected %@\n",absoluteFilePath);
        }
        else{
            NSLog(@"User hit cancel\n");
            result.bSuccess = false;
        }

        //restore app window focus
        NSWindow * appWindow = (NSWindow *)ofGetCocoaWindow();
        if(appWindow) {
            [appWindow makeKeyAndOrderFront:nil];
        }

        [context makeCurrentContext];

        if( result.filePath.length() > 0 ){
            result.bSuccess = true;
            result.fileName = ofFilePath::getFileName(result.filePath);
        }
        return result;
    }
#else
    return ofSystemLoadDialog(windowMessage);
#endif

}
