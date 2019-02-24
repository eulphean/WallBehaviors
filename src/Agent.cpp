#pragma once

#include "Agent.h"

Agent::Agent(ofxBox2d &box2d, GuiParams &params, glm::vec2 pos, int soundId, ofImage img) {
  ofRectangle r;
  r.width = img.getWidth(); r.height = img.getHeight();
  
  face.createFaceMesh(r, pos, params);
  face.createFaceBox2DSprings(box2d, params); // Create the soft body. Pass all GUI physics parameters.
  
  // Allocate
  agentImg = img;
}

void Agent::update() {
  // Update face.
  // obj->addForce(glm::vec2(ofRandom(-25, 25), ofRandom(-25, 25)), 11.0);
  //auto pos = obj->getPosition();
  face.updateFaceMeshPlane();
}

void Agent::draw(DebugParameters params) {
  // Draw face.
  face.draw(agentImg, params.showMesh, params.showTexture, params.showSoftBody);
}

SoundData* Agent::getData() {
  return (SoundData*) obj -> getData();
}


// SOUND

//  obj = std::make_shared<ofxBox2dCircle>();
//  float rad = ofRandom(30, 50);
//
//  // Physics
//  obj->setPhysics(8.0, 1.0, 0.2); // Density, bounce, and friction.
//  // Setup
//  obj->setup(box2d->getWorld(), pos.x, pos.y, rad);
//  // Sound data
//  obj->setData(new SoundData());
//  SoundData * sd = (SoundData*)obj->getData();
//  sd->soundID = soundId;
//  sd->bHit = false;
