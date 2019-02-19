/*
  ==============================================================================

    PlayCursorWindow.cpp
    Created: 4 Jan 2019 2:15:49pm
    Author:  Adam Shield

  ==============================================================================
*/

#include "PlayCursorWindow.h"



PlayCursorWindow::PlayCursorWindow(){
    //setOpaque(true);
    setInterceptsMouseClicks(false, false);
    playCursorLine = 0.0f;
    setAlwaysOnTop(true);
    startTimer(100);
}

 void PlayCursorWindow::paint(Graphics& g){
     g.setColour(Colours::white);
     g.setOpacity(0.0f);
     g.fillAll();
     float height = getHeight();
     float width = getWidth();
     g.setColour(Colours::yellow);
     g.setOpacity(1.0f);
     g.drawLine(width * playCursorLine, 0., width * playCursorLine, height, 3);
 
 }

void PlayCursorWindow::setPlayCursor(float val){
    playCursorLine = val;
    //repaint();
}

void PlayCursorWindow::timerCallback(){
    repaint();
}
