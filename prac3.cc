#include <iostream>
#include <string.h>
#include "Container.h"
#include "Ship.h"
#include "Base.h"
#include "Util.h"

using namespace std;


void pruebaBase() {
  Base b("Base prueba");

  cout << b.getName() << b.getNumContainers() << b.getNumShips() <<endl;


  b.addContainer(100,100);
  cout << "1" << endl;
  b.addContainer();
  cout << "2" << endl;
  b.addContainer(1, 100);
  cout << "3" << endl;
  b.addContainer(100, 1);
  cout << "4" << endl;
  cout << b.getNumContainers();
}

void pruebaContainer() {

  cout << "------------------------------------------------" << endl;

  try{
    Container c1(0, 0);
  } catch(Error e) {
    Util::error(e);
  }
  try{
    Container c2(100, 0);
  } catch(Error e) {
    Util::error(e);
  }
  try{
    Container c3(0, 100);
  } catch(Error e) {
    Util::error(e);
  }
  
  try{
    Container c4(50, 50);
  } catch(Error e) {
    Util::error(e);
  }

  try{
    Container c5(0, 50);
  } catch(Error e) {
    Util::error(e);
  }

  try{
    Container c6(50, 0);
  } catch(Error e) {
    Util::error(e);
  }
  Container c1(0,0);
  Container c2(0,0);
  cout << c1.getId() << c2.getId() << " " << c1.getWeight() << c2.getWeight() << " " << c1.getValue() << c2.getValue() << endl;
  c1.resetNextId();
  Container c7(100, 100);
  cout << c7.getId() << endl;

  c1.setWeight(200);

  cout << c1.getWeight() << endl;
  try{
  c1.setWeight(50);
} catch(Error e) {
  Util::error(e);
}
  cout << c1.getWeight() << endl;

  try{
    c1.setValue(200);
  }catch(Error e) {
    Util::error(e);
  }

  cout << c1.getValue() << endl;

  try{

c1.setValue(50);
    
  }catch(Error e) {
    Util::error(e);
  }
  

  cout << c1.getValue() << endl;

  cout << c1 << endl;

  return;
  cout << "------------------------------------------------" << endl;
  
}

void pruebaShip() {
  cout << "------------------------------------------------" << endl;
  Ship s("hola", 5, 1000);
  cout << s.getWeight() << " " << s.getValue() << " " << s.getMaxWeight() << " " << s.getMaxContainers() << " " << s.getNumContainers() << endl;
  Container c(100,100);
  Container c1(10000, 100);
  Container c2(100, 10000);
  cout << s.admitsContainer(c) << endl;

  s.addContainer(c);

  cout << s.admitsContainer(c1) << endl;
  s.addContainer(c1);

  cout << s.admitsContainer(c2) << endl;

  s.addContainer(c2);
  s.addContainer(c2);
  s.addContainer(c2);
  s.addContainer(c2);
  s.addContainer(c2);
  s.addContainer(c2);

  cout << "HOLA" << endl;
  cout << s.getWeight() << " " << s.getValue() << " " << s.getMaxWeight() << " " << s.getMaxContainers() << " " << s.getNumContainers() << endl;

  
  try{
    s.getContainer(2);
  }
  catch(Error e) {
    Util::error(e);
  }

  s.removeContainer(1);
  s.removeContainer(2);
  s.removeContainer(3);
  s.removeContainer(4);
  s.removeContainer(5);
  cout << s.getWeight() << " " << s.getValue() << " " << s.getMaxWeight() << " " << s.getMaxContainers() << " " << s.getNumContainers() << endl;


  

  cout << s;

  cout << "------------------------------------------------" << endl;
  return;

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
       << "8- Unassign container" << endl
       << "9- Clear assignations" << endl
       << "q- Quit" << endl
       << "Option: " ;
}

int main()
{
  Base base("Logistic Center");
  vector<Ship*> naves;
  
  char option;


  do
  {
    menu();
    cin >> option; cin.get();
        
    switch (option)
    { 
      case '1':
      {
        cout << base;
        break;
      }
      case '2':
      { 
        /*cout << "ADD CONTAINER " <<*/base.addContainer();/* << endl;*/
        break;
      }
      case '3':
      {
        /*cout << "REMOVE CONTAINER " << */base.removeContainer();/* << endl;*/
        break;
      }
      case '4':
      {
        try
        {
          Ship *nueva=new Ship;
          naves.push_back(nueva);
          /*cout << "ADD SHIP " << */base.addShip(nueva);/* << endl;*/
        }
        catch(Error e)
        {
          Util::error(e);
        }
        break;
      }
      case '5':
      {
        
        /*cout << "REMOVE SHIP " << */base.removeShip();/* << endl;*/
        break;
      }
      case '6':
      {
        /*cout << "MANUAL DISTRIBUTION " << */base.manualDistribution();/* << endl;*/
        break;
      }
      case '7':
      {
        base.automaticDistribution();
        break;
      }
      case '8':
      {
        /*cout << "UNASSIGN CONTAINER " << */base.unassignContainer();/*;*/
        break;
      }
      case '9':
      {
        base.clearAssignations();
        break;
      }
      case 'q':
      {
        for(int i=0;(unsigned)i<naves.size();i++)
        {
          delete naves[i];
        }
        break;
      }
      default:
      {
        Util::error(ERR_MENU_OPTION); 
        break;
      }
    }
  } while(option != 'q');
   
  return 0;
}
