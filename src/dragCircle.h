#ifndef __dragCircle_H__
#define __dragCircle_H__

#include "ofMain.h"

class dragCircleMouseArgs
{
    public:
        ofMouseEventArgs mouseArgs;
        size_t id;

};

class dragCircle_t
{

public:

    dragCircle_t();

    void setup(size_t _id);
    void add_style(ofColor color, bool fill, float rad, float linewidth);
    void draw();
    bool near(int x, int y);

    bool drag;
    bool dragged;
    bool selected;

    size_t id;
    size_t idx;

    ofVec2f pos;
    vector <bool> filled;
    vector <float> linewidth;
    vector <float> rad;
    vector <ofColor> color;



    void mouseMoved(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    bool mousePressed(ofMouseEventArgs & args);
    bool mouseReleased(ofMouseEventArgs & args);

};





#endif



