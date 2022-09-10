#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
    
    float radius{};
    
    
    ofxBox2d box2d;
    ofxDatGui* gui;
    ofxDatGuiSlider* slider;
    void onSliderEvent(ofxDatGuiSliderEvent e);
    
    // Tombola
    ofVec3f v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11;
    ofVec2f canvasCenter;
    vector <shared_ptr<ofxBox2dEdge>> tEdges;
    
    ofPolyline tLine0;
    ofPolyline tLine1;
    ofPolyline tLine2;
    ofPolyline tLine3;
    ofPolyline tLine4;
    ofPolyline tLine5;
    
    // Ball
    vector <shared_ptr<ofxBox2dCircle>> circles;
    
    
};
