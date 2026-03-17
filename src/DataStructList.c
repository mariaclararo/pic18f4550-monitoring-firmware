/*
 * File:   DataStructList.c
 * Author: ultim
 *
 * Created on 10 de Maio de 2024, 12:58
 */


#include "DataStructList.h"
#include <stdlib.h>








//adiciona um elemento
void add(node **head, unsigned char val, unsigned char index)
{
    node *newnode = malloc(sizeof(node));
    newnode->data = val;
    newnode->index = index;
    newnode->next = NULL;

    //add no inicio da lista
    if(*head == NULL || (*head)->data >= val)
    {
        newnode->next = *head;
        *head = newnode;
        return;
    }


    node *i = *head;

    while(i->next != NULL && i->next->data < val)
    {
        i = i->next;
    }
    newnode->next = i->next;
    i->next = newnode;
}



//limpa a lista
void freelist(node **head)
{
    node *current = *head;
    while (current != NULL)
    {
        node *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL; // Assegura que o ponteiro original também seja setado como NULL
}



//busca por um elemento
int search(node *head, unsigned char val)
{
    node *i = head;

    while(i != NULL)
    {
        if(i->data == val)
        {
            return 1;
        }

        i = i->next;
    }
    return 0;
}



//busca por um elemento e retorna o index
unsigned char searchIndex(node *head, unsigned char val)
{
    node *i = head;

    while(i != NULL)
    {
        if(i->data == val)
        {
            return i->index;
        }

        i = i->next;
    }
    return 0;
}