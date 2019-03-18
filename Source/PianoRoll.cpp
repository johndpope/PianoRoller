
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



PianoRoll::PianoRoll(OwnedArray<Preset> * processorPresetLocation, Staff * auditionStaffLocation, PianoRollComponent * pianoKeyLocation)
{
    topNote = 84;
    canScroll = true;
    processorPresets = processorPresetLocation;
    auditionStaff = auditionStaffLocation;
    pianoKeys = pianoKeyLocation;
    isChildOfBeatCanvas = false;
    isDoubleClick = false;
    setOpaque(true);
    
    if (! sender.connect ("127.0.0.1", 9001))
        showConnectionErrorMessage ("Error: could not connect to UDP port 9001.");
    
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
    
    PaintData paintData(&g, width, height, noteHeight, numOfRows, rootRow, topNote);
    
    g.fillAll (PianoRollerColours::beatCanvasJungleGreen); //BACKGROUND COLOR
    
    drawRows(paintData);
    
    //FILL IN NOTES
    
    for(int beat=0;beat<numOfBeats;beat++){
        const int beatSwitch = (*processorPresets)[currentPreset]->tracks[currentTrack]->beatSwitch[beat];
        const bool isMono = (*processorPresets)[currentPreset]->isMono;
        
        auto [noteArray, polyNoteArray] = [&](){
            switch (beatSwitch){
                case 0:  return std::make_pair( &(*processorPresets)[currentPreset]->tracks[currentTrack]->sixteenths     ,
                                                &(*processorPresets)[currentPreset]->tracks[currentTrack]->polySixteenths );
                case 1:  return std::make_pair( &(*processorPresets)[currentPreset]->tracks[currentTrack]->triplets       ,
                                               &(*processorPresets)[currentPreset]->tracks[currentTrack]->polyTriplets   );
                default: DBG("BEATSWITCH INVALID\n");
            }
        }();
        
        
        if (beatSwitch == 0){
            for(int subDiv=0;subDiv<4;subDiv++){
                float col = (beat*4) + subDiv;
                
                (isMono) ? monoNoteFill(paintData, noteArray, col, noteWidth) : polyNoteFill(paintData, polyNoteArray, col, noteWidth);
                drawColumnLine(paintData, subDiv, col, noteWidth);
            }
        
        }else if(beatSwitch == 1){
            for(int subDiv=0;subDiv<3;subDiv++){
                float tripCol = (beat*3) + subDiv;
                
                (isMono) ? monoNoteFill(paintData, noteArray, tripCol, tripNoteWidth) : polyNoteFill(paintData, polyNoteArray, tripCol, tripNoteWidth);
                drawColumnLine(paintData, subDiv, tripCol, tripNoteWidth);
            }
        }
        
    }
    
    
    g.setColour (Colours::black);
    
    //DRAWS ROW LINES
    for(int i=0;i<=numOfRows;i++){
        const float yPosition = 0. + (i*height/(float)numOfRows);
        g.setColour(Colours::black);
        g.drawLine(0., yPosition, width, yPosition);
        if(i==numOfRows || i==0){ //Reasons to draw a thicker line.
            g.drawLine(0., yPosition, width, yPosition, 4);
        }
    }
    g.drawLine(width, 0.0f, width, height, 3); //Right side line.
    g.setFont (30.0f);
    
    //stuff = (String)(*processorPresets)[currentPreset]->currentMode;
    //g.drawText(stuff, 100, 100, width* 0.6, 100, Justification::centred);
    
}

void PianoRoll::drawRows(PaintData p){
    
    for(int row=0;row<numOfRows;row++){
        float yPosition = 0. + (row * p.height/p.numOfRows);
        int pitch = p.topNote-row;
        
        if (checkIfBlackKey(pitch)){
            p.g->setColour (PianoRollerColours::greyOff);
            p.g->fillRect(0.0f,yPosition,p.width, p.noteHeight);
        }
        
        if(row == p.rootRow && isChildOfBeatCanvas){
            p.g->setColour (Colours::white);
            p.g->setOpacity(0.5);
            p.g->fillRect(0.0f,yPosition, p.width, p.noteHeight);
            p.g->setOpacity(1.);
        }
    }

}

void PianoRoll::drawColumnLine(PaintData p, const int subDiv, const int col, const float noteWidth){
    const int lineWidth = [subDiv]() -> int {
        if(subDiv==0){return 3;}
        else         {return 1;};
    }();
    const float xPosition = 0.0f + ( (float)col*noteWidth );
    
    p.g->setColour(Colours::black);
    p.g->drawLine(xPosition, 0., xPosition, p.height, lineWidth);
}

void PianoRoll::drawRowLines(PaintData p){
    
}

void PianoRoll::monoNoteFill(PaintData p, const Array<int> * noteArray, const int col, const float noteWidth){
    int pitch = (*noteArray)[col];
    if(pitch > 0){ //If note is active.
        p.g->setColour (PianoRollerColours::whiteBlue);
        float x = ( col * noteWidth );
        float y = ( ((float)topNote-(float)pitch)/(float)numOfRows * p.height );
        p.g->fillRect(x, y, noteWidth, p.noteHeight);
    }
}

