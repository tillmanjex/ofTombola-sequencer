//
//  tombola.hpp
//  CC2-tombola-xcode
//
//  Created by Tillman on 12.08.22.
//

#ifndef tombola_hpp
#define tombola_hpp

#include <stdio.h>
#include "ofMain.h"

#endif /* tombola_hpp */

class Tombola {
    
public:
    Tombola();
    ~Tombola();
    
    void update();
    void draw();
    
    ofPolyline tombolaLine;
  
private:
    ofColor color{};
    int length{};
    int width{};
    float rotation{};
    float spinSpeed{};
    float radius{};
    ofPoint pt;

    
};
