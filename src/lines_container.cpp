#include "lines_container.h"
#include "ofMain.h"

lines_container::lines_container()
{
    ofAddListener(ofEvents().draw, this, &lines_container::draw);
    id = 0;
}

void lines_container::setup(size_t N)
{
    for(size_t i=0; i<N; i++)
        dL.push_back( new dragLine_t );

    for(size_t i=0; i<N; i++)
        dL[i]->setup(i);
}

void lines_container::draw(ofEventArgs & args)
{
    for (size_t i=0; i < dL.size(); i++ )
    {
        dL[i]->draw();
    }

}

void lines_container::add_line(ofVec2f pos0, ofVec2f pos1)
{

    dragLine_t* dL_aux = new dragLine_t;

    dL_aux->setup(id);
    id++;
    dL_aux->pos0 = pos0;
    dL_aux->pos1 = pos1;

    //Styles
    //normal
    dL_aux->add_style( ofColor::fromHsb( 85, 255, 180 ) , 2.0 );
    //drag
    dL_aux->add_style( ofColor::fromHsb( 30, 255, 180 ) , 3.0 );
    //selected
    dL_aux->add_style( ofColor::fromHsb( 125, 255, 180 ) , 3.0 );

    dL.push_back( dL_aux );

}

void lines_container::remove_line(size_t id)
{
    for(size_t i=0; i<dL.size(); i++)
    {
        if(dL[i]->id == id)
        {
            dL[i] = dL.back();
            dL.pop_back();
        }
    }
}

/*void lines_container::mouseDragged(int x,int y)
{
    for (size_t i=0; i<dL.size(); i++ )
        dL[i]->mouseDragged(x,y);
}*/

void lines_container::mousePressed(int x,int y,int button)
{

}

void lines_container::mouseRelease()
{

}
