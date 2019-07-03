// NIE Y0025435B PASKER GONZÁLEZ, SEBASTIAN

#include <iostream>
#include <vector>

using namespace std;


const int MIN_CONTAINER_VALUE = 100;
const int MIN_CONTAINER_WEIGHT = 100;
const int MIN_SHIP_CONTAINERS = 5;
const int MIN_SHIP_WEIGHT = 500;

const string ENTER_WEIGHT = "Container weight:";
const string ENTER_VALUE = "Container value:";
const string ENTER_CONTAINER_ID = "Container id:";
const string ENTER_MAX_CONTAINERS = "Ship max. containers:";
const string ENTER_MAX_WEIGHT_S = "Ship max. weight:";
const string ENTER_SHIP_NAME = "Ship name:";

int idAsigner = 1;


struct Container
{
  unsigned int id;
  unsigned int weight;
  unsigned int value;
};

struct Ship
{
  string name;
  unsigned int weight;
  unsigned int value;
  unsigned int maxWeight;
  unsigned int maxContainers;
  vector<Container> containers;
};

struct Base
{
  string name;
  vector<Container> containers;
  vector<Ship> ships;
};

enum Error
{
  ERR_MENU_OPTION,
  ERR_CONTAINER_WEIGHT,
  ERR_CONTAINER_VALUE,
  ERR_CONTAINER_ID,
  ERR_SHIP_NAME,
  ERR_SHIP_MAXCONTAINERS,
  ERR_SHIP_MAXWEIGHT,
  ERR_SHIP_NO_MORE_CONTAINERS,
  ERR_SHIP_NO_MORE_WEIGHT
};

void error(Error n) // Error print in each case
{
  switch (n)
  {
    case ERR_MENU_OPTION:
      cout << "Error: unknown menu option" << endl;
      break;

    case ERR_CONTAINER_WEIGHT:
      cout << "Error: container weight is below minimum" << endl;
      break;

    case ERR_CONTAINER_VALUE:
      cout << "Error: container value is below minimum" << endl;
      break;

    case ERR_CONTAINER_ID:
      cout << "Error: wrong container id" << endl;
      break;

    case ERR_SHIP_NAME:
      cout << "Error: wrong ship name" << endl;
      break;

    case ERR_SHIP_MAXCONTAINERS:
      cout << "Error: wrong maximum number of containers" << endl;
      break;

    case ERR_SHIP_MAXWEIGHT:
      cout << "Error: wrong maximum weight" << endl;
      break;

    case ERR_SHIP_NO_MORE_CONTAINERS:
      cout << "Error: ship cannot carry more containers" << endl;
      break;

    case ERR_SHIP_NO_MORE_WEIGHT:
      cout << "Error: ship cannot not hold more containers" << endl;
      break;
  }
}

void printContainer(const Container &c) // Called by printBase & printShip
{
    cout << "[" << c.id << " " << c.weight << ":" << c.value << "]";
}

void printShip(const Ship &s) // Called by printBase
{
    float i;
    
    cout << "{" << s.name << ": ";
    cout << s.weight << " (" << s.maxWeight << "), ";
    cout << s.containers.size() << " (" << s.maxContainers << "), ";
    cout << s.value << endl;
    
    for(i=0; i < s.containers.size(); i++){ 
        printContainer(s.containers[i]); // Prints containers inside the ship
    }
    cout << endl << "}";
}

void printBase(const Base &b) 
{
    float i;
    
    cout << "Name: " << b.name << endl << "Containers:" << endl;
    
    for(i=0; i < b.containers.size(); i++){
        printContainer(b.containers[i]); // Prints containers inside the base
        cout << endl;
    }
    
    cout << endl;
    cout << "Ships:" << endl;
    
    for(i=0; i < b.ships.size(); i++){
        printShip(b.ships[i]); // Prints ships inside the base
        cout << endl;
    }
    cout << endl;
}

void addContainer(Base &b)
{
    Container newC; 

    cout << ENTER_WEIGHT;
    cin >> newC.weight;

                                              // Actual min weight = 100
    if(newC.weight < MIN_CONTAINER_WEIGHT){   // Returns to menu in case of error
        error(ERR_CONTAINER_WEIGHT);
        return;
    }

    cout << ENTER_VALUE;
    cin >> newC.value;
                                              // Actual min value = 100
    if(newC.value < MIN_CONTAINER_VALUE){
        error(ERR_CONTAINER_VALUE);
        return;
    }
    
    newC.id = idAsigner;
    
    b.containers.push_back(newC);
    
    idAsigner++;
    
}

void searchContainer(Base &b,unsigned int &idSearch, int &idPosition){
    float i;
    
    for(i=0; i < b.containers.size(); i++){ /* Search inserted number (idSearch)
                                             in base containers register */
        if(b.containers[i].id == idSearch){
            idPosition = i;
        }
    }
}

