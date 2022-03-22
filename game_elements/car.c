#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "car.h"

pCar createCar(void){
	pCar car;
	ennemyCounter++;
	car = (pCar) malloc (sizeof(struct car));	
	sprintf((*car).name,"Bot %d",ennemyCounter);

	(*car).healthPoints=(rand()%5)+1;
	
	(*car).next=NULL;
	
	return car;
}

void addCar(pCar *liste, pCar *newElement){
	(**newElement).next = *liste;
	*liste = *newElement;
}

void displayCar(pCar list){
	while (list != NULL){
		printf("%s - %i HP\n",(*list).name,(*list).healthPoints);
		list = (*list).next;
	}
}

void removeCar(pCar * list, pCar * elementToRemove){
	pCar temp = *list;
	if(temp == *elementToRemove){ // if the element to remove is the first of the list
		if(temp->next == NULL){ // and if it is the only one in the list, then there are no more ennemies to maintain
			list = NULL;
		}
		else{
			list = &temp->next; // if there's still at least one extra element in the list, the head of the list is now the second item
		}
	}
	else{	// if the element to remove is not the first one
		while (temp->next != *elementToRemove){ // as long as the next element is not the one to delete, jump to the next element
			temp = temp->next;
		}
		temp->next=temp->next->next; // the next element of the current (ie, the one before the element to delete), now points to the next of the one to delete
	}
	
	ennemyCounter--;
	free(*elementToRemove); // in any case, free memory allocation of the item to delete
}

void damageAllCars(pCar * list){
	pCar tempItem;
		tempItem = *list;
		while (tempItem != NULL){
			(*tempItem).healthPoints--;
			if((*tempItem).healthPoints==0){
				printf("\n%s has now %i HP and is dead.\n",(*tempItem).name,(*tempItem).healthPoints);
				pCar tt = tempItem;
				removeCar(list,&tt);
			}
			tempItem = (*tempItem).next;
		}
}
