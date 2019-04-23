//
//  main.cpp
//  KalahGame
//
//  Created by wei24 on 4/1/19.
//  Copyright © 2019 wei24. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstdio>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Kalah.h"

using namespace std;

int main() {
    
    // Print introduction
    cout << "Welcome to Kalah game!" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "Below is the rule. A nice illustration can be found in this wiki page [https://en.wikipedia.org/wiki/Kalah]" << endl;
    cout << endl;
    cout << "1. At the beginning of the game, four seeds are placed in each house." << endl;
    cout << "2. Each player controls the six houses and their seeds on the player's side of the board. The player's score is the number of seeds in the store to their right." << endl;
    cout << "3. Players take turns sowing their seeds. On a turn, the player removes all seeds from one of their houses. Moving counter-clockwise, the player drops one seed in each house in turn, including the player's own store but not their opponent's." << endl;
    cout << "4. If the last sown seed lands in an empty house owned by the player, and the opposite house contains seeds, both the last seed and the opposite seeds are captured and placed into the player's store." << endl;
    cout << "5. If the last sown seed lands in the player's store, the player gets an additional move. There is no limit on the number of moves a player can make in their turn." << endl;
    cout << "6. When one player no longer has any seeds in any of their houses, the game ends. The other player moves all remaining seeds to their store, and the player with the most seeds in their store wins." << endl;
    cout << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "Now, let's enjoy the game!" << endl;

    string name1;
    string name2 = "Computer";
    cout << "Enter name: ";
    cin >> name1;
    cout << endl << "Hi " + name1 + "! You will be playing against the computer." << endl;


    // Initializing all houses with four seeds

    int numSeeds = 4; // The program supports up to 4 seeds (4 included) in each house

    Kalah player1(name1);
    for (int i = 0; i < 6; i++) {
        player1.Kalah::SetSeeds(numSeeds,i);
    }
    player1.Kalah::SetSeeds(0,6);

    Kalah player2(name2);
    for (int i = 0; i < 6; i++) {
        player2.Kalah::SetSeeds(numSeeds,i);
    }
    player2.Kalah::SetSeeds(0,6);

    
    // Main loop: the games keeps going until someone wins
    int turn = 1;
    int numMove = 0;
    
    while ((!player1.Kalah::Finished())&&(!player2.Kalah::Finished())) {
        numMove += 1;
        int house1 = 0;
        int house2 = 0;
        
        // This is for the user to play............
        if (turn == 1) {
            
            // Lets print configuration
            
            cout << endl << "------------------ below is move " << numMove << ": user's turn ----------------------" << endl;
            cout << endl << "\t Player " << player1.Kalah::Name(name1) << "\t Player " << player2.Kalah::Name(name2) << endl;
            for (int i = 0; i < 6; i++) {
                cout << "House " << i << ":    " << player1.Kalah::NumSeeds(i) << "\t\t\t  " << player2.Kalah::NumSeeds(i) << endl;
            }
            cout << "Store" << ":      " << player1.Kalah::NumSeeds(6) << "\t\t\t  " << player2.Kalah::NumSeeds(6) << endl;
            
            // Tell player to play
            cout << endl << "Choose a house to sow (enter number from 0 to 5): ";
            cin >> house1;
            cout << endl;
            while ((house1 > 5) || (house1 < 0) || (player1.Kalah::NumSeeds(house1) == 0)) {
                cout << "Your choice is invalid. Try again: ";
                cin >> house1;
                cout << endl;
            }
            
            // Analyze if user should keep playing
            if (player1.Kalah::StillPlaying(house1)) {
                turn = 1;
                cout << "You get an additional move!" << endl;
            } else {
                turn = 2;
            }
            
            player1.Kalah::MoveSeeds(house1,player1,player2);
            
        } // end of turn 1
        
        // This is for the computer to play............
        else if (turn == 2) {
            
            // Lets print configuration

            cout << endl << "------------------ below is move " << numMove << ": computer's turn ----------------------" << endl;
            cout << endl << "\t Player " << player1.Kalah::Name(name1) << "\t Player " << player2.Kalah::Name(name2) << endl;
            for (int i = 0; i < 6; i++) {
                cout << "House " << i << ":    " << player1.Kalah::NumSeeds(i) << "\t\t\t  " << player2.Kalah::NumSeeds(i) << endl;
            }
            cout << "Store" << ":      " << player1.Kalah::NumSeeds(6) << "\t\t\t  " << player2.Kalah::NumSeeds(6) << endl;
            
//            cout << endl << "Wait. Computer is playing..." << endl;
            house2 = rand() % 6;
            while (player2.Kalah::NumSeeds(house2) == 0) {
                house2 = rand() % 6;
            }
            cout << endl << "Computer chose to sow house: " << house2 << endl;
            
            // Analyze if user should keep playing
            if (player2.Kalah::StillPlaying(house2)) {
                turn = 2;
                cout << "Computer gets an additional move!" << endl;
            } else {
                turn = 1;
            }
            
            player2.Kalah::MoveSeeds(house2,player2,player1);
            
        } // end of turn 2
        
    } // end while loop
    
    // Game is Kalah::Finished! Print the result before sowing remaining seeds into stores
    cout << endl << "------------------ game is finished ----------------------" << endl;
    cout << endl << "\t Player " << player1.Kalah::Name(name1) << "\t Player " << player2.Kalah::Name(name2) << endl;
    for (int i = 0; i < 6; i++) {
        cout << "House " << i << ":    " << player1.Kalah::NumSeeds(i) << "\t\t\t  " << player2.Kalah::NumSeeds(i) << endl;
    }
    cout << "Store" << ":      " << player1.Kalah::NumSeeds(6) << "\t\t\t  " << player2.Kalah::NumSeeds(6) << endl;
    
    // Sowing all remaining seeds into store
    player1.Kalah::SowRemainingSeeds();
    player2.Kalah::SowRemainingSeeds();
    
    // Analyzing who won, if stores have the same number of seeds, it's a tie!
    cout << endl << "------------------ final result ----------------------" << endl;
    cout << endl << "\t Player " << player1.Kalah::Name(name1) << "\t Player " << player2.Kalah::Name(name2) << endl;
    for (int i = 0; i < 6; i++) {
        cout << "House " << i << ":    " << player1.Kalah::NumSeeds(i) << "\t\t\t  " << player2.Kalah::NumSeeds(i) << endl;
    }
    cout << "Store" << ":      " << player1.Kalah::NumSeeds(6) << "\t\t\t  " << player2.Kalah::NumSeeds(6) << endl;
    
    if (player1.Kalah::NumSeeds(6) == player2.Kalah::NumSeeds(6)) {
        cout << endl << "Tied game." << endl;
    } else if (player1.Kalah::NumSeeds(6) > player2.Kalah::NumSeeds(6)) {
        cout << endl << player1.Kalah::Name(name1) << " wins!" << endl;
    } else {
        cout << endl << player2.Kalah::Name(name2) << " wins!" << endl;
    }

    cout << endl << "------------------ the end ----------------------" << endl;
    
    return 0;
    
}


