#include "ui.h"

ui_t::ui_t()
{
    N.setup();

//    colorText=  ofColor::fromHsb(120, 250, 250);
    verdana.loadFont("verdana.ttf", 10, true, true);
	verdana.setLineHeight(10.0f);
	verdana.setLetterSpacing(1.0);

    ofAddListener(ofEvents().mouseDragged,this, &ui_t::onDrag);
    ofAddListener(ofEvents().update,this, &ui_t::update);
    ofAddListener(ofEvents().mousePressed,this, &ui_t::onClick);
    ofAddListener(ofEvents().mouseReleased,this, &ui_t::onClickRelease);
    ofAddListener(ofEvents().keyPressed,this, &ui_t::onKeyPressed);
    ofAddListener(ofEvents().draw,this, &ui_t::draw);

    p_dc.addListener(this, &ui_t::p_dc_callback);

    gui_neuron.setup("Neuron","settings1.xml",10,10);
    gui_neuron.add(p_dc.set( "DC", 0, 0, 200));

    gui_conn.setup("Connections","settings2.xml",10,100);
    gui_conn.add(p_w.set( "Weight", 0, MIN_WEIGHT, MAX_WEIGHT));

}

void ui_t::patchbay()
{
    for (size_t i=0; i<C.dC.size(); i++ )
    {
        C.dC[i]->rad[0] = ofMap( N.neurons[i]->V, -75.0, 30, 10.0, 30.0, true);
        C.dC[i]->rad[2] = C.dC[i]->rad[0];
    }

    for (size_t i=0; i<G.nodes.size(); i++ )
    {
        G.nodes[i]->pos = C.dC[i]->pos;
    }

    for (size_t i=0; i<L.dL.size(); i++ )
    {
        L.dL[i]->pos0           = G.links[i]->from->pos;
        L.dL[i]->pos1           = G.links[i]->to->pos;

        L.dL[i]->linewidth[0]   = ofMap( G.links[i]->weight , MIN_WEIGHT,MAX_WEIGHT,MIN_LINEWIDTH,MAX_LINEWIDTH, true);
        //cout <<"Line " <<  L.dL[i]->linewidth[0] << endl;
        L.dL[i]->linewidth[2]   = L.dL[i]->linewidth[0];

    }

    for (size_t i=0; i<N.synapses.size(); i++ )
    {
        N.synapses[i]->weight = G.links[i]->weight;
    }


}

///Callbacks
void ui_t::update(ofEventArgs & args)
{

    N.update();

    patchbay();

}
void ui_t::draw(ofEventArgs & args)
{
    //if (gui_conn_draw = false)
        gui_neuron.draw();

  //  if (gui_conn_draw = true)
        gui_conn.draw();
}

void ui_t::p_dc_callback(float & p_dc)
{
    if(selected_circle!=None)
    {
        N.neuronId(selected_circle->id)->dc = p_dc;

    }

}

void ui_t::onKeyPressed(ofKeyEventArgs & args)
{
    if(args.key==127)
    {
        if(selected_circle!=None)
            remove_agent();
    }

    if(args.key=='p')
        G.print_graph();


    if(args.key=='p')
        gui_conn.minimize();

}