void searchShip( Base &b, string &shipName, bool &shipFound, float &shipNum){
    float i = 0;

    for(i=0; i < b.ships.size(); i++){       /* Search introduced name
                                                in ships of base */
        if(b.ships[i].name == shipName){
            shipFound = true;
            shipNum = i;                    // Ship number in base register
        }
    }

}

void removeContainer(Base &b)
{
  int idPosition = -1;
  unsigned int  idSearch;
  
  cout << ENTER_CONTAINER_ID;
  cin >> idSearch;

  searchContainer(b, idSearch, idPosition);
  
  if(idPosition == -1){ // Returns to menu and prints container id error
    error(ERR_CONTAINER_ID);
    return;
  }
    
    b.containers.erase( b.containers.begin()+idPosition ); // Eliminate founded container

}

void addShip(Base &b)
{
  Ship s;
  bool shipRepeat = false;
  float i;

  cout << ENTER_SHIP_NAME;
  getline(cin, s.name); // Data introduction for no repition verification
    
  for(i=0; i < b.ships.size(); i++){ // Search name repetition
    if(s.name == b.ships[i].name){
      shipRepeat = true;
    }
  }

  if(shipRepeat == true){ // Returns to menu and prints error
    error(ERR_SHIP_NAME);
    return;
  }

  cout << ENTER_MAX_CONTAINERS;
  cin >> s.maxContainers; // Ship characteristics

  if(s.maxContainers < MIN_SHIP_CONTAINERS){
    error(ERR_SHIP_MAXCONTAINERS);
    return;
  }
  
  cout << ENTER_MAX_WEIGHT_S;
  cin >> s.maxWeight;
  
  if(s.maxWeight < MIN_SHIP_WEIGHT){
    error(ERR_SHIP_MAXWEIGHT);
    return;
  }
  
  s.weight = 0;
  s.value = 0;
  
  b.ships.push_back(s); // Base addition
}

void containerReturnToBase (Base &b, float &shipNum){
    Container toBase;
    Ship shipReference;
    float i;
    
    shipReference = b.ships[shipNum];
    
    for(i=0; i < shipReference.containers.size(); i++){ // Ship to Base transmission
        toBase = shipReference.containers[i];
        b.containers.push_back(toBase);
    }
}

void removeShip(Base &b)
{
    string nameSearch;
    float shipNum;
    bool shipFound = false;
    
    cout << ENTER_SHIP_NAME;
    getline(cin, nameSearch); 
    
    searchShip(b, nameSearch, shipFound, shipNum);
    
    if(!shipFound){
        error(ERR_SHIP_NAME);
        return;
    }
    
    containerReturnToBase(b, shipNum);
    
    b.ships.erase( b.ships.begin()+shipNum ); // Ship elimination from base
    
}

void manualDistribution(Base &b)
{
    Container c;
    Ship s;
    bool shipFounded = false;
    float shipNum;
    int idPosition = -1;        // Position in ships & containers vector
    unsigned int searchId;
    
    cout << ENTER_CONTAINER_ID;
    cin >> searchId;                         
    
    searchContainer(b, searchId, idPosition);
    
    if(idPosition == -1){ // Returns to menu and print error
        error(ERR_CONTAINER_ID);
        return;
    }
    
    cin.ignore();
    
    cout << ENTER_SHIP_NAME;
    getline(cin, s.name);
    
    searchShip(b, s.name, shipFounded, shipNum);

    if(!shipFounded){
        error(ERR_SHIP_NAME);
        return;
    }
        
    if(b.ships[shipNum].maxContainers == b.ships[shipNum].containers.size()){ 
                                            /* no more space in 
                                              actual searched ship */
        error(ERR_SHIP_NO_MORE_CONTAINERS);
        return;
    }
    
    if(b.ships[shipNum].weight + b.containers[idPosition].weight > b.ships[shipNum].maxWeight){ 
        error(ERR_SHIP_NO_MORE_WEIGHT);
        return;
    }                                        // Case container addition surpass ship max weight
    c = b.containers[idPosition];
    
    b.containers.erase( b.containers.begin()+idPosition );        // Eliminate container in base
    
    b.ships[shipNum].containers.push_back(c);                     // Add container in introduced ship
    b.ships[shipNum].weight = b.ships[shipNum].weight + c.weight; // Add container weight to ship weight
    b.ships[shipNum].value = b.ships[shipNum].value + c.value;
}


void containerChoice(Base &b, float &posMaxValue)
{
    Container c;
    float i;
    float maxValueFound = 0;
    
    if(b.containers.size() == 0)
        return;

    for(i=0; i< b.containers.size(); i++){
        c = b.containers[i];   // Container traspass > clarity

        if(c.value == maxValueFound){                            // Chose > weight when there same values
            if(c.weight < b.containers[posMaxValue].weight){
                posMaxValue = i;
                maxValueFound = c.value;
               
            }
        } // Case same weight stays with < position
        else if(c.value > maxValueFound){
            posMaxValue = i;
            maxValueFound = b.containers[i].value;
        }
    }
}

