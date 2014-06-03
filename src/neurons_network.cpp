#include "neurons_network.h"


neurons_network::neurons_network(){

}

void neurons_network::setup()
{

    bool_syn_matrix = true;

    neuron_id = 0;
    synapse_id = 0;
}

void neurons_network::add_neuron()
{
    neuron_t* neuron = new neuron_t;
    neuron->setup(neuron_id);
    neuron_id++;

    neurons.push_back(neuron);
}

void neurons_network::remove_neuron(size_t id)
{
    for(size_t i = 0 ; i < neurons.size();i++)
        if (neurons[i]->id==id)
            {
                neurons[i]=neurons.back();
                neurons.pop_back();
            }
}

void neurons_network::remove_synapse(size_t id)
{
    for(size_t i=0; i<synapses.size(); i++)
    {
        if(synapses[i]->id == id)
        {
            synapses[i] = synapses.back();
            synapses.pop_back();
        }
    }
}

void neurons_network::add_synapse(size_t source_id,size_t target_id )
{

    synapse_t* synapse = new synapse_t;

    for(size_t i = 0 ; i < neurons.size();i++)
    {
        if (neurons[i]->id==source_id)
            {
                synapse->from = neurons[i];
            }

        if (neurons[i]->id==target_id)
            {
                synapse->to = neurons[i];
            }
    }

    synapse->id = synapse_id;
    synapses.push_back(synapse );
    synapse_id++;

}

void neurons_network::update()
{

    for(size_t i = 0; i < neurons.size(); i++)
        neurons[i]->update();

    if (bool_syn_matrix)
        for(size_t i = 0; i < synapses.size(); i++)
            synapses[i]->to->currentBuffer( synapses[i]->weight, synapses[i]->delay, synapses[i]->from );

}

neuron_t* neurons_network::neuronId(size_t id)
{
    neuron_t* neuron;
    for(size_t i = 0; i < neurons.size(); i++)
    {
        if(id==neurons[i]->id)
            neuron = neurons[i];
    }

    return neuron;
}

synapse_t* neurons_network::synapseId(size_t id)
{
    synapse_t* synapse;
    for(size_t i = 0; i < synapses.size(); i++)
    {
        if(id==synapses[i]->id)
            synapse = synapses[i];
    }

    return synapse;
}

void neurons_network::draw(float zscale)
{
    for(size_t i = 0; i < neurons.size(); i++)
    {


    }
}

void neurons_network::set_currents(float dc_mean, float dc_std)
{
    for(size_t i = 0; i < neurons.size(); i++)
        neurons[i]->dc = dc_mean + dc_std*random_normal();
}

void neurons_network::set_dts(float dt)
{
    for(size_t i = 0; i < neurons.size(); i++)
        neurons[i]->dt = dt;
}

void neurons_network::set_syn_w_matrix(float type_prop, float syn_w_mean, float syn_w_std)
{
    for(size_t i = 0; i < neurons.size(); i++)
    {
        neurons[i]->syn_type = (i < type_prop*neurons.size())*2-1;

        ofColor aux_color;
        aux_color.setHsb((-neurons[i]->syn_type+1)/2 * 50.0,(-neurons[i]->syn_type+1)/2 * 127.0,(neurons[i]->syn_type+1)/2 * 50.0 + 127.0 );


        neurons[i]->color = aux_color;

        for(size_t j = 0; j < neurons.size(); j++)
        {
            if (i!=j)
            {
                float aux = syn_w_mean + syn_w_std*random_normal();
                aux = MAX(aux,0);
                synapses[i][j].weight = aux;
                }
        }
    }
}

void neurons_network::set_syn_d_matrix(float syn_d_mean, float syn_d_std)
{
    for(size_t i = 0; i < neurons.size(); i++)
    {
        for(size_t j = 0; j < neurons.size(); j++)
        {
            if (i!=j)
            {
                float aux = syn_d_mean + syn_d_std*random_normal();
                aux = floor( CLAMP(aux,0,neurons[j]->sp_bufferSize) );
                synapses[i][j].delay = aux;
            }
        }
    }
}


void neurons_network::togg_syn_matrix()
{
    bool_syn_matrix = !bool_syn_matrix;
}

void neurons_network::reset()
{
    for(size_t i = 0; i < neurons.size(); i++){
        neurons[i]->reset();
    }
}



float drand()   /* uniform distribution, (0..1] */
{    return (rand()+1.0)/(RAND_MAX+1.0);   }

float random_normal()  /* normal distribution, centered on 0, std dev 1 */
{    return sqrt(-2*log(drand())) * cos(2*M_PI*drand());    }

