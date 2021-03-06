#ifndef QOLWINDOW_HPP
#define QOLWINDOW_HPP

#include "QrOfLife.hpp"
#include "GameOfLife.hpp"
#include "MyDrawing.hpp"
using namespace std;
using namespace Gtk;

class QOLWindow : public Window
{

    public:
        QOLWindow(struct arguments args, GameOfLife *agol);

        string qrtext;

    // controls
    protected:
        VBox vBoxMain;
        Label labelTextToDisplay;
        Entry entryTextToDisplay;
        Label labelDisplayTo;
        ComboBoxText comboBoxDisplayTo;
        CheckButton checkButtonPrependMessage;
        Button buttonDisplay;
        MyArea myArea;
        struct arguments args;

    // event handlers
        void buttonDisplayClicked();
        bool on_timeout();
};

#endif