void PianoRoll::polyNoteFill(PaintData p, const Array<Array<int>> * polyNoteArray, const int col, const float noteWidth){
    //TODO******

    //for(int polyNote=0; polyNote<polyArray.size(); polyNote++){ //For each note in the polyphony.
    for(int polyNote=0; polyNote<(*polyNoteArray)[col].size(); polyNote++){
        //int pitch = polyArray[polyNote];
        int pitch = (*polyNoteArray)[col][polyNote];
        if(pitch > 0){ //If note is active.
            p.g->setColour (PianoRollerColours::whiteBlue);
            float x = ( col * noteWidth );
            float y = ( ((float)topNote-(float)pitch)/(float)numOfRows * p.height );
            p.g->fillRect(x, y, noteWidth, p.noteHeight);

        }
    }
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
    pianoKeys->repaint();
}

void PianoRoll::mouseUp(const MouseEvent& event){
    BeatCanvasOSC_MessageOut("/BeatCanvas/reloadTrack",currentTrack);
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
                String newNoteName = Theory::setClassToPitchName[pitch%12];
                noteName->setValue(newNoteName);

                //========Send to BeatCanvasJava.Java=======
                //public void setPitch(int track, int div, int note, int pitch)
                //int content[] = {currentTrack, beatDiv, col, pitch};
                BeatCanvasOSC_MessageOut("/BeatCanvas/setPitch",currentTrack, beatDiv, thisCol, pitch);
                BeatCanvasOSC_MessageOut("/BeatCanvas/noteOnOff",currentTrack, beatDiv, thisCol, 1);
            }
            else if(( (pitch == prevPitch) || (pitch == prevPitch+1) || (pitch == prevPitch-1) ||
                      (pitch == prevPitch+2) || (pitch == prevPitch-2) )
                    && rightClick)
            {
                updateNote(thisCol, 0, beatSwitch);
                
                //========Send to BeatCanvasJava.Java=======
                //public void noteOnOff(int track, int div, int note, int onOff)
                BeatCanvasOSC_MessageOut("/BeatCanvas/noteOnOff",currentTrack, beatDiv, thisCol, 0);
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
            String newNoteName = Theory::setClassToPitchName[pitch%12];
            noteName->setValue(newNoteName);
        }
    }
    auditionStaff->notes.clear();
    auditionStaff->notes.push_back(NoteHead(pitch, -1, -1));
    
    repaint();
    auditionStaff->repaint();
}

void PianoRoll::spacebar(){
    BeatCanvasOSC_MessageOut("/BeatCanvas/spacebar");
}

void PianoRoll::changeBeatCanvasPreset(const int preset){
    BeatCanvasOSC_MessageOut("/BeatCanvas/updatePreset", preset);
}

void PianoRoll::changeBeatCanvasTrack(const int track){
    BeatCanvasOSC_MessageOut("/BeatCanvas/updateTrack", track);
}

void PianoRoll::changeBeatCanvasBeats(const int beats){
    BeatCanvasOSC_MessageOut("/BeatCanvas/updateBeat", beats);
}

void PianoRoll::changeBeatCanvasTriplet(const int beat, const int val){
    //Java code:
    //changeRhythmDiv(int track, int beatMinusOne, int divSwitch)
    BeatCanvasOSC_MessageOut("/BeatCanvas/changeRhythmDiv", currentTrack, beat, val);
}









//=============================================================================================================


void PianoKeys::paint(juce::Graphics &g){
    const int topNote = pianoRoll->topNote;
    const float width = getWidth();
    const float height = getHeight();
    const float noteHeight = ( height / (float)numOfRows );
    
    g.fillAll (PianoRollerColours::beatCanvasJungleGreen); //BACKGROUND COLOR
    
    for(int row=0; row<numOfRows; row++){
        int pitch = topNote-row;
        float yPosition = row * noteHeight;
        
        if (checkIfBlackKey(pitch)){
            g.setColour (Colours::darkgrey);
            //g.setColour (Colours::black);
            
            g.fillRect(0.0f,yPosition,width*0.666, noteHeight);
            
            g.setColour (Colours::black);
            //g.drawLine(0.0f, yPosition, width*0.66, yPosition);
            g.setColour (Colours::black);
            g.drawRect(0.0f,yPosition,width*0.66, noteHeight);
            
        }else{ //is a White Key
            g.setColour (PianoRollerColours::beatCanvasJungleGreen);
            //g.setColour (Colours::floralwhite);
            
            g.fillRect(0.0f,yPosition,width, noteHeight);
            
            g.setColour (Colours::black);
            if(pitch%12==4 || pitch%12==11){ //Note E or B
                g.drawLine(0.0f, yPosition, width, yPosition);
            }else{
                g.drawLine(width*0.66f, yPosition-(noteHeight*0.5f), width-0.66f, yPosition-(noteHeight*0.5f));
            }
        }
        
    }
    
    g.drawRoundedRectangle(0.0f, 0.0f, width, height, 0.0f, 4.0f);
    
    
}

void PianoKeys::mouseUp(const juce::MouseEvent &event){
    
}

void PianoKeys::mouseDown(const juce::MouseEvent &event){
    
    
}

void PianoKeys::mouseDrag(const juce::MouseEvent &event){
    
}

