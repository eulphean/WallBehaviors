#pragma once

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
};
