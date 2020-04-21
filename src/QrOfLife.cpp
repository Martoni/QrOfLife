#include "QrOfLife.hpp"

using namespace std;
using namespace Gtk;
using namespace qrcodegen;

class GTKTest : public Window
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

    // methods

    public: GTKTest()
    {
        set_border_width(10);

        // vBoxMain
        add(vBoxMain);
        vBoxMain.show();

        // labelTextToDisplay
        labelTextToDisplay.set_label("Text to Display:");
        vBoxMain.add(labelTextToDisplay);
        labelTextToDisplay.show();

        // entryTextToDisplay
        entryTextToDisplay.set_text("This is a test!");
        vBoxMain.add(entryTextToDisplay);
        entryTextToDisplay.show();

        // labelDisplayTo
        labelDisplayTo.set_label("Display to:");
        vBoxMain.add(labelDisplayTo);
        labelDisplayTo.show();

        // comboBoxDisplayTo
        comboBoxDisplayTo.append("Console");
        comboBoxDisplayTo.append("Dialog");
        comboBoxDisplayTo.set_active(0);
        vBoxMain.add(comboBoxDisplayTo);
        comboBoxDisplayTo.show();

        // checkButtonPrependMessage
        checkButtonPrependMessage.set_label("Prepend 'Message: '");
        vBoxMain.add(checkButtonPrependMessage);
        checkButtonPrependMessage.show();

        // buttonDisplay
        buttonDisplay.set_label("Display");
        buttonDisplay.signal_clicked().connect
        (
            sigc::mem_fun
            (
                *this,
                &GTKTest::buttonDisplayClicked
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

        string displayMode = comboBoxDisplayTo.get_active_text();

        if (displayMode == "Console")
        {
            printf("%s\n", textToDisplay.c_str());
        }
        else if (displayMode == "Dialog")
        {
            MessageDialog dialog(textToDisplay);
            dialog.run();
        }
        else
        {
            throw runtime_error("Unrecognized display mode!");
        }
    }
};


int main(int argc, char **argv)
{
    cout << "Welcome in QrOfLife program" << endl;
    // Simple operation
    QrCode qr0 = QrCode::encodeText("Hello, world!", QrCode::Ecc::MEDIUM);
    std::string svg = qr0.toSvgString(4);

    ofstream fsvg;
    fsvg.open("qrtest.svg");
    fsvg << svg;
    fsvg.close();

    // Manual operation
    std::vector<QrSegment> segs =
    QrSegment::makeSegments("3141592653589793238462643383");
    QrCode qr1 = QrCode::encodeSegments(
    segs, QrCode::Ecc::HIGH, 5, 5, 2, false);
//    for (int y = 0; y < qr1.getSize(); y++) {
//        for (int x = 0; x < qr1.getSize(); x++) {
//            (... paint qr1.getModule(x, y) ...)
//        }
//    }

    Main kit(argc, argv);
    GTKTest GTKTest;
    Main::run(GTKTest);

    return 0;
}
