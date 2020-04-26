#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H

#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include "QrCode.hpp"
using namespace std;
using namespace qrcodegen;

class MyArea : public Gtk::DrawingArea
{
public:
    MyArea();
    virtual ~MyArea();

    const int mawidth = 500;
    const int maheight = 500;

    QrCode *qr;

    void set_qr(QrCode *);

protected:
//Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

  Glib::RefPtr<Gdk::Pixbuf> m_image;
};
#endif // GTKMM_EXAMPLE_MYAREA_H
