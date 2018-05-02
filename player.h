//
// Created by Hila Kornis on 30-Apr-18.
//
#include <stddef.h>

#ifndef DATA_WET1_PLAYER_H
#define DATA_WET1_PLAYER_H

//No C'ctor
//todo shared pointers for player
//TODO: check input parameters in oasis.
class Player{
public:
    Player(int playerID, int initialCoins):playerID(playerID),coins
            (initialCoins),numChallengesCompleted(0),clan(NULL){    }

    //changes the player's clan.
    void joinClan(void * clanToJoin);
    void completeChallenge(int coinsToAdd);

private:
    int playerID;
    int coins;
    int numChallengesCompleted;//beginning zero
    void * clan;

};


#endif //DATA_WET1_PLAYER_H