/*
 * functions to be used in the above main() function
 */


void Kalah::MoveSeeds(int houseNum, Kalah &player, Kalah &playeropo) {
    // How many seeds are in this house?
    int nseeds = Kalah::NumSeeds(houseNum);
    
    // Lets clear this house
    player.Kalah::RemoveSeeds(houseNum);
    
    // Seeds should be added to houses up to the number of seeds in this particular house
    // So which is the last house receiving a seed?
    int lasthouse = houseNum + nseeds;
    int ownSide = 1;
    
    if (lasthouse <= 6) {
        
        // We are still in the player board
        cout << "lasthouse is: " << lasthouse << endl;

        // Putting the seeds in each house:
        player.Kalah::AddSeeds(houseNum+1,lasthouse);
        
    } else if ((lasthouse > 6)&&(lasthouse <= 12)) {
        
        lasthouse = lasthouse - 7; // need to count that opponents board starts with zero and not one
        
        // We are in the opponent board 1st time
        ownSide = 0;
        cout << "we are in the opponent board 1st time" << endl;
        cout << "lasthouse is: " << lasthouse << endl;
        
        // Putting the seeds in each house:
        player.Kalah::AddSeeds(houseNum+1,6);
        playeropo.Kalah::AddSeeds(0,lasthouse);
        
    } else if (lasthouse == 13) {
        
        // We stopped in opponent store, not good
        cout << "we are in the player board 2nd time" << endl;
        cout << "lasthouse is: " << "0" << endl;

        // Putting the seeds in each house:
        player.Kalah::AddSeeds(houseNum+1,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,0);
        
    } else if ((lasthouse > 13)&&(lasthouse <= 19)) {
        
        lasthouse = lasthouse - 13; // need to count that opponents board starts with zero and not one
        
        // We are in the player board 2nd time
        cout << "we are in the player board 2nd time" << endl;
        cout << "lasthouse is: " << lasthouse << endl;
        
        // Putting the seeds in each house:
        player.Kalah::AddSeeds(houseNum+1,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,lasthouse);
        
    } else if ((lasthouse > 19)&&(lasthouse <= 25)) {
        
        lasthouse = lasthouse - 20; // need to count that opponents board starts with zero and not one
        
        // We are in the opponent board 2nd time
        ownSide = 0;
        cout << "we are in the opponent board 2nd time" << endl;
        cout << "lasthouse is: " << lasthouse << endl;
        
        // Putting the seeds in each house:
        player.Kalah::AddSeeds(houseNum+1,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,6);
        playeropo.Kalah::AddSeeds(0,lasthouse);
        
    } else if (lasthouse == 26) {
        
        // We stopped in opponent store 2nd time, not good
        cout << "we are in the player board 3rd time" << endl;
        cout << "lasthouse is: " << "0" << endl;
        
        // Putting the seeds in each house:
        player.Kalah::AddSeeds(houseNum+1,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,0);
        
    } else if ((lasthouse > 26)&&(lasthouse <= 32)) {
        
        lasthouse = lasthouse - 26; // need to count that opponents board starts with zero and not one
        
        // We are in the player board 3rd time
        cout << "we are in the player board 3rd time" << endl;
        cout << "lasthouse is: " << lasthouse << endl;
        
        // Putting the seeds in each house:
        player.Kalah::AddSeeds(houseNum+1,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,lasthouse);
        
    } else if ((lasthouse > 32)&&(lasthouse <= 38)){
     
        lasthouse = lasthouse - 33; // need to count that opponents board starts with zero and not one
        
        // We are in the opponent board 3rd time
        ownSide = 0;
        cout << "we are in the opponent board 3rd time" << endl;
        cout << "lasthouse is: " << lasthouse << endl;
        
        // Putting the seeds in each house:
        player.Kalah::AddSeeds(houseNum+1,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,6);
        playeropo.Kalah::AddSeeds(0,lasthouse);
        
    } else if (lasthouse == 39){
        
        // We stopped in opponent store 3rd time, not good
        cout << "we are in the player board 4th time" << endl;
        cout << "lasthouse is: " << "0" << endl;
        
        // Putting the seeds in each house:
        player.Kalah::AddSeeds(houseNum+1,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,0);
        
    } else if ((lasthouse > 39)&&(lasthouse <= 45)) {
        
        lasthouse = lasthouse - 39; // need to count that opponents board starts with zero and not one
        
        // We are in the player board 4th time
        cout << "we are in the player board 4th time" << endl;
        cout << "lasthouse is: " << lasthouse << endl;
        
        // Putting the seeds in each house:
        player.Kalah::AddSeeds(houseNum+1,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,lasthouse);
        
    } else if ((lasthouse > 45)&&(lasthouse <= 51)) {
        
        lasthouse = lasthouse - 46; // need to count that opponents board starts with zero and not one
    
        // We are in the opponent board 4th time
        ownSide = 0;
        cout << "we are in the opponent board 4th time" << endl;
        cout << "lasthouse is: " << lasthouse << endl;
        
        // Putting the seeds in each house:
        player.Kalah::AddSeeds(houseNum+1,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,6);
        playeropo.Kalah::AddSeeds(0,5);
        player.Kalah::AddSeeds(0,6);
        playeropo.Kalah::AddSeeds(0,lasthouse);
        
    } else {
        
        cout << "Something is wrong with the numbers of seeds!" << endl;
        
    }
    
    // Checking if stopped in an Kalah::Empty house of this Kalah::Player (house 6 is the store).
    // That is, the lasthouse should be on player's own side & have 1 seed after AddSeeds
    if ((lasthouse != 6)&&(ownSide == 1)&&(Kalah::NumSeeds(lasthouse)==1)&&(!playeropo.Kalah::Empty(lasthouse))) {
        house[6] = house[6] + (Kalah::NumSeeds(lasthouse) + playeropo.Kalah::NumSeeds(lasthouse));
        // Clearing the last house and the opposite house from the other Kalah::Player
        Kalah::RemoveSeeds(lasthouse);
        playeropo.Kalah::RemoveSeeds(lasthouse);
    }
    
} // end of Kalah::MoveSeeds


