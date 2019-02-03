#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "Agent.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
  
    void createAgents();
    void createObstructions();
  
    // Flags
    bool hideObstructions;
    
		void keyPressed(int key);
  
    // Bounds.
    ofRectangle bounds;
    // World
    ofxBox2d box2d;
  
    // Agents.
    int numAgents;
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
  
    ofPolyline line;
  
    // Array of textures. 
    std::vector<ofTexture> textures;
};