void shipChoice(Base &b,float &shipPos, float &containerPos, bool &containerDiv){
    
    Ship s;
    float i;
    float minValue = -1;
    bool firstEntry = true;
    
    if(b.ships.size() == 0 || containerPos == -1){ // No ship or no containers in base
        return;
    }

    for(i = 0; i < b.ships.size(); i++){
        s = b.ships[i];
        if(s.weight + b.containers[containerPos].weight <= s.maxWeight &&
            s.containers.size() < s.maxContainers){
            
            // Not superation of max weight & containers verification
            containerDiv = false;
        
            if(s.value == minValue){ // In case same value chose first position
                continue;
            }
            else if(firstEntry == true){
                minValue = s.value;
                shipPos = i;
                firstEntry = false;
            }
            else if(s.value < minValue){
                minValue = s.value;
                shipPos = i;
            }
        }
        else if(s.weight != s.maxWeight && s.containers.size() != s.maxContainers &&
         minValue == -1 && b.containers[containerPos].weight/2 >= MIN_CONTAINER_WEIGHT &&
          b.containers[containerPos].weight/2 >= MIN_CONTAINER_VALUE){ /*  min weight and containers comprobation, not another ship founded
                                                                           and container division lower min value and weight comprobation */
             containerDiv = true;
        }
    }
        
}

void containerDivision(Base &b, float &shipPos, float &containerPos, bool &finishDistribution){
    
    Container c1, c2;
    
    c1 = b.containers[containerPos];
    c2 = b.containers[containerPos];                  // One container to two container division 
     
    if(b.containers[containerPos].weight%2 == 1){     // Odd division, no decimal numbers
        c1.weight = c1.weight/2;
        c2.weight = c2.weight/2+1;
    }
    else{                                            // Even division
        c1.weight = c1.weight/2;
        c2.weight = c2.weight/2;
    }
    
    if(b.containers[containerPos].value%2 == 1){
        c1.value = c1.value/2;
        c2.value = c2.value/2+1;
    }
    else{
        c1.value = c1.value/2;
        c2.value = c2.value/2;
    }

    if(c1.weight < MIN_CONTAINER_WEIGHT || c2.weight < MIN_CONTAINER_WEIGHT ||
        c1.value < MIN_CONTAINER_VALUE || c2.value < MIN_CONTAINER_VALUE){ 

                                    // Weight & value error comprobation with each divided container
        finishDistribution = true; // Stop algorithm
        return;
    }

    
    c1.id = idAsigner;
    idAsigner++;
    
    c2.id = idAsigner;
    idAsigner++;
    
    b.containers.erase( b.containers.begin() + containerPos ); // Primary container elimination
    
    b.containers.push_back(c1);
    b.containers.push_back(c2);                                // New containers addition
    
}

void automaticDistribution(Base &b)
{
    Container c;
    float containerPos, shipPos;
    bool finishDistribution = false, containerDiv = false;
    
    while(finishDistribution == false){
        containerPos = -1;
        shipPos = -1;
        containerChoice(b, containerPos);
        shipChoice(b, shipPos, containerPos, containerDiv); // Search container, ship and container division verification

        if(shipPos != -1 && containerDiv == false){ // Add container to ship
                c = b.containers[containerPos];
                
                b.ships[shipPos].weight = b.ships[shipPos].weight + c.weight;
                b.ships[shipPos].value = b.ships[shipPos].value + c.value; // Add container values to ship
            
                b.ships[shipPos].containers.push_back( c );
                b.containers.erase( b.containers.begin() + containerPos ); // Container transmission
            
        }
        else if(containerDiv == true){ // Divide actual container
            containerDiv = false;
            containerDivision(b, shipPos, containerPos, finishDistribution);
        }
        else if(shipPos == -1){         // No container or No ship found = finishProgram
            finishDistribution = true;
        }
    }
    
}

void menu()
{
  cout << "1- Info base" << endl
       << "2- Add container" << endl
       << "3- Remove container" << endl
       << "4- Add ship" << endl
       << "5- Remove ship" << endl
       << "6- Manual distribution" << endl
       << "7- Automatic distribution" << endl
       << "q- Quit" << endl
       << "Option: " ;
}


int main()
{
   Base base;

   base.name = "Logistic Center";
   char option;

   do
   {
        menu();
        cin >> option; cin.get();
        switch (option) {
          case '1': {
            printBase(base);
            break;
          }
          case '2':
          {
            addContainer(base);
            break;
          }
          case '3':
          {
            removeContainer(base);
            break;
          }
          case '4':
          {
            addShip(base);
            break;
          }
          case '5':
          {
            removeShip(base);
            break;
          }
          case '6':
          {
            manualDistribution(base);
            break;
          }
          case '7':
          {
            automaticDistribution(base);
            break;
          }
          case 'q': {
            break;
          }
          default:  {
            error(ERR_MENU_OPTION);
            break;
          }
        }
   } while(option != 'q');

   return 0;
}
