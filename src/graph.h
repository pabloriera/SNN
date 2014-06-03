#pragma once

#include "ofMain.h"
#include "ofxGui.h"

using namespace std;


class node_t
{
    public:

        size_t id;
        //vector <node_t*> to;

        //basic atributes
        ofVec2f pos;
        double rad;
        size_t type;
        string label;

        //vector <string> att_str;
        //vector <float> att_float;
};

class link_t
{
    public:

        size_t id;

        node_t *from,*to;

        //atributes
        //float weight;
        ofParameter<float> weight;
        //ofParameterGroup parameters;
};


class graph_t
{

    public:

        graph_t();

        void add_node(int x, int y, size_t type, string label);
        void add_link(size_t source_id,size_t target_id );

        void remove_node(size_t id);
        int remove_link(size_t source_id,size_t target_id );


        node_t* nodeId(size_t id);
        link_t* linkId(size_t id);

        void clear_all();

        int degree(size_t id);

        void save(string fname);
        void load(string fname);
        void print_graph();

        vector <node_t*> nodes;
        vector <link_t*> links;
        //vector <string> att_names;

        size_t node_id;
        size_t link_id;
};
