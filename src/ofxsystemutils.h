#ifndef __ofxSystemUtils__
#define __ofxSystemUtils__

// ofxSystemUtils:
// util to get around the opengl issues with load/save panels in osx 10.10
// (platforms other than osx are unaffected)
// v1.1: added support for default name, remembers last used folder
// v1.0: initial version

#include "ofMain.h"

ofFileDialogResult ofxSystemSaveDialog(string defaultName = "", string windowMessage = "");
ofFileDialogResult ofxSystemLoadDialog( string windowMessage = "");

#endif
