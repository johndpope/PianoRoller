/*
  ==============================================================================

    PlayCursorWindow.h
    Created: 3 Jan 2019 8:37:17pm
    Author:  Adam Shield

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Setup.h"




class PlayCursorWindow : public Component,
                         public Timer
{
public:
    
    PlayCursorWindow();
    
    void paint(Graphics&) override;
    void setPlayCursor(float val);
    float playCursorLine;
    
private:
    void timerCallback() override;
};


