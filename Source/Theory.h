/*
  ==============================================================================

    Theory.h
    Created: 18 Jan 2019 1:13:06pm
    Author:  Adam Shield

  ==============================================================================
*/

#pragma once
#include <map>
#include <iostream>

class Theory{
    
public:
    
    struct Mode{
        Array<int> mode;
        Array<int> enharmIndex;
        Mode(const Array<int> Array1, const Array<int> Array2){
            mode = Array1;
            enharmIndex = Array2;
        }
    };
    
    struct Scale : Mode{
        
    };
    
    struct Chord : Mode{
        
    };
    
    
    const Mode foo = {{0,1,2,3}, {0,0,0,0,0,0,0}};
    
    class Scales{
    public:
        Scales(){}
        
        Array<int>  major =      {0,2,4,5,7,9,11},
                    natMinor =   {0,2,3,5,7,8,10},
                    harmMinor =  {0,2,3,5,7,8,11},
                    melMinor =   {0,2,3,5,7,9,11},
                    locrian =    {0,1,3,5,6,8,1},
                    dorian =     {0,2,3,5,7,8,10},
                    phrygian =   {0,1,3,5,7,8,10},
                    lydian =     {0,2,4,6,7,9,11},
                    mixolydian = {0,2,4,5,7,9,10},
                    wholeTone =  {0,2,4,6,8,10},
                    pentaMaj =   {0,2,4,7,9},
                    pentaMin =   {0,3,5,7,10},
                    pentaMajB =  {0,2,3,4,7,9},
                    pentaMinB =  {0,3,5,6,7,10},
                    dimWholeHalf={0,2,3,5,6,8,9,11},
                    dimHalfWhole={0,1,3,4,6,7,9,10},
                    hungarMinor= {0,2,3,6,7,8,11},
                    phrygDom =   {0,1,4,5,7,8,10},
                    lydDom =     {0,2,4,6,7,9,10},
                    yo =         {0,2,5,7,9},
                    insen =      {0,1,5,7,10},
                    bebopDom =   {0,2,4,5,7,9,10,11},
                    bebopMaj =   {0,2,4,5,7,8,9,11};
    };
    
    
    class Chords{
    public:
        Chords(){}
        
        Array<int>  majChord =       {0,4,7},
                    minChord =       {0,3,7},
                    augChord =       {0,4,8},
                    dimChord =       {0,3,6},
                    seventhChord =   {0,4,7,10},
                    min7Chord =      {0,3,7,10},
                    min7b5Chord =    {0,3,6,10},
                    dim7Chord =      {0,3,6,9},
                    maj7Chord =      {0,4,7,11},
                    minMaj7Chord =   {0,3,7,11},
                    ninthChord =     {0,2,4,7,10},
                    min9Chord =      {0,2,3,7,10},
                    min7b9Chord =    {0,1,3,7,10},
                    maj9Chord =      {0,2,4,7,11},
                    add9Chord =      {0,2,4,7},
                    minAdd9Chord =   {0,2,3,7},
                    sevenSharp9Chord={0,3,4,7,10},
                    sus2Chord =      {0,2,7},
                    sus4Chord =      {0,5,7},
                    powerChord =     {0,7},
                    sixthChord =     {0,4,7,9},
                    minSixthChord =  {0,3,7,8},
                    sixNineChord =   {0,2,4,7,9},
                    thirteenthChord= {0,4,7,9,10},
                    min13thChord =   {0,3,7,8,10},
                    maj13thChord =   {0,4,7,9,11},
                    eleventhChord =  {0,4,5,7,10},
                    sharp11Chord =   {0,4,6,7,10},
                    minSharp11Chord= {0,3,6,7,10},
                    min7Flat5Flat9Chord={0,1,3,10},
                    aug7thChord =    {0,4,8,10},
                    petrushka =      {0,1,4,6,7,10},
                    farben =         {0,4,8,9,11};
    };
    
    
    
    const String setClassToPitchName[12] = {"C","C#/Db","D","D#/Eb","E","F","F#/Gb","G","G#/Ab","A","A#/Bb", "B"};
    
    Scales scales;
    Chords chords;
    
    std::map<String, Array<int>> modeMap;
    std::map<int, Array<int>> circleOfFifths;
    std::map<int, Array<String>> diatonicNoteNames;
    
