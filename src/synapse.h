 #ifndef SINAPSIS
    #define SINAPSIS

    #include "ofMain.h"
    #include "neuron.h"
    #include "ofxControlFloat.h"

    class synapse_t {
    public:
        synapse_t();

        void set(float w, float d);
        void update();
        void random_weight(float min, float max);

        neuron_t* from;
        neuron_t* to;

        size_t id;


        ofxControlFloat weight, delay;
    };
    #endif
