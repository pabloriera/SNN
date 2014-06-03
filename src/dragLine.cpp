#include "dragLine.h"

dragLine_t::dragLine_t()
{
    dist = 30;

    pos0.set( ofGetWindowWidth()/2.0 + ofRandom(-100,100), ofGetWindowHeight()/2.0 + ofRandom(-100,100) );
    pos1.set( ofGetWindowWidth()/2.0 + ofRandom(-100,100), ofGetWindowHeight()/2.0 + ofRandom(-100,100) );

    idx = 0;
    drag = false;
    selected = false;

}

void dragLine_t::setup(size_t _id){
    id = _id;
}

void dragLine_t::add_style(ofColor _color, float _linewidth)
{
    color.push_back(_color);
    linewidth.push_back(_linewidth);
}

void dragLine_t::draw()
{
    if(selected==true)
        idx = 2;
    else
        idx = 0;

    ofPushStyle();
        ofSetLineWidth(linewidth[idx]);
        ofSetColor( color[idx] );
        ofLine(pos0.x, pos0.y,  pos1.x , pos1.y );

       // ofLine(p.x,p.y,(p+aux).x,(p+aux).y);
       //ofLine(a.x,a.y,(a+n.rotate(90)*10).x,(a+n.rotate(90)*10).y);

        ofVec2f head = (pos0-pos1).rotate(10+linewidth[idx]*0.8);
        head.normalize();
        head *=20;
        head += pos1;

        ofSetLineWidth(100);
        ofLine(pos1.x, pos1.y, head.x, head.y  );

    ofPopStyle();
}


bool dragLine_t::near(int x, int y)
{

    ofVec2f p(x,y);
    bool sel = false;

  //  int hh = 10;
  //  int vv = 10;


    /*a = pos0;

    b = pos1;

   // bool bh = false;
 //bool bv = false;

    //point x,y is in the rectangle with the link as diagonal?
    //if((a.x < b.x && x > a.x-hh && x < b.x+hh) || (a.x > b.x && x > b.x-hh && x < a.x+hh ))
            bh = true;

    if((a.y < b.y && y > a.y-vv && y < b.y+vv) || (a.y > b.y && y > b.y-vv && y < a.y+vv ))
            bv = true;

    if(bh && bv)*/
   // {*/

        //point distance to line segment

    dist2click = distance2segment(p,pos0,pos1);

    if (interiorAngs(p,pos0,pos1))
        if(dist2click<0)
            if (abs(dist2click) < dist)
                sel = true;
   // }

    return sel;

}

bool dragLine_t::mousePressed(ofMouseEventArgs & args)
{
    bool sel = false;
    if (near(args.x,args.y))
    {
        if (args.button == 0 )
            drag = true;

        sel = true;
    }

    return sel;
}

void dragLine_t::mouseDragged(ofMouseEventArgs & args)
{
    dist2click = distance2segment(ofVec2f(args.x,args.y),pos0,pos1);
}


void dragLine_t::mouseReleased(ofMouseEventArgs & args){
     if (args.button == 0 )
        drag = false;
}

/*
void dragLine_t::mouseDragged(int x,int y)
{
    if (drag)
    {
        pos0.x = x;
        pos0.y = y;
    }
}


*/

float dragLine_t::distance2segment(ofVec2f p, ofVec2f a, ofVec2f b)
{
    ofVec2f n = (b - a);
    n.normalize();
    ofVec2f aux = (a-p)-n.dot((a-p))*n;

    return n.rotate(-90).dot(aux);
}

bool dragLine_t::interiorAngs(ofVec2f p, ofVec2f a, ofVec2f b)
{
    ofVec2f n = (b - a);
    float ang0 = (-n).angle(a-p);
    float ang1 = n.angle(b-p);

    bool inter = false;
    //cout << "ang0 " << ang0 << endl;
    //cout << "ang1 " << ang1 << endl;

    if(abs(ang0)<90 && abs(ang1)<90)
        inter = true;


    return inter;
}