void Kalah::RemoveSeeds(int houseNum) {
    house[houseNum] = 0;
}


void Kalah::AddSeeds(int houseNum, int lasthouse) {
    
    for (int i = houseNum; i <= lasthouse; ++i) {
        ++house[i];
    }
}


int Kalah::NumSeeds(int houseNum) {
    return house[houseNum];
}


void Kalah::SetSeeds(int numSeeds, int houseNum) {
    house[houseNum] = numSeeds;
}


void Kalah::SowRemainingSeeds() {
    for (int i = 0; i != 6; ++i) {
        house[6] += house[i];
        house[i] = 0;
    }
}


string Kalah::Name(string name) {
    return playerName = name;
}


bool Kalah::Empty(int houseNum) {
    return (house[houseNum] == 0);
}


// Check is the same Kalah::Player keeps playing (is the last seed stopping in his store?)
bool Kalah::StillPlaying(int houseNum) {
    int lasthouse = houseNum + house[houseNum];
    return (lasthouse % 13 == 6); // need to divide by 13
}


// Check if the game is Kalah::Finished (sum of seeds from all houses, for a particular Kalah::Player, is zero)
bool Kalah::Finished() {
    int totalseeds = 0;
    for (int i=0; i < 6; ++i) { // be careful not to count the store
        totalseeds += house[i];
    }
    return (totalseeds == 0);
}


Kalah::Kalah(string name) {
    
}


Kalah::~Kalah() {
    
}


// void InitGame();
