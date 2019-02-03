#pragma once

#include "Agent.h"

Agent::Agent(ofxBox2d * box2d, glm::vec2 pos, int soundId) {
  obj = std::make_shared<ofxBox2dCircle>();
  float rad = ofRandom(5, 10);

  // Physics
  obj->setPhysics(3.0, 1.0, 0.5); // Density, bounce, and friction.
  // Setup
  obj->setup(box2d->getWorld(), pos.x, pos.y, rad);
  // Sound data
  obj->setData(new SoundData());
  SoundData * sd = (SoundData*)obj->getData();
  sd->soundID = soundId;
  sd->bHit = false;
}

void Agent::update() {
  obj->addForce(glm::vec2(ofRandom(-20, 20), ofRandom(-20, 20)), 1.0);
  auto pos = obj->getPosition();
  vertices.push_back({pos.x, pos.y, 0});
 //x line.addVertices(vertices);
}

void Agent::draw() {
  obj->draw();
  cout << "Size" << vertices.size() << "\n";
  line.draw();
}

SoundData* Agent::getData() {
  return (SoundData*) obj -> getData();
}