void ui_t::onClick(ofMouseEventArgs & args)
{

    ///says wich circle was clicked
    int circle_id_click = -1;
    int line_id_click = -1;

    ///click on objects
    bool circle_click = false;
    bool line_click = false;

    clicked_line = None;
    clicked_circle = None;

     ///Was a Circle clicked?
    for(size_t i=0 ; i<C.dC.size();i++)
    {
        ///True if click is inside circle
        circle_click = C.dC[i]->mousePressed(args);
        if (circle_click)
        {
            circle_id_click = i;
            clicked_circle = C.dC[i];

            break;
        }
    }

       ///Was a Line clicked?
    if(!circle_click)
        for (size_t i=0; i<L.dL.size(); i++ )
        {
            line_click = L.dL[i]->mousePressed(args);
             if (line_click)
            {
                line_id_click = i;
                clicked_line = L.dL[i];

                break;
            }
        }

    ///Actios for clicked line with button 0
    if ( (line_id_click!=-1) & (args.button == 0))
    {

        if(selected_line!=None)
            selected_line->selected=false;

        selected_line = clicked_line;
        selected_line->selected=true;

        //ui_conn_parameters.clear();
        //ui_conn_parameters.setName("Connection "+ofToString(selected_line->id));
        //ui_conn_parameters.add(G.links[selected_line->id]->parameters);
        //gui_conn.clear();
        //gui_conn.setup(ui_conn_parameters);

        //gui_conn.render =
        G.links[selected_line->id]->weight.makeReferenceTo(p_w);

    }

    ///Actios for clicked circle with button 0
    if ( (circle_id_click!=-1) & (args.button == 0))
    {

        if(selected_circle!=None)
            selected_circle->selected=false;

        selected_circle = clicked_circle;
        selected_circle->selected=true;

        p_dc = N.neuronId(selected_circle->id)->dc;

    }

    ///Actions for clicked circle with button 2
    if ( (circle_id_click!=-1) & (args.button == 2))
    {
        if(selected_circle!=None)
        {
            int aux_id;
            aux_id = remove_connection();

            selected_circle->selected=false;
            previous_circle = selected_circle;
            selected_circle = clicked_circle;
            selected_circle->selected=true;

            if (aux_id==-1)
                add_connection( previous_circle->pos , ofVec2f(args.x,args.y));
        }
    }

    ///button 0 If not clickin anything unselect
    if ((!circle_click && !line_click) && (args.button==0))
    {
        if(selected_circle!=None)
        {
            selected_circle->selected = false;
            selected_circle = None;
        }

        if(selected_line!=None)
        {
            selected_line->selected = false;
            selected_line = None;
        }

    }

    ///buton 2 If not clickin anything add circle, change focus
    if ((!circle_click && !line_click) & (args.button==2))
    {

        ///If was a selected circle, add a new Circle, clickit and add connection
        if(selected_circle!=None)
        {
            selected_circle->selected = false;
            previous_circle = selected_circle;

            add_agent(args.x,args.y);
            selected_circle->mousePressed(args);

            add_connection( previous_circle->pos , ofVec2f(args.x,args.y));

        }
        else
        {
            add_agent(args.x,args.y);
            selected_circle->mousePressed(args);
        }

    }

}

void ui_t::onClickRelease(ofMouseEventArgs & args)
{
    bool dragged=false;

    for(size_t i=0 ; i<C.dC.size();i++)
        dragged  = C.dC[i]->mouseReleased(args);

}

void ui_t::onDrag(ofMouseEventArgs & args)
{
    int dmx, dmy;

    dmx = mousex_old-args.x;
    dmy = mousey_old-args.y;
    //cout << dmy << endl;

    for(size_t i=0 ; i<C.dC.size();i++)
    {
        C.dC[i]->mouseDragged(args);
    }

   /* if(clicked_circle!=None)
        if(clicked_circle->drag)
           G.nodes[clicked_circle->id]->pos = clicked_circle->pos;*/

    if(clicked_line!=None)
    {

        //if(dmy>0)
        //if(clicked_line->dist2click<0)
        //    increase_connection();

        //else if(dmy<0)
        //else if(clicked_line->dist2click>0)
        //    decrease_connection();
        //cout << clicked_line->dist2click<< endl;
        set_connection(-clicked_line->dist2click) ;

    }

    for(size_t i=0 ; i<L.dL.size();i++)
    {
        L.dL[i]->mouseDragged(args);
    }

    mousex_old = args.x;
    mousey_old = args.y;
}

void  ui_t::set_connection(float conn)
{
    G.links[clicked_line->id]->weight = ofMap(conn,0,100,MIN_WEIGHT, MAX_WEIGHT,true);
    //cout <<  G.links[clicked_line->id]->weight  << endl;
    //clicked_line->linewidth[0] += 0.1;
}

