#include "dragCircle.h"

dragCircle_t::dragCircle_t()
{
    pos.set( ofGetWindowWidth()/2.0 + ofRandom(-50,50), ofGetWindowHeight()/2.0 + ofRandom(-50,50) );

    idx = 0;
    drag = false;
    selected = false;

}

void dragCircle_t::add_style(ofColor _color, bool _fill, float _rad, float _linewidth)
{
    color.push_back(_color);
    filled.push_back(_fill);
    rad.push_back(_rad);
    linewidth.push_back(_linewidth);

}

void dragCircle_t::setup(size_t _id){
    id = _id;
}

void dragCircle_t::draw()
{

    if(drag == true)
        idx = 1;
    else if(selected==true)
        idx = 2;
    else
        idx = 0;

    ofPushStyle();
        if (filled[idx])
            ofFill();
        else
            ofNoFill();

        ofSetLineWidth(linewidth[idx]);
        ofSetColor( color[idx] ) ;
        ofCircle(pos.x,pos.y,rad[idx]);
    ofPopStyle();

}

bool dragCircle_t::near(int x, int y)
{
    return (ofDist(x,y, pos.x, pos.y) < rad[idx]*1.8);
}

void dragCircle_t::mouseMoved(ofMouseEventArgs & args){}

void dragCircle_t::mouseDragged(ofMouseEventArgs & args)
{
    if (drag)
    {
        pos.x = args.x;
        pos.y = args.y;
        dragged = true;
    }
}


bool dragCircle_t::mousePressed(ofMouseEventArgs & args)
{
    bool sel = false;
    dragged = false;
    if (near(args.x,args.y))
    {
        if (args.button == 0 )
            drag = true;

        sel = true;
    }

    return sel;

}
bool dragCircle_t::mouseReleased(ofMouseEventArgs & args){

    if (args.button == 0 )
        drag = false;

    return dragged;
}

