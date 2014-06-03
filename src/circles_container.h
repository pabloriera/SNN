#pragma once

#include "ofMain.h"
#include "dragCircle.h"

using namespace std;

class circles_container
{

public:

    circles_container();
    void setup(size_t N);

    void draw(ofEventArgs & args);

    void add_circle(int x, int y);
    void remove_circle(size_t id);

    void mousePressed(int x,int y, int button);
    void mouseDragged(int x,int y);
    void mouseRelease();

    size_t id;

    vector <dragCircle_t*> dC;
};


