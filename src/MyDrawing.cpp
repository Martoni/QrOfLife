#include "MyDrawing.hpp"
#include <cairomm/context.h>
#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <glibmm/fileutils.h>
#include <iostream>

MyArea::MyArea()
{
  try
  {
    // The fractal image has been created by the XaoS program.
    // http://xaos.sourceforge.net
    m_image = Gdk::Pixbuf::create_from_file("qrtest.svg");
  }
  catch(const Gio::ResourceError& ex)
  {
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  }
  catch(const Gdk::PixbufError& ex)
  {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }

  // Show at least a quarter of the image.
//  if (m_image)
//    set_size_request(m_image->get_width()/2, m_image->get_height()/2);
//    set_size_request(mawidth, maheight);
}

MyArea::~MyArea()
{
}

void MyArea::set_qr(QrCode *aqr){
    qr = aqr;
}


bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    if (!m_image)
      return false;

    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    int asize = qr->getSize();
    float fullsize = asize * 10.0;
    set_size_request(fullsize, fullsize);

    std::cout << "drawing my area" << std::endl;

    cr->scale(fullsize, fullsize);
    int i, j;
    cr->set_source_rgb (0, 0, 0);

    for (int y = 0; y < asize; y++) {
        for (int x = 0; x < asize; x++) {
            if(qr->getModule(x, y)){
                cr->rectangle ((1.0+x)/(1.0 + asize),
                               (1.0+y)/(1.0 + asize),
                               0.05, 0.05);
            }
        }
    }
    std::cout << "Drawing pix size:" << asize << std::endl;


//    for (i=1; i<10; i++)
//        for (j=1; j<10; j++)
//            cr->rectangle (i/10.0 - 0.04, j/10.0 - 0.04, 0.08, 0.08);
    cr->fill ();
    return true;
}
