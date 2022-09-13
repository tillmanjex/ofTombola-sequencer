//
//  ofxMidiData.cpp
//  CC2-tombola
//
//  Created by Tillman on 13.09.22.
//

#include "ofxMidiData.hpp"

MidiData::MidiData(){

    channel = 1;
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

void MidiData::update(std::string port){
    // update port
    midiOut.openPort(port);
};

void MidiData::playNote(int ch){
    
    note = 70;
    velocity = 64;
    midiOut.sendNoteOn(ch, note, velocity);
    std::cout << "note sent on ch:" << ch << std::endl;
}
