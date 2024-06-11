#include "QOLWindow.hpp"
#include "MyDrawing.hpp"
#include <ctime>

QOLWindow::QOLWindow(struct arguments args, GameOfLife *agol):
    args(args), qrtext(args.args[0])
{
    set_border_width(10);

    // vBoxMain
    add(vBoxMain);
    vBoxMain.show();

    vBoxMain.add(myArea);
    myArea.set_gol(agol);
    myArea.show();

    if(args.arggen <= 0) {
        // buttonDisplay
        buttonDisplay.set_label("Evolve");
        buttonDisplay.signal_clicked().connect(
            sigc::mem_fun (
                *this, &QOLWindow::buttonDisplayClicked
                ));
        vBoxMain.add(buttonDisplay);
        buttonDisplay.show();
    } else {
        // timeout evolution
        Glib::signal_timeout().connect(
                sigc::mem_fun(
                    *this, &QOLWindow::on_timeout),
                500 );
    }
}

void QOLWindow::buttonDisplayClicked() {

    myArea.gol_evolve(args.verbose);
    myArea.queue_draw();

    bool prependMessage = checkButtonPrependMessage.get_active();
    if(args.verbose > 0) {
        string textToDisplay = qrtext;
        if (prependMessage == true)
        {
            textToDisplay.insert(0, "Message: ");
        }
        printf("%s\n", textToDisplay.c_str());
    }
}

bool QOLWindow::on_timeout() {
    if(myArea.gol->get_generation() < args.arggen){
        myArea.gol_evolve(args.verbose);
        myArea.queue_draw();
    }
    return true;
}
