
#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>

using namespace std;

const int MIN_CONTAINER_VALUE = 100;
const int MIN_CONTAINER_WEIGHT = 100;
const int MIN_SHIP_CONTAINERS = 5;
const int MIN_SHIP_WEIGHT = 500;
const int MAXNAME = 20;

const string ENTER_WEIGHT = "Container weight: ";
const string ENTER_VALUE = "Container value: ";
const string ENTER_CONTAINER_ID = "Container id: ";
const string ENTER_MAX_CONTAINERS = "Ship max. containers: ";
const string ENTER_MAX_WEIGHT_S = "Ship max. weight: ";
const string ENTER_SHIP_NAME = "Ship name: ";
const string ENTER_FILE_NAME = "Enter filename: ";
const string ENTER_CONFIRM = "Confirm? (y/n): ";

int idAsigner = 1;


struct Container {
  unsigned int id;
  unsigned int weight;
  unsigned int value;
};

struct Ship {
  string name;
  unsigned int weight;
  unsigned int value;
  unsigned int maxWeight;
  unsigned int maxContainers;
  vector<Container> containers;
};

struct Base {
  string name;
  vector<Container> containers;
  vector<Ship> ships;
};

struct BinShip {
  char name[MAXNAME];
  unsigned int weight;
  unsigned int value;
  unsigned int maxWeight;
  unsigned int maxContainers;
  unsigned int numContainers;
};

struct BinBase {
  char name[MAXNAME];
  unsigned int numContainers;
  unsigned int nextId;
};

enum Error {
  ERR_MENU_OPTION, 
  ERR_CONTAINER_WEIGHT,
  ERR_CONTAINER_VALUE,
  ERR_CONTAINER_ID,
  ERR_SHIP_NAME,
  ERR_SHIP_MAXCONTAINERS,
  ERR_SHIP_MAXWEIGHT,
  ERR_SHIP_NO_MORE_CONTAINERS,
  ERR_SHIP_NO_MORE_WEIGHT,
  ERR_CANT_OPEN_FILE,
  ERR_ARGS
}; 

void error(Error n) {
  switch (n) {
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

    case ERR_CANT_OPEN_FILE:
      cout << "Error: can't open file" << endl;
      break;

    case ERR_ARGS:
      cout << "Error: wrong arguments" << endl;
  }
}

void printContainer(const Container &c) {               // Called by printBase & printShip
    cout << "[" << c.id << " " << c.weight << ":" << c.value << "]";
}

void printShip(const Ship &s) {                             // Called by printBase
    float i;
    
    cout << "{" << s.name << ": ";
    cout << s.weight << " (" << s.maxWeight << "), ";
    cout << s.containers.size() << " (" << s.maxContainers << "), ";
    cout << s.value << endl;
    
    for(i=0; i < s.containers.size(); i++){ 
        printContainer(s.containers[i]);                   // Prints containers inside the ship
    }
    cout << endl << "}";
}

void printBase(const Base &b) {
    float i;
    
    cout << "Name: " << b.name << endl << "Containers:" << endl;
    
    for(i=0; i < b.containers.size(); i++){
        printContainer(b.containers[i]);                  // Prints containers inside the base
        cout << endl;
    }
    
    cout << endl;
    cout << "Ships:" << endl;
    for(i=0; i < b.ships.size(); i++) {
        printShip(b.ships[i]);                            // Prints ships inside the base
        cout << endl;
    }

    cout << endl;
}

void addContainer(Base &b) {
    Container newC; 

    cout << ENTER_WEIGHT;
    cin >> newC.weight;
                                                          // Actual min weight = 100
    if(newC.weight < MIN_CONTAINER_WEIGHT){                // Returns to menu in case of error
      error(ERR_CONTAINER_WEIGHT);
        
    } else {
      cout << ENTER_VALUE;
      cin >> newC.value;
                                                            // Actual min value = 100
      if(newC.value < MIN_CONTAINER_VALUE){
        error(ERR_CONTAINER_VALUE);

      } else {
        newC.id = idAsigner;
        b.containers.push_back(newC);
        idAsigner++;
    }
  }
}

