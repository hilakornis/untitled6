//
// Created by Ido on 03/05/2018.
//
#include "clan.h"

InsertResult Clan::insertPlayer(Player *player) {
    InsertResult result = players_by_id.insert(player->getID(),player);
    if(result != INSERT_SUCCESS) return result;
    result = insertPlayerCoins(player);
    if(result != INSERT_SUCCESS) return result;
    player->joinClan(this);
    if(!best_player) {
        best_player=player;
    } else {
        if((best_player->getChallenges() < player->getChallenges()) ||
           ((best_player->getChallenges() == player->getChallenges()) && (best_player->getID() > player->getID()))) {
            best_player=player;
        }
    }
}

void Clan::removePlayer(Player *to_remove) {
    IdAndCoins coins_key(to_remove->getID(),to_remove->getCoins());
    players_by_coins.remove(coins_key);
    players_by_id.remove(to_remove->getID());
    to_remove->joinClan(NULL);
}

InsertResult Clan::insertPlayerCoins(Player *to_insert) {
    IdAndCoins coins_key(to_insert->getID(),to_insert->getCoins());
    return players_by_coins.insert(coins_key,to_insert);
}

void Clan::removePlayerCoins(Player *to_remove) {
    IdAndCoins coins_key(to_remove->getID(),to_remove->getCoins());
    players_by_coins.remove(coins_key);
}


