//
// Created by Hila Kornis on 30-Apr-18.
//

#ifndef DATA_WET1_CLAN_H
#define DATA_WET1_CLAN_H
#include "player.h"
#include "AVLTree.h"
//TODO: check input parameters in oasis.
class Clan{
public:
    //function print_players_by_coins
    explicit Clan(int ID):clanID(ID),num_members(0),best_player(NULL),
                          players_by_id( Player::CompareById() ),players_by_coins( CompareByIdAndCoins() ) { }
    //Todo check input in oasis.
    //todo implement insert player func
    InsertResult insertPlayer(Player* player);
    //TODO implement get player.
    void removePlayer(Player *to_remove);
    InsertResult insertPlayerCoins(Player *to_insert);
    void removePlayerCoins(Player *to_remove);
    Player* getBestPlayer();
    void setBestPlayer(Player *new_best);
    Player* getScoreboard();
    void unite(Clan &second);
private:
    class IdAndCoins {
    public:
        IdAndCoins():id(0),coins(0){}
        IdAndCoins(const int &id,const int &coins):id(id),coins(coins){}
        IdAndCoins(const IdAndCoins &original): id(original.id),coins(original.coins){}
        void operator=(IdAndCoins &other) {
            id=other.id;
            coins=other.coins;
        }
        int id;
        int coins;
    };
    class CompareByIdAndCoins {
    public:
        int operator()(const IdAndCoins &first, const IdAndCoins &second) const{
          if(first.id == second.id) return 0;
          if(first.coins > second.coins) return 1;
          if(first.coins < second.coins) return -1;

          //coins are equal, sort by id ascending
          if(first.id < second.id) return 1;//lower id = higher key
          return -1; //first.coins = second.coins and first.id > second.id
        }
    };
    int clanID;
    int num_members;
    Player* best_player;//the player that compeleted the most challenges in
    // the clan.
    AVLTree<IdAndCoins,Player*,CompareByIdAndCoins> players_by_coins;
    AVLTree<int,Player*,Player::CompareById> players_by_id;
    //todo: update when any player complete a challenge.


};


#endif //DATA_WET1_CLAN_H
