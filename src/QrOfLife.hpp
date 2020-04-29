#ifndef QROFLIFE_HPP
#define QROFLIFE_HPP

#include <argp.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <gtkmm.h>
#include <gtkmm/drawingarea.h>

struct arguments
{
    std::string args[1]; /* Text to encode */
    int verbose = 0;
    int arggen = -1;
    std::string output_file;
    std::string input_text;
};

#endif
