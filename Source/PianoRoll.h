/*
 ==============================================================================
 
 PianoRoll.h
 Created: 29 Dec 2018 10:30:33pm
 Author:  Adam Shield
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Setup.h"
#include "PluginProcessor.h"
#include <map>

//==============================================================================




class PianoRoll    : public PianoRollComponent//,
                    // public KeyListener
{
public:
    
    
    
    PianoRoll(OwnedArray<Preset> * processorPresetLocation);
    ~PianoRoll();
    
    void paint (Graphics&) override;
    void resized() override;
    void (*setParentMidiDisplay)(int);
    MidiMessage midiMessage;
    //bool keyPressed (const KeyPress& key, Component* originatingComponent) override;
    void changeBeatCanvasPreset(const int preset);
    void changeBeatCanvasTrack(const int track);
    void changeBeatCanvasBeats(const int beats);
    void changeBeatCanvasTriplet(const int beat, int val);
    int topNote;
    int polySelectedNote;
    bool canScroll;
    bool isChildOfBeatCanvas;
    void spacebar();
    bool isDoubleClick;
    String stuff = "stuff to say";
    Value * noteName;
    
private:

    void mouseEnter(const MouseEvent& event) override;
    void mouseExit(const MouseEvent& event) override;
    void mouseUp(const MouseEvent& event) override;
    void mouseDown(const MouseEvent& event) override;
    void mouseDrag (const MouseEvent& event) override;
    void mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) override;
     void mouseDoubleClick (const MouseEvent&) override;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PianoRoll)
    
    
    
};



