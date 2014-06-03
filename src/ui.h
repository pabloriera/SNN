#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "graph.h"
#include "dragCircle.h"
#include "neurons_network.h"
#include "circles_container.h"
#include "lines_container.h"
#include "conste_constants.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class ui_t
{

public:

    ui_t();

    void clear_all();

    void add_agent(int x, int y);
    void add_connection(ofVec2f pos0, ofVec2f pos1);

    void increase_connection();
    void decrease_connection();

    void set_connection(float conn);

    int  remove_connection();
    void remove_agent();
    void patchbay();

    dragLine_t* link2line(link_t* );
    link_t* line2link(dragLine_t* );

    //callbacks
    void update(ofEventArgs & args);
    void draw(ofEventArgs & args);
    void onClick(ofMouseEventArgs & args);
    void onDrag(ofMouseEventArgs & args);
    void onClickRelease(ofMouseEventArgs & args);
    void onKeyPressed(ofKeyEventArgs & args);

    int mousex_old,mousey_old;

    graph_t G;

        size_t node_type;
        string node_label;


    lines_container L;

        dragLine_t* clicked_line;
        dragLine_t* selected_line;
        dragLine_t* previous_line;

    circles_container C;

        dragCircle_t* clicked_circle;
        dragCircle_t* selected_circle;
        dragCircle_t* previous_circle;


    neurons_network N;



    //void set_osc_server(ofxOscSender* _sender);
        //bool osc_enable;
        //ofxOscSender sender;
  /*  typedef struct
    map<dragLine_t*, > map_link;
    map<dragLine_t*, link_t*> map_link;*/

    ofTrueTypeFont	verdana;

    //ofxButton ringButton;

    ofxPanel gui_neuron;

	ofParameter<float> p_dc;
	void p_dc_callback(float & p_dc);

	ofxPanel gui_conn;

    ofParameterGroup ui_conn_parameters;
    ofParameter<float> p_w;

};

