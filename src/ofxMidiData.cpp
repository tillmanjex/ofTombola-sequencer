//
//  ofxMidiData.cpp
//  CC2-tombola
//
//  Created by Tillman on 13.09.22.
//

#include "ofxMidiData.hpp"

MidiData::MidiData(int ch){

    channel = ch;
    currentPgm = 0;
    note = 0;
    velocity = 0;
    pan = 0;
    bend = 0;
    touch = 0;
    polytouch = 0;
}

MidiData::~MidiData(){
    
}

void MidiData::playNote(){
    note = 70;
    velocity = 64;
    midiOut.sendNoteOn(channel, note, velocity);
}
