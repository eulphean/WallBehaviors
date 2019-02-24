#pragma once

#include "ofMain.h"
#include "World.h"
#include "ofxBox2d.h"
#include "ofxFaceTracker2.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void keyPressed(int key);
    void exit();
  
    // Flags
    bool grabberDebug;
    bool takeSnapshot;
    bool showDebug; 
  
    // World
    World world;
    DebugParameters params; 
  
    // Camera
    ofVideoGrabber grabber;
    ofxFaceTracker2 tracker;
    std::vector<ofRectangle> boundingBoxes;
    ofPixels crop;
    ofImage dst;
  
    // GUI
    ofxPanel gui;
    GuiParams faceParams;
  
    long curTime; 
};
