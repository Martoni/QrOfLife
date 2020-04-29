#include "QrCode.hpp"
#include "MyDrawing.hpp"
#include "QOLWindow.hpp"
#include "QrOfLife.hpp"

using namespace std;
using namespace Gtk;
using namespace qrcodegen;

// argp example copied from:
// https://www.gnu.org/software/libc/manual/html_node/Argp-Example-3.html
const char *argp_program_version = "QrOfLife 0.1";
const char *argp_program_bug_address = "<mail@fabienm.eu>";
static char doc[] =
        "QrOfLife -- A tribute to John Horton Conway, make Qr Code alive :)";
static char args_doc[] = "TEXT_TO_QR";
static struct argp_option options[] = {
  {"help",       'h', 0,      0, "Get help message" },
  {"generation", 'g', "INT",  0, "Give generation number" },
  {"verbose",    'v', 0,      0, "Produce verbose output" },
  {"output",     'o', "FILE", 0, "Output gif" },
  { 0 }
};

static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = static_cast<struct arguments *> (state->input);

  switch (key)
    {
    case 'h':
        argp_usage (state);
        break;
    case 'v':
        arguments->verbose = 1;
        break;
    case 'o':
        arguments->output_file = arg;
        break;
    case 'g':
        arguments->arggen = atoi(arg);
        break;
    case ARGP_KEY_ARG:
        if (state->arg_num >= 1)
            argp_usage (state);
        arguments->args[state->arg_num] = arg;
        break;
    case ARGP_KEY_END:
        if (state->arg_num < 1)
        /* Not enough arguments. */
            argp_usage (state);
        break;
    default:
      return ARGP_ERR_UNKNOWN;
    }

  return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char **argv)
{
    struct arguments arguments;

    cout << "Welcome in QrOfLife program" << endl;

    /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
    argp_parse (&argp, argc, argv, 0, 0, &arguments);

    cout << "Let's make Qr Code with text :" << endl;
    cout << arguments.args[0] << endl;

    // Simple operation
    QrCode qr0 = QrCode::encodeText(arguments.args[0].c_str(),
                                    QrCode::Ecc::MEDIUM);
    GameOfLife gol(&qr0, arguments);

    Main kit(argc, argv);
    QOLWindow QOLWindow(arguments, &gol);
    Main::run(QOLWindow);

    return 0;
}
