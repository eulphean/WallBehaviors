#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "SoundData.h"
#include "Face.h"
#include "GuiParams.h"

class Agent {

	public:
    Agent(ofxBox2d &box2d, GuiParams &params, glm::vec2 bounds, int soundId, ofImage img);
    SoundData* getData();
    ofImage agentImg;
    ofFbo masker; 
  
		void update();
		void draw();
  
    // Box2D object. 
    std::shared_ptr<ofxBox2dCircle> obj;
    Face face;
};

