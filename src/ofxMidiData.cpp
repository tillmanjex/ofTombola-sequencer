//
//  ofxMidiData.cpp
//  CC2-tombola
//
//  Created by Tillman on 13.09.22.
//

#include "ofxMidiData.hpp"

MidiData::MidiData(){

    // scales
    dMaj = { 50, 52, 54, 55, 57, 58, 61};
    dMin = { 50, 52, 53, 56, 57, 59, 61};
    // choose a random note for class instance
    dMajSel = dMaj.at(int(ofRandom(0, dMaj.size())));
    dMinSel = dMin.at(int(ofRandom(0, dMaj.size())));
    
    // defaults
    channel = 1;
    currentPgm = 0;
    note = 0;
    velocity = 0;
    pan = 0;
    bend = 0;
    touch = 0;
    polytouch = 0;
    
    bHit = false;
}

MidiData::~MidiData(){
    
}

void MidiData::update(std::string port, int channel, int scaleSelect){
    // update port to globally selected port
    midiOut.openPort(port);
    channel = channel;
    
    // user scale selection
    if (scaleSelect == 0) {
        note = dMajSel;
    } else if (scaleSelect == 1){
        note = dMinSel;
    }
};

void MidiData::playNote(){
    
    velocity = int(ofRandom(30, 100));
    midiOut.sendNoteOn(channel, note, velocity);

};


                            
