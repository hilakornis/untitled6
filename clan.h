//
// Created by Hila Kornis on 30-Apr-18.
//

#ifndef DATA_WET1_CLAN_H
#define DATA_WET1_CLAN_H
#include "player.h"
#include "includes.h"
//TODO: check input parameters in oasis.
class Clan{
public:
    //function print_players_by_coins
    //todo update ctor to intialize trees
    Clan(int ID):clanID(ID){}
    //Todo check input in oasis.
    //todo shared pointers for player
    //todo implement insert player func
    void insertPlayer(void * player);
    //TODO implement get player.
    void * getBestPlayer();
    std::shared_ptr<Player>* getScoreboard();
    void unite(Clan second);
private:
    int clanID;
    int num_members;
    void * best_player;//the player that compeleted the most challenges in
    // the clan.
    //todo: update when any player complete a challenge.

    //TODO playerID_tree AVL pointers
    //TODO playerCoins_tree AVL pointers

};


#endif //DATA_WET1_CLAN_H
