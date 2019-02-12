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

class DebugParameters {
  public:
    bool hideObstructions;
    bool showMesh;
    bool showTexture;
    bool showSoftBody;
};

// Sound data for the object.
class SoundData
{
public:
    ~SoundData()
    {
        std::cout << "destroyed!" << std::endl;
    }

    int soundID = -1;
    bool bHit = false;
    float rotation = 0;
};
