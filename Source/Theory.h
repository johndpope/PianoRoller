/*
  ==============================================================================

    Theory.h
    Created: 18 Jan 2019 1:13:06pm
    Author:  Adam Shield

  ==============================================================================
*/


#ifndef MUSIC_THEORY_HEADER
#define MUSIC_THEORY_HEADER
#pragma once
#include <map>
#include <iostream>

namespace Theory{
    
    struct Mode{
        Array<int> mode;
        Array<int> enharmIndex;
        Array<int> intervals;
        Mode(const Array<int> Array1, const Array<int> Array2, const Array<int> Array3){
            mode = Array1;
            enharmIndex = Array2;
            intervals = Array3;
        }
        
        Array<int> getMode(){ return mode; }
        Array<int> getEnharmIndex(){ return enharmIndex; }
        Array<int> getIntervals(){ return intervals; }
    };
    
    
    struct Scale : public Mode{
        Scale(const Array<int> Array1, const Array<int> Array2, const Array<int> Array3) : Mode(Array1, Array2, Array3)
        {
        }
    };
    
    struct Chord : public Mode{
        Chord(const Array<int> Array1, const Array<int> Array2, const Array<int> Array3) : Mode(Array1, Array2, Array3)
        {
        }
    };
    
    /*
     * Scales are built using Arrays of
     *      1. Their pitch classes.
     *      2. Their "enharmonic index" (i.e. which note deviates from the major scale)
     *      3. Their intervals (which degrees of the diatonic scale do they draw from)
     *
     */
    namespace Scales{
        
        inline Array<int>   major =      {0,2,4,5,7,9,11},
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
    
    
    namespace Chords{

        inline Array<int>   majChord =       {0,4,7},
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
    
    
    //static HashMap<String, Array<int>> modeMap; //= {
    inline std::map<String, Array<int>> modeMap = {
        //Scales
        {"Major", Scales::major},
        {"Natural Minor", Scales::natMinor},
        {"Harmonic Minor", Scales::harmMinor},
        {"Melodic Minor", Scales::melMinor},
        {"Locrian", Scales::locrian},
        {"Dorian", Scales::dorian},
        {"Phrygian", Scales::phrygian},
        {"Lydian", Scales::lydian},
        {"Mixolydian", Scales::mixolydian},
        {"WholeTone", Scales::wholeTone},
        {"Pentatonic Major", Scales::pentaMaj},
        {"Pentatonic Minor", Scales::pentaMin},
        {"Pentatonic Maj Blues", Scales::pentaMajB},
        {"Pentatonic Min Blues", Scales::pentaMinB},
        {"Diminished Whole-Half", Scales::dimWholeHalf},
        {"Diminished Half-Whole", Scales::dimHalfWhole},
        {"Hangarian Minor", Scales::hungarMinor},
        {"Phrygian Dominant", Scales::phrygDom},
        {"Lydian Dominant",Scales::lydDom},
        {"Yo (Japanese)", Scales::yo},
        {"Insen (Japanese)", Scales::insen},
        {"Bebop Dominant", Scales::bebopDom},
        {"Bebop Major", Scales::bebopMaj},
        //Chords
        {"Maj (Chord)", Chords::majChord},
        {"min (Chord)", Chords::minChord},
        {"Aug (Chord)", Chords::augChord},
        {"dim (Chord)", Chords::dimChord},
        {"7th (Chord)", Chords::seventhChord},
        {"min7 (Chord)", Chords::min7Chord},
        {"m7b5 (Chord)", Chords::min7b5Chord},
        {"dim7 (Chord)", Chords::dim7Chord},
        {"Maj7 (Chord)", Chords::maj7Chord},
        {"minMaj7 (Chord)", Chords::minMaj7Chord},
        {"9th (Chord)", Chords::ninthChord},
        {"m9 (Chord)", Chords::min9Chord},
        {"m7b9 (Chord)", Chords::min7b9Chord},
        {"Maj9 (Chord)", Chords::maj9Chord},
        {"add9 (Chord)", Chords::add9Chord},
        {"minAdd9 (Chord)", Chords::minAdd9Chord},
        {"7#9 (Chord)", Chords::sevenSharp9Chord},
        {"sus2 (Chord)", Chords::sus2Chord},
        {"sus4 (Chord)", Chords::sus4Chord},
        {"Power Chord", Chords::powerChord},
        {"6th (Chord)", Chords::sixthChord},
        {"m6 (Chord)", Chords::minSixthChord},
        {"6/9 (Chord)", Chords::sixNineChord},
        {"13th (Chord)", Chords::thirteenthChord},
        {"m13 (Chord)", Chords::min13thChord},
        {"Maj13 (Chord)", Chords::maj13thChord},
        {"11th (Chord)", Chords::eleventhChord},
        {"#11 (Chord)", Chords::sharp11Chord},
        {"m#11 (Chord)", Chords::minSharp11Chord},
        {"m7b5b9 (Chord)", Chords::min7Flat5Flat9Chord},
        {"aug7 (Chord)", Chords::aug7thChord},
        {"Petrushka (Chord)", Chords::petrushka},
        {"Farben (Chord)", Chords::farben}
         

    }; //TODO, change everything to scales

    
    const std::map<int, Array<String>> diatonicNoteNames = {
        {0,{"C♭♭","C♭","C", "C♯","Cx"}},
        {1,{"D♭♭","D♭","D","D♯","Dx"}},
        {2,{"E♭♭","E♭","E", "E♯","Ex"}},
        {3,{"F♭♭","F♭","F", "F♯","Fx"}},
        {4,{"G♭♭","G♭","G", "G♯","Gx"}},
        {5,{"A♭♭","A♭","A", "A♯","Ax"}},
        {6,{"B♭♭","B♭","B", "B♯","Bx"}}
    };

        
    const std::map<int, Array<int>> circleOfFifths = {
    
        {0,{0,0,0,0,0,0,0}}, //C
        {1,{1,1,1,1,1,1,1}}, //C#
        {2,{1,0,0,1,0,0,0}}, //D
        {3,{2,1,1,2,1,1,1}}, //D#
        {4,{1,1,0,1,1,0,0}}, //E
        {5,{0,0,0,0,0,0,-1}}, //F
        {6,{1,1,1,1,1,1,0}}, //F#
        {7,{0,0,0,1,0,0,0}}, //G
        {8,{1,1,1,2,1,1,1}}, //G#
        {9,{1,0,0,1,1,0,0}}, //A
        {10,{2,1,1,2,2,1,1}}, //A#
        {11,{1,1,0,1,1,1,0}}, //B
        {11,{0,-1,-1,0,0,-1,-1}}, //Db
        {11,{0,0,-1,0,0,-1,-1}}, //Eb
        {11,{-1,-1,-1,0,-1,-1,-1}}, //Gb
        {11,{0,-1,-1,0,0,-1,-1}}, //Ab
        {11,{0,0,-1,0,0,0,-1}} //Bb
    };
    
    
};


#endif /* MUSIC_THEORY_HEADER */



