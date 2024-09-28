#include "priority_list.hpp"

// ------------------------------------------------------------------------------------------------

PriorityList *CreateEmptyPriorityList()
{
    PriorityList *list = (PriorityList *)malloc(sizeof(PriorityList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}
void AddToPriorityList(PriorityList *list, BattleCharacter *character, int relativeSpeed)
{
    switch (list->size)
    {
    case 0:
        list->head = (PriorityEntity *)malloc(sizeof(PriorityEntity));
        list->head->character = character;
        list->head->relativeSpeed = relativeSpeed;
        list->head->hasMadeAction = false;
        list->head->next = NULL;
        list->tail = list->head;
        break;
    case 1:
        list->tail = (PriorityEntity *)malloc(sizeof(PriorityEntity));
        list->tail->character = character;
        list->tail->relativeSpeed = relativeSpeed;
        list->tail->hasMadeAction = false;
        list->tail->next = NULL;
        list->head->next = list->tail;
        break;
    default:
        PriorityEntity *newEntity = (PriorityEntity *)malloc(sizeof(PriorityEntity));
        newEntity->character = character;
        newEntity->relativeSpeed = relativeSpeed;
        newEntity->hasMadeAction = false;
        newEntity->next = NULL;
        list->tail->next = newEntity;
        list->tail = newEntity;
        break;
    }
    list->size++;
}
void RemoveFromPriorityList(PriorityList *list, BattleCharacter *character)
{
    PriorityEntity *current = list->head;
    PriorityEntity *previous = NULL;
    while (current != NULL && current->character != character)
    {
        previous = current;
        current = current->next;
    }
    if (current == NULL)
    {
        return;
    }
    if (previous == NULL)
    {
        list->head = current->next;
    }
    else
    {
        previous->next = current->next;
    }
    if (current == list->tail)
    {
        list->tail = previous;
    }
    free(current);
    list->size--;
}
void DestroyPriorityList(PriorityList *list)
{
    PriorityEntity *current = list->head;
    PriorityEntity *next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

// ------------------------------------------------------------------------------------------------

void SortPriorityList(PriorityList *list)
{
    PriorityEntity *current, *min, *previous;
    int minIndex;

    for (current = list->head; current != NULL; current = current->next)
    {
        min = current;
        minIndex = 0;
        for (int i = 1; i < list->size; i++)
        {
            if (list->head->relativeSpeed < min->relativeSpeed)
            {
                min = list->head;
                minIndex = i;
            }
        }
        if (minIndex != 0)
        {
            previous = min;
            for (int i = minIndex - 1; i >= 0; i--)
            {
                previous = previous->next;
            }
            previous->next = min->next;
            min->next = list->head;
            list->head = min;
        }
    }
}
void CleanPreviousActions(PriorityList *list)
{
    std::vector<BattleCharacter *> charactersToRemove;
    PriorityEntity *current = list->head;
    while (current != NULL)
    {
        if (current->hasMadeAction)
        {
            charactersToRemove.push_back(current->character);
        }
        current = current->next;
    }

    for (unsigned int i = 0; i < charactersToRemove.size(); i++)
    {
        RemoveFromPriorityList(list, charactersToRemove[i]);
    }
}

// ------------------------------------------------------------------------------------------------