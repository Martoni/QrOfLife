#ifndef QOLWINDOW_HPP
#define QOLWINDOW_HPP

#include "QrOfLife.hpp"
using namespace std;
using namespace Gtk;

class QOLWindow : public Window
{
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
    // methods

    public: QOLWindow()
    {
        set_border_width(10);

        // vBoxMain
        add(vBoxMain);
        vBoxMain.show();

        vBoxMain.add(myArea);
        myArea.show();

        // buttonDisplay
        buttonDisplay.set_label("Display");
        buttonDisplay.signal_clicked().connect
        (
            sigc::mem_fun
            (
                *this,
                &QOLWindow::buttonDisplayClicked
            )
        );
        vBoxMain.add(buttonDisplay);
        buttonDisplay.show();
    }

    // event handlers

    protected: void buttonDisplayClicked()
    {
        string textToDisplay = entryTextToDisplay.get_text();

        bool prependMessage = checkButtonPrependMessage.get_active();
        if (prependMessage == true)
        {
            textToDisplay.insert(0, "Message: ");
        }
        printf("%s\n", textToDisplay.c_str());
    }
};

#endif
