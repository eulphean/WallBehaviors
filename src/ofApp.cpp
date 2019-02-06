#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  
  // Initialize world's debug parameters.
  params.hideObstructions = false;
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
}

//--------------------------------------------------------------
void ofApp::update(){
  // update World
  world.update();
  
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
    
    if (takeSnapshot) {
      if (boundingBoxes.size() > 0) {
        ofPixels p = grabber.getPixels();
        auto r = boundingBoxes[0];
        p.cropTo(crop, r.x, r.y, r.width, r.height);
        dst.setFromPixels(crop);
        world.createAgent(dst);
        
        // Create an agent now that the texture is ready.
        takeSnapshot = false;
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
}