int searchContainer(Base &b,unsigned int idSearch) {
  float i;
  int idPosition = -1;

  for(i=0; i < b.containers.size(); i++){                   /* Search inserted number (idSearch)
                                                               in base containers register */
    if(b.containers[i].id == idSearch) {
      idPosition = i;
    }
  }
  return idPosition;
}



float searchShip(Base &b, string shipName) {
  float i = 0;
  float shipNum = -1;

  for(i=0; i < b.ships.size(); i++){                         /* Search introduced name
                                                                 in ships of base */
    if(b.ships[i].name == shipName){
      shipNum = i;                                         // Ship number in base register
    }
  }
  return shipNum;
}

int searchContainerinShip(Base &b, unsigned int idSearch, float shipNum) {
  float i;
  int idPosition = -1;

  for(i=0; i < b.ships[shipNum].containers.size(); i++){ /* Search inserted number (idSearch)
                                                              in base containers register */
    if(b.ships[shipNum].containers[i].id == idSearch){
      idPosition = i;
    }
  }
  return idPosition;
}

void removeContainer(Base &b) {
  int idPosition = -1;
  unsigned int  idSearch;
  
  cout << ENTER_CONTAINER_ID;
  cin >> idSearch;

  idPosition = searchContainer(b, idSearch);
  
  if(idPosition == -1){                                    // Returns to menu and prints container id error
    error(ERR_CONTAINER_ID);
  } else {
    b.containers.erase( b.containers.begin()+idPosition ); // Eliminate founded container
  }
}


void addShip(Base &b) {
  Ship s;
  float shipRep = -1;

  cout << ENTER_SHIP_NAME;
  getline(cin, s.name);                                   // Data introduction for no repition verification

 shipRep = searchShip(b, s.name);

  if(shipRep != -1){                                      // Returns to menu and prints error
    error(ERR_SHIP_NAME);

  } else {
    cout << ENTER_MAX_CONTAINERS;
    cin >> s.maxContainers;                              // Ship characteristics

    if(s.maxContainers < MIN_SHIP_CONTAINERS) {
      error(ERR_SHIP_MAXCONTAINERS);

    } else {
      cout << ENTER_MAX_WEIGHT_S;
      cin >> s.maxWeight;
  
      if(s.maxWeight < MIN_SHIP_WEIGHT) {
      error(ERR_SHIP_MAXWEIGHT);
      } else {
        s.weight = 0;
        s.value = 0;
        b.ships.push_back(s);                           // Base addition
      }
    }
  }
}

void containerReturnToBase (Base &b, float &shipNum) {
  Container toBase;
  Ship shipReference;
  float i=0;

  shipReference = b.ships[shipNum];
    
  while(b.ships[shipNum].containers.size() > 0){     // Ship to Base transmission
    toBase = shipReference.containers[i];
    b.containers.push_back(toBase);
    b.ships[shipNum].containers.erase(b.ships[shipNum].containers.begin());
    i++;
  }
  b.ships[shipNum].weight = 0;
  b.ships[shipNum].value = 0;
}

void removeShip(Base &b) {
    string nameSearch;
    float shipNum;
    
    cout << ENTER_SHIP_NAME;
    getline(cin, nameSearch);

    shipNum = searchShip(b, nameSearch);
    
    if(shipNum == -1) {
        error(ERR_SHIP_NAME);

    } else { 
    containerReturnToBase(b, shipNum);
    b.ships.erase( b.ships.begin()+shipNum );        // Ship elimination from base
  }
}

