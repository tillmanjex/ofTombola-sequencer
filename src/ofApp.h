#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxDatGui.h"
#include "ofxMidi.h"
#include "ofxMidiData.hpp"



class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void tombolaInit();
    void tombolaRotate();
    void tombolaSpin();
    void tombolaScale();
    void tombolaCenter();

    int tSpinSpeed, modulo360;

    // ofxMidi
    ofxMidiOut midi;
    
    MidiData midiVoice;
    vector <shared_ptr<MidiData>> midiVoices;
    
    // ofxDatGui
    ofxDatGui* gui;
    ofxDatGuiButton* ballSpawn;
    ofxDatGuiSlider* slider;
    ofxDatGuiLabel* label;
    ofxDatGuiFolder* folder;
    vector <ofxDatGuiButton> midiOutPorts;
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    std::vector <string> outPorts;
    
    // ofxBox2d
    ofxBox2d box2d;
    void contactStart(ofxBox2dContactArgs &e);
    void contactEnd(ofxBox2dContactArgs &e);
    float gravity;
    
    // Tombola
    ofVec3f v0, v1, v2, v3, v4, v5;
    ofVec3f v0r, v1r, v2r, v3r, v4r, v5r, canvasCenter;
    vector <shared_ptr<ofxBox2dEdge>> tEdges;
    vector <shared_ptr<ofxBox2dRect>> tRects;
    int tLength, tWidth;
    float tRotAngle{};
    float tRadius{};
    float tSpin{};
    bool tCollision;
    float redTarget;
    int redInit; // used in draw()
    
    // Ball
    vector <shared_ptr<ofxBox2dCircle>> circles;
    float bBounce, bDensity;
    
};
