#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  
  // Setup gui
  gui.setup();
  gui.add(faceParams.softCircleRadius.setup("Radius", 18, 2, 50)); // Should be set algorithmically most likely. 
  gui.add(faceParams.softJointLength.setup("JointLength", 2, 0, 20)); // Should be set algorithmically most likely.
  gui.add(faceParams.density.setup("Density", 0.5, 0, 1));
  gui.add(faceParams.bounce.setup("Bounce", 0.5, 0, 1));
  gui.add(faceParams.friction.setup("Friction", 0.5, 0, 1));
  gui.add(faceParams.centerJointFrequency.setup("CenterJointFrequency", 4.f, 0.f, 20.f ));
  gui.add(faceParams.centerJointDamping.setup("CenterJointDamping", 1.f, 0.f, 5.f));
  gui.add(faceParams.outerJointFrequency.setup("OuterJointFrequency", 1.f, 0.f, 20.f));
  gui.add(faceParams.outerJointDamping.setup("OuterJointDamping", 1.f, 0.f, 5.f));
  
  gui.loadFromFile("wallbehaviors.xml");
  
  // Initialize world's debug parameters.
  params.hideObstructions = false;
  params.showMesh = true;
  params.showTexture = true;
  params.showSoftBody = false;
  grabberDebug = true;
  takeSnapshot = false;
  
  ofSetVerticalSync(true);
  ofSetLogLevel(OF_LOG_NOTICE);
  
  // Setup world
  world.setup();
  
  // Setup Grabber
  grabber.setup(500, 500);
  tracker.setup();
  ofSetCircleResolution(30);
  
  curTime = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void ofApp::update(){
  // update World
  world.update();
  
  grabber.listDevices();
  grabber.setDeviceID(1);
  grabber.update();
  
  if (grabber.isFrameNew()) {
    boundingBoxes.clear();
    tracker.update(grabber);
    
    // Get the bounding boxes.
    if (tracker.size() > 0){
      auto& instances = tracker.getInstances();
      for (auto &i : instances) {
        auto rect = i.getBoundingBox();
        boundingBoxes.push_back(rect);
      }
    }
    
    auto elapsedTime = ofGetElapsedTimeMillis() - curTime;
    if (elapsedTime > 1000) {
      if (boundingBoxes.size() > 0) {
        // Go through all the bounding boxes and create agents.
        for (auto r : boundingBoxes) {
          ofPixels p = grabber.getPixels();
          p.cropTo(crop, r.x, r.y, r.width, r.height);
          dst.setFromPixels(crop);
          dst.resize(crop.getWidth()/2, crop.getHeight()/2);
          world.createAgent(faceParams, dst);
          curTime = ofGetElapsedTimeMillis();
        }
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  // Draw world
  world.draw(params);
  
  if (grabberDebug) {
    // Face recognition stuff.
    grabber.draw(0, 0);
    for (auto& b : boundingBoxes) {
      ofPushStyle();
        ofNoFill();
        ofSetColor(ofColor::red);
        ofDrawRectangle(b.getX(), b.getY(), b.getWidth(), b.getHeight());
      ofPopStyle();
    }
    
    // Draw destination image.
    if (dst.getTexture().isAllocated()) {
      dst.draw(0, 0);
    }
  }
  
  gui.draw();
}

void ofApp::exit() {
  gui.saveToFile("wallbehaviors.xml");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == 'h') {
    params.hideObstructions = !params.hideObstructions;
  }
  
  if (key == 's') {
    takeSnapshot = true;
  }
  
  if (key == 'd') {
    grabberDebug = !grabberDebug;
  }
  
  if (key == 'm') {
    params.showMesh = !params.showMesh;
  }
  
  if (key == 't') {
    params.showTexture = !params.showTexture;
  }
  
  if (key == 'b') {
    params.showSoftBody = !params.showSoftBody;
  }
}