void manualDistribution(Base &b) {
    Container c;
    Ship s;
    float shipNum;
    int idPosition = -1;                            // Position in ships & containers vector
    unsigned int searchId;
                          
    
    cout << ENTER_CONTAINER_ID;
    cin >> searchId;

    idPosition = searchContainer(b, searchId);
    
    if(idPosition == -1){                           // Returns to menu and print error
        error(ERR_CONTAINER_ID);
        return;
    }
    
    cin.ignore();

    cout << ENTER_SHIP_NAME;
    getline(cin, s.name);
    
    shipNum = searchShip(b, s.name);

    if(shipNum == -1) {
        error(ERR_SHIP_NAME);
        return;
    } else {
        
      if(b.ships[shipNum].maxContainers == b.ships[shipNum].containers.size()) { 
                                                    /* no more space in 
                                                      actual searched ship */
        error(ERR_SHIP_NO_MORE_CONTAINERS);
      } else {
        if(b.ships[shipNum].weight + b.containers[idPosition].weight > b.ships[shipNum].maxWeight) { 
          error(ERR_SHIP_NO_MORE_WEIGHT);
          
        } else {                                                      // Case container addition surpass ship max weight
        c = b.containers[idPosition];
        b.containers.erase( b.containers.begin()+idPosition );        // Eliminate container in base
    
        b.ships[shipNum].containers.push_back(c);                     // Add container in introduced ship
        b.ships[shipNum].weight = b.ships[shipNum].weight + c.weight; // Add container weight to ship weight
        b.ships[shipNum].value = b.ships[shipNum].value + c.value;
      }
    }
  }
}


void containerChoice(Base &b, float &posMaxValue) {
  Container c;
  float i;
  float maxValueFound = 0;

  for(i=0; i< b.containers.size(); i++){
    c = b.containers[i];                                     // Container traspass > clarity

    if(c.value == maxValueFound){                            // Chose > weight when there same values
      if(c.weight < b.containers[posMaxValue].weight) {
        posMaxValue = i;
        maxValueFound = c.value;
      } // Case same weight stays with < position
    } else if(c.value > maxValueFound) {
        posMaxValue = i;
        maxValueFound = b.containers[i].value;
    }
  }
}

void shipChoice(Base &b,float &shipPos, float &containerPos, bool &containerDiv) {
  
  Ship s;
  float i;
  float minValue = -1;
  bool firstEntry = true;
  
  if(containerPos != -1){                                              // No ship or no containers in base
    for(i = 0; i < b.ships.size(); i++) {
      s = b.ships[i];
      if(s.weight + b.containers[containerPos].weight <= s.maxWeight &&
        s.containers.size() < s.maxContainers) {
          // Not superation of max weight & containers verification
          containerDiv = false;
      
        if(s.value == minValue) {                                     // In case same value chose first position
          continue;
        } else if(firstEntry == true) {
          minValue = s.value;
          shipPos = i;
          firstEntry = false;
        } else if(s.value < minValue) {
          minValue = s.value;
          shipPos = i;
        }
      } else if(s.weight != s.maxWeight && s.containers.size() != s.maxContainers &&
        minValue == -1 && b.containers[containerPos].weight/2 >= MIN_CONTAINER_WEIGHT &&
        b.containers[containerPos].value/2 >= MIN_CONTAINER_VALUE) { /*  min weight and containers comprobation, not another ship founded
                                                                         and container division lower min value and weight comprobation */
        containerDiv = true;
      } 
    }
  }
}

void containerDivision(Base &b, float &shipPos, float &containerPos, bool &finishDistribution) {
  
  Container c1, c2;
  
  c1 = b.containers[containerPos];
  c2 = b.containers[containerPos];                            // One container to two container division 
   
  if(b.containers[containerPos].weight%2 == 1) {              // Odd division, no decimal numbers
    c1.weight = c1.weight/2;
    c2.weight = c2.weight/2+1;
  } else {                                                   // Even division
    c1.weight = c1.weight/2;
    c2.weight = c2.weight/2;
  }
  
  if(b.containers[containerPos].value%2 == 1) {
    c1.value = c1.value/2;
    c2.value = c2.value/2+1;
  } else {
    c1.value = c1.value/2;
    c2.value = c2.value/2;
  }

  if(c1.weight < MIN_CONTAINER_WEIGHT || c2.weight < MIN_CONTAINER_WEIGHT ||
    c1.value < MIN_CONTAINER_VALUE || c2.value < MIN_CONTAINER_VALUE) { 
                                                          // Weight & value error comprobation with each divided container
    finishDistribution = true;                            // Stop algorithm
    
  } else {

    c1.id = idAsigner;
    idAsigner++;
  
    c2.id = idAsigner;
    idAsigner++;
  
    b.containers.erase( b.containers.begin() + containerPos ); // Primary container elimination
  
    b.containers.push_back(c1);
    b.containers.push_back(c2);                                // New containers addition
  }
}

