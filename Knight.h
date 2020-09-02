//
// Created by Camtheconqueror on 5/3/2020.
//

#ifndef HW7CLIENT_KNIGHT_H
#define HW7CLIENT_KNIGHT_H
#include <vector>
#include <string>
using namespace std;
class Knight {
public:
    //default constructor
    Knight();
    std::vector<string> queOfMessages;
    string knightFileName;
    string knightName;
    int knightHp;
    int knightBrav;
    int knightRate;
    int knightHit;
    int knightDmg;
    int knightCount;
    int knightPriority;
    bool priority = false;
    bool knightAlive = true;

    //Knight constructor
    Knight(string name, int hp, int bravery, int rate, int hit, int dmg);
    int validateAmountOfKnights();
    //create knight
    std::vector<Knight> createKnight();
    //Validate values of key:value for knight file
    int validateKnights();
    //Validate format of key:value for knight file
    void openKnightFile();
    //Display Knight properties
    void ToString();
    //Return knights name
    string getKnightName();
};


#endif //HW7CLIENT_KNIGHT_H
