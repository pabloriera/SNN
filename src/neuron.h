 #ifndef NEURONA
    #define NEURONA

    #include "ofMain.h"
    #include <vector>
    #include "ofxOsc.h"
    #include "ofxControlFloat.h"

    class neuron_t {
    public:
        neuron_t();

        void currentBuffer(float w, float d, neuron_t* _neurona);
        void reset();

        void setup(size_t id);
        bool update();

        void drawCircle();
        void drawEvent();

        void FRset(float Fc,float Q);
        void FRcalc();

        size_t id;

        //Visualization
        ofColor color;

        ofVec2f visEvent_pos;
        ofVec2f visCircle_pos;

        float visEvent_width;
        float visEvent_height;

        //Izhikevich
        float a,b,c,d;

        float t;
        float dt;
        float V,u;
        float Vnorm;

        //Synaptic variables
        float sp,s0;
        float tau;

        //vector buffers
        vector<float> sp_buff;
        int sp_bufferSize;
        int sp_buff_ptr;

        int syn_type;
        bool fix_syn_type;

        float maxV,minV;
        float dc;
        ofxControlFloat I;
        float Ibuf;

        struct s_fr{

            vector<float> v;
            float W;
            float N;
            float B_0;
            float B1;
            float B2;
            float A1;
            float A2;
            float Fs;
            float Fc;

        } fr;

        float FR;

        //Circle visualization
        float vis_circle_radio;
        float vis_circle_radio0;

        //Event visualization
        float event_pos;
        float event_vel;
        float event_vis_width;
        float event_vis_height;
        bool event;
        bool event_draw;

        vector<float> event_vector;

    };
    #endif
