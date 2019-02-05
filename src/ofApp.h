#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "Agent.h"
#include "ofxFaceTracker2.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
  
    void createAgent();
    void createObstructions();
  
    // Flags
    bool hideObstructions;
    bool grabberDebug; 
    
		void keyPressed(int key);
  
    // Bounds.
    ofRectangle bounds;
    // World
    ofxBox2d box2d;
  
    // Agents.
    std::vector<Agent> agents;
  
    // Obstructions
    std::vector<std::shared_ptr<ofxBox2dRect>> rectangles;
  
    // Sounds
    std::vector<std::shared_ptr<ofSoundPlayer>> sounds;
  
    // Contact listening callbacks.
    void contactStart(ofxBox2dContactArgs &e);
    void contactPreSolve(ofxBox2dPreSolveArgs& e);
    void contactPostSolve(ofxBox2dPostSolveArgs& e);
    void contactEnd(ofxBox2dContactArgs &e);
  
    // Array of textures. 
    std::vector<ofTexture> textures;
  
    // Camera
    ofVideoGrabber grabber;
    ofxFaceTracker2 tracker;
    std::vector<ofRectangle> boundingBoxes;
    ofPixels crop;
    ofImage dst; 
  
    bool takeSnapshot;
    ofFbo masker; 
};
