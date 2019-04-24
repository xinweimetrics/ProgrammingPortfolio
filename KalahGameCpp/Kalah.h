//
//  Kalah.h: Header for the Main.cpp code
//  KalahGame
//
//  Created by Xin Wei on 4/2/19.
//  Copyright © 2019 Xin Wei. All rights reserved.

#ifndef KALAH_H
#define KALAH_H

#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Kalah {
    
public:
    Kalah(string name); /* constructor */
    ~Kalah(); // ?
    
public:
    
    // Variables needed for the functions above
    int house[7];
    string playerName; // Can't we initialize playerName = name?
    
    // Handle game moves
//    void InitGame();
    void AddSeeds(int houseNum, int lasthouse);
    void RemoveSeeds(int houseNum);
    void MoveSeeds(int houseNum, Kalah &player, Kalah &oponent);
    void SetSeeds(int numSeeds, int houseNum);
    void SowRemainingSeeds();
    int NumSeeds(int houseNum);
    string Name(string name);
    bool StillPlaying(int houseNum);
    bool Empty(int houseNum);
    bool Finished();
    
    //   private:
    // Variables needed for the functions above
    //     int house[7]; // One for each player. Can access by calling Kalah class
    //     string playerName;
    
};

#endif // KALAH_H
////////////////////////////////////////////////////////////////////////
