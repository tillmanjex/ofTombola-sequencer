---
date-created: 2022-07-12 11:23
modified: 2022-07-12 11:23
tags: [filmuni]
summary: Diary kept during development of second term CC2 project.
stimulus: Make it smooth, make it simple. 
---
# CC2 - Tombola Sequencer Dev Diary

#### 2022-07-12
---
Angela's recommendations for tools and references for project:
- https://github.com/aaronaanderson/ofxATK
- https://github.com/npisanti/ofxPDSP
- https://github.com/braitsch/ofxDatGui
- https://github.com/moostrik/ofxFlowTools
- https://basmyr.wordpress.com/2015/12/08/fluids-and-particles-in-openframeworks/
- https://github.com/fusefactory/ofxFastParticleSystem
- https://github.com/pierdr/ofxFractalGeometry
- http://umi.codes/geek/2015/3/funky-particles-in-openframeworks

Can't run ofxFastParticleSystem examples, but the screenshots / references look amazing. 
Check out the [[& Dökk - Interactive Multimedia Performance]]



#### 2022-08-12
---
Creating classes 
- tombola
- ball

#### 2022-08-15
---
Programatically creating Tombola hexagon. 

```c++
// sudo-ish code to create a hexagon (60 degrees between each division)
angle = 0;
x = circleOriginX + radius * cos(angle);
y = circleOriginY + radius * sin(angle);

angle += 60;

hexagonVertex1 = (x, y)
...
```

```c++
v0.set(centerX + radius * cos(glm::radians(0.0)), centerY + radius * sin(glm::radians(0.0)), 0);
v1.set(centerX + radius * cos(glm::radians(60.0)), centerY + radius * sin(glm::radians(60.0)), 0);
v2.set(centerX + radius * cos(glm::radians(60.0)), centerY + radius * sin(glm::radians(60.0)), 0);
v3...
v4...

//...//
tombolaLine.lineTo(v0);
tombolaLine.lineTo(v1);
...etc
tombolaLine.draw();

```
![tombola first drawn](./media/hexagon-drawn.png)

At the moment changing the radius changes the size of the whole hexagon and remains as an entire intact shape (naturally). But what I want is that increasing the size of the hexagon, increases the distance of the lines from the center, but the *distance between vertex pairs* (ie v0,v1 - v2,v3 - etc) remain the same. This means that gaps will appear, that will allow the balls to fall through.

Is it as simple as adding the radius to x and y independently? ie:  
`v0 += radius` ?
yup, it was (pretty much) that simple. The code implementation works, but I need a bipolar control so that the radius can increase/decrease in size. 
With this implementation, the hexagon will only ever increase due to `+=` 

