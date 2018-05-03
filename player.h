//
// Created by Hila Kornis on 30-Apr-18.
//
#ifndef DATA_WET1_PLAYER_H
#define DATA_WET1_PLAYER_H
#include <cstddef>

class Clan; //avoid circular dependency

//TODO: check input parameters in oasis.
class Player{
public:
    Player(int playerID, int initialCoins):playerID(playerID),coins(initialCoins),numChallengesCompleted(0),clan(NULL){}

    //changes the player's clan.
    void joinClan(Clan* clanToJoin);
    void completeChallenge(int coinsToAdd);

    //getters
    int getID();
    int getCoins();
    int getChallenges();

    //to compare keys which are ints (id)
    class CompareById {
    public:
        int operator()(const int &first,const int &second) {
            if(first > second) return 1;
            if(first < second) return -1;
            return 0;

        }
    };

private:
    int playerID;
    int coins;
    int numChallengesCompleted;//beginning zero
    Clan *clan; //changed from void

};


#endif //DATA_WET1_PLAYER_H
