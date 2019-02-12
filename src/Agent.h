#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "Face.h"
#include "Global.h"

class Agent {

	public:
    Agent(ofxBox2d &box2d, GuiParams &params, glm::vec2 bounds, int soundId, ofImage img);
    SoundData* getData();
    ofImage agentImg;
    ofFbo masker; 
  
		void update();
		void draw(DebugParameters params);
  
    // Box2D object. 
    std::shared_ptr<ofxBox2dCircle> obj;
    Face face;
};