[Rotating the Tombola lines](https://openframeworks.cc/documentation/math/ofVec3f/#show_getRotated)

#### 2022-08-26
---
Trying to use [this approach](https://stackoverflow.com/questions/17692922/check-is-a-point-x-y-is-between-two-points-drawn-on-a-straight-line?noredirect=1&lq=1) to detect collisions, but the `ofVec3f.distance`  method is returning me different distances between the Tombola vertices on every run...


#### 2022-09-05
---
[ofxGui tutorial](https://www.youtube.com/watch?v=OzTtd79vfQw&list=PL4neAtv21WOlqpDzGqbGM_WN2hc5ZaVv7&index=18) - Lewis Lepton

Calculating collisions with ofPolyLines proved to be much too problematic. In the process of troubleshooting I came across the addon [ofxBox2d](https://github.com/vanderlin/ofxBox2d), which is a physics simulation library for openFrameworks. 
It has in built line / volume collision detection. Will move forward with this and hope it suits.


#### 2022-09-26
---
Getting ofxBox2d to work within classes is confusing as each element needs to have an ofxBox2d.getWorld() call, which (as I highly expect) needs to be the same world for all - to keep things related. But it seems like a problematic road to go down, to "pipe in" the ofxBox2d world from ofApp to each class... I forsee problems. 
So I'm going to move ahead with just doing most of the work in ofApp.h and .cpp. Just to get it done...

#### 2022-09-08
---
Got the tombola drawn with ofxBox2dEdge, which means that ball and edge collision is working by default as well as physics simulation. But I'm getting really bad performance. CPU is maxing out after a few seconds. 
It's because of the vertex positions being calculated and then updated in their vector array every frame. But I need this to happen so that the user can modulate the radius of the tombola and rotation, which needs to be calculated every frame...

I realised that as I'm using a library, that transformations are built in. So it's a lot smarter to hard code the values of the initial state of the tombola, and then access transformations / modifications via the libraries methods. 

![Time for a (progress) Picture](./media/t-prog-1.png)   

Having trouble controlling the edges. The edges use polylines as the input coordinates; the edges are also the object being called in `draw`. However, when modulating the position of the edges, while the coordinates of the edges do move, the graphical representation does not. This is confirmed by the balls resting on the actual position of the edges, which does not correlate to the graphical representation as seen below after the position of all edges are offset by (50, 50): 

![tombola control problem](./media/t-mod-prob-1.png)

#### 2022-09-10
---
The problem in the last paragraph above was to do with confusion (and forgetfulness) regarding coordinate space, computer graphics and the library itself. 
The tombola was hard coded to draw in the middle of the canvas, with the verticies being calculated as such: `v0.set(canvasCenter.x + radius * cos(glm::radians(0.0)), canvasCenter.y + radius * sin(glm::radians(0.0)), 0);`  
This meant that when scaling or rotating, the shape was not staying in the middle. I had to recalculate without the `canvasCenter` offset, and then use `ofTranslate` to put it in the middle, which then allows regular transformations to work (along with pushing and popping).  

However, there was an extra layer to the problem whereby the ofxBox2d world did not listen to the translation, meaning that the Tombola was being *graphically* drawn in the center, but as far as ofxBox2d was concerned, the Tombola was still centered around the top left at (0, 0).

Again I suffered for a while due to the non-existence of any API reference for the library, and not much forum activity on the topic. But then moved through the method suggestions from within VS code's auto completion, and eventually found the method `.setPosition()`, which I could apply in the for loop within `draw()` for the Tombola, meaning that all vertex positions for the Tombola (as seen by ofxBox2d world) get offset by `canvasCenter.x and canvasCenter.y`

```c++
    for (auto &edge : tEdges){
        ofSetColor(255, 0, 80);
        ofTranslate(canvasCenter.x, canvasCenter.y); // graphical representation
        edge->setPosition(canvasCenter); // value offset for correct performance
        edge->draw(); 
    };

```

#### 2022-09-12
---
Added ofxDatGui (ball spawn and tombola size slider).
Had trouble initially with the size slider, as it was working with the `.scale` method. The problem with this was that the scale value would scale relative to the original tombola size. This meant that if the slider was below 1.0 (eg 0.8), and the user *increased* the value, the tombola would still decrease in size, as mathematically it would represent: 0.81 * [the current size], which is a further reduction. 

To get around this, I had to clear all vertices and vectors and calculate the ofVec3s on each slider change, using the slider value as the radius. I'm versy sure there is a cleaner way of doing this, but I can't put time into optimization right now...
Also added tombola rotation.

```c++
           void ofApp::onSliderEvent(ofxDatGuiSliderEvent e){
    
    // clear polylines for fresh input
    tLine0.clear();
    tLine1.clear();
    tLine2.clear();
    tLine3.clear();
    tLine4.clear();
    tLine5.clear();
    
    for (auto &edge : tEdges){
        // clear &edge on each iteration for correct drawing behavior
        edge->clear();
        
        if (e.target->is("Tombola Size")){

            v0.set(e.value * cos(glm::radians(0.0)), e.value * sin(glm::radians(0.0)), 0);
            v1.set(e.value * cos(glm::radians(60.0)), e.value * sin(glm::radians(60.0)), 0);
            v2.set(e.value * cos(glm::radians(120.0)), e.value * sin(glm::radians(120.0)), 0);
            v3.set(e.value * cos(glm::radians(180.0)), e.value * sin(glm::radians(180.0)), 0);
            v4.set(e.value * cos(glm::radians(240.0)), e.value * sin(glm::radians(240.0)), 0);
            v5.set(e.value * cos(glm::radians(300.0)), e.value * sin(glm::radians(300.0)), 0);
            
        } else if (e.target->is("Tombola Rotate")) {
            
            v0.rotate(e.value, ofVec3f(0, 0, 1));
            v1.rotate(e.value, ofVec3f(0, 0, 1));
            v2.rotate(e.value, ofVec3f(0, 0, 1));
            v3.rotate(e.value, ofVec3f(0, 0, 1));
            v4.rotate(e.value, ofVec3f(0, 0, 1));
            v5.rotate(e.value, ofVec3f(0, 0, 1));
        }
            // add the updated verticies to the polyline objects
            tLine0.addVertex(v0);
            tLine0.addVertex(v1);
        
            tLine1.addVertex(v1);
            tLine1.addVertex(v2);
        
            tLine2.addVertex(v2);
            tLine2.addVertex(v3);
        
            tLine3.addVertex(v3);
            tLine3.addVertex(v4);
        
            tLine4.addVertex(v4);
            tLine4.addVertex(v5);
        
            tLine5.addVertex(v5);
            tLine5.addVertex(v0);
               
            // add the updated polylines to edges
            edge->addVertexes(tLine0);
            edge->addVertexes(tLine1);
            edge->addVertexes(tLine2);
            edge->addVertexes(tLine3);
            edge->addVertexes(tLine4);
            edge->addVertexes(tLine5);
            edge->create(box2d.getWorld());
            
    };
    
    
}
```

Will move on to implementing ofxMidi - so as to get through the problems on that front.   
When that's working I'll come back to iron out the small changes that need to be made with the tombola:
- instead of manual control of tombola rotation, have a speed control.
- make the lines thicker (if possible)
	- at the moment there is a problem where if the tombola is made smaller, the balls fall through the edges.

#### 2022-09-13
---
Implemented collisions listener with ofxBox2d as I needed to check I have a useable event working for midi implementation. 
ofxMidi is seemlingly fine, except I've come across a pretty impossible error with an event listener callback for `ofxDatGuiDropdownEvent`.  
Posted in the ofxDatGui github [here](https://github.com/braitsch/ofxDatGui/issues/160) and am hoping I'll get an answer. As far as I could understand, it's a linker error - but all the necessary .cpp files are being linked in the build phase -> compilation source section of xcode... So I really don't know. I tried the lower version of openFrameworks as well as a newer version of xcode, but neither worked.   
In the interest of time, I'm going to move on and try and think of a different sollution.   
The dropdown box was going to be used for midi port output selection, which is a pretty nice feature to have! damn. 

#### 2022-09-15
---
With regards to last entries problem, the app simply creates as many buttons as there are midi ports. These buttons open the specified port on click. Will do for now...

A checklist of what is working:
- Ball spawn on button click
- Collision detection
  - Midi note (randomly selected from a scale of dMinor as default) output on collision (along with midi channel and velocity)
- Tombola size control
- Tombola spin control
- Midi output port selection via UI
- GUI preservation with window resize

Problems
-[x] Balls fall through edges if at rest when tombola begins to spin
  -[x] Only solution found so far - convert edges to ofxBox2dRects

Still To Implement As Per Original Plan
-[x] Physics controls (ball bounce, ball density)
-[x] Tombola line rotation on central z-axis of the line
-[x] Tombola spin control as "speed of rotation" - rather than a manual rotation degree setting.

Porting the tombola to rects looks like it will also help solve the problem of rotating the tombola lines on the central z-axis to achieve the same as this:   
![op1-tombola open](./media/op1-tomb-open.png)   
I had no good idea how I was going to achieve this with a group of polylines. Would've required a lot more math and recalculation of all the vertex points I would say. The ofxBox2dRect class has a built in rotation function, that rotates around the central pivot point!

As the rects are centered around this pivot point, I needed to derive new vector positions between each current set of vector points (as the poly lines are drawn from end to end). I used vector subtraction to derive the middle point.

```c++
    // vertex positions for tomobola made of ofxBox2dEdges
    v0.set(200, 0, 0);
    v1.set(100, 173, 0);
    v2.set(-100, 173, 0);
    v3.set(-200, 0, 0);
    v4.set(-100, -173, 0);
    v5.set(100, -173, 0);
    
    // derive the central point between each pair of vectors above (for tombola made of rectangles drawn from center)
    // [v0 and v1], [v1 and v2] etc
    v0r.set(canvasCenter.x + v0.x - (v1.x / 2), canvasCenter.y + v0.y - (v1.y / 2));
    v1r.set(canvasCenter.x + v1.x - (v2.x / 2), canvasCenter.y + v1.y - (v2.y / 2));
    v2r.set(canvasCenter.x + v2.x - (v3.x / 2), canvasCenter.y + v2.y - (v3.y / 2));
    v3r.set(canvasCenter.x + v3.x - (v4.x / 2), canvasCenter.y + v3.y - (v4.y / 2));
    v4r.set(canvasCenter.x + v4.x - (v5.x / 2), canvasCenter.y + v4.y - (v5.y / 2));
    v5r.set(canvasCenter.x + v5.x - (v0.x / 2), canvasCenter.y + v5.y - (v0.y / 2));
    
```

Spent time trying to figure out why after changing scale values or window size, the two right tombola lines would rotate incorectly. Both of these actions called a function which recalculated the vertex positions for the tombola lines. In the end, it was because I missordered the filling of the tEdges vector in the program setup step: 

```c++
    tRects.push_back(rect1);    
    tRects.push_back(rect0);
    tRects.push_back(rect2);
    tRects.push_back(rect3);
    tRects.push_back(rect4);
    tRects.push_back(rect5);
```

This meant that when the verticies got recalcualated, that rect1 and rect0 effectively switched positions in the vector, meaning that visually they flipped around! Stumped me for a while. 

![before window resize](./media/tombola-bug-pre.png)   
![after window resize](./media/tombola-bug-post.png)   

Got tombola spin finally to work. Again I was tricked by thinking that it should work, but because I wasn't graphically seeing it - I thought it wasn't working.   
However, it was also because of some still yet to be understood reason that my `tombolaScale` function needs to be called *before* `tombolaSpin`, otherwise it doesn't work at all! No idea.

Spin is working as mentioned, but another vector math problem has reared it's grotesque head whereby the lines of course maintain their set degrees of rotation - meaning that they do not stay facing the central axis of the tobola when spinning around it. From memory the cross product comes in handy, but a quick research didn't convince me. 
Have found a [tutorial in processing](https://behreajj.medium.com/3d-rotations-in-processing-vectors-matrices-quaternions-10e2fed5f0a3) that achieves what I want but it's using world space and local space as vector variables. Need to understand if that makes sense for my situation or not and figure out how to apply it. 

After much time and confusion trialling out Quaternions, cross products, dot products and vector operation hacks of all sorts - all it came down to was: % (good old modulo).   
```c++
    // current rotation + spin speed % 360 
    tRects.at(0)->setRotation(60 + tSpinSpeed % modulo360);
```   
![forever modulo](./media/forever-modulo.png)

(was still worth it)

