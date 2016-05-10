#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "colorspace/colorspaceinterface.h"

enum DATAVIZ_MODE{SPARSE_CS,IMAGE};

class ColorspaceDisplayer : public ofBaseApp{
private:
    /**
    * @brief currentColorSpace convert a color from RGB color space to a given color space
    */
    cs::ColorspaceInterface* currentColorSpace;
    /**
    * @brief MODE what kind of data display ?
    *
    * SPARCE_CS : a sparse version of the entire color space
    * IMAGE : colors taken in a given image
    */
    DATAVIZ_MODE mode;
    /**
    * @brief colorspace a set of elements, one element by displayed color
    *
    * In SPARCE_CS mode : a square by color
    * In IMAGE mode : a poiny by color
    */
    ofMesh colorspace;
    ofEasyCam cam;/*!< to navigate in 3d scene*/
    string imPath;/*!< path to the image selected by the user in IMAGE mode*/
    ofVec3f targetLocation;/*!< camera location*/
    string xAxisName;/*!< name of the first color channel*/
    string yAxisName;/*!< name of the second color channel*/
    string zAxisName;/*!< name of the third color channel*/
    bool showAxis;/*!< if true draw color space axis*/
public:
    ColorspaceDisplayer();
    ~ColorspaceDisplayer();
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
private:

    /**
     * @brief save screenshot
     */
    void save() const;
    /**
     * @brief getCoordinates convert color from rgb to selected color space
     * and give it a position according its 3 channels in this color space
     * @param color
     * @return
     */
    ofVec3f getCoordinates(ofColor color);
    /**
     * @brief generateSparseColorSpace generate a sparce version of the color space
     *
     * red, green and blue channel are incremented by 8, so not all the colors are
     * displayed
     */
    void generateSparseColorSpace();
    /**
     * @brief extractImageColors extract all the colors in a image and display them
     * by a colored point corresponding to colors values in selected color space
     * @param path
     */
    void extractImageColors(string path);
    /**
     * @brief updateDisplay update display because displaying mode or color space h
     * has been changed
     */
    void updateDisplay();
    //to display help about application usage
    bool showHelp;/*!< to know if help must be displayed or not */
    /**
     * @brief createHelpGui create window with indication about application commands
     */
    void createHelpGui();
    ofxPanel helpPanel;/*!< help panel*/
    ofxLabel saveLabel;/*!< how to save*/
    ofxLabel helpLabel;/*!< how to save*/
    ofxLabel F1Label;/*!< how to switch to XYZ color space*/
    ofxLabel F2Label;/*!< how to switch to Luv color space*/
    ofxLabel F3Label;/*!< how to switch to Lab color space*/
    ofxLabel F4Label;/*!< how to switch to AC1C2 color space*/
    ofxLabel F5Label;/*!< how to switch to YC1C2 color space*/
    ofxLabel F6Label;/*!< how to switch to HSI color space*/
    ofxLabel F7Label;/*!< how to switch to I1I2I3 color space*/
    ofxLabel F8Label;/*!< how to switch to H1H2H3 color space*/
    ofxLabel EnterLabel;/*!< how to switch to sparce color space displaying mode */
    ofxLabel iLabel;/*!< how to switch to image colors displaying mode */
    ofxLabel axisLabel;/*!< how to show or hide color space axis */


};