void automaticDistribution(Base &b) {
  Container c;
  float containerPos, shipPos;
  bool finishDistribution = false, containerDiv = false;

  while(finishDistribution == false) {
    containerPos = -1;
    shipPos = -1;
    containerChoice(b, containerPos);
    shipChoice(b, shipPos, containerPos, containerDiv);         // Search container, ship and container division verification

  if(shipPos != -1 && containerDiv == false) {                // Add container to ship
    c = b.containers[containerPos];
    
    b.ships[shipPos].weight = b.ships[shipPos].weight + c.weight;
    b.ships[shipPos].value = b.ships[shipPos].value + c.value; // Add container values to ship

    b.ships[shipPos].containers.push_back( c );
    b.containers.erase( b.containers.begin() + containerPos ); // Container transmission
      
    } else if(containerDiv == true) {                           // Divide actual container
      containerDiv = false;
      containerDivision(b, shipPos, containerPos, finishDistribution);
    } else if(shipPos == -1) {                                  // No container or No ship found = finishProgram
      finishDistribution = true;
    }
  } 
}


void unassignContainer(Base &b) {
  string shipName;
  float shipNum;
  int idPosition = -1;
  unsigned int idSearch = 0;
  Container c;

  cout << ENTER_SHIP_NAME;
  getline(cin, shipName);

  shipNum = searchShip(b, shipName);
                                                                   // Search ship from base && return to menu
  if(shipNum == -1) {
    error(ERR_SHIP_NAME);

  } else {

    cout << ENTER_CONTAINER_ID;
    cin >> idSearch;

    idPosition = searchContainerinShip(b, idSearch, shipNum);     // Search container from ship

    if(idPosition == -1) {
      error(ERR_CONTAINER_ID);
      
    } else {
      c = b.ships[shipNum].containers[idPosition];              
      b.containers.push_back(c);
      b.ships[shipNum].containers.erase( b.ships[shipNum].containers.begin()+idPosition );
      b.ships[shipNum].value -= c.value;
      b.ships[shipNum].weight -= c.weight;
    }                                                             // Send container from ship to base
  }
}

// Return al containers from ship to base
void clearAssignations(Base &b) {
  Ship s;
  float i=0;

  for(i=0; i<b.ships.size(); i++) {
    containerReturnToBase(b, i);
  }
}

// Search X number in string
int importValueNum(string fileline, bool &notTerminated,unsigned int &j, int actualNum) {
  int importNum;
  unsigned int i;

  importNum = actualNum;

  for(i=j; i<fileline.size() && notTerminated == true; i++) {
    if(fileline[i] >= '0' && fileline[i] <= '9'){
      importNum = importNum*10 + (fileline[i] - '0');
    } else if(fileline[i] == ',' || fileline[i] == ']' || fileline[i] == ':' || fileline[i] == ')') {
     notTerminated = false;
    }
  }

  j=i-1;

  return importNum;
}

// Search "X" name in string
string importValueString(string fileline, bool &notTerminated, unsigned int &j, string actualString){
  string importString;
  bool startName = false;
  unsigned int i;

  importString = actualString;
 
  for(i=j; i<fileline.size() && notTerminated == true; i++) {
    if(fileline[i] == '"' && startName == true) {                             // Finish name search & copy
      notTerminated = false;
    } else if(fileline[i] == '"' && startName == false) {
      startName = true;
    } else if(startName == true){
      importString += fileline[i];
    }
  }

  j=i-1;                                                                      // Save actual position
  
  return importString;

}

void importFinishComprobation(bool &notTerminated, int &process) {
  string numNOterminated;

  if (notTerminated == false && process == 1) {                                  // C. weight --> value
    process = 2;
    notTerminated = true;
  } else if(notTerminated == false && process == 2) {                            // Finish container search
    process = 0;
  } else if (notTerminated == false && process == 3) {                           // S. name --> maxWeight
    process = 4;
    notTerminated = true;
  } else if (notTerminated == false && process == 4) {                           // S. maxWeight --> maxContainers
    process = 5;
    notTerminated = true;
  } else if (notTerminated == false && process == 5) {                           // Finish ship search
    process = 0;
  }
}

