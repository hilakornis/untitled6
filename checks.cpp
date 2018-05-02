//
// Created by Hila Kornis on 30-Apr-18.
//

//check functions
#include "library1.h"
#include <stddef.h>
StatusType check_addPlayer_input(void * DS, int& playerID, int& initialCoins){
    if((DS == NULL) || (playerID <= 0) || (initialCoins < 0))
        return INVALID_INPUT;
    return SUCCESS;
}

StatusType check_addClan_input(void * DS, int& clanID){
    if((DS == NULL) || (clanID <= 0))
        return INVALID_INPUT;
    return SUCCESS;
}
