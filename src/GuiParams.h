#include "ofxGui.h"

#pragma once

class GuiParams {
  public:
    ofxFloatSlider softCircleRadius;
    ofxFloatSlider softJointLength;
    ofxFloatSlider density;
    ofxFloatSlider bounce;
    ofxFloatSlider friction;
    ofxFloatSlider centerJointFrequency;
    ofxFloatSlider centerJointDamping;
    ofxFloatSlider outerJointFrequency;
    ofxFloatSlider outerJointDamping;
};
