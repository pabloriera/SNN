#pragma once

#include "ofMain.h"
#include "dragLine.h"

using namespace std;

class lines_container
{

public:

    lines_container();
    void setup(size_t N);

    void draw(ofEventArgs & args);

    void add_line(ofVec2f pos0, ofVec2f pos1);
    void remove_line(size_t id);
    void mousePressed(int x,int y, int button);
    void mouseDragged(int x,int y);
    void mouseRelease();

    size_t id;

    vector <dragLine_t* > dL;
};


