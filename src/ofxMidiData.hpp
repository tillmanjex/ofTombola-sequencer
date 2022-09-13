//
//  ofxMidiData.hpp
//  CC2-tombola
//
//  Created by Tillman on 13.09.22.
//

#ifndef ofxMidiData_hpp
#define ofxMidiData_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxMidi.h"

#endif /* ofxMidiData_hpp */

class MidiData {
    
public:
    
     MidiData();
     ~MidiData();
    
    void update(std::string port, int channel, int scaleSelect);
    void playNote();
    
    ofxMidiOut midiOut;
    int channel;
    unsigned int currentPgm;
    int note, velocity;
    int pan, bend, touch, polytouch;
    int value;
    int dMajSel, dMinSel;
    bool bHit;
    
    std::vector <int> dMaj;
    std::vector <int> dMin;
};
