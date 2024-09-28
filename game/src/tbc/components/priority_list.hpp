#ifndef PRIORITY_LIST_HPP
#define PRIORITY_LIST_HPP

#include "battle_character.hpp"

typedef struct PriorityEntity
{
    BattleCharacter *character;
    int relativeSpeed;
    bool hasMadeAction;

    struct PriorityEntity *next;

} PriorityEntity;

typedef struct PriorityList
{
    PriorityEntity *head;
    PriorityEntity *tail;
    int size;
} PriorityList;

PriorityList *CreateEmptyPriorityList();
void AddToPriorityList(PriorityList *list, BattleCharacter *character, int relativeSpeed);
void RemoveFromPriorityList(PriorityList *list, BattleCharacter *character);
void DestroyPriorityList(PriorityList *list);
PriorityEntity *GetEntityFromList(PriorityList *list, int index);

PriorityList *SortPriorityList(PriorityList *list);
void CleanPreviousActions(PriorityList *list);

#endif