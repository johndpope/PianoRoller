/*
  ==============================================================================

    Setup.h
    Created: 2 Jan 2019 1:56:52pm
    Author:  Adam Shield

  ==============================================================================
*/

#pragma once


#include "../JuceLibraryCode/JuceHeader.h"
#include <map>

namespace PianoRollerColours {
    inline Colour greyOff = Colour(110,110,110);
    inline Colour whiteBlue = Colour(195,223,226);
    inline Colour beatCanvasJungleGreen = Colour(152,152,115);
    inline Colour calmGreen = Colour(156,168,152);
}



class PianoRollComponent : public Component
{
public:
    //const Colour greyOff = Colour(128,128,128);
    static constexpr int numOfTracks = 8;
    static constexpr int numOfPresets = 8;
    static constexpr int maxBeats = 16;
    static constexpr int numOfRows = 32;
    static constexpr int blackKeys[5] = {1,3,6,8,10};
    
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
        String rootName;
        String currentMode;
        String generatorType;
        String arpType;
        Array<int> currentModeNotes;
        OwnedArray<Track> tracks;
        
        Preset(){
            numOfBeats = 4;
            isMono = true;
            currentModeNotes = {0,2,4,5,7,9,11}; //Major Scale
            rootName = "C";
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
    
    //OwnedArray<Preset> * processorPresets;
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
    bool checkIfBlackKey(const int pitch);
    
    //template <class T>
    //void BeatCanvasOSC_MessageOut(String initMessage, std::initializer_list<T> data);
    template<typename T, typename... Args>
    void BeatCanvasOSC_MessageOut(String initMessage, T t, Args... data){
        if (! sender.send (initMessage, data...))
            showConnectionErrorMessage ("Error: could not send OSC message.");
    }
    
    void BeatCanvasOSC_MessageOut(String message){
        if (! sender.send (message))
            showConnectionErrorMessage ("Error: could not send OSC message.");
    }
    
    OSCSender sender;
    
    void showConnectionErrorMessage (const String& messageText)
    {
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "Connection error",
                                          messageText,
                                          "OK");
    }
    
    struct PaintData{
        Graphics * g;
        float width;
        float height;
        float noteHeight;
        float numOfRows;
        float rootRow;
        float topNote;
        
        PaintData(Graphics * _g, float _width, float _height, float _noteHeight, float _numOfRows, float _rootRow, float _topNote)
        {
            g = _g;
            width = _width;
            height = _height;
            noteHeight = _noteHeight;
            numOfRows = _numOfRows;
            rootRow = _rootRow;
            topNote = _topNote;
        };
    };
    

    
private:

    
};












