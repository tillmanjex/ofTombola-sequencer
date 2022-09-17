//
//  ofxMidiData.cpp
//  CC2-tombola
//
//  Created by Tillman on 13.09.22.
//

#include "ofxMidiData.hpp"


MidiData::MidiData(){

    // scales - todo: user selection of scales
    dMaj = { 50, 52, 54, 55, 57, 58, 61, 62, 64, 66, 67, 69, 70, 73 };
    dMin = { 50, 52, 53, 56, 57, 59, 61, 62, 64, 65, 68, 69, 71, 73 };
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

}

MidiData::~MidiData(){
    
}

void MidiData::update(std::string port, int midiChannel, int scale){
    // update port to globally selected port
    midiOut.openPort(port);
    channel = midiChannel;
    
    // user scale selection
    if (scale == 0) {
        note = dMajSel;
    } else if (scale == 1){
        note = dMinSel;
    }
};

void MidiData::noteOn(){
    
    velocity = int(ofRandom(30, 100));
    midiOut.sendNoteOn(channel, note, velocity);
};

void MidiData::noteOff(){
    midiOut.sendNoteOff(channel, note);
}


                            