void evaluateContainer(Base &b, Container &c) {

  if(c.weight < MIN_CONTAINER_WEIGHT) { 
    error(ERR_CONTAINER_WEIGHT);
  }
  if(c.weight < MIN_CONTAINER_VALUE) {
    error(ERR_CONTAINER_VALUE);
  }
  if(c.value >= MIN_CONTAINER_VALUE && c.weight >= MIN_CONTAINER_WEIGHT) {
    c.id = idAsigner;
    idAsigner++;
    b.containers.push_back(c);
  }
}

void evaluateShip(Base &b, Ship &s) {
  int namerepetition;

  namerepetition = searchShip(b, s.name);

  if(namerepetition != -1) {
    error(ERR_SHIP_NAME);
  }
  if(s.maxContainers < MIN_SHIP_CONTAINERS) {
    error(ERR_SHIP_MAXCONTAINERS);
  }
  if(s.maxWeight < MIN_SHIP_WEIGHT) {
    error(ERR_SHIP_MAXWEIGHT);
  }
  if(namerepetition == -1 && s.maxWeight >= MIN_SHIP_WEIGHT && s.maxContainers >= MIN_SHIP_CONTAINERS) {
    b.ships.push_back(s);
  }
  
}

void importProcessController(Base &b, int &process, string &fileline,unsigned int &j, Container  &c, Ship &s, bool &notTerminated) {
  unsigned int i;

  for(i=j; i<fileline.size() && process != 0; i++){
    if(process == 1) { // Initialize container & saves container value 
      notTerminated = true;
      c.weight = importValueNum(fileline, notTerminated, i, c.weight);           // Search numeric value in text
      importFinishComprobation(notTerminated, process);                         // Check search finished and change process

    } else if(process == 2) {                                          // Saves container weight and transfer container to base
      c.value = importValueNum(fileline,notTerminated, i, c.value); 
      importFinishComprobation(notTerminated, process);
      if(notTerminated == false) {
        evaluateContainer(b, c);
      } // Error comprobation & container transfer

    } else if(process == 3) {                                                        // Initialize ship & saves ship name 
      notTerminated = true;
      s.name = importValueString(fileline,notTerminated, i, s.name);                   // Search string value in text
      importFinishComprobation(notTerminated, process);                                // Check search finished and change process

    } else if(process == 4) {                                                       // Saves ship maxWeight
      s.maxWeight = importValueNum(fileline,notTerminated, i, s.maxWeight);
      importFinishComprobation(notTerminated, process);

    } else if(process == 5) {                                             // Saves ship maxContainers & transfer ship to base
      s.maxContainers = importValueNum(fileline,notTerminated, i, s.maxContainers);
      importFinishComprobation(notTerminated, process);

                                                                                    // Error comprobation & ship transfer
      if (notTerminated == false){
        evaluateShip(b, s);
      }
    }
  }

  j=i-1;                                            // (Actual position -1) to importComandController for correct char read

}


void importComandController(Base &b, string fileline, Container &c, Ship &s, bool &notTerminated) {
  int process = 0;      // 1 = C.weight, 2 = C.value,  3 = S.name, 4 = S.maxWeight, 5 = S.maxContainers


  for(unsigned int i=0; i<fileline.size(); i++) {
    if(fileline[i] == 'C' && process == 0){                                 // Start container import
      process = 1;
      c.weight = 0;
      c.value = 0;
    } else if(fileline[i] == 'S' && process == 0) {                          // Start ship import
      process = 3;
      s.weight = 0;
      s.value = 0;
      s.maxWeight = 0;
      s.maxContainers = 0;
      s.name.clear();
    } else if(process != 0) {
      importProcessController(b, process, fileline, i, c, s, notTerminated); // Ship/Container import

    }  
  }
}

