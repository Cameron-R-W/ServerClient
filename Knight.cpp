//
// Created by Camtheconqueror on 4/19/2020.
//

#include <fstream>
#include <iostream>
#include "Knight.h"
#include <vector>
#include <sstream>
#include <cstring>
#include <string>
using namespace std;
//default constructor
Knight::Knight()
{

}
//constructor for knight
Knight::Knight(string name, int hp, int bravery, int rate, int hit, int dmg)
{
    this->knightName = name;
    this->knightHp = hp;
    this->knightBrav = bravery;
    this->knightRate = rate;
    this->knightHit = hit;
    this->knightDmg = dmg;
}
//display knight values
void Knight::ToString()
{
    cout << "Knight Name: " << this->knightName << "\n";
    cout << "Knight hp: " << this->knightHp << "\n";
    cout << "Knight Bravery: " << this->knightBrav << "\n";
    cout << "Knight attack rate: " << this->knightRate << "\n";
    cout << "Knight hit chance: " << this->knightHit << "\n";
    cout << "Knight damage: " << this->knightDmg << "\n";
}
//return knights name
string Knight::getKnightName(){
    string name = this->knightName;
    return name;
}
//validate amount of knights with the count
int Knight::validateAmountOfKnights()
{
    string line;
    //Validate that we can open the knight file
    ifstream knight;
    knight.open(knightFileName.c_str(), ios::in);
    if(!knight)
    {
        line = "Fail: cannot open knight file.\n";
        queOfMessages.push_back(line);
        return -1;
    }
    else
    {
        line = "Success: Knight file opened succesfully.\n";
        queOfMessages.push_back(line);
    }
    knight.close();


    //Obtain first line of knight text file
    string newLine;
    ifstream knightFile(knightFileName);

    std::getline(knightFile, newLine);

    //Check if line contains invalid character
    int strLength = newLine.length();
    for(int a = 0; a < strLength; a++)
    {
        if(newLine[a]==' ' || newLine[a]==',' || newLine[a]=='?' || newLine[a]=='.' || newLine[a]==';' )
        {
            line = "Fail: Incorrect format: key:value: Line: " + to_string(a);
            queOfMessages.push_back(line);
            return -1;
        }
    }
    //Split line with delimiter :
    //Source: https://thispointer.com/how-to-split-a-string-in-c/
    std::stringstream ss(newLine);
    std::string item;
    std::vector<std::string> splitStrings;
    while(std::getline(ss, item, ':'))
    {
        splitStrings.push_back(item);
    }
    //check size of line, if vector size > 2 incorrect key:pair format
    if(splitStrings.size() > 2)
    {
        line = "Fail: Incorrect format: key:value: Line:";
        queOfMessages.push_back(line);
        return -1;
    }

    if(splitStrings[0] == "count")
    {
        //if [0] == count then check value after key
        int count;
        if(sscanf(splitStrings[1].c_str(), "%d", &count) == 1)
        {
            line = "Success: Correct format: Key: " + splitStrings[0] + " value: " + splitStrings[1] + "\n";
            queOfMessages.push_back(line);
            //if value is integer check if within range 1 - 8
            if(count < 1 || count > 8)
            {
                line = "Fail: incorrect value: Key " + splitStrings[0] + " value: " + splitStrings[1] + " not within range[1,8]\n";
                queOfMessages.push_back(line);
                return -1;
            }
                //if within range log, then verify that amount of lines correlate to the count
            else
            {
                line = "Success: Correct range Key: " + splitStrings[0] + " value: " + splitStrings[1] + "\n";
                queOfMessages.push_back(line);
                //set amount of knights
                knightCount = count;
                //check number of lines
                int numLines = 0;
                std::string line;
                std::ifstream knightFileCount(knightFileName);
                while(std::getline(knightFileCount, line))
                    numLines++;
                knightFileCount.close();

                //number of lines should equal count * count + 1(the + 1 is counting the first line)
                count *= 5;
                count++;
                if(numLines == count)
                {
                    line = "Success:: Amount of knights correlate to count\n";
                    queOfMessages.push_back(line);
                }
                else {
                    line = "Fail: Amount of knights do not correlate to count\n";
                    queOfMessages.push_back(line);
                    return -1;
                }
            }


        }
            //if value is not an integer log then exit
        else
        {
            line = "Fail: Incorrect value: " + splitStrings[1] + "\n";
            queOfMessages.push_back(line);
            return -1;
        }
    }
        //if first value is not "count" then incorrect format
    else
    {
        line = "Fail: Incorrect format: key:value \n";
        queOfMessages.push_back(line);
        return -1;
    }
    return 0;
}
//validate the values of knight text file
int Knight::validateKnights()
{
    string line;
    int sizeName = this->knightName.size();
    if(sizeName < 2 || sizeName > 50)
    {
        line = "Fail: Incorrect value: " + knightName + " not within name range: [2,50]\n";
        queOfMessages.push_back(line);
        return -1;
    }
    if(this->knightHp < 10 || knightHp > 40)
    {
        line = "Fail: Incorrect value: " + to_string(knightHp) + " not within Hp range: [10,40]\n";
        queOfMessages.push_back(line);
        return -1;
    }
    if(this->knightBrav < 0 || this->knightBrav >= this->knightHp)
    {
        line = "Fail: Incorrect value: " + to_string(knightBrav) + " not within bravery range: [0, < HP]\n";
        queOfMessages.push_back(line);
        return -1;
    }
    if(this->knightRate < 10 || this->knightRate > 50)
    {
        line = "Fail: Incorrect value: " + to_string(knightRate) + " not within rate range: [60,75]\n";
        queOfMessages.push_back(line);
        return -1;
    }
    if(this->knightDmg < 1 || this->knightDmg > 8)
    {
        line = "Fail: Incorrect value " + to_string(knightDmg) + " not within damage range: [1,8]\n";
        queOfMessages.push_back(line);
        return -1;
    }
    return 0;
}
//Validate the format of the knight  file (key:value)
void Knight::openKnightFile() {
    string line;
    //Validate key and pair format
    string newLine;
    ifstream knightFile(knightFileName);
    cout << knightFileName;
    //ignore the first line (contains count)
    std::getline(knightFile, newLine);
    //Loop through each line and parse each line. Check for key and pair format
    for(int counter = 0; counter < knightCount; counter++) {
        for (int i = 2; i < 7; i++) {
            std::getline(knightFile, newLine);

            //Check if line contains invalid character
            int strLength = newLine.length();
            for (int a = 0; a < strLength; a++) {
                if (newLine[a] == ' ' || newLine[a] == ',' || newLine[a] == '?' || newLine[a] == '.' ||
                    newLine[a] == ';') {

                    line = "Fail: Incorrect format: key:value: Line: " + to_string(i) + "\n";
                    queOfMessages.push_back(line);
                }
            }

            //Split line with delimiter :
            //Source: https://thispointer.com/how-to-split-a-string-in-c/
            std::stringstream ss(newLine);
            std::string item;
            std::vector<std::string> splitStrings;
            while (std::getline(ss, item, ':')) {
                splitStrings.push_back(item);
            }
            //check size of line, if vector size > 2 incorrect key:pair format
            if (splitStrings.size() > 2) {
                line = "Fail: Incorrect format: key:value Line: " + to_string(i) + "\n";
                queOfMessages.push_back(line);
            }
            //check name key & value
            if (i == 2)
            {
                if (splitStrings[0] == "name")
                {
                    line = "Success: Correct format: Key: " + splitStrings[0] + " value: " + splitStrings[1] + "\n";
                    queOfMessages.push_back(line);
                }

            }
            if (i == 3) {
                if (splitStrings[0] == "hp") {
                    line = "Success: Correct format: Key: " + splitStrings[0] + " value: " + splitStrings[1] + "\n";
                    queOfMessages.push_back(line);
                    int rate;
                    if (sscanf(splitStrings[1].c_str(), "%d", &rate) == 1) {
                    } else {
                        line = "Fail: Inccorect value: " + splitStrings[1] + " Line: " + to_string(i) + "\n";
                        queOfMessages.push_back(line);
                    }
                } else {
                    line = "Fail: Incorrect format: Key: " + splitStrings[0] + " Incorrect key";
                    queOfMessages.push_back(line);
                }
            }
            if (i == 4) {
                if (splitStrings[0] == "bravery") {
                    line = "Success: Correct format: Key: " + splitStrings[0] + " value: " + splitStrings[1] + "\n";
                    queOfMessages.push_back(line);
                    int bite;
                    if (sscanf(splitStrings[1].c_str(), "%d", &bite) == 1) {
                    } else {
                        line = "Fail: Incorrect value: " + splitStrings[1] + " Line: " + to_string(i) + "\n";
                        queOfMessages.push_back(line);
                    }

                } else {
                    line = "Fail: Incorrect format: Key: " + splitStrings[0] + " Inorrect key";
                    queOfMessages.push_back(line);
                }
            }
            if (i == 5) {
                if (splitStrings[0] == "rate") {
                    line = "Success: Correct format: Key: " + splitStrings[0] + " value: " + splitStrings[1] + "\n";
                    queOfMessages.push_back(line);
                    int quick;
                    if (sscanf(splitStrings[1].c_str(), "%d", &quick) == 1) {
                    } else {
                        line = "Fail: Incorrect value: " + splitStrings[1] + " Line: " + to_string(i) + "\n";
                        queOfMessages.push_back(line);
                    }
                } else {
                    line = "Fail: Incorrect format: Key: " + splitStrings[0] + " Incorrect key";
                    queOfMessages.push_back(line);
                }
            }
            if (i == 6) {
                if (splitStrings[0] == "damage") {
                    line = "Success: Correct format: Key: " + splitStrings[0] + " value: " + splitStrings[1] + "\n";
                    queOfMessages.push_back(line);
                    int throat;
                    if (sscanf(splitStrings[1].c_str(), "%d", &throat) == 1) {

                    } else {
                        line = "Fail: Incorrect value: " + splitStrings[1] + " Line: " + to_string(i) + "\n";
                        queOfMessages.push_back(line);
                    }
                } else {
                    line = "Fail: Incorrect format: Key: " + splitStrings[0] + " Incorrect key";
                    queOfMessages.push_back(line);
                }
            }
        }
    }

}
//Validates knight data and return vector of knights
std::vector<Knight> Knight::createKnight()
{
    string line;
    std::vector<Knight> listofKnights;
    //Validate key and pair format
    string newLine;
    ifstream knightFile(knightFileName);
    //ignore the first line (contains count)
    std::getline(knightFile, newLine);
    //Loop through each line and parse each line. Check for key and pair format
    for(int counter = 0; counter < knightCount; counter++) {
        //create new knight
        Knight newKnight;
        for (int i = 2; i < 7; i++) {
            std::getline(knightFile, newLine);

            //Split line with delimiter :
            //Source: https://thispointer.com/how-to-split-a-string-in-c/
            std::stringstream ss(newLine);
            std::string item;
            std::vector<std::string> splitStrings;
            while (std::getline(ss, item, ':')) {
                splitStrings.push_back(item);
            }
            //check name key & value
            if (i == 2)
            {
                newKnight.knightName = splitStrings[1];
            }
            if (i == 3)
            {
                int hp;
                if (sscanf(splitStrings[1].c_str(), "%d", &hp) == 1)
                {
                    newKnight.knightHp = hp;
                }
            }
            if (i == 4) {
                int bravery;
                if (sscanf(splitStrings[1].c_str(), "%d", &bravery) == 1)
                {
                    newKnight.knightBrav = bravery;
                }
            }
            if (i == 5) {
                int rate;
                if (sscanf(splitStrings[1].c_str(), "%d", &rate) == 1)
                {
                    newKnight.knightRate = rate;
                }
            }
            if (i == 6) {
                int dmg;
                if (sscanf(splitStrings[1].c_str(), "%d", &dmg) == 1)
                {
                    newKnight.knightDmg = dmg;
                }
            }
        }
        //validate the knights data
        int validate = newKnight.validateKnights();
        if(validate == 0)
        {
            line = "Knight: was successfully created.\n";
            queOfMessages.push_back(line);
        } else
        {
            line = "Knight:  failed to create.";
            queOfMessages.push_back(line);
            exit(3);
        }
        //if knight properties succesfully validate add them to vector of knights
        listofKnights.push_back(newKnight);
    }

    return listofKnights;
}





