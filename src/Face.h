#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "Global.h"

#pragma once

class Face {
  private:
    std::vector<std::shared_ptr<ofxBox2dCircle>> circles; // default box2d circles
    std::vector<std::shared_ptr<ofxBox2dJoint>> joints;  // joints
    ofMesh faceMesh;
  
    // Constants
    int meshPoints;
    float faceMeshRadius;
    float faceCircumference;
  
  public:
    void createFaceMesh(ofRectangle boundingRect, glm::vec2 pos, GuiParams &params);
    void createFaceBox2DSprings(ofxBox2d &box2d, GuiParams &params);
    void updateFaceMeshVertices();
    void updateFaceMeshTexture();
    void updateFaceMeshPlane();
    void draw(ofImage img, bool showMesh, bool showTexture, bool showSoftBody);
};
