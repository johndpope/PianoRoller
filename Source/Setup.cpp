/*
  ==============================================================================

    Setup.cpp
    Created: 3 Jan 2019 6:19:18pm
    Author:  Adam Shield

  ==============================================================================
*/

#include "Setup.h"

void PianoRollComponent::updateNote(int col, int pitch, int beatSwitch){
    bool userSelected;
    bool isMono = (*processorPresets)[currentPreset]->isMono;
    userSelected = (pitch>0); //TODO
    
    if (isMono){
        if (beatSwitch == 0){
            (*processorPresets)[currentPreset]->tracks[currentTrack]->sixteenths.set(col, pitch);
            (*processorPresets)[currentPreset]->tracks[currentTrack]->sixteenthUserSelected = userSelected;
        }
        if (beatSwitch == 1){
            (*processorPresets)[currentPreset]->tracks[currentTrack]->triplets.set(col,pitch);
            (*processorPresets)[currentPreset]->tracks[currentTrack]->tripletUserSelected = userSelected;
        }
    }else{ //isPoly
        
        Array<Array<int>> * polyNotes;
        if (beatSwitch == 0){
            polyNotes = &((*processorPresets)[currentPreset]->tracks[currentTrack]->polySixteenths);
        }else if (beatSwitch == 1){
            polyNotes = &((*processorPresets)[currentPreset]->tracks[currentTrack]->polyTriplets);
        }else{polyNotes = nullptr;}
    
        
        Array<int>newPitchArray = (*polyNotes).operator[](col);
        if (pitch > 0){ //leftClick
            if(newPitchArray.size()<=12){
                newPitchArray.addIfNotAlreadyThere(pitch);
            }
        }else{ //rightClick
            newPitchArray.removeFirstMatchingValue(pitch * -1);
        }
        polyNotes->set(col, newPitchArray);
    }
    
    repaint();
}

void PianoRollComponent::updateVolume(int col, int vol, int beatSwitch){
    if (beatSwitch == 0){
        (*processorPresets)[currentPreset]->tracks[currentTrack]->sixteenthVols.set(col, vol);
    }
    if (beatSwitch == 1){
        (*processorPresets)[currentPreset]->tracks[currentTrack]->tripletVols.set(col,vol);
    }
    repaint();
}

void PianoRollComponent::updateBeatSwitch(int beat, int switchVal){
    (*processorPresets)[currentPreset]->tracks[currentTrack]->beatSwitch.set(beat,switchVal);
    repaint();
}

void PianoRollComponent::updateNumOfBeats(int beats){
    updateNumOfBeats(beats, currentPreset);
    repaint();
}

void PianoRollComponent::updateNumOfBeats(int beats, const int preset){
    beats = limitRange(beats, 1, maxBeats);
    (*processorPresets)[preset]->numOfBeats = beats;
}

void PianoRollComponent::changeRhythmDiv(int track, int beat, int beatSwitch){
    (*processorPresets)[currentPreset]->tracks[track]->beatSwitch.set(beat, beatSwitch);
    repaint();
}

void PianoRollComponent::updatePreset(const int preset){
    currentPreset = preset;
    repaint();
}

int PianoRollComponent::midiLimit(int midiVal){
    if(midiVal>127){midiVal=127;}
    else if(midiVal<0){midiVal=0;}
    return midiVal;
}

int PianoRollComponent::limitRange(int val, int low, int high){
    if(val>high){val=high;}
    else if(val<low){val=low;}
    return val;
}

bool PianoRollComponent::checkIfBlackKey(const int pitch){
    bool result = false;
    for(auto key : PianoRollComponent::blackKeys){
        if(pitch%12 == key) result = true;
    }
    return result;
}

void PianoRollComponent::updateTrack(const int track){
    currentTrack = track;
    repaint();
}

void PianoRollComponent::noteOnOff(const int track, const int div, const int note, const int onOff){
    
    
    int newPitch;
    if(onOff==1){newPitch=65;}
    else        {newPitch=0;}
    
    if(div==4){
        (*processorPresets)[currentPreset]->tracks[track]->sixteenths.set(note,newPitch);
    }
    else if(div==3){
        (*processorPresets)[currentPreset]->tracks[track]->triplets.set(note,newPitch);
    }
    repaint();
}

void PianoRollComponent::copyPreset(const int presetSource,const  int presetReplaced){
    int copyBeats = presets[presetSource]->numOfBeats;
    (*processorPresets)[presetReplaced]->numOfBeats = copyBeats;
    (*processorPresets)[presetReplaced]->tracks.deleteAllObjects();
    (*processorPresets)[presetReplaced]->tracks.addCopiesOf(presets[presetSource]->tracks);
    
    repaint();
}

//From Java
//public void setPitch(int track, int div, int note, int pitch, int preset)
void PianoRollComponent::setPitch(const int track, const int div, const int note, const int pitch, const int preset){
    if (div == 4){
        (*processorPresets)[preset]->tracks[track]->sixteenths.set(note, pitch);
    }
    if (div == 3){
        (*processorPresets)[preset]->tracks[track]->triplets.set(note,pitch);
    }
}

void PianoRollComponent::drawColumnLine(PaintData p, const int subDiv, const int col, const float noteWidth){
    const int lineWidth = (subDiv==0) ? 3 : 1;
    const float xPosition = 0.0f + ( (float)col*noteWidth );
    
    p.g->setColour(Colours::black);
    p.g->drawLine(xPosition, 0., xPosition, p.height, lineWidth);
}

