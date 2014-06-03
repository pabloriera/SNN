#include "graph.h"
#include "igraph/igraph.h"
#include "conste_constants.h"

graph_t::graph_t()
{
    node_id = 0;
    link_id = 0;

}

void graph_t::add_node(int x, int y, size_t type, string label)
{
    node_t* node;
    node = new node_t;
    node->id = node_id;
    node->pos.set(x,y);
    node->type = type;
    node->label = label;
    node_id++;

    nodes.push_back(node);

}

void graph_t::remove_node(size_t id)
{
    for(size_t i = 0 ; i < nodes.size();i++)
        if (nodes[i]->id==id)
            {
                nodes[i]=nodes.back();
                nodes.pop_back();
            }
}

int graph_t::remove_link(size_t source_id,size_t target_id )
{
    int aux_id=-1;
    for(size_t i = 0 ; i < links.size();i++)
    {

        if ( ((links[i]->from==nodes[source_id]) && (links[i]->to==nodes[target_id])))
        {
            //||  ((links[i]->from==nodes[target_id]) && (links[i]->to==nodes[source_id])))
            aux_id = links[i]->id;
            links[i] = links.back();
            links.pop_back();

            break;
        }
    }
    return aux_id;
}

void graph_t::add_link(size_t source_id,size_t target_id )
{
    size_t target_idx;
    size_t source_idx;

    for(size_t i = 0 ; i < nodes.size();i++)
    {
        if (nodes[i]->id==source_id)
            {
                source_idx = i;
            }

        if (nodes[i]->id==target_id)
            {
                target_idx = i;
            }
    }

    link_t* link;
    link = new link_t;
    link->id = link_id;
    link->from = nodes[source_idx];
    link->to = nodes[target_idx];
    link->weight.set("weight",0,MIN_WEIGHT,MAX_WEIGHT);
    links.push_back(link );
    link_id++;
}

node_t* graph_t::nodeId(size_t id)
{
    node_t* node;
    for(size_t i = 0; i < nodes.size(); i++)
    {
        if(id==nodes[i]->id)
            node = nodes[i];
    }

    return node;
}

link_t* graph_t::linkId(size_t id)
{
    link_t* link;
    for(size_t i = 0; i < links.size(); i++)
    {
        if(id==links[i]->id)
            link = links[i];
    }

    return link;
}

int graph_t::degree(size_t id)
{
    int degree=0;
    for(size_t i=0; i < links.size(); i++)
    {
        if(links[i]->from->id == id)
            degree++;
        if(links[i]->to->id == id)
            degree++;
    }

    return degree;
}


void  graph_t::clear_all()
{
    nodes.clear();
    links.clear();
    node_id = 0;
    link_id = 0;
}

void graph_t::save(string xml_file_name)
{
    igraph_i_set_attribute_table(&igraph_cattribute_table);

    igraph_t g;

    igraph_vector_t v;

    igraph_vector_init(&v, links.size()*2);
    size_t c = 0;

    for(size_t i = 0; i<links.size();i++)
    {
        VECTOR(v)[c]=links[i]->from->id;
        VECTOR(v)[c+1]=links[i]->to->id;
        c+=2;
    }

    igraph_create(&g, &v, 0, 1);


    for(size_t i = 0; i<links.size();i++)
        SETEAN(&g, "weight",i,links[i]->weight);

    for(size_t i = 0; i<nodes.size();i++)
    {
        SETVAN(&g, "x", nodes[i]->id, nodes[i]->pos.x);
        SETVAN(&g, "y", nodes[i]->id, nodes[i]->pos.y);
        SETVAN(&g, "type",nodes[i]->id, nodes[i]->type);
        SETVAS(&g, "label",nodes[i]->id, " ");

    }

    FILE *ifile;
    ifile=fopen(xml_file_name.c_str(), "w");
    igraph_write_graph_graphml(&g,ifile);
    igraph_destroy(&g);
    igraph_vector_destroy(&v);
    fclose(ifile);

}

void graph_t::load(string xml_file_name)
{

    igraph_i_set_attribute_table(&igraph_cattribute_table);

    FILE *ifile;
    ifile=fopen(xml_file_name.c_str(), "r");

    if (ifile==0)
    {
        cout << "File " << xml_file_name << " missing"<< endl;
        //fclose(ifile);
    }
    else
    {
        clear_all();

        igraph_vector_t v;
        igraph_t g;

        igraph_read_graph_graphml(&g,ifile,0);
        fclose(ifile);

        for(int i=0; i<igraph_vcount(&g); i++)
        {
            add_node(VAN(&g,"x",i),-VAN(&g,"y",i),0,VAS(&g,"label",i));
        }

        /*for(int i=0; i<igraph_vcount(&g); i++)
        {
            nodes[i]->id = i;
            //actual_node->to.clear();
            nodes[i]->pos.x = VAN(&g,"x",i);
            nodes[i]->pos.y = -VAN(&g,"y",i);
            nodes[i]->label = VAS(&g,"label",i);
        }*/


        links.clear();

        igraph_vector_init(&v,0);
        igraph_get_edgelist(&g,&v,false);

        size_t c = 0;

        for(int i=0; i<igraph_vector_size(&v); i+=2)
        {
            int source = VECTOR(v)[i];
            int target = VECTOR(v)[i+1];

            link_t* link;
            link = new link_t;
            link->weight =  EAN(&g,"weight",c);
            link->from = nodes[source];
            link->to = nodes[target];
            links.push_back(link);
            c++;

        }

        for(size_t i=0; i<nodes.size(); i++)
        {
            nodes[i]->type = VAN(&g,"type",i);
        }


        igraph_destroy(&g);
        igraph_vector_destroy(&v);
    }
}




void graph_t::print_graph()
{
    for(size_t i = 0; i<links.size();i++)
    {
        cout << "Link " << i  << " "  << links[i]->from->id << "->" << links[i]->to->id << endl;
    }

    for(size_t i = 0; i<nodes.size();i++)
    {
        cout << "Node " << nodes[i]->id  << " " << nodes[i]->type << " ("  << nodes[i]->pos.x << "," << nodes[i]->pos.y << ")" <<endl;;
    }
}
