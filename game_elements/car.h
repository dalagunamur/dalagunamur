#ifndef _CAR_H_
#define _CAR_H_

#define MAX_SIZE_NAME 20
#define MAX_ENNEMY_COUNT 5

// structure de cours

int ennemyCounter;

struct car{
	char name[MAX_SIZE_NAME];
	int healthPoints;
	struct car * next;
};

typedef struct car * pCar;

// functions handling with the chained list of cars
pCar createCar(void);
void addCar(pCar * list, pCar * newElement);
void removeCar(pCar * list, pCar * elementToRemove);
void displayCar(pCar list);


// functions related to game features and impacting cars
void damageAllCars(pCar * list);

#endif

/*

#ifndef _CAR_H_
#define _CAR_H_
typedef struct car{
     int pos_x;
int pos_y;
int status; // cars will by default be MOVING, but can become FROZEN if hit by the special attack
int hp; // cars will have 1 health point, until the game reaches a certain difficulty level
     car_t *next_element;
} car_t;
car_t create_car(); // to create a new instance of a car
void move_car(car_t *car);
void car_fires(car_t *car);
void car_hit(); // when the car is hit by the main weapon
void car_hit_alt(); // when the car is hit by the alternate weapon, it is frozen
void destroy_car(car_t *car);
#endif
*/