void importData(Base &b, string EntranceFile) {
  string filename, fileline;
  Container c;
  Ship s;
  bool notTerminated = true;

  if(EntranceFile.empty()){
    cout << ENTER_FILE_NAME;
    getline(cin, filename);
  } else if(!EntranceFile.empty()) {
    filename = EntranceFile;
  }

  ifstream importfile(filename.c_str());                        // Usuary searched file transfer to code

  if(importfile.is_open()) {
    while(getline(importfile, fileline)) {                      // Save text lines in string
      importComandController(b, fileline, c, s, notTerminated); // Save values and control processes for container or ship
    }

    importfile.close();
  } else {
    error(ERR_CANT_OPEN_FILE);
  }
}

// Translate introduced container in text format
string containerToString(Container c, unsigned int pos) {
  string containerLine;

  containerLine += "C(";
  containerLine += std::to_string(c.weight); 
  containerLine += ",";
  containerLine += std::to_string(c.value);
  containerLine += ")";

  return containerLine;
}

// Translate introduced ship in text format
string shipToString(Ship s, unsigned int pos) {
  string shipLine;

  shipLine += "S[";
  shipLine += '"';
  shipLine += s.name;
  shipLine += '"';
  shipLine += " ";
  shipLine += std::to_string(s.maxWeight);
  shipLine += ":";
  shipLine += std::to_string(s.maxContainers);
  shipLine += "]";

  return shipLine;

} 


void exportData(Base &b) {
  string filename, fileline;
  Container c;
  Ship s;

  cout << ENTER_FILE_NAME;
  getline(cin, filename);

  ofstream exportfile(filename.c_str());

  if(exportfile.is_open()) {

    for(unsigned int i=0; i<b.containers.size(); i++) { // Translate and insert al base containers in file
      c = b.containers[i];
      fileline = containerToString(c, i);             
      exportfile << fileline << endl;                 // Insert container string (from base) format in file 
    }

    for(unsigned int i=0; i<b.ships.size(); i++) {    // Translate and insert al base ships in file
      s = b.ships[i];
      fileline = shipToString(s, i);
      exportfile << fileline << endl;                 // Insert ship string (from base) format in file
      for(unsigned int j=0; j< s.containers.size(); j++) {
        c = s.containers[j];
        fileline = containerToString(c, i);            
        exportfile << fileline << endl;               // Insert container string (from ship) format in file
      }
    }

    exportfile.close();
  } else {
    error(ERR_CANT_OPEN_FILE);
  }
}

void deleteBase(Base &b) {
  unsigned int i=0, SIZE;

  b.name = " ";
  SIZE = b.containers.size();
  for(i=0; i<SIZE; i++) {
    b.containers.erase(b.containers.begin());
  }
  SIZE = b.ships.size();
  for(i=0; i<SIZE; i++) {
    b.ships.erase(b.ships.begin());
  }

}

// Binary ship information to regular ship transmission
Ship BinShiptoShip(BinShip binaryShip) {
  Ship regularShip;

  regularShip.name = binaryShip.name;
  regularShip.weight = binaryShip.weight;
  regularShip.value = binaryShip.value;
  regularShip.maxContainers = binaryShip.maxContainers;
  regularShip.maxWeight = binaryShip.maxWeight;

  return regularShip;
}

void LoadBaseExtraction(Base &b, ifstream &baseFile) {
  BinBase lBinBase;
  BinShip lBinShip;
  Container c;
  Ship s;



  baseFile.seekg(0, ios::beg);                            // Start in begin positon in binary file
  baseFile.read((char *)&lBinBase, sizeof(lBinBase));     // Read base information in binary file
  idAsigner = lBinBase.nextId;
  b.name = lBinBase.name;

  for(unsigned int i=0; i<lBinBase.numContainers; i++) {
    baseFile.read((char *)&c, sizeof(Container));
    b.containers.push_back(c);
  }                                                       /* Extracts the containers from binary file
                                                             and add to actual base                  */
  bool Finish = false;
  while(baseFile.read((char *)&lBinShip, sizeof(lBinShip)) && Finish == false) {
    s = BinShiptoShip(lBinShip);

    if(s.name.empty()) {
      Finish = true;
    }

    for(unsigned int i=0; i<lBinShip.numContainers; i++) {
      baseFile.read((char *)&c, sizeof(Container));
      s.containers.push_back(c);
    }                                                     /* Extracts the containers (belonging to the ship) 
                                                             from binary file and add to regular ship    */
    b.ships.push_back(s);
  }
}

