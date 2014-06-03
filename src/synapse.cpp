 #include "synapse.h"

    synapse_t::synapse_t(){
        weight = 0;
        delay = 0;
    }

    void synapse_t::random_weight(float _min,float _max){

        weight = ofRandom(_min,_max);
    }
    void synapse_t::set(float w,float d){

        weight = w;
        delay = d;
    }
