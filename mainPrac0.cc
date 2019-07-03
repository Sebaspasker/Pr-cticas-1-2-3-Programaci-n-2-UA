// Assignment 0: Basic concepts

#include <iostream>

using namespace std;

bool multiple(int,int);
int printN(int);
int firstPrimes(int);
void Goldbach(int,int &,int &);
bool search(int [],const int,int);
int position(int [],const int,int);
int count(int [],const int,int);
int minOdds(int [],const int);
int posMaxMultFive(int v[],const int);
void extractStudentData(char []);

int main()
{
    /*
  // Exercise 1
  cout << "Exercise 1" << endl << endl;
  
  cout << "multiple(15,3) = " << multiple(15,3) << endl;
  cout << "multiple(17,5) = " << multiple(17,5) << endl;
  cout << "multiple(5,76) = " << multiple(5,76) << endl;
  cout << "multiple(12,72) = " << multiple(12,72) << endl;

  cout << "-----------------------------------------------------------" << endl;

  // Exercise 2
  cout << "Exercise 2" << endl << endl;
  
  int nAsteriscs = 0;

  nAsteriscs = printN(1);
  cout << "printN(1) = " << nAsteriscs << endl;
  nAsteriscs = printN(4);
  cout << "printN(4) = " << nAsteriscs << endl;
  nAsteriscs = printN(6);
  cout << "printN(6) = " << nAsteriscs << endl;

  cout << "-----------------------------------------------------------" << endl;

  // Exercise 3
  cout << "Exercise 3" << endl << endl;
  
  int sum = 0;
  
  sum = firstPrimes(1);
  cout << endl << "firstPrimes(1) = " << sum << endl;

  sum = firstPrimes(3);
  cout << endl << "firstPrimes(3) = " << sum << endl;
  
  sum = firstPrimes(6);
  cout << endl << "firstPrimes(6) = " << sum << endl;
  
  sum = firstPrimes(10);
  cout << endl << "firstPrimes(10) = " << sum << endl;
  
  cout << endl << "-----------------------------------------------------------" << endl;
  
  // Exercise 4
  cout << "Exercise 4" << endl << endl;
  */
  int p1 = 0;
  int p2 = 0;
  
  Goldbach(4,p1,p2);
  cout << "Goldbach(4,p1,p2) = (" << p1 << "," << p2 << ")" << endl;
/*
  Goldbach(12,p1,p2);
  cout << "Goldbach(12,p1,p2) = (" << p1 << "," << p2 << ")" << endl;

  Goldbach(458,p1,p2);
  cout << "Goldbach(458,p1,p2) = (" << p1 << "," << p2 << ")" << endl;

  Goldbach(32896,p1,p2);
  cout << "Goldbach(32896,p1,p2) = (" << p1 << "," << p2 << ")" << endl;

  cout << "-----------------------------------------------------------" << endl;

  // Exercise 5
  cout << "Exercise 5" << endl << endl;
  
  int v[] = {1,2,3,4,5,6,5,4,3,2,1};
  
  cout << "search({1,2,3,4,5,6,5,4,3,2,1},11,7) = " << search(v,11,7) << endl;
  cout << "search({1,2,3,4,5,6,5,4,3,2,1},11,2) = " << search(v,11,2) << endl;
  
  cout << "position({1,2,3,4,5,6,5,4,3,2,1},11,7) = " << position(v,11,7) << endl;
  cout << "position({1,2,3,4,5,6,5,4,3,2,1},11,2) = " << position(v,11,2) << endl;

  cout << "count({1,2,3,4,5,6,5,4,3,2,1},11,7) = " << count(v,11,7) << endl;
  cout << "count({1,2,3,4,5,6,5,4,3,2,1},11,2) = " << count(v,11,2) << endl;
  
  cout << "------------------------------------------------------------" << endl;
  
  // Exercise 6
  cout << "Exercise 6" << endl << endl;
  */
  int v1[] = {6,4,0,2};
  /*
  int v2[] = {2,4,8,0,24,8};
  int v3[] = {3,7,8,51,3,2};
  
  cout << "minOdds({3,4,7,2,275,5,1},7) = " << minOdds(v1,7) << endl;
  cout << "minOdds({2,4,8,0,24,8},6) = " << minOdds(v2,6) << endl;
  cout << "minOdds({3,7,8,51,3,2},6) = " << minOdds(v3,6) << endl;

  int v4[] = {2,3,8,17,24,8};
  int v5[] = {3,7,8,50,3,2};
    */
  cout << "posMaxMultFive({6,4,0,2},4) = " << posMaxMultFive(v1,4) << endl;
  /*
  cout << "posMaxMultFive({2,3,8,17,24,8},6) = " << posMaxMultFive(v4,6) << endl;
  cout << "posMaxMultFive({3,7,8,50,3,2},6) = " << posMaxMultFive(v5,6) << endl;

  cout << "------------------------------------------------------------" << endl;

  // Exercise 7
  cout << "Exercise 7" << endl << endl;
  
  char data1[] = "1234:Perez Perez, Pedro:3.4:Good work, but did not submit the last assignment";  
  extractStudentData(data1);
  cout << endl;
  
  char data2[] = "33452:Cruz Pi, Teo:7.9:No comment";
  extractStudentData(data2);
  cout << endl;
  
  char data3[] = "12:Mas Mora, Ana:9.4:Superb!";
  extractStudentData(data3);
  */
  return 0;
}
