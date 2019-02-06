#pragma once

#include "World.h"

World::World() {}

void World::setup() {
  // Initialize box 2d.
  box2d.init();
  box2d.enableEvents();
  box2d.setGravity(0, 0);
  box2d.setFPS(60.0);
  
  // Not sure what this is for right now.
  box2d.registerGrabbing();
  
  // Create bound.
  int sizeX = ofGetWidth()/2; int sizeY = ofGetHeight();
  bounds.x = ofGetWidth()/2 - sizeX/2; bounds.y = ofGetHeight()/2 - sizeY/2;
  bounds.width = sizeX; bounds.height = sizeY;
  box2d.createBounds(bounds);
  
  // Contact start and contact end
  ofAddListener(box2d.contactStartEvents, this, &World::contactStart);
  ofAddListener(box2d.contactEndEvents, this, &World::contactEnd);
  
  // Load sounds.
  ofDirectory directory("sfx/");
  directory.allowExt("mp3");
  for (auto file: directory)
  {
      auto sound = std::make_shared<ofSoundPlayer>();
      sound->load(file);
      sound->setMultiPlay(true);
      sound->setLoop(false);
      sounds.push_back(sound);
  }
}

void World::update() {
  box2d.update();
  
  // Update agents.
  for (auto a : agents) {
    a.update();
  }
}

void World::draw(DebugParameters params) {
  // Draw the bounds.
  ofSetColor(119, 118, 135);
  ofFill();
  ofSetLineWidth(3.0);
  ofDrawRectangle(bounds);
  
  if (params.hideObstructions) {
    // Draw obstructions
    for (auto r : rectangles) {
      ofFill();
      SoundData * data = (SoundData*)r->getData();
      if (data) {
        if (data->bHit) {
          ofSetHexColor(0xff0000);
        } else {
          ofSetColor(ofColor::blue);
        }
        
        float rotation = data->rotation;
        r->setRotation(rotation);
      }
      
      r->draw();
    }
  }
  
  // Draw the circles falling on the ground.
  ofFill();
  for (auto a : agents) {
    ofFill();
    SoundData * data = a.getData();
    if(data && data->bHit) ofSetHexColor(0xff0000);
    else ofSetColor(ofColor::white);
    a.draw();
  }
}

void World::createAgent(ofImage img) {
  glm::vec2 pos = glm::vec2(bounds.x + ofRandom(bounds.width), bounds.y);
  int soundId = ofRandom(0, sounds.size());
  Agent agent(&box2d, pos, soundId, img);
  agents.push_back(agent);
}

void World::createObstructions() {
  // Shelf shape.
  int sizeX = 247; int sizeY = 15;
  glm::vec2 pos = glm::vec2(ofGetWidth()/2, ofGetHeight()/2 - 43);
  ofRectangle shelf = ofRectangle(pos, sizeX, sizeY);
  
  // Pos is the center of the rectangle. in box2d, that's how it's drawn.
  glm::vec2 leftPos = glm::vec2(pos.x - sizeX/2 + 29, pos.y + sizeY/2 + 25);
  glm::vec2 rightPos = glm::vec2(pos.x + sizeX/2 - 31, pos.y + sizeY/2 + 25);
  ofRectangle leftJoint = ofRectangle(leftPos, 13, 58);
  ofRectangle rightJoint = ofRectangle(rightPos, 13, 58);
  
  // CREATE A SHELF.
  
  // Top base
  auto c = std::make_shared<ofxBox2dRect>();
  c->setPhysics(0.0, 0.7, 0.1); // Density, bounce, and friction.
  c->setup(box2d.getWorld(), shelf);
  c->setData(new SoundData());
  SoundData * sd = (SoundData*)c->getData();
  sd->soundID = -1;
  sd->bHit = false;
  rectangles.push_back(c);
  
  // Left joint
  c = std::make_shared<ofxBox2dRect>();
  c->setPhysics(0.0, 0.7, 0.1); // Density, bounce, and friction.
  c->setup(box2d.getWorld(), leftJoint);
  c->setData(new SoundData());
  sd = (SoundData*)c->getData();
  sd->soundID = -1;
  sd->bHit = false;
  rectangles.push_back(c);

  // Right Joint
  c = std::make_shared<ofxBox2dRect>();
  c->setPhysics(0.0, 0.7, 0.1); // Density, bounce, and friction.
  c->setup(box2d.getWorld(), rightJoint);
  c->setData(new SoundData());
  sd = (SoundData*)c->getData();
  sd->soundID = -1;
  sd->bHit = false;
  rectangles.push_back(c);
  
  // Some panel
  glm::vec2 panelPos = glm::vec2(bounds.x + 280, bounds.y + 152);
  ofRectangle panel = ofRectangle(panelPos, 200, 20);
  c = std::make_shared<ofxBox2dRect>();
  c->setPhysics(0.0, 0.7, 0.1); // Density, bounce, and friction.
  c->setup(box2d.getWorld(), panel);
  c->setData(new SoundData());
  sd = (SoundData*)c->getData();
  sd->soundID = -1;
  sd->bHit = false;
  sd->rotation = 42; // Degrees
  rectangles.push_back(c);
}

void World::contactStart(ofxBox2dContactArgs& e) {
  if(e.a != NULL && e.b != NULL) {
    
    // Only when a circle contacts the polygon, then this routine will run.
    if(e.a->GetType() == b2Shape::e_polygon && e.b->GetType() == b2Shape::e_circle) {
      // Extract sound data.
      SoundData* aData = reinterpret_cast<SoundData*>(e.a->GetBody()->GetUserData());
      SoundData* bData = reinterpret_cast<SoundData*>(e.b->GetBody()->GetUserData());
      
      // Play the sound
      if(aData) {
        aData->bHit = true;
        // Don't play any sound for the polygon.
      }
      
      // Play the sound.
      if(bData) {
        bData->bHit = true;
        sounds[bData->soundID]->play();
      }
    }
  }
}

// Reset the sound.
void World::contactEnd(ofxBox2dContactArgs &e) {
  if(e.a != NULL && e.b != NULL) {
    
    SoundData* aData = reinterpret_cast<SoundData*>(e.a->GetBody()->GetUserData());
    SoundData* bData = reinterpret_cast<SoundData*>(e.b->GetBody()->GetUserData());
    
    if(aData)
        {
      aData->bHit = false;
    }
    
    if(bData)
        {
      bData->bHit = false;
    }
  }
}
