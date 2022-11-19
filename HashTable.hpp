#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

static int numOfUnsolvedCollisions=0;

// We keep track of Total Number Of Collisions
static int totalCollisions=0;

int nextPrime( int n );
int previousPrime( int n );


template <typename HashedObj>
class HashTable
{
public:
    explicit HashTable( int size = 100003) : array( size  )
    {
        makeEmpty( );
    }

    bool contains( const HashedObj & x ) const
    {
        return isActive( findPos( x ) );
    }

    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : array )
            entry.info = EMPTY;
    }

        void printHT () const
    {
        for ( int i=0; i<array.size(); i++)
            cout<<array[i].element<<endl;
    }

    void REsetCollisions () const
    {
        numOfUnsolvedCollisions=0;
        totalCollisions=0;
    }
    bool insertQP( const HashedObj & x )
    {
        // Insert x as active
        int currentPos = findPosQP( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ].element = x;
        array[ currentPos ].info = ACTIVE;


        return true;
    }


        bool insertLP( const HashedObj & x )
    {
        // Insert x as active
        int currentPos = findPosLP( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ].element = x;
        array[ currentPos ].info = ACTIVE;


        return true;
    }



        bool insertDH( const HashedObj & x )
    {
        // Insert x as active
        int currentPos = findPosDH( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ].element = x;
        array[ currentPos ].info = ACTIVE;


        return true;
    }



    enum EntryType { ACTIVE, EMPTY, DELETED };



//    Private Attributes    //

// HashTable is a vector of HashEntry Obj
// Of CurrentSize


private:

    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
            : element{ e }, info{ i } { }

        HashEntry( HashedObj && e, EntryType i = EMPTY )
            : element{ std::move( e ) }, info{ i } { }
    };



    vector < HashEntry > array;
    int    currentSize;


    bool isActive( int currentPos ) const
    {
        return array[ currentPos ].info == ACTIVE;
    }


    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % array.size( );
    }


    // findPosition Using Quadratic Probing QP //
    int findPosQP( const HashedObj & x ) const
    {


                int offset = 1;
                int i=0;
        int currentPos = myhash( x );

      while( array[ currentPos ].info != EMPTY &&
               array[ currentPos ].element != x  )
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            ++i;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }
        totalCollisions+=i;

        return currentPos;
    }


    // findPosition Using Linear Probing LP //
    int findPosLP( const HashedObj & x ) const
    {

        int offset = 1;
        int currentPos = myhash( x );
        int numOfCheckings=0;
        int counter=0;

        while( array[ currentPos ].info != EMPTY &&
                array[ currentPos ].element != x &&
                numOfCheckings < array.size())
        {

            currentPos += offset;  // Compute ith probe
            offset += 1;
            numOfCheckings=++counter;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );


        }
        if ( numOfCheckings== array.size())
        {
            ++numOfUnsolvedCollisions;
        }
        else
        {

            totalCollisions+=numOfCheckings;
            return currentPos;
        }
    }




    // findPosition Using Double Hashing DH //

    int findPosDH( const HashedObj & x ) const
    {
        int i=0;

        int currentPos = myhash( x );
        int copy = currentPos;
        int pos1= std::move(copy) ;

        while( array[ pos1 ].info != EMPTY &&
                array[ pos1 ].element != x &&
                i< (array.size())/2)
        {

            pos1 = currentPos + (i *  ( secondHashFun( x )));
            ++i;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );


        }
        if ( i== (array.size())/2)
        {
            ++numOfUnsolvedCollisions;
        }
        else
        {

            totalCollisions+=i;
            return currentPos;
        }
    }

    int secondHashFun ( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return ( previousPrime(array.size()))-(hf( x ) % previousPrime(array.size( )));
    }



};

#endif
