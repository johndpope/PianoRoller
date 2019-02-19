/*
  ==============================================================================

    Setup.h
    Created: 2 Jan 2019 1:56:52pm
    Author:  Adam Shield

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Theory.h"
#include <map>




class PianoRollComponent : public Component
{
public:
    //const Colour greyOff = Colour(128,128,128);
    const Colour greyOff = Colour(110,110,110);
    const Colour whiteBlue = Colour(195,223,226);
    const Colour beatCanvasJungleGreen = Colour(152,152,115);
    const Colour calmGreen = Colour(156,168,152);
    const static int numOfTracks = 8;
    const static int numOfPresets = 8;
    const static int maxBeats = 16;
    const int numOfRows = 32;
    
    int currentPreset,
        currentTrack;
    
    
    class Track{
    public:
        Array<int> sixteenths;
        Array<int> triplets;
        Array<int> sixteenthVols;
        Array<int> tripletVols;
        Array<int> beatSwitch;
        Array<bool> sixteenthUserSelected;
        Array<bool> tripletUserSelected;
        Array<Array<int>> polySixteenths;
        Array<Array<int>> polyTriplets;
        Array<int> polySixteenthVols;
        Array<int> polyTripletVols;
        Array<Array<int>> polySixteenthUserSelected; //Not in use
        Array<Array<int>> polyTripletUserSelected; //Not in use
        int octaveShift;
        String selectedScale, selectedGenerator, selectedRoot, selectedArpDirection;
        
        Track(){
            octaveShift=0;
            selectedRoot = "C";
            selectedScale = "Major";
            selectedGenerator = "random";
            selectedArpDirection = "ascend";
            
            for(int note=0;note<maxBeats*4;note++){
                //Mono
                sixteenths.add(0);
                sixteenthVols.add(96);
                sixteenthUserSelected.add(false);
                //Poly
                polySixteenths.add({-1});
                polySixteenthVols.add(96);

            }
            for(int note=0;note<maxBeats*3;note++){
                //Mono
                triplets.add(0);
                tripletVols.add(96);
                tripletUserSelected.add(false);
                //Poly
                polyTriplets.add({-1});
                polyTripletVols.add(96);
            }
            for(int note=0;note<maxBeats;note++){
                beatSwitch.add(0);
            }
        }
    };
    
    class Preset{
        
    public:
        int numOfBeats;
        int root;
        bool isMono;
        String currentMode;
        String generatorType;
        String arpType;
        Array<int> currentModeNotes;
        OwnedArray<Track> tracks;
        
        Preset(){
            numOfBeats = 4;
            isMono = true;
            currentModeNotes = {0,2,4,5,7,9,11}; //Major Scale
            currentMode = "Major";
            generatorType = "random";
            root = 0;
            
            for(int track=0;track<=numOfTracks;track++){
                tracks.add(new Track());
            }
        }
    };
    

    ////THE ALMIGHTY PRESET ARRAY////
    OwnedArray<Preset> presets;
    ////========================////
    
    OwnedArray<Preset> * processorPresets;
    
    ////==============CONSTRUCTOR==============//
    PianoRollComponent(){
        currentPreset = 1;
        currentTrack = 1;
        
        //SETUP PRESETS
        for(int preset=0;preset<=numOfPresets;preset++){
            presets.add(new Preset);
        }
    }
    
    void updateNote(int col, int pitch, int beatSwitch);
    void setPitch(int track, int div, int note, int pitch, int preset);
    void updateVolume(int col, int vol, int beatSwitch);
    void updateBeatSwitch(int beat, int switchVal);
    void updateNumOfBeats(int beats);
    void updateNumOfBeats(int beats, const int preset);
    void changeRhythmDiv(int track, int beat, int beatSwitch);
    void updatePreset(const int preset);
    void updateTrack(const int track);
    void noteOnOff(const int track, const int div, const int note, const int onOff);
    void copyPreset(const int presetSource, const int presetReplaced);
    int midiLimit(int midiVal);
    int limitRange(int val, int low, int high);
    
    Theory theory;

    OSCSender sender;
    
    void showConnectionErrorMessage (const String& messageText)
    {
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "Connection error",
                                          messageText,
                                          "OK");
    }
    
    
private:

    
};













