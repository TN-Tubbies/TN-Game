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

PriorityEntity *GetEntityFromList(PriorityList *list, int index)
{
    if (index < 0 || index > list->size)
    {
        return NULL;
    }

    PriorityEntity *current = list->head;
    for (int i = 1; i < index; i++)
    {
        current = current->next;
    }

    return current;
}

// ------------------------------------------------------------------------------------------------
PriorityList *SortPriorityList(PriorityList *list)
{
    std::vector<std::vector<int>> indexes_and_speeds;
    for (int i = 1; i <= list->size; i++)
    {
        std::vector<int> index_and_speed;
        index_and_speed.push_back(i);
        index_and_speed.push_back(GetEntityFromList(list, i)->relativeSpeed);
        indexes_and_speeds.push_back(index_and_speed);
    }

    std::vector<std::vector<int>> indexes_and_speeds_sorted;
    while (indexes_and_speeds.size() > 0)
    {
        int maxIndex = 0;
        int maxSpeed = indexes_and_speeds[0][1];
        for (int i = 1; i < indexes_and_speeds.size(); i++)
        {
            if (indexes_and_speeds[i][1] > maxSpeed)
            {
                maxIndex = i;
                maxSpeed = indexes_and_speeds[i][1];
            }
        }

        indexes_and_speeds_sorted.push_back(indexes_and_speeds[maxIndex]);
        indexes_and_speeds.erase(indexes_and_speeds.begin() + maxIndex);
    }

    PriorityList *sortedList = CreateEmptyPriorityList();
    for (int i = 0; i < list->size; i++)
    {
        AddToPriorityList(sortedList, GetEntityFromList(list, indexes_and_speeds_sorted[i][0])->character, indexes_and_speeds_sorted[i][1]);
    }

    DestroyPriorityList(list);

    return sortedList;
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