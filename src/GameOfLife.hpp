#ifndef GAME_OF_LIFE_HPP
#define GAME_OF_LIFE_HPP
#include "QrCode.hpp"
using namespace qrcodegen;

/* TODO:
 * - Manage donut world
 */

class GameOfLife {
    public:
        bool donut;
        GameOfLife(QrCode * const aqr);
        int get_square_size();
        bool get_module(int x, int y);
        int get_generation();
        void set_module(int x, int y, bool value);
        void evolve();
        void nevolve(int n);
	int population();

    protected:
        int count(int x, int y);
        std::vector<std::vector<bool> > lifeArray;
        int square_size;
        int generation = 0;
};

#endif // GAME_OF_LIFE_HPP
