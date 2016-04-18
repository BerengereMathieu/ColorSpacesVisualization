#include "ofApp.h"
#include "colorspace/xyz.h"
#include "colorspace/luv.h"
#include "colorspace/lab.h"
#include "colorspace/ac1c2.h"
#include "colorspace/yc1c2.h"
#include "colorspace/hsi.h"
#include "colorspace/i1i2i3.h"
#include "colorspace/h1h2h3.h"






#include <set>
ColorspaceDisplayer::ColorspaceDisplayer(){
    currentColorSpace=new cs::XYZ();
    mode=SPARSE_CS;

}

ColorspaceDisplayer::~ColorspaceDisplayer(){
    delete currentColorSpace;

}

//--------------------------------------------------------------
void ColorspaceDisplayer::setup(){

    showHelp=true;
    ofSetBackgroundColor(128);

    generateSparseColorSpace();
    createHelpGui();


}

ofVec3f ColorspaceDisplayer::getCoordinates(ofColor color){

    ofVec3f pos;
    currentColorSpace->convertFromRGB(color.r,color.g,color.b);
    pos=ofVec3f(currentColorSpace->getNormalizedC1(),currentColorSpace->getNormalizedC2(),currentColorSpace->getNormalizedC3());
    pos.z= ofMap(pos.z,0,1,-ofGetWidth(),0);
    return pos;
}

void ColorspaceDisplayer::generateSparseColorSpace(){
    colorspace.clear();
    colorspace.setMode(OF_PRIMITIVE_TRIANGLES);
    for(int r=0;r<256;r+=8) {
        for(int g=0;g<256;g+=8){
            for(int b=0;b<256;b+=8){
                ofColor color=ofColor(r,g,b);
                ofVec3f pos=getCoordinates(color);


                colorspace.addVertex(ofVec3f(pos.x*ofGetWidth()-5,pos.y*ofGetHeight()-5,pos.z));
                colorspace.addColor(color);
                colorspace.addVertex(ofVec3f(pos.x*ofGetWidth()+5,pos.y*ofGetHeight()-5,pos.z));
                colorspace.addColor(color);
                colorspace.addVertex(ofVec3f(pos.x*ofGetWidth()+5,pos.y*ofGetHeight()+5,pos.z));
                colorspace.addColor(color);
                colorspace.addVertex(ofVec3f(pos.x*ofGetWidth()-5,pos.y*ofGetHeight()-5,pos.z));
                colorspace.addColor(color);
                colorspace.addVertex(ofVec3f(pos.x*ofGetWidth()-5,pos.y*ofGetHeight()+5,pos.z));
                colorspace.addColor(color);
                colorspace.addVertex(ofVec3f(pos.x*ofGetWidth()+5,pos.y*ofGetHeight()+5,pos.z));
                colorspace.addColor(color);
            }
        }
    }

}

void ColorspaceDisplayer::extractImageColors(string path){

    ofImage im;
    if(im.load(path)){
        colorspace.clear();
        colorspace.setMode(OF_PRIMITIVE_POINTS);
        set<int> colors;
        for(int y=0;y<im.getHeight();y++){
            for(int x=0;x<im.getWidth();x++){
                ofColor c=im.getColor(x,y);
                colors.insert(c.getHex());
            }
        }
        for(auto it=colors.begin();it!=colors.end();it++){
            ofColor color=ofColor::fromHex(*it);
            ofVec3f pos= getCoordinates(color);
            colorspace.addVertex(ofVec3f(pos.x*ofGetWidth(),pos.y*ofGetHeight(),pos.z));

            colorspace.addColor(color);
        }
    }


}

//--------------------------------------------------------------
void ColorspaceDisplayer::update(){

}
//--------------------------------------------------------------
void ColorspaceDisplayer::draw(){

    if(showHelp){
        helpPanel.draw();
    }
    cam.begin();
    colorspace.draw();
    cam.end();
}

