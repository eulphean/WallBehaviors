#pragma once

#include "ofMain.h"
#include "World.h"
#include "ofxBox2d.h"
#include "ofxFaceTracker2.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void keyPressed(int key);
  
  
    // Flags
    bool grabberDebug;
    bool takeSnapshot;
  
    // World
    World world;
    DebugParameters params; 
  
    // Camera
    ofVideoGrabber grabber;
    ofxFaceTracker2 tracker;
    std::vector<ofRectangle> boundingBoxes;
    ofPixels crop;
    ofImage dst;
};
