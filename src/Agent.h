#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "SoundData.h"

class Agent {

	public:
    Agent(ofxBox2d * box2d, glm::vec2 bounds, int soundId, ofTexture tex);
    SoundData* getData();
    ofTexture tex; 
  
		void update();
		void draw();
  
    // Box2D object. 
    std::shared_ptr<ofxBox2dCircle> obj;
    std::vector<glm::vec3> vertices; 
    ofPolyline line;
};

