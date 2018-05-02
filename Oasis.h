//
// Created by Hila Kornis on 30-Apr-18.
//

#include "checks.cpp"
#ifndef DATA_WET1_OASIS_H
#define DATA_WET1_OASIS_H


enum {SMALLER, EQUAL, BIGGER} StatusPlayerComp;

class playerCmp{


};


//need to add here an cmp fuction for 2 players.
//here we have the main of all the clans AVL tree.
class ClansTree{
private:

    void * best_player_in_oasis;//the most challenges in the system.
    //TODO:  updates when we any player complete a challenge.

};

template <class Data, class Key, class FuncCmp>
class Oasis{

private:
    int numOfPlayers;

    //playerID_tree AVL originals
    //playerCoins_tree AVL pointers
    ////incase that we need to print all of the players.
    ClansTree clans;//clan_tree AVL


};



#endif //DATA_WET1_OASIS_H
