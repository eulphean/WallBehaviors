#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "Agent.h"
#include "Global.h"

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
    std::vector<std::shared_ptr<ofSoundPlayer>> sounds;
  
    glm::vec2 gridUnitSize; 
  
    World();
    void setup();
    void update();
    void draw(DebugParameters params);
    void createAgent(GuiParams &params, ofImage img);
    void createShelf();
    void createPlanks();
    void createMaze();
    void createPanel(glm::vec2 panelPos, glm::vec2 size, int rotation);
  
    // Contact listening callbacks.
    void contactStart(ofxBox2dContactArgs &e);
    void contactEnd(ofxBox2dContactArgs &e);
};

