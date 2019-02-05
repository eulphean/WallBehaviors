#pragma once

#include "Agent.h"

Agent::Agent(ofxBox2d * box2d, glm::vec2 pos, int soundId, ofTexture t) {
  obj = std::make_shared<ofxBox2dCircle>();
  float rad = ofRandom(35, 40);

  // Physics
  obj->setPhysics(5.0, 1.0, 0.1); // Density, bounce, and friction.
  // Setup
  obj->setup(box2d->getWorld(), pos.x, pos.y, rad);
  // Sound data
  obj->setData(new SoundData());
  SoundData * sd = (SoundData*)obj->getData();
  sd->soundID = soundId;
  sd->bHit = false;
  
  // Incoming texture. 
  tex = t;
}

void Agent::update() {
  obj->addForce(glm::vec2(ofRandom(-25, 25), ofRandom(-25, 25)), 9.0);
  auto pos = obj->getPosition();
  vertices.push_back({pos.x, pos.y, 0});
  // line.addVertices(vertices);
}

void Agent::draw() {
  auto pos = obj->getPosition();
  auto rot = obj->getRotation();
  
  ofPushMatrix();
    ofTranslate(pos);
      ofRotate(rot);
        float width = obj -> getRadius() * 2;
        float height = width;
        float x = - width/2;
        float y = - height/2;
        tex.draw(x, y, width, height);
  ofPopMatrix();
}

SoundData* Agent::getData() {
  return (SoundData*) obj -> getData();
}
