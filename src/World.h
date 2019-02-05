#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "Agent.h"

class DebugParameters {
  public:
    bool hideObstructions;
}

class World {

	public:
    // World
    ofxBox2d box2d;
    // Bounds.
    ofRectangle bounds;
    // Agents.
    std::vector<Agent> agents;
    // Obstructions
    std::vector<std::shared_ptr<ofxBox2dRect>> rectangles;
  
    World();
    void update();
    void draw(DebugParamaters params);
    void createAgent(ofImage &img);
    void createObstructions();
  
    // Contact listening callbacks.
    void contactStart(ofxBox2dContactArgs &e);
    void contactEnd(ofxBox2dContactArgs &e);
  
};

