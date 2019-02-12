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
        world.createAgent(faceParams, dst);
        
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
  
  gui.draw();
}

void ofApp::exit() {
  gui.saveToFile("SoftBodyBox2D.xml");
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