void  ui_t::increase_connection()
{
    /*
    clicked_line->linewidth[0] += 0.1;
    if(clicked_line->linewidth[0]>50)
        clicked_line->linewidth[0]=50;

    link_t* link = G.linkId(clicked_line->id);
    link->weight += 10;
    if(link->weight>100)
        link->weight = 100;

    synapse_t* synapse = N.synapseId(clicked_line->id);
    synapse->weight =synapse->weight + 10;
    if(synapse->weight>500)
        synapse->weight = 500;
*/

}
void  ui_t::decrease_connection()
{
    /*
    clicked_line->linewidth[0]-=0.1;
    if(clicked_line->linewidth[0]<1)
        clicked_line->linewidth[0]=1;

    link_t* link = G.linkId(clicked_line->id);
    link->weight -= 10;
    if(link->weight<0)
        link->weight = 0;

    synapse_t* synapse = N.synapseId(clicked_line->id);
    synapse->weight =synapse->weight- 10;
    if(synapse->weight<0)
        synapse->weight = 0;
    */
}

void  ui_t::add_agent(int x, int y)
{
    C.add_circle(x, y);
    C.dC.back()->selected = true;
    selected_circle = C.dC.back();
    G.add_node(x,y,node_type,node_label);
    N.add_neuron();

}

void  ui_t::add_connection(ofVec2f pos0, ofVec2f pos1)
{
    L.add_line(pos0,pos1);
    G.add_link(previous_circle->id, selected_circle->id);
    N.add_synapse(previous_circle->id, selected_circle->id);
    //cout << L.dL.back()->selected << endl;
}

int ui_t::remove_connection()
{
    int aux_id=-1;
    aux_id = G.remove_link(selected_circle->id, clicked_circle->id);
    if (aux_id!=-1)
        L.remove_line(aux_id);

    return aux_id;
}

void ui_t::remove_agent()
{
    G.remove_node(selected_circle->id);
    C.remove_circle(selected_circle->id);
    N.remove_neuron(selected_circle->id);

}
/*
dragLine_t* ui::link2line(link_t* )
{

}

link_t* ui::line2link(dragLine_t* )
{

}
*/
/*void neurons_network::set_osc_server(ofxOscSender* _sender)
{
    osc_enable = true;
    sender = *_sender;
}*/



        /*        //SEND OSC MESSAGE
                ofxOscMessage m;
                m.setAddress("/neuron");
                m.addIntArg(i);
                sender.sendMessage(m);
        */

/*
void ui_t::mousePressed(int x,int y,int button)
{

    C.mousePressed(x,y,button);

    for(int )

        int sel_node = node_near(x,y);
        int sel_link = link_near(x,y);

        if (button==0)
        {
            if (selected_node) //prevents failure at start
            {
                actual_node->selected = false;
                selected_node = false;
            }

            if (selected_link) //prevents failure at start
            {
                actual_link->selected = false;
                selected_link = false;
            }


            if (sel_node!=-1)
            {
                nodes[sel_node]->selected = true;
                actual_node = nodes[sel_node];
                selected_node = true;
            }

            else if (sel_link!=-1)
            {
                links[sel_link]->selected = true;
                actual_link = links[sel_link];
                selected_link= true;
            }

        }
        else if(button==2)
        {

            actual_link->selected = false;
            selected_link = false;

            if (sel_node==-1)
                add_node(x,y);
            else
                connect(sel_node);
        }

        return sel_node;
}

*/

