#ifndef neurons_network
    #define RES_NEURONAS

    #define MAXN 100
    #include <vector>
    #include "neuron.h"
    #include "synapse.h"

    float drand();
    float random_normal();

    class neurons_network {
    public:
        neurons_network();

        void setup();
        void update();

        void add_neuron();
        void remove_neuron(size_t id);
        void add_synapse(size_t source_id,size_t target_id );
        void remove_synapse(size_t id);

        void reset();
        void draw(float zscale);

        void set_dts(float dt);
        void set_currents(float dc_mean, float dc_std);

        void set_syn_w_matrix(float type_prop,float syn_w_mean, float syn_w_weight);
        void set_syn_d_matrix(float syn_d_mean, float syn_d_weight);

        void togg_syn_matrix();


        neuron_t* neuronId(size_t id);
        synapse_t* synapseId(size_t id);

        vector <neuron_t*> neurons;
        vector<synapse_t*> synapses;

        size_t neuron_id,synapse_id;

        bool bool_syn_matrix;


    };
#endif
