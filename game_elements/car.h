#ifndef _CAR_H_
#define _CAR_H_

// structures created to handle cars and list of cars
struct car{
    float pos_x;
    float pos_y;
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

// this function creates a new car as a pointer to struct car, it is called each time a new car has to be created. When creating a new car in game, the value loadedCar is set to 0 and the other attributes are 0 as well. When the value loadedCar is set to 1, then it means the car is created while loading a saved game; the other attributes then store the coordinates x, y of the car, its number of health points and the active status of the car.
pCar createCar(int loadedCar, float x, float y, int active, int hp);
void addCar(pCarList list, pCar newCar); // adds a newly created car to the chained list of all cars, as new head of the list
void destroyCars(pCarList list); // remove all inactive cars from the list of cars to display on screen
void moveCars(pCarList list); // make all the cars move one row down
void carHit(pCar car); // this function is called whenever a car is hit by a missile shot from the player. It reduces its health by 1 and if the health drops to 0, the car is deactivated
void setInactiveAllCars(pCarList list); // this function sets all active cars as inactive. It is called along with the destroyCars() function when killing a game.

// NOT IMPLEMENTED YET
void carHitAlt(pCar car);


#endif