/*
void ui_t::del_node(){

    if (actual_node!=NULL && selected_node)
    {

        cout << links.size() << endl;
        for(size_t i=0; i < links.size(); i++)
        {
            //cout << "From " << links[i]->from->id << endl;
            //cout << "To " << links[i]->to->id << endl;

            if(links[i]->from == actual_node || links[i]->to == actual_node )
            {
                cout << "delting " << i<<" link" << endl;
                links[i] = links[links.size()-1];
                links.pop_back();
                i--;
            }
        }

        for(size_t i = 0 ; i < nodes.size();i++)
            if (nodes[i]==actual_node)
                {
                    nodes[i]=nodes[nodes.size()-1];
                    nodes.pop_back();
                }

        delete actual_node;

        if (nodes.size()>0)
        {
            actual_node=nodes[nodes.size()-1];
            actual_node->selected=true;
        }
        else
        {
            clear_all();
        }
    }
}


void ui_t::change_shape()
{
    if (actual_link->selected)
    {
        actual_shape = actual_link->shape;
        actual_shape++;
        if (actual_shape>shape_n-1)
            actual_shape = 0;

        actual_link->shape = actual_shape;
    }
}


void ui_t::change_type()
{
    if (actual_node->selected)
    {
        actual_type = actual_node->type;
        actual_type++;
        if (actual_type>types_n-1)
            actual_type = 0;

        actual_node->type = actual_type;

        update_type();
    }

}

void ui_t::update_type()
{
    for (size_t i = 0; i <  nodes.size(); i ++)
    {
        if (degree(nodes[i]->id) >= 2)
        {
            nodes[i]->type = 0;
        }
    }

}


void  ui_t::clear_all()
{
    nodes.clear();
    links.clear();
    id = 0;
    actual_node=NULL;
    selected_node = false;
}

void ui_t::connect(int sel)
{
    bool link_deleted=false;

    if (sel!=-1){

        for(size_t i=0; i < links.size(); i++)
        {
            if((links[i]->from == actual_node && links[i]->to==nodes[sel]) || (links[i]->to == actual_node && links[i]->from ==nodes[sel]))
            {
                links[i] = links[links.size()-1];
                links.pop_back();
                link_deleted = true;

                old_node = actual_node;
                actual_node = nodes[sel];
                actual_node->selected = true;
                old_node->selected = false;

                break;
            }
        }

        if (!link_deleted && nodes[sel]!=actual_node)
        {

            old_node = actual_node;
            actual_node = nodes[sel];

            actual_link = new link_t;
            actual_link->shape=0;
            actual_link->from = old_node;
            actual_link->to = actual_node;
            links.push_back(actual_link );

            actual_link->selected=false;

            actual_node->selected = true;
            old_node->selected = false;

        }
    }
}

int ui_t::mousePressed(int x,int y,int button)
{
        int sel_node = node_near(x,y);
        int sel_link = link_near(x,y);

        if (button==0)
        {
            if (selected_node) //prevents failure at start
            {
                actual_node->selected = false;
                selected_node = false;
            }

            if (selected_link) //prevents failure at start
            {
                actual_link->selected = false;
                selected_link = false;
            }


            if (sel_node!=-1)
            {
                nodes[sel_node]->selected = true;
                actual_node = nodes[sel_node];
                selected_node = true;
            }

            else if (sel_link!=-1)
            {
                links[sel_link]->selected = true;
                actual_link = links[sel_link];
                selected_link= true;
            }

        }
        else if(button==2)
        {

            actual_link->selected = false;
            selected_link = false;

            if (sel_node==-1)
                add_node(x,y);
            else
                connect(sel_node);
        }

        return sel_node;
}

void ui_t::draw()
{

    for(size_t j = 0; j < links.size(); j++)
    {
        if(links[j]->selected)
        {
            ofSetColor(colorLinkSelected);
            ofSetLineWidth(links[j]->shape*0.5+3.0);
        }
        else
        {
            ofSetColor(color0);
            ofSetLineWidth(links[j]->shape*0.5+2.0);
        }

        ofLine( links[j]->from->pos.x, links[j]->from->pos.y,  links[j]->to->pos.x , links[j]->to->pos.y );

        if(draw_shapes)
        {
            ofSetColor(colorText);
            verdana.drawString(ofToString(links[j]->shape), ( links[j]->from->pos.x+links[j]->to->pos.x )*0.5, (links[j]->from->pos.y+ links[j]->to->pos.y )*0.5);
        }

    }

    ofSetLineWidth(2.0);

    for(size_t i = 0; i < nodes.size();i++)
    {
        if (nodes[i]->selected)
        {
            ofFill();
            ofColor auxcolor = colorNodeTypes[nodes[i]->type];
            auxcolor.setBrightness(255);

            ofSetColor( auxcolor) ;
            ofCircle(nodes[i]->pos.x,nodes[i]->pos.y,nodes[i]->rad*1.2);
        }
        else
        {
            ofSetLineWidth(3.0);
            ofSetColor( colorNodeTypes[nodes[i]->type] );
            ofCircle(nodes[i]->pos.x,nodes[i]->pos.y,nodes[i]->rad);
        }
    }

}*/