char YesOrNoCuestion(char YoN) {

  while(YoN != 'y' && YoN != 'n') {
    cout << ENTER_CONFIRM;
    cin >> YoN;
  } // Usuary delete confirmation
  return YoN;
}

void loadBase(Base &b, string &EntranceFile, bool &Question) {
  string filename;
  char YoN = ' ';
  Ship s;

  if(EntranceFile.empty()){
    cout << ENTER_FILE_NAME;
    getline(cin, filename);
  } else {
    filename = EntranceFile;
  }

  ifstream FileComprobation(filename.c_str(), ios::binary);

  if(FileComprobation.is_open()) {
    if(Question == true) {
    YoN = YesOrNoCuestion(YoN);
    }
    if(Question == false || YoN == 'y'){
      deleteBase(b);
      LoadBaseExtraction(b, FileComprobation);                  // Binary file to actual base transmission
    }
    FileComprobation.close();
  } else {
    error(ERR_CANT_OPEN_FILE);
  }
}


BinBase basetoBinBase(Base &regularBase) {
  BinBase sBinBase;

  strncpy(sBinBase.name, regularBase.name.c_str(), MAXNAME-1);
  sBinBase.name[MAXNAME-1] = '\0';
  sBinBase.nextId = idAsigner;
  sBinBase.numContainers = regularBase.containers.size();

  return sBinBase;
}

BinShip shiptoBinShip(Ship &regularShip) {
  BinShip sBinShip;

  strncpy(sBinShip.name, regularShip.name.c_str(), MAXNAME-1);
  sBinShip.name[MAXNAME-1] = '\0';
  sBinShip.weight = regularShip.weight;
  sBinShip.value = regularShip.value;
  sBinShip.maxWeight = regularShip.maxWeight;
  sBinShip.maxContainers = regularShip.maxContainers;
  sBinShip.numContainers = regularShip.containers.size();

  return sBinShip;
}

void saveContainers(Base &b, ofstream &saveFile) {
  Container c;

  for(unsigned int i=0; i<b.containers.size(); i++) {
    c = b.containers[i];
    saveFile.write((const char *)&c, sizeof(Container));            // Save containers in binary file
  }                                           
}

void saveContainersFromShip(Ship s, ofstream &saveFile) {
  Container c;

  for(unsigned int j=0; j< s.containers.size(); j++) {
  c = s.containers[j];
  saveFile.write((const char *)&c, sizeof(Container));                // Save containers from ship in binary file
  }
}

void saveShip(Base &b, ofstream &saveFile) {
  Ship s;
  BinShip sBinShip;

  for(unsigned int i=0; i<b.ships.size(); i++) {
  s = b.ships[i];
  sBinShip = shiptoBinShip(s);                                        // Pass ship to Binary ship
  saveFile.write((const char *)&sBinShip, sizeof(sBinShip));          // Save ships in binary file
  saveContainersFromShip(s, saveFile);
  } 
}


void saveBase(Base &b) {
  string filename;
  BinBase sBinBase;
  cout << ENTER_FILE_NAME;
  getline(cin,filename);

  ofstream saveFile(filename.c_str(), ios::binary);

  if(saveFile.is_open()) {
    
    sBinBase = basetoBinBase(b);
    saveFile.write((const char *)&sBinBase, sizeof(BinBase));        // Save base in binary file
    saveContainers(b, saveFile);
    saveShip(b, saveFile);
    saveFile.close();
  } else {
    error(ERR_CANT_OPEN_FILE);
  }
}

void menu() {
  cout << "1- Info base" << endl
       << "2- Add container" << endl
       << "3- Remove container" << endl
       << "4- Add ship" << endl
       << "5- Remove ship" << endl
       << "6- Manual distribution" << endl
       << "7- Automatic distribution" << endl
       << "8- Unassign container" << endl
       << "9- Clear assignations" << endl
       << "i- Import data" << endl
       << "x- Export data" << endl
       << "l- Load base" << endl
       << "s- Save base" << endl
       << "q- Quit" << endl
       << "Option: " ;
}

