#include <iostream>
#include <chrono>
#include "HashTable.hpp"

using namespace std;

HashTable < int > HT1;
HashTable < int > HT2;
HashTable < int > HT3;

// FIRST QUADRATIC PROBING //
void collisionVsSequenceLengthQPE1 ( )
{
    cout << " ___________________________________________ QUADRATIC PROBING _________________________________________"<<endl;
    srand(time(0));
    double LF=0.10;
    int j=1;

    int sum5TotalECollisions=0;
    while ( LF< 0.96 )
    {
 cout<<"enter loop for "<<j <<" time"<<endl;

        for ( int i=1; i< LF*100003; i++)
        {
            HT1.insertQP( rand ());
        }

        cout<<"Number of COLLISIONS in Experiment  "<< j <<"  with LF  "<<LF<<"  is  "<< totalCollisions<<"     collision"<<endl;
        //HT1.REsetCollisions();

        ++j;
        LF+=0.05;
        sum5TotalECollisions+=totalCollisions;
}
        //

    cout<<"AVERAGE OF COLLISIONS WITH DIIF SEQUENCE LENGTHS    "<< sum5TotalECollisions/5<<endl;

// end of function
}






int main()
{
    collisionVsSequenceLengthQPE1();






    return 0;
}
