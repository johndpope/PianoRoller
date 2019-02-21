
/*
 ==============================================================================
 
 PianoRoll.cpp
 Created: 29 Dec 2018 10:30:33pm
 Author:  Adam Shield
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "PianoRoll.h"

//==============================================================================



PianoRoll::PianoRoll(OwnedArray<Preset> * processorPresetLocation)
{
    topNote = 84;
    canScroll = true;
    processorPresets = processorPresetLocation;
    isChildOfBeatCanvas = false;
    isDoubleClick = false;
    
    if (! sender.connect ("127.0.0.1", 9001))
    {
        showConnectionErrorMessage ("Error: could not connect to UDP port 9001.");
    }
    
    //stuff = "eegergerg";
    stuff = "";

    setSize(getWidth(), getHeight());
    //setOpaque(true);
}

PianoRoll::~PianoRoll()
{
}

void PianoRoll::paint (Graphics& g)
{
    const int numOfBeats = (*processorPresets)[currentPreset]->numOfBeats;
    const int rootRow = topNote-65;
    const float width = getWidth();
    const float height = getHeight();
    const float noteWidth = (width / ((float)numOfBeats * 4.0f) );
    const float noteHeight = ( height / (float)numOfRows );
    const float tripNoteWidth = width / ((float)numOfBeats * 3.0f);
    
    g.fillAll (beatCanvasJungleGreen); //BACKGROUND COLOR
    
    for(int row=0;row<numOfRows;row++){
        float yPosition = 0. + (row * getHeight()/numOfRows);
        //int blackKeys[5] = {2,4,6,9,11};
        int blackKeys[5] = {1,3,6,8,10};
        int pitch = topNote-row;
        
        if (std::find(std::begin(blackKeys), std::end(blackKeys), pitch%12) != std::end(blackKeys)){
            g.setColour (greyOff);
            g.fillRect(0.0f,yPosition,width, noteHeight);
        }
        if(pitch%12 == 0){
            //g.setColour(Colours::black);
        }
        
        if(row == rootRow && isChildOfBeatCanvas){
            g.setColour (Colours::white);
            g.setOpacity(0.5);
            g.fillRect(0.0f,yPosition,width, noteHeight);
            g.setOpacity(1.);
        }
    }
    
    //FILL IN NOTES
    
    for(int beat=0;beat<numOfBeats;beat++){
        const int beatSwitch = (*processorPresets)[currentPreset]->tracks[currentTrack]->beatSwitch[beat];
        const bool isMono = (*processorPresets)[currentPreset]->isMono;
        if (beatSwitch == 0){
            for(int subDiv=0;subDiv<4;subDiv++){
                float col = (beat*4) + subDiv;
                
                if(isMono){
                    int pitch = (*processorPresets)[currentPreset]->tracks[currentTrack]->sixteenths[col];
                    if(pitch > 0){ //If note is active.
                        g.setColour (whiteBlue);
                        float x = ( col * noteWidth );
                        float y = ( ((float)topNote-(float)pitch)/(float)numOfRows * height );
                        g.fillRect(x, y, noteWidth, noteHeight);
                    }
                }else{ //isPoly
                    
                    //TODO******
                    //Array<int> polyArray = (*processorPresets)[currentPreset]->tracks[currentTrack]->polySixteenths[col];
                    Array<Array<int>> * polyArrays = &((*processorPresets)[currentPreset]->tracks[currentTrack]->polySixteenths);
                    
                    //for(int polyNote=0; polyNote<polyArray.size(); polyNote++){ //For each note in the polyphony.
                    for(int polyNote=0; polyNote<(*polyArrays)[col].size(); polyNote++){
                        //int pitch = polyArray[polyNote];
                        int pitch = (*polyArrays)[col][polyNote];
                        if(pitch > 0){ //If note is active.
                            g.setColour (whiteBlue);
                            float x = ( col * noteWidth );
                            float y = ( ((float)topNote-(float)pitch)/(float)numOfRows * height );
                            g.fillRect(x, y, noteWidth, noteHeight);
                            
                        }
                    }
                    
                }
                
                //DRAW COLUMN LINES
                const int lineWidth = [subDiv]() -> int {
                    if(subDiv==0){return 3;}
                    else         {return 1;};
                }();
                const float xPosition = 0.0f + ( col*noteWidth );
                
                g.setColour(Colours::black);
                g.drawLine(xPosition, 0., xPosition, height, lineWidth);
            }
        }else if(beatSwitch == 1){
            for(int subDiv=0;subDiv<4;subDiv++){
                float tripCol = (beat*3) + subDiv;
                
                if(isMono){
                    int pitch = (*processorPresets)[currentPreset]->tracks[currentTrack]->triplets[tripCol];
                    if(pitch > 0){ //If note is active.
                        g.setColour (whiteBlue);
                        const Point<float> pos = {
                            tripCol * tripNoteWidth,                                //X
                            ((float)topNote-(float)pitch)/(float)numOfRows * height //Y
                        };
                        g.fillRect(pos.getX(), pos.getY(), tripNoteWidth, noteHeight);
                    }
                }else{ //isPoly
                    
                    //TODO******
                    Array<int> polyArray = (*processorPresets)[currentPreset]->tracks[currentTrack]->polyTriplets[tripCol];
                    for(int polyNote=0; polyNote<polyArray.size(); polyNote++){ //For each note in the polyphony.
                        int pitch = polyArray[polyNote];
                        if(pitch > 0){ //If note is active.
                            g.setColour (whiteBlue);
                            const Point<float> pos = {
                                tripCol * tripNoteWidth,                                //X
                                ((float)topNote-(float)pitch)/(float)numOfRows * height //Y
                            };
                            g.fillRect(pos.getX(), pos.getY(), tripNoteWidth, noteHeight);
                        }
                    }
                    
                }
                
                //DRAW COLUMN LINES
                const int lineWidth = [subDiv]() -> int {
                    if(subDiv==0){return 3;}
                    else         {return 1;};
                }();
                const int xPosition = 0.0f + ( tripCol*tripNoteWidth );
                
                g.setColour(Colours::black);
                g.drawLine(xPosition, 0., xPosition, height, lineWidth);
            }
        }
        
        
    }
    
    
    g.setColour (Colours::black);
    
    //DRAWS ROW LINES
    for(int i=0;i<=numOfRows;i++){
        const float yPosition = 0. + (i*getHeight()/numOfRows);
        g.setColour(Colours::black);
        g.drawLine(0., yPosition, width, yPosition);
        if(i==numOfRows || i==0){ //Reasons to draw a thicker line.
            g.drawLine(0., yPosition, width, yPosition, 4);
        }
    }
    g.drawLine(width, 0.0f, width, height, 3); //Right side line.
    
    //g.setColour(Colours::black);
    g.setFont (30.0f);
    g.drawText(stuff, 100, 100, 100, 100, Justification::centred);
    
    
    
}

void PianoRoll::resized()
{
    
}


void PianoRoll::mouseEnter(const MouseEvent& event){
    //repaint();
}

void PianoRoll::mouseExit(const MouseEvent& event){
    //repaint();
}

void PianoRoll::mouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel){
    float verticalAdjust = wheel.deltaY * 50.0f;
    verticalAdjust = verticalAdjust < 0 ? floor(verticalAdjust) : ceil(verticalAdjust);
    
    topNote = limitRange( (topNote + (int)verticalAdjust), 8+numOfRows, 127);
    repaint();
}

void PianoRoll::mouseUp(const MouseEvent& event){
    if (! sender.send ("/BeatCanvas/reloadTrack",currentTrack)){
        showConnectionErrorMessage ("Error: could not send OSC message.");
        stuff = "failed to send note message.";
    }
}

void PianoRoll::mouseDrag(const MouseEvent& event){
    mouseDown(event);
}

void PianoRoll::mouseDoubleClick(const juce::MouseEvent &event){
    isDoubleClick = true;
    mouseDown(event);
}

void PianoRoll::mouseDown(const MouseEvent& event){
    const bool leftClick = event.mods.isLeftButtonDown();
    bool rightClick = event.mods.isRightButtonDown();
    const bool isMono = (*processorPresets)[currentPreset]->isMono;
    const bool isDragging = event.mouseWasDraggedSinceMouseDown();
    if(isDoubleClick){rightClick = true; isDoubleClick=false;}
    
    const Point<int> pos = {getMouseXYRelative().getX(), getMouseXYRelative().getY()};
    float x = getMouseXYRelative().getX();
    float y = getMouseXYRelative().getY();
    
    const int numOfBeats = (*processorPresets)[currentPreset]->numOfBeats;
    const int row = (int) (y/(float)getHeight() * (float) numOfRows); //Final (int) cast rounds it down.
    const int col = (int) (x/(float)getWidth() * (float) (numOfBeats*4)); //Final (int) cast rounds it down.
    const int tripCol = (int) (x/(float)getWidth() * (float) (numOfBeats*3)); //Final (int) cast rounds it down.
    const int currentBeat = col / 4;
    const int beatSwitch = (*processorPresets)[currentPreset]->tracks[currentTrack]->beatSwitch[currentBeat];
    int pitch = topNote - row;
    int beatDiv;
    int thisCol;
    int prevPitch;

    if(pitch<128 && pitch>8){
        //Scroll up and down
        if(canScroll){
            if (pitch>topNote){topNote = pitch;}
            else if(pitch<topNote-numOfRows){topNote = pitch+numOfRows;}
        }else{
            if (pitch>topNote){pitch = topNote;}
            else if(pitch<topNote-numOfRows){pitch = topNote-numOfRows;}
        }
        //Setup previous pitch
        if(beatSwitch==0){
            beatDiv=4;
            thisCol = col;
            prevPitch = (*processorPresets)[currentPreset]->tracks[currentTrack]->sixteenths[col];
        }else{
            beatDiv=3;
            thisCol = tripCol;
            prevPitch = (*processorPresets)[currentPreset]->tracks[currentTrack]->triplets[tripCol];
        };

        if(isMono){
            if(pitch != prevPitch && leftClick){
                updateNote(thisCol, pitch, beatSwitch);
                String newNoteName = theory.setClassToPitchName[pitch%12];
                noteName->setValue(newNoteName);

                //========Send to BeatCanvasJava.Java=======
                //public void setPitch(int track, int div, int note, int pitch)
                //int content[] = {currentTrack, beatDiv, col, pitch};
                if (! sender.send ("/BeatCanvas/setPitch",currentTrack, beatDiv, thisCol, pitch)){
                    showConnectionErrorMessage ("Error: could not send OSC message.");
                    stuff = "failed to send note message.";
                }
                if (! sender.send ("/BeatCanvas/noteOnOff",currentTrack, beatDiv, thisCol, 1)){
                    showConnectionErrorMessage ("Error: could not send OSC message.");
                    stuff = "failed to send note message.";
                }
            }
            else if(( (pitch == prevPitch) || (pitch == prevPitch+1) || (pitch == prevPitch-1) ||
                      (pitch == prevPitch+2) || (pitch == prevPitch-2) )
                    && rightClick)
            {
                updateNote(thisCol, 0, beatSwitch);
                
                //========Send to BeatCanvasJava.Java=======
                //public void noteOnOff(int track, int div, int note, int onOff)
                if (! sender.send ("/BeatCanvas/noteOnOff",currentTrack, beatDiv, thisCol, 0))
                {
                    showConnectionErrorMessage ("Error: could not send OSC message.");
                    stuff = "failed to send note message.";
                }
            }
        }else{ //isPoly
            if(leftClick && !rightClick){
                if(isDragging==false){
                    polySelectedNote = pitch;
                }else{ //isDragging
                    updateNote(thisCol, polySelectedNote * -1, beatSwitch); //Remove previous note (move it to new pitch)
                    polySelectedNote = pitch;
                }
                updateNote(thisCol, pitch, beatSwitch);
            }else{ //rightClick
                updateNote(thisCol, pitch * -1, beatSwitch);
            }
            String newNoteName = theory.setClassToPitchName[pitch%12];
            noteName->setValue(newNoteName);
        }
    }
    
    repaint();
}
/*
bool PianoRoll::keyPressed(const juce::KeyPress &key, juce::Component *originatingComponent){
    
    //SPACEBAR
    if(key.getKeyCode() == 32){
        if (! sender.send ("/BeatCanvas/spacebar"))
        {
            showConnectionErrorMessage ("Error: could not send OSC message.");
        }
    }
    
    return true;
}
 
*/
void PianoRoll::spacebar(){
    if (! sender.send ("/BeatCanvas/spacebar"))
    {
        showConnectionErrorMessage ("Error: could not send OSC message.");
    }
}



void PianoRoll::changeBeatCanvasPreset(const int preset){
    if (! sender.send ("/BeatCanvas/updatePreset", preset))
    {
        showConnectionErrorMessage ("Error: could not send OSC message.");
    }
}

void PianoRoll::changeBeatCanvasTrack(const int track){
    if (! sender.send ("/BeatCanvas/updateTrack", track))
    {
        showConnectionErrorMessage ("Error: could not send OSC message.");
    }
}

void PianoRoll::changeBeatCanvasBeats(const int beats){
    if (! sender.send ("/BeatCanvas/updateBeat", beats))
    {
        showConnectionErrorMessage ("Error: could not send OSC message.");
    }
}

void PianoRoll::changeBeatCanvasTriplet(const int beat, const int val){
    //Java code:
    //changeRhythmDiv(int track, int beatMinusOne, int divSwitch)
    int divSwitch;
    if (! sender.send ("/BeatCanvas/changeRhythmDiv", currentTrack, beat, val))
    {
        showConnectionErrorMessage ("Error: could not send OSC message.");
    }
}

