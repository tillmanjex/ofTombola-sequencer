# Tombola Sequencer


![image](https://user-images.githubusercontent.com/83029642/190852810-5fb24fb0-eabb-4ead-9136-472b6b2a274a.png)

Here's a quick and dirty preview video: https://youtu.be/14QYflLPp5k

The Tombola Sequencer is a MIDI note generator that "sequences" notes based on the simulated physical behavior of bouncing balls and is very much a copy of the Teenage Engineering OP-1 Tombola Sequencer.  
Each ball represents a MIDI note and upon colliding with any object, the ball sends that MIDI note.

There is no hard limit to the amount of balls the user can generate except for the internal area of the Tombola, if it is left enclosed.  
The Tombola is a hollow hexagon which provides playground for the balls to bounce within. The user has control over the size, spin and rotation (individual line segments) of the Tombola, which allows for a multitude of obstacle arrangements for the balls to deal with. Additionally the amount of bounce and also the mass of the balls are user controllable.

## Usage

> Note: The midi destination device needs to be connected, switched on and accessible *before* the Tombola Sequencer app is opened.

1. Activate your MIDI device
2. Start the Tombola Sequencer App
3. Click the desired MIDI output port in the GUI menu
   1. If you do not see your MIDI port - be sure that it was accessible *before* opening the Tombola Sequencer app and its settings are allowing for MIDI input
   2. Be sure to select a specific MIDI channel if you need to (but most instruments / plugins are set to receive on all MIDI channels)
4. Click "Spawn Ball" to generate balls
5. Click "Clear Balls" to remove all balls from the program

## Road Map

I've been wanting to make this app since at least 2015, so I'm very stoked and hope to be able to keep the bock up to continue developing it.   
I implemented everything I wanted to from the plan, but it's still missing a few things to make it really usable:   

-[] Midi panic button (to kill hanging MIDI notes)
-[] Update midi output ports button (for when a midi destination is added after app start)
-[] Octave range parameter (at the moment it's hard set to 2 octave range) 
-[] Midi keyboard to trigger ball, setting the note value of ball to the key pressed.

## Libraries Used to Make this App
- [ofxBox2d](https://github.com/vanderlin/ofxBox2d)
- [ofxDatGui](https://github.com/braitsch/ofxDatGui)
- [ofxMidi](https://github.com/danomatika/ofxMidi)

