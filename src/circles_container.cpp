#include "circles_container.h"

circles_container::circles_container()
{
    ofAddListener(ofEvents().draw, this, &circles_container::draw);
    id = 0;
}

void circles_container::setup(size_t N)
{
    for(size_t i=0; i<N; i++)
        dC.push_back( new dragCircle_t );

    for(size_t i=0; i<dC.size(); i++)
        dC[i]->setup(i);
}

void circles_container::add_circle( int x, int y)
{
    dragCircle_t* dC_aux = new dragCircle_t;

    dC_aux->setup(id);
    id++;

    dC_aux->pos.set(x,y);

    //Styles
    //normal
    dC_aux->add_style(ofColor::fromHsb( 85, 255, 255 ), true, 10.0, 2.0 );
    //clicked
    dC_aux->add_style(ofColor::fromHsb( 10, 255, 255 ), true, 15.0, 2.0 );
    //selected
    dC_aux->add_style(ofColor::fromHsb( 30, 255, 255 ), true, 10.0, 2.0 );

    dC.push_back( dC_aux );
}

void circles_container::remove_circle(size_t id)
{
    for(size_t i = 0 ; i < dC.size();i++)
        if (dC[i]->id==id)
            {
                dC[i]=dC.back();
                dC.pop_back();
            }
}

void circles_container::draw(ofEventArgs & args)
{
    for (size_t i=0; i<dC.size(); i++ )
        dC[i]->draw();
}
