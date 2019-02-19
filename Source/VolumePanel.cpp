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
    
    if (! sender.connect ("127.0.0.1", 9001)) // [4]
    {
        showConnectionErrorMessage ("Error: could not connect to UDP port 9001.");
    }
    
    stuff = "foo";
    
    setVisible(true);
    setSize(getWidth(), getHeight());
}

VolumePanel::~VolumePanel(){
    
}

void VolumePanel::paint (Graphics& g)
{
    //int numOfBeats = presets[currentPreset]->numOfBeats;
    int numOfBeats = (*processorPresets)[currentPreset]->numOfBeats;
    float width = getWidth();
    float height = getHeight();
    float noteWidth = (width / ((float)numOfBeats * 4.0f) );
    float tripNoteWidth = width / ((float)numOfBeats * 3.0f);
    bool isMono = (*processorPresets)[currentPreset]->isMono;
    
    g.fillAll (greyOff); //BACKGROUND COLOR
    
    
    for(int beat=0;beat<numOfBeats;beat++){
        float col, xPosition, rectX, rectY;
        int vol,lineWidth;
        int currentBeatSwitch = (*processorPresets)[currentPreset]->tracks[currentTrack]->beatSwitch[beat];
        
        if(currentBeatSwitch == 0){
            for(int subDiv=0;subDiv<4;subDiv++){
                col = (beat*4) + subDiv;
                if(isMono){
                    vol = (*processorPresets)[currentPreset]->tracks[currentTrack]->sixteenthVols[col];
                }else{ //isPoly
                    vol = (*processorPresets)[currentPreset]->tracks[currentTrack]->polySixteenthVols[col];
                }
                
                //g.setColour (Colours::yellow);
                g.setColour (whiteBlue);
                rectX = ( col * noteWidth );
                rectY = height - ( height/127.f * (float)vol );
                g.fillRect(rectX, rectY, noteWidth, height);
                
                
                //DRAW COLUMN LINES
                if(subDiv==0){lineWidth=3; g.setColour(Colours::black);}
                         else{lineWidth=1; g.setColour(Colours::black);};
                g.setColour (Colours::black);
                xPosition = 0.0f + ( col*noteWidth );
                g.drawLine(xPosition, 0., xPosition, height, lineWidth);
            }
        }else if(currentBeatSwitch == 1){
            for(int subDiv=0;subDiv<3;subDiv++){
                col = (beat*3) + subDiv;
                if(isMono){
                    vol = (*processorPresets)[currentPreset]->tracks[currentTrack]->tripletVols[col];
                }else{ //isPoly
                    vol = (*processorPresets)[currentPreset]->tracks[currentTrack]->polyTripletVols[col];
                }
                
                //g.setColour (Colours::yellow);
                g.setColour (whiteBlue);
                rectX = ( col * tripNoteWidth );
                rectY = height - ( height/127.f * (float)vol );
                g.fillRect(rectX, rectY, tripNoteWidth, height);
                
                //DRAW COLUMN LINES
                if(subDiv==0){lineWidth=3;}
                         else{lineWidth=1;};
                g.setColour(Colours::black);
                xPosition = 0.0f + ( col*tripNoteWidth );
                g.drawLine(xPosition, 0., xPosition, height, lineWidth);
            }
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
    bool leftClick = event.mods.isLeftButtonDown();
    bool rightClick = event.mods.isRightButtonDown();
    
    //int numOfBeats = presets[currentPreset]->numOfBeats;
    int numOfBeats = (*processorPresets)[currentPreset]->numOfBeats;
    float x = getMouseXYRelative().getX();
    float y = getMouseXYRelative().getY();
    int vol = (int) ( 127.f - y/(float)getHeight() * 127.f ); //Final (int) cast rounds it down.
    int col = (int) (x/(float)getWidth() * (float) (numOfBeats*4)); //Final (int) cast rounds it down.
        vol = midiLimit(vol);
        col = midiLimit(col);
    int tripCol = (int) (x/(float)getWidth() * (float) (numOfBeats*3)); //Final (int) cast rounds it down.
    int currentBeat = col / 4;
    int beatSwitch = (*processorPresets)[currentPreset]->tracks[currentTrack]->beatSwitch[currentBeat];
    int beatDiv;
    int thisCol;
    if(rightClick){vol = 96;}
    
    if((*processorPresets)[currentPreset]->isMono){
        if(beatSwitch==0){
            beatDiv=4;
            thisCol=col;
            (*processorPresets)[currentPreset]->tracks[currentTrack]->sixteenthVols.set(col, vol);
        }
        else{
            beatDiv=3;
            thisCol=tripCol;
            (*processorPresets)[currentPreset]->tracks[currentTrack]->tripletVols.set(tripCol, vol);
        };
        
    }else{ //isPoly
        if(beatSwitch==0){
            beatDiv=4;
            thisCol=col;
            (*processorPresets)[currentPreset]->tracks[currentTrack]->polySixteenthVols.set(col, vol);
        }
        else{
            beatDiv=3;
            thisCol=tripCol;
            (*processorPresets)[currentPreset]->tracks[currentTrack]->polyTripletVols.set(tripCol, vol);
        };
    }
    
    
    //========Send to BeatCanvasJava.Java=======
    //public void setVol(int track, int div, int note, int vol)
    if (! sender.send ("/BeatCanvas/setVol",currentTrack, beatDiv, thisCol, vol)) // [5]
    {
        showConnectionErrorMessage ("Error: could not send OSC message.");
        stuff = "failed to send note message.";
    }
    
    stuff = (String) vol;
    
    repaint();
}