void ColorspaceDisplayer::save() const{

    ofFileDialogResult saveDialog= ofSystemSaveDialog("Save","Save");
    if(saveDialog.bSuccess){
        ofSaveScreen(saveDialog.getPath());

    }
}
void ColorspaceDisplayer::updateDisplay(){
    switch (mode) {
    case IMAGE:
        extractImageColors(imPath);
        break;
    case SPARSE_CS:
        generateSparseColorSpace();
        break;
    }
}

//--------------------------------------------------------------
void ColorspaceDisplayer::keyPressed(int key){
    if(key=='s' ||key== 'S') {
        save();
    }else if(key=='i' || key=='I'){
        ofFileDialogResult saveDialog= ofSystemSaveDialog("Load","Load");
        if(saveDialog.bSuccess){
            imPath=saveDialog.getPath();
            mode=IMAGE;
            updateDisplay();
        }
    }else if(key=='h' || key=='H'){
        if(showHelp){
            showHelp=false;
        }else{
            showHelp=true;
        }
    }else if(key==OF_KEY_RETURN){
        mode=SPARSE_CS;
        updateDisplay();
    }else{
        switch(key){
        case OF_KEY_F1:
            delete currentColorSpace;
            currentColorSpace=new cs::XYZ();
            break;
        case OF_KEY_F2:
            delete currentColorSpace;
            currentColorSpace=new cs::LUV();
            updateDisplay();
            break;
        case OF_KEY_F3:
            delete currentColorSpace;
            currentColorSpace=new cs::LAB();
            updateDisplay();
            break;
        case OF_KEY_F4:
            delete currentColorSpace;
            currentColorSpace=new cs::AC1C2();
            updateDisplay();
            break;
        case OF_KEY_F5:
            delete currentColorSpace;
            currentColorSpace=new cs::YC1C2();
            updateDisplay();
            break;
        case OF_KEY_F6:
            delete currentColorSpace;
            currentColorSpace=new cs::HSI();
            updateDisplay();
            break;
        case OF_KEY_F7:
            delete currentColorSpace;
            currentColorSpace=new cs::I1I2I3();
            updateDisplay();
            break;
        case OF_KEY_F8:
            delete currentColorSpace;
            currentColorSpace=new cs::H1H2H3();
            updateDisplay();
            break;
        }
    }

}

void ColorspaceDisplayer::createHelpGui(){
        helpPanel.setup("Usage");
        helpPanel.setDefaultWidth(400);
        helpPanel.add(helpLabel.setup("h","show/hide help"));
        helpPanel.add(saveLabel.setup("s","save screenshot"));
        helpPanel.add(F1Label.setup("F1 ","XYZ color space (default)"));
        helpPanel.add(F2Label.setup("F2 ","Luv color space "));
        helpPanel.add(F3Label.setup("F3 ","Lab color space "));
        helpPanel.add(F4Label.setup("F4 ","AC1C2 color space "));
        helpPanel.add(F5Label.setup("F5 ","YC1C2 color space "));
        helpPanel.add(F6Label.setup("F6 ","HSI color space "));
        helpPanel.add(F7Label.setup("F7 ","A1A2A color space "));
        helpPanel.add(F8Label.setup("F8 ","H1H2H3 color space "));
        helpPanel.add(EnterLabel.setup("ENTER ","global view of color space (default)"));
        helpPanel.add(iLabel.setup("i ","display colors of an image"));

}

//--------------------------------------------------------------
void ColorspaceDisplayer::keyReleased(int key){

}

//--------------------------------------------------------------
void ColorspaceDisplayer::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ColorspaceDisplayer::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ColorspaceDisplayer::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ColorspaceDisplayer::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ColorspaceDisplayer::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ColorspaceDisplayer::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ColorspaceDisplayer::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ColorspaceDisplayer::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ColorspaceDisplayer::dragEvent(ofDragInfo dragInfo){

}

