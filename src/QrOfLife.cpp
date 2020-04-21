#include "QrOfLife.hpp"

using namespace std;
using namespace Gtk;
using namespace qrcodegen;

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
    return 0;
}
