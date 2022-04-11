#ifndef _CAR_H_
#define _CAR_H_

// structures created to handle cars and list of cars
struct car{
    int pos_x;
    int pos_y;
	int healthPoints;
    bool carFrozen; // cars will by default be moving (=false), but can become frozen (=true) if hit by the special attack of the player
    bool carActive; // an inactive car means it must be deleted from the game, as it either reached the botton of the screen or lost all its health points
    struct car * previousCar;
    struct car * nextCar;
};

// pCar points to a car
typedef struct car * pCar;

// the car list structure will be used to store the head and the tail of the chained list of all cars. It also contains a counter indicating how many cars are present on screen at any time
struct carList{
    int carCounter;
    pCar firstCar;
    pCar lastCar;
};

//pCarList points to carList
typedef struct carList * pCarList;

pCarList listOfCars; // this global variable is used to store the list of the cars.

pCarList createCarList(void); // this function creates a list of cars as a pointer to struct carList. It is called when initializing the game
pCar createCar(void); // this function creates a new car as a pointer to struct car, it is called each time a new car has to be created
void addCar(pCarList list, pCar newCar); // adds a newly created car to the chained list of all cars, as new head of the list
void destroyCars(pCarList list); // remove all inactive cars from the list of cars to display on screen
void moveCars(pCarList list); // make all the cars move one row down

void glutCreateCars(int timer); // calls the functions related to the creation of a new car following a given timer, and handles the callback via glutTimerFunc()
void glutMoveCars(int timer); // calls the functions related to the movement of the cars following a given timer, and handles the callback via glutTimerFunc()
void glutDestroyCars(int timer); // calls the functions related to the destruction of all inactive cars following a given timer, and handles the callback via glutTimerFunc()
void carHit(pCar car); // this function is called whenever a car is hit by a missile shot from the player. It reduces its health by 1 and if the health drops to 0, the car is deactivated

// NOT IMPLEMENTED YET
void carHitAlt(pCar car);


#endif
