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
#include "Theory.h"
#include "PluginProcessor.h"
#include <map>

//==============================================================================




class PianoRoll    : public PianoRollComponent//,
                    // public KeyListener
{
public:
    
    
    
    PianoRoll(OwnedArray<Preset> * processorPresetLocation, Staff * auditionStaffLocation, PianoRollComponent * pianoKeyLocation);
    ~PianoRoll();
    
    void resized() override;
    void (*setParentMidiDisplay)(int);
    MidiMessage midiMessage;
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
    PianoRollComponent * pianoKeys;
    Staff * auditionStaff;
    
private:
    void paint (Graphics&) override;
    void drawRows(PaintData p);
    void drawColumnLine(PaintData p, const int subDiv, const int col, const float noteWidth);
    void drawRowLines(PaintData p);
    void monoNoteFill(PaintData p, const Array<int> * noteArray, const int col, const float thisNoteWidth);
    void polyNoteFill(PaintData p, const Array<Array<int>> * polyNoteArray, const int col, const float thisNoteWidth);
    void drawNotes(PaintData p);

    void mouseEnter(const MouseEvent& event) override;
    void mouseExit(const MouseEvent& event) override;
    void mouseUp(const MouseEvent& event) override;
    void mouseDown(const MouseEvent& event) override;
    void mouseDrag (const MouseEvent& event) override;
    void mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) override;
    void mouseDoubleClick (const MouseEvent&) override;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PianoRoll)
    
    
    
};

//===================Piano Keys===================//

class PianoKeys    : public PianoRollComponent
{
public:
    PianoRoll * pianoRoll;
    Staff * auditionStaff;
    
    PianoKeys(PianoRoll * pianoRollInput){
        pianoRoll = pianoRollInput;
    }
    
private:
    void paint (Graphics&) override;
    
    void mouseUp(const MouseEvent& event) override;
    void mouseDown(const MouseEvent& event) override;
    void mouseDrag (const MouseEvent& event) override;
    
};

