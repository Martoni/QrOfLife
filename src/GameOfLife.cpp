#include "GameOfLife.hpp"
#include <iostream>
#include <assert.h>
using namespace std;

GameOfLife::GameOfLife(QrCode * const aqr): donut(false) {
    int y, x;
    square_size = aqr->getSize();
    lifeArray = vector<vector<bool> >(square_size,
                      vector<bool>(square_size));
    for (int y = 0; y < square_size; y++) {
        for (int x = 0; x < square_size; x++) {
            lifeArray.at(x).at(y) = aqr->getModule(x, y);
        }
    }
}

int GameOfLife::get_square_size(){
    return square_size;
}

bool GameOfLife::get_module(int x, int y){
    return lifeArray.at(x).at(y);
}

int GameOfLife::get_generation(){
    return generation;
}

void GameOfLife::set_module(int x, int y, bool value){
    lifeArray.at(x).at(y) = value;
}

void GameOfLife::nevolve(int n){
    for(int i=0; i<n; i++)
        evolve();
}

int GameOfLife::population(){
	int population = 0;
	for (auto i: lifeArray)
		for(auto j: i)
			if(j) population++;
	return population;
}

int GameOfLife::count(int x, int y){
    int friends = 0;
    int max = square_size - 1;
    assert(donut == false);

    if(x != 0 && y != 0)
        if(lifeArray.at(x-1).at(y-1))
            friends++;
    if(y != 0)
        if(lifeArray.at(x).at(y-1))
            friends++;
    if(y != 0 && x != max)
        if(lifeArray.at(x+1).at(y-1))
            friends++;

    if(x != 0)
        if(lifeArray.at(x-1).at(y))
            friends++;
    /* lifeArray.at(x).at(y)
     *  not counted */
    if(x != max)
        if(lifeArray.at(x+1).at(y))
            friends++;

    if(x != 0 && y != max)
        if(lifeArray.at(x-1).at(y+1))
            friends++;
    if(y != max)
        if(lifeArray.at(x).at(y+1))
            friends++;
    if(x != max && y != max)
        if(lifeArray.at(x+1).at(y+1))
            friends++;

    return friends;
}

void GameOfLife::evolve(){
    int x, y;
    int nfriends;
    bool alive;
    int asize;
    asize = get_square_size();

    vector<vector<bool> > newgen;

    std::cout << "Evolve from gen " << generation
	    << " population : " << population()
	    << std::endl;

    newgen = vector<vector<bool> >(square_size,
                                   vector<bool>(square_size));

    /* calculate newgen */
    for (y = 0; y < asize; y++) {
        for (x = 0; x < asize; x++) {
            alive = get_module(x, y);
            nfriends = count(x, y);
            if(alive){
                if(nfriends == 2 || nfriends == 3){
                    alive = true;
                }else{
                    alive = false;
                }
            }else{
                if(nfriends == 3)
                    alive = true;
            }
            newgen.at(x).at(y) = alive;
        }
    }

    /* copy new gen */
    for (y = 0; y < asize; y++) {
        for (x = 0; x < asize; x++) {
            set_module(x, y, newgen.at(x).at(y));
        }
    }

    generation += 1;
}
