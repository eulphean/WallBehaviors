#pragma once

#include "Agent.h"

Agent::Agent(ofxBox2d &box2d, GuiParams &params, glm::vec2 pos, int soundId, ofImage img) {
  ofRectangle r;
  r.width = img.getWidth(); r.height = img.getHeight();
  
  face.createFaceMesh(r, params);
  face.createFaceBox2DSprings(box2d, params); // Create the soft body. Pass all GUI physics parameters.
  
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

  // Allocate
  agentImg = img;

  // Prepare mask.
//  masker.allocate(agentImg.getWidth(), agentImg.getHeight(), GL_RGBA);
//  masker.begin();
//    ofClear(0, 0, 0, 0);
//    ofSetColor(ofColor::white);
//    ofFill();
//    ofDrawEllipse(agentImg.getWidth()/2, agentImg.getHeight()/2, agentImg.getWidth(), agentImg.getHeight());
//  masker.end();
}

void Agent::update() {
  // Update face.
  // obj->addForce(glm::vec2(ofRandom(-25, 25), ofRandom(-25, 25)), 11.0);
  //auto pos = obj->getPosition();
  face.updateFaceMeshPlane();
}

void Agent::draw() {
  // Draw face.
  face.draw(agentImg, true, true, true);
  
//  auto pos = obj->getPosition();
//  auto rot = obj->getRotation();
//  ofPushMatrix();
//    ofTranslate(pos);
//      ofRotate(rot);
//        float width = obj -> getRadius() * 2;
//        float height = width;
//        float x = - width/2;
//        float y = - height/2;
//        // Keep masking.
//        agentImg.getTexture().setAlphaMask(masker.getTexture());
//        agentImg.getTexture().draw(x, y, width, height);
//  ofPopMatrix();
}

SoundData* Agent::getData() {
  return (SoundData*) obj -> getData();
}
