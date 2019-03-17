/*
  ==============================================================================

    VolumePanel.cpp
    Created: 2 Jan 2019 12:47:35pm
    Author:  Adam Shield

  ==============================================================================
*/

#include "VolumePanel.h"


VolumePanel::VolumePanel(OwnedArray<Preset> * processorPresetLocation){
    processorPresets = processorPresetLocation;
    setOpaque(true);
    
    if (! sender.connect ("127.0.0.1", 9001)) // [4]
        showConnectionErrorMessage ("Error: could not connect to UDP port 9001.");
    
    stuff = "foo";
    
    setVisible(true);
    setSize(getWidth(), getHeight());
}

VolumePanel::~VolumePanel(){

}

void VolumePanel::paint (Graphics& g)
{
    const int numOfBeats = (*processorPresets)[currentPreset]->numOfBeats;
    const float width = getWidth();
    const float height = getHeight();
    const float noteWidth = (width / ((float)numOfBeats * 4.0f) );
    const float tripNoteWidth = width / ((float)numOfBeats * 3.0f);
    const bool isMono = (*processorPresets)[currentPreset]->isMono;
    
    g.fillAll (PianoRollerColours::greyOff); //BACKGROUND COLOR
    
    
    for(int beat=0;beat<numOfBeats;beat++){
        const int currentBeatSwitch = (*processorPresets)[currentPreset]->tracks[currentTrack]->beatSwitch[beat];
        const int div = [currentBeatSwitch]() -> int{
            if(currentBeatSwitch==0) return 4;
            else                     return 3;
        }();
        const float thisNoteWidth = [&]() -> float{
            if(currentBeatSwitch==0) return noteWidth;
            else                     return tripNoteWidth;
        }();
        
        for(int subDiv=0;subDiv<div;subDiv++){
            const int col = (beat*div) + subDiv;
            const int vol = [&]() -> int{
                if(currentBeatSwitch==0){
                    if(isMono) return (*processorPresets)[currentPreset]->tracks[currentTrack]->sixteenthVols[col];
                    else       return (*processorPresets)[currentPreset]->tracks[currentTrack]->polySixteenthVols[col];
                }else if(currentBeatSwitch==1){
                    if(isMono) return (*processorPresets)[currentPreset]->tracks[currentTrack]->tripletVols[col];
                    else       return (*processorPresets)[currentPreset]->tracks[currentTrack]->polyTripletVols[col];
                }else return 0;
            }();
            const float rectX = ( col * thisNoteWidth );
            const float rectY = height - ( height/127.f * (float)vol );
            
            g.setColour (PianoRollerColours::whiteBlue);
            g.fillRect(rectX, rectY, thisNoteWidth, height);
            
            //DRAW COLUMN LINES
            const int lineWidth = [subDiv](){
                if(subDiv==0) return 3;
                else          return 1;
            }();
            const int xPosition = 0.0f + ( (float)col*thisNoteWidth );
            g.setColour (Colours::black);
            g.drawLine(xPosition, 0., xPosition, height, lineWidth);
        }
    }
    g.drawLine(width, 0.0f, width, height, 3); //Right side line.
    g.setFont(40);
    
    
    //g.drawText(stuff, 80, 50, 200, 200, Justification::centred);
    
}

void VolumePanel::resized(){

}

void VolumePanel::mouseDrag(const MouseEvent& event){
    mouseDown(event);
}

void VolumePanel::mouseDown(const MouseEvent &event){
    const bool leftClick = event.mods.isLeftButtonDown();
    const bool rightClick = event.mods.isRightButtonDown();
    
    const int numOfBeats = (*processorPresets)[currentPreset]->numOfBeats;
    const float x = getMouseXYRelative().getX();
    const float y = getMouseXYRelative().getY();
    int vol = (int) ( 127.f - y/(float)getHeight() * 127.f ); //Final (int) cast rounds it down.
    int col = (int) (x/(float)getWidth() * (float) (numOfBeats*4)); //Final (int) cast rounds it down.
        vol = midiLimit(vol);
        col = midiLimit(col);
    const int tripCol = (int) (x/(float)getWidth() * (float) (numOfBeats*3)); //Final (int) cast rounds it down.
    const int currentBeat = col / 4;
    const int beatSwitch = (*processorPresets)[currentPreset]->tracks[currentTrack]->beatSwitch[currentBeat];
    const int beatDiv = [&]() -> int{
        if(beatSwitch==0) return 4;
        else              return 3;
    }();
    int thisCol;
    if(rightClick){vol = 96;}
    
    if((*processorPresets)[currentPreset]->isMono){
        if(beatSwitch==0){
            thisCol=col;
            (*processorPresets)[currentPreset]->tracks[currentTrack]->sixteenthVols.set(col, vol);
        }
        else{
            thisCol=tripCol;
            (*processorPresets)[currentPreset]->tracks[currentTrack]->tripletVols.set(tripCol, vol);
        };
        
    }else{ //isPoly
        if(beatSwitch==0){
            thisCol=col;
            (*processorPresets)[currentPreset]->tracks[currentTrack]->polySixteenthVols.set(col, vol);
        }
        else{
            thisCol=tripCol;
            (*processorPresets)[currentPreset]->tracks[currentTrack]->polyTripletVols.set(tripCol, vol);
        };
    }
    
    //========Send to BeatCanvasJava.Java=======
    //public void setVol(int track, int div, int note, int vol)
    BeatCanvasOSC_MessageOut("/BeatCanvas/setVol",currentTrack, beatDiv, thisCol, vol);
    
    stuff = (String) vol;
    
    repaint();
}


