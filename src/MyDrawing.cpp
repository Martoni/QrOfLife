#include "MyDrawing.hpp"
#include <cairomm/context.h>
#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <glibmm/fileutils.h>
#include <iostream>

MyArea::MyArea()
{
}

MyArea::~MyArea()
{
}

void MyArea::set_gol(GameOfLife *agol){
    gol = agol;
}

void MyArea::gol_evolve(int verbose){
	gol->evolve(verbose);
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    int asize = gol->get_square_size();
    float fullsize = asize * 10.0;
    set_size_request(fullsize, fullsize);

    cr->scale(fullsize, fullsize);
    cr->set_source_rgb (0, 0, 0);

    for (int y = 0; y < asize; y++) {
        for (int x = 0; x < asize; x++) {
            if(gol->get_module(x, y)){
                cr->rectangle ((1.0+x)/(1.0 + asize),
                               (1.0+y)/(1.0 + asize),
				1.0/asize, 1.0/asize);
            }
        }
    }
    cr->fill ();

    return true;
}