    //static std::map<String, Array<int>> modeMap2 = {{"Major", scales.major}, {"Natural Minor", scales.natMinor}};
    
    
    HashMap<String, Array<int>> hashScales; //TODO, change everything to scales and Juce HashMaps
    
    
    
    
    Theory(){
        scales = Scales();
        chords = Chords();
        
        //hashScales.set("Major", scales.major); //TODO
        
        
        //Scales
        modeMap.insert({"Major", scales.major});
        modeMap.insert({"Natural Minor", scales.natMinor});
        modeMap.insert({"Harmonic Minor", scales.harmMinor});
        modeMap.insert({"Melodic Minor", scales.melMinor});
        modeMap.insert({"Locrian", scales.locrian});
        modeMap.insert({"Dorian", scales.dorian});
        modeMap.insert({"Phrygian", scales.phrygian});
        modeMap.insert({"Lydian", scales.lydian});
        modeMap.insert({"Mixolydian", scales.mixolydian});
        modeMap.insert({"WholeTone", scales.wholeTone});
        modeMap.insert({"Pentatonic Major", scales.pentaMaj});
        modeMap.insert({"Pentatonic Minor", scales.pentaMin});
        modeMap.insert({"Pentatonic Maj Blues", scales.pentaMajB});
        modeMap.insert({"Pentatonic Min Blues", scales.pentaMinB});
        modeMap.insert({"Diminished Whole-Half", scales.dimWholeHalf});
        modeMap.insert({"Diminished Half-Whole", scales.dimHalfWhole});
        modeMap.insert({"Hangarian Minor", scales.hungarMinor});
        modeMap.insert({"Phrygian Dominant", scales.phrygDom});
        modeMap.insert({"Lydian Dominant",scales.lydDom});
        modeMap.insert({"Yo (Japanese)", scales.yo});
        modeMap.insert({"Insen (Japanese)", scales.insen});
        modeMap.insert({"Bebop Dominant", scales.bebopDom});
        modeMap.insert({"Bebop Major", scales.bebopMaj});
        //Chords
        modeMap.insert({"Maj (Chord)", chords.majChord});
        modeMap.insert({"min (Chord)", chords.minChord});
        modeMap.insert({"Aug (Chord)", chords.augChord});
        modeMap.insert({"dim (Chord)", chords.dimChord});
        modeMap.insert({"7th (Chord)", chords.seventhChord});
        modeMap.insert({"min7 (Chord)", chords.min7Chord});
        modeMap.insert({"m7b5 (Chord)", chords.min7b5Chord});
        modeMap.insert({"dim7 (Chord)", chords.dim7Chord});
        modeMap.insert({"Maj7 (Chord)", chords.maj7Chord});
        modeMap.insert({"minMaj7 (Chord)", chords.minMaj7Chord});
        modeMap.insert({"9th (Chord)", chords.ninthChord});
        modeMap.insert({"m9 (Chord)", chords.min9Chord});
        modeMap.insert({"m7b9 (Chord)", chords.min7b9Chord});
        modeMap.insert({"Maj9 (Chord)", chords.maj9Chord});
        modeMap.insert({"add9 (Chord)", chords.add9Chord});
        modeMap.insert({"minAdd9 (Chord)", chords.minAdd9Chord});
        modeMap.insert({"7#9 (Chord)", chords.sevenSharp9Chord});
        modeMap.insert({"sus2 (Chord)", chords.sus2Chord});
        modeMap.insert({"sus4 (Chord)", chords.sus4Chord});
        modeMap.insert({"Power Chord", chords.powerChord});
        modeMap.insert({"6th (Chord)", chords.sixthChord});
        modeMap.insert({"m6 (Chord)", chords.minSixthChord});
        modeMap.insert({"6/9 (Chord)", chords.sixNineChord});
        modeMap.insert({"13th (Chord)", chords.thirteenthChord});
        modeMap.insert({"m13 (Chord)", chords.min13thChord});
        modeMap.insert({"Maj13 (Chord)", chords.maj13thChord});
        modeMap.insert({"11th (Chord)", chords.eleventhChord});
        modeMap.insert({"#11 (Chord)", chords.sharp11Chord});
        modeMap.insert({"m#11 (Chord)", chords.minSharp11Chord});
        modeMap.insert({"m7b5b9 (Chord)", chords.min7Flat5Flat9Chord});
        modeMap.insert({"aug7 (Chord)", chords.aug7thChord});
        modeMap.insert({"Petrushka (Chord)", chords.petrushka});
        modeMap.insert({"Farben (Chord)", chords.farben});
        
        
        
        diatonicNoteNames.insert({0,{"C♭♭","C♭","C", "C♯","Cx"}});
        diatonicNoteNames.insert({1,{"D♭♭","D♭","D","D♯","Dx"}});
        diatonicNoteNames.insert({2,{"E♭♭","E♭","E", "E♯","Ex"}});
        diatonicNoteNames.insert({3,{"F♭♭","F♭","F", "F♯","Fx"}});
        diatonicNoteNames.insert({4,{"G♭♭","G♭","G", "G♯","Gx"}});
        diatonicNoteNames.insert({5,{"A♭♭","A♭","A", "A♯","Ax"}});
        diatonicNoteNames.insert({6,{"B♭♭","B♭","B", "B♯","Bx"}});
        
        circleOfFifths.insert({0,{0,0,0,0,0,0,0}}); //C
        circleOfFifths.insert({1,{1,1,1,1,1,1,1}}); //C#
        circleOfFifths.insert({2,{1,0,0,1,0,0,0}}); //D
        circleOfFifths.insert({3,{2,1,1,2,1,1,1}}); //D#
        circleOfFifths.insert({4,{1,1,0,1,1,0,0}}); //E
        circleOfFifths.insert({5,{0,0,0,0,0,0,-1}}); //F
        circleOfFifths.insert({6,{1,1,1,1,1,1,0}}); //F#
        circleOfFifths.insert({7,{0,0,0,1,0,0,0}}); //G
        circleOfFifths.insert({8,{1,1,1,2,1,1,1}}); //G#
        circleOfFifths.insert({9,{1,0,0,1,1,0,0}}); //A
        circleOfFifths.insert({10,{2,1,1,2,2,1,1}}); //A#
        circleOfFifths.insert({11,{1,1,0,1,1,1,0}}); //B
        circleOfFifths.insert({11,{0,-1,-1,0,0,-1,-1}}); //Db
        circleOfFifths.insert({11,{0,0,-1,0,0,-1,-1}}); //Eb
        circleOfFifths.insert({11,{-1,-1,-1,0,-1,-1,-1}}); //Gb
        circleOfFifths.insert({11,{0,-1,-1,0,0,-1,-1}}); //Ab
        circleOfFifths.insert({11,{0,0,-1,0,0,0,-1}}); //Bb
    }
    
    
    

    
private:
    
    
    
};