// Check if next to the current argument there is a string (X)  (Ex: ./prac2 -i X)
bool case1Comprobation(int &argc, char *argv[], bool &Option, int &i, bool &Exit) {

  if((i+1) < argc) {
    Option = true;
  } else if((i+1) == argc) {
    error(ERR_ARGS);
    Exit = true;
  }

  return Option;
}

// Print error and finish program
bool caseRepetition(bool Option, bool &Exit) {
  Option = false;
  error(ERR_ARGS);
  Exit = true;
  return Option;
}

// Entrance argument to option argument transmission
string argumentAsigner(string argvString,bool Option) {
  string Argument;
  if(Option == true) {
    Argument = argvString;
  }
  return Argument;
}


void EntranceComprobation(int argc, char *argv[], bool &iOption, bool &lOption, bool &aOption, string &argi,
                          string &argl, bool &Exit) { 
                          // Entrance num & arguments, Entrance Confirmation (i,l & a) Options & nameFile


  for(int i=1; i<argc && Exit != true; i++) {
    if(strcmp(argv[i], "-i") == 0 && iOption == false) {            // No repetition & -i option
      iOption = case1Comprobation(argc, argv, iOption, i, Exit);
      if(iOption == true) {
        argi = argumentAsigner(argv[i+1], iOption);
        i++;
      }
    } else if(strcmp(argv[i], "-l") == 0 && lOption == false) {     // No repetition & -l option
      lOption = case1Comprobation(argc, argv, lOption, i, Exit);
      if(lOption == true) {
        argl = argumentAsigner(argv[i+1], lOption);
        i++;
      }
    } else if(strcmp(argv[i], "-a") == 0 && aOption == false) {     // No repetition & -a option
      aOption = true;
    } else if(strcmp(argv[i], "-i") == 0 && iOption == true) {      // Repetition of -i
      iOption = caseRepetition(iOption, Exit);

    } else if(strcmp(argv[i], "-l") == 0 && lOption == true) {      // Repetition of -l
      lOption = caseRepetition(lOption, Exit);

    } else if(strcmp(argv[i], "-a") == 0 && aOption == true) {      // Repetition of -a
      aOption = caseRepetition(aOption, Exit);
    } else {
      aOption = caseRepetition(aOption, Exit);
    }
  }
}


int main(int argc, char **argv) {
  Base base;

  base.name = "Logistic Center";
  char option;
  string EntranceFile, argi, argl;
  bool Exit = false, Question = true;
  bool iOption = false, lOption = false, aOption = false;
  EntranceComprobation(argc, argv, iOption, lOption, aOption, argi, argl, Exit);

  if(Exit == false) {
   do {
      if(lOption == true) {                       // Case -l  argument copy & loadBase choice
        option = 'l';
        EntranceFile = argl;
        Question = false;
        lOption = false;
      } else if(iOption == true) {                // Case -i argument copy & importData choice
        option = 'i';
        EntranceFile = argi;
        iOption = false;
      } else if(aOption == true) {                // Case -a argument copy & automaticDistribution choice
        option = '7';
        aOption = false;
      } else {
        menu();
        cin >> option; 
        cin.get();
      }
        switch (option) {
          case '1': {
            printBase(base);
            break;
          }
          case '2': {
            addContainer(base);
            break;
          }
          case '3': {
            removeContainer(base);
            break;
          }
          case '4': {
            addShip(base);
            break;
          }
          case '5': {
            removeShip(base);
            break;
          }
          case '6': {
            manualDistribution(base);
            break;
          }
          case '7': {
            automaticDistribution(base);
            break;
          }
          case '8': {
            unassignContainer(base);
            break;
          }
          case '9': {
            clearAssignations(base);
            break;
          }
          case 'i': {
            importData(base, EntranceFile);
            break;
          }
          case 'x': {
            exportData(base);
            break;
          }
          case 'l': {
           loadBase(base, EntranceFile, Question);
           Question = true;                           
            break;
          }
          case 's': {
            saveBase(base);
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
 }
   return 0;
}
