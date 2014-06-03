#pragma once

#include "ofMain.h"

class dragLine_t
{

public:

    dragLine_t();

    void setup(size_t _id);
    void add_style(ofColor color, float linewidth);
    void draw();

    void mouseMoved(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    bool mousePressed(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);

    float distance2segment(ofVec2f p, ofVec2f a, ofVec2f b);
    bool interiorAngs(ofVec2f p, ofVec2f a, ofVec2f b);
    bool near(int x, int y);
    bool drag;
    bool selected;

    vector <float> linewidth;
    vector <ofColor> color;

    size_t idx;
    size_t id;
    int dist;

    float dist2click;

    ofVec2f pos0, pos1;

};


