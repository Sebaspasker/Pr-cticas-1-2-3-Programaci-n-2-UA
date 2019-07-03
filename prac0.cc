// NIE/DNI Y0025435B PASKER, SEBASTIAN

#include<iostream>
#include<string.h>

using namespace std;

// EJERCICIO 1
// Multiple verification

bool multiple(int a, int b){
    bool mult;

    if(b%a == 0){
        mult = true;
        return(mult);
    }
    else if(a%b == 0){
        mult = true;
        return(mult);
    }
    else{
        mult = false;
        return(mult);
    }
}

// EJERCICIO 2
// 'N' print & '*' contabilization

int printN(int n){
    int sumast = 0, fil, col;
    if(n>=4){ // '*' first col, last col & when fil == col to create 'N'
        for(fil=0; fil<n; fil++){
            for(col=0; col<n; col++){
                if(col == 0 || col == n-1){
                    cout << "*";
                    sumast++; // asterisk adder
                }
                else if(fil == col){
                    cout << "*";
                    sumast++;
                }
                else
                    cout << " ";
            }
            cout << endl;
        }
        return(sumast);
    }
    else{
        cout << "ERROR" << endl;
        return(sumast);
    }
}

// EJERCICIO 3
// Prime number verification & n prime numbers print

bool isprime(int busc){
    int div = 2; // 0 & 1 not real prime numbers
    bool prime = true;

    while(div<=busc/2){ //Prove a division of all combination before busc/2
        if(busc%div == 0){
            prime = false; //Busc not prime
        }
        div++;
    }
    return(prime);
}

int firstPrimes(int n){
    int primelook = 0, busc = 2, sumtot = 0;
    bool prime;

    while(primelook < n){
        prime = isprime(busc); //prime number verification
        if(prime == true){
            cout << busc << " ";
            primelook++; //prime number founded
            sumtot = sumtot + busc; //Sum primes
        }
        busc++;
    }

    return(sumtot);
}

// EJERCICIO 4
// Goldbach

void Goldbach(int n, int &p1, int &p2){
    int primefinder=3;
    bool prime = false, prime2 = false; // Prime verification
    bool found = false;
    p1 = 0; // Smallest prime number
    p2 = 0; // Biggest prime number

    do{
        prime = isprime(primefinder);
        if(prime == true){ // filter 1
            prime2 = isprime(n-primefinder);
            if(primefinder + (n-primefinder) == n && prime2 == true){ // filter 2 & 3, p2 is always p1 - n
                p1 = primefinder;
                p2 = n-primefinder;
                found = true; // Goldbach founded
            }
        }
        primefinder++; // Counter
        prime = false;
        prime2 = false; // Prime verification reset
    }while(primefinder<n && found == false);
}

// Ejercicio 5
// Busquedad de un elemento en un vector

bool search(int v[], const int TAMVECTOR, int n){ // Check if n is in v[]
    int vectpos; // Actual vector position
    bool found = false;

    for(vectpos=0; vectpos<TAMVECTOR; vectpos++){
        if(v[vectpos] == n){
            found = true;
            return(found);
        }
    }
    return(found);
}

int position(int v[], const int TAMVECTOR, int n){ // Check the position of n in v[]
    int vectpos;
    int position = -1; // Position where is n

    for(vectpos = 0; vectpos < TAMVECTOR; vectpos++){
        if(v[vectpos] == n){
            position = vectpos;
            return(position);
        }
    }
    return(position);
}

int count(int v[], const int TAMVECTOR, int n){ // Returns how much n is in v[]
    int countfound = 0, vectpos;

    for(vectpos=0; vectpos < TAMVECTOR; vectpos++){
        if(v[vectpos] == n){
            countfound++;
        }
    }

    return(countfound);
}

// Ejercicio 6
// Min y Max de un vector

int minOdds(int v[], const int TAMVECTOR){ //Returns min impar vector
    int vectpos;
    int foundimpar = -1; //Copy the last min number

    for(vectpos=0; vectpos<TAMVECTOR; vectpos++){
        if(v[vectpos]%2==1){ // Impar condition & smaller than actual foundimpar
            if(foundimpar == -1)
                foundimpar = v[vectpos]; // Copy first impar number for reference
            else if(v[vectpos]<foundimpar)
                foundimpar = v[vectpos];
        }
    }

    return(foundimpar);
}

int posMaxMultFive(int v[], const int TAMVECTOR){ // Returns position of max mult 5 number
    int vectpos, position = -1, numfound = 0;

    for(vectpos=0; vectpos<TAMVECTOR; vectpos++){
        if(v[vectpos] %5 == 0 && v[vectpos] > numfound){
            position = vectpos;
            numfound = v[vectpos];
        }
    }
    return(position);
}

// Ejercicio 7
// Extraer datos

typedef struct{
    int number;
    string name;
    double mark;
    string obs;
}TStudent;



void extractStudentData(char data[]){
    TStudent studreg;
    int length;
    int extnumber; // Extraction number from data
    int contdata = 0, contreg = 0, contnom = 0; // Counters of data (contdata),
                                                //**all register transfer process (contreg)
                                                //** & name and observations (contnom)
    double extmark = 0; // Extraction mark from data
    double exp10 = 10, convertcharnum = 0; // 10 exponential and char to number converter
    bool allcpy = false, markdecimal = false;
    char searchnom[20], searchobs[100];

    length = strlen(data);
    extnumber = 0;

    do{
        if(data[contdata] != ':'){ // Convert data to necesarry separated register copy
            if(contreg == 0){
                convertcharnum = data[contdata] - 48; // To pass char to int = number-48 (48 == '0')
                extnumber = extnumber*10 + convertcharnum;
            }
            else if(contreg == 1){
                searchnom[contnom] = data[contdata];
                contnom++;
            }
            else if(contreg == 2){
                if(data[contdata] == '.'){
                    markdecimal = true;
                } // Confirm that data is actually in decimal part (mark)
                else if(markdecimal == false){
                    convertcharnum = data[contdata] - 48;
                    extmark = extmark *10 + convertcharnum;
                } // Extraction of no decimal part (mark)
                else if(markdecimal == true){
                    convertcharnum = (data[contdata]-48)/exp10;
                    extmark = extmark + convertcharnum;
                    exp10 = exp10*10;
                } // Extraction of decimal part (mark)
            }
            else if(contreg == 3){
                searchobs[contnom] = data[contdata];
                contnom++;
                if(contdata == length ){
                    searchobs[contnom] = '\0';
                    studreg.obs = searchobs;
                    allcpy = true;
                } // Finish loop & traspass observations copy to register
            }
        }
        else if(data[contdata] == ':'){ // Traspass copies to register and change transfer process
            if(contreg == 0){
                studreg.number = extnumber;
            }
            else if(contreg == 1){
                searchnom[contnom] = '\0';
                studreg.name = searchnom;
            }
            else if(contreg == 2){
                studreg.mark = extmark;
                contnom = 0; // Mark & number counter reset
            }
            contreg++;
        }

        contdata++;
    }while(allcpy == false);

    cout << "Name: " << studreg.name << endl;
    cout << "Mark: " << studreg.mark << endl;
    cout << "Obs: " << studreg.obs << endl;
    cout << "Number: " << studreg.number << endl;

}
