#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  
  numAgents = 20;
  hideObstructions = false;
  
  ofSetVerticalSync(true);
  ofSetLogLevel(OF_LOG_NOTICE);

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
  
  // Contact start and contact end
  ofAddListener(box2d.contactStartEvents, this, &ofApp::contactStart);
  ofAddListener(box2d.contactEndEvents, this, &ofApp::contactEnd);
  
  // Load image
  ofTexture t;
//  ofLoadImage(t, "smile.png"); textures.push_back(t);
  ofLoadImage(t, "p1.png"); textures.push_back(t);
  ofLoadImage(t, "p2.png"); textures.push_back(t);
  ofLoadImage(t, "p3.png"); textures.push_back(t);
  ofLoadImage(t, "p4.png"); textures.push_back(t);
  ofLoadImage(t, "p5.png"); textures.push_back(t);
  ofLoadImage(t, "p6.png"); textures.push_back(t);
}

//--------------------------------------------------------------
void ofApp::update(){
  box2d.update();
  
  // Update agents. 
  for (auto a : agents) {
    a.update();
  }
  
  line.addVertex({ofGetMouseX(), ofGetMouseY(), 0});
}

//--------------------------------------------------------------
void ofApp::draw(){
  // Draw the bounds.
  ofSetColor(ofColor::white);
  ofFill();
  ofSetLineWidth(3.0);
  ofDrawRectangle(bounds);
  
  if (hideObstructions) {
    // Draw obstructions
    for (auto r : rectangles) {
      ofFill();
      SoundData * data = (SoundData*)r->getData();
      if(data && data->bHit) ofSetHexColor(0xff0000);
      else ofSetColor(ofColor::blue);
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

void ofApp::createAgents() {
  // Initialize agents. 
  for (int i = 0; i < numAgents; i++) {
    glm::vec2 pos = glm::vec2(bounds.x + ofRandom(bounds.width), bounds.y);
    int soundId = ofRandom(0, sounds.size());
    int texId = ofRandom(0, textures.size());
    Agent agent(&box2d, pos, soundId, textures[texId]);
    agents.push_back(agent);
  }
}

void ofApp::createObstructions() {
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
}

void ofApp::contactStart(ofxBox2dContactArgs& e) {
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
void ofApp::contactEnd(ofxBox2dContactArgs &e) {
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  // When space bar is pressed, create bunch of circles to fall from the top.
  if (key == 'c') {
    createAgents();
  }
  
  if (key == 'o') {
    createObstructions();
  }
  
  if (key == 'h') {
    hideObstructions = !hideObstructions;
  }
}
