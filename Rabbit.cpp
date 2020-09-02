//
// Created by Camtheconqueror on 4/19/2020.
//

#include "Rabbit.h"

//
// Created by Camtheconqueror on 2/19/2020.
//

#include <iostream>
#include "Rabbit.h"
#include <vector>
#include <sstream>
#include <string>
#include <fstream>



//Check format key:value for rabbit file
int Rabbit::openRabbitFile() {
    string msg;
    //Validate if file can be open
    ifstream rabbit;
    rabbit.open(rabbitFileName.c_str(), ios::in);
    if(!rabbit)
    {
        msg = "Fail: cannot open rabbit file. \n";
        queOfMessages.push_back(msg);
        return -1;
    }
    else
    {
        msg = "Success: rabbit file opened succesfully.\n";
        queOfMessages.push_back(msg);
    }
    rabbit.close();
    //Validate number of lines
    int numLines = 0;
    std::string line;
    std::ifstream rabbitFile(rabbitFileName);
    while(std::getline(rabbitFile, line))
        numLines++;
    if(numLines == 8)
    {
        msg = "Success: Correct amount of lines input.\n";
        queOfMessages.push_back(msg);
    }
    else
    {
        msg = "Fail: Incorrect amount of lines input.\n";
        queOfMessages.push_back(msg);
        return -1;
    }
    rabbitFile.close();

    //Validate key and pair format
    string newLine;
    ifstream rabbitFile2(rabbitFileName);

    //Loop through each line and parse each line. Check for key and pair format
    for(int i = 1; i < 9; i++)
    {
        std::getline(rabbitFile2, newLine);

        //Check if line contains invalid character
        int strLength = newLine.length();
        for(int a = 0; a < strLength; a++)
        {
            if(newLine[a]==' ' || newLine[a]==',' || newLine[a]=='?' || newLine[a]=='.' || newLine[a]==';' )
            {
                msg = "Fail: Incorrect format: key:value: " + to_string(i) + "\n";
                queOfMessages.push_back(msg);
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
            msg = "Fail: Incorrect format: key:value: Line: " + to_string(i); + "\n";
            queOfMessages.push_back(msg);
            return -1;
        }
        //check hp key & value
        if(i == 1)
        {
            if(splitStrings[0] == "hp")
            {
                msg = "Success: Correct format: Key: " + splitStrings[0] + " value: " + splitStrings[1] + "\n";
                queOfMessages.push_back(msg);
                int hp;
                if(sscanf(splitStrings[1].c_str(), "%d", &hp) == 1)
                {
                    rabbitHp = hp;
                }
                else
                {
                    msg = "Fail: Incorrect value: " + splitStrings[1] + " Line: " + to_string(i) + "\n";
                    queOfMessages.push_back(msg);
                    return -1;
                }
            }
            else
            {
                msg = "Fail: Incorrect format: Key: " + splitStrings[0] + " Incorrect key";
                queOfMessages.push_back(msg);
                return -1;
            }
        }
        if(i == 2)
        {
            if(splitStrings[0] == "rate")
            {
                msg = "Success: Correct format: Key: " + splitStrings[0] + " value: " + splitStrings[1] + "\n";
                queOfMessages.push_back(msg);
                int rate;
                if(sscanf(splitStrings[1].c_str(), "%d", &rate) == 1)
                {
                    rabbitRate = rate;
                }
                else
                {
                    msg = "Fail: Incorrect value: " + splitStrings[1] + " Line: " + to_string(i) + "\n";
                    queOfMessages.push_back(msg);
                    return -1;
                }
            }
            else
            {
                msg = "Fail: Incorrect format: Key: " + splitStrings[0] + " Incorrect key";
                queOfMessages.push_back(msg);
                return -1;
            }
        }
        if(i == 3)
        {
            if(splitStrings[0] == "bite")
            {
                msg = "Success: Correct format: Key: " + splitStrings[0] + " value: " + splitStrings[1] + "\n";
                queOfMessages.push_back(msg);
                int bite;
                if(sscanf(splitStrings[1].c_str(), "%d", &bite) == 1)
                {
                    rabbitBite = bite;
                }
                else
                {
                    msg = "Fail: Incorrect value: " + splitStrings[1] + " Line: " + to_string(i) + "\n";
                    queOfMessages.push_back(msg);
                    return -1;
                }

            }
            else
            {
                msg = "Fail: Incorrect format: Key: " + splitStrings[0] + " Incorrect key";
                queOfMessages.push_back(msg);
                return -1;
            }
        }
        if(i == 4)
        {
            if(splitStrings[0] == "quick")
            {
                msg = "Success: Correct format: Key: " + splitStrings[0] + " value: " + splitStrings[1] + "\n";
                queOfMessages.push_back(msg);
                int quick;
                if(sscanf(splitStrings[1].c_str(), "%d", &quick) == 1)
                {
                    rabbitQuick = quick;
                }
                else
                {
                    msg = "Fail: Incorrect value: " + splitStrings[1] + " Line: " + to_string(i) + "\n";
                    queOfMessages.push_back(msg);
                    return -1;
                }
            }
            else
            {
                msg = "Fail: Incorrect format: Key: " + splitStrings[0] + " Incorrect key";
                queOfMessages.push_back(msg);
                return -1;
            }
        }
        if(i == 5)
        {
            if(splitStrings[0] == "throat")
            {
                msg = "Success: Correct format: Key: " + splitStrings[0] + " value: " + splitStrings[1] + "\n";
                queOfMessages.push_back(msg);
                int throat;
                if(sscanf(splitStrings[1].c_str(), "%d", &throat) == 1)
                {
                    rabbitThroat = throat;
                }
                else
                {
                    msg = "Fail: Incorrect value: " + splitStrings[1] + " Line: " + to_string(i) + "\n";
                    queOfMessages.push_back(msg);
                    return -1;
                }
            }
            else
            {
                msg = "Fail: Incorrect format: Key: " + splitStrings[0] + " Incorrect key";
                queOfMessages.push_back(msg);
                return -1;
            }
        }
        if(i == 6)
        {
            if(splitStrings[0] == "weak")
            {
                msg = "Success: Correct format: Key: " + splitStrings[0] + " value: " + splitStrings[1] + "\n";
                queOfMessages.push_back(msg);
                int weak;
                if(sscanf(splitStrings[1].c_str(), "%d", &weak) == 1)
                {
                    rabbitWeak = weak;
                }
                else
                {
                    msg = "Fail: Incorrect value: " + splitStrings[1] + " Line: " + to_string(i) + "\n";
                    queOfMessages.push_back(msg);
                    return -1;
                }
            }
            else
            {
                msg = "Fail: Incorrect format: Key: " + splitStrings[0] + " Incorrect key";
                queOfMessages.push_back(msg);
                return -1;
            }
        }
        if(i == 7)
        {
            if(splitStrings[0] == "strong")
            {
                msg = "Success: Correct format: Key: " + splitStrings[0] + " value: " + splitStrings[1] + "\n";
                queOfMessages.push_back(msg);
                int strong;
                if(sscanf(splitStrings[1].c_str(), "%d", &strong) == 1)
                {
                    rabbitStrong = strong;
                }
                else
                {
                    msg = "Fail: Incorrect value: " + splitStrings[1] + " Line: " + to_string(i) + "\n";
                    queOfMessages.push_back(msg);
                    return -1;
                }
            }
            else
            {
                msg = "Fail: Incorrect format: Key: " + splitStrings[0] + " Incorrect key\n";
                queOfMessages.push_back(msg);
                return -1;
            }
        }
        if(i == 8)
        {
            if(splitStrings[0] == "evade")
            {
                msg = "Success: Correct format: Key: " + splitStrings[0] + " value: " + splitStrings[1] + "\n";
                queOfMessages.push_back(msg);
                int evade;
                if(sscanf(splitStrings[1].c_str(), "%d", &evade) == 1)
                {
                    rabbitEvade = evade;
                }
                else
                {
                    msg = "Fail: Incorrect value: " + splitStrings[1] + " Line: " + to_string(i) + "\n";
                    queOfMessages.push_back(msg);
                    return -1;
                }
            }
            else
            {
                msg = "Fail: incorrect format: Key: " + splitStrings[0] + " Incorrect key";
                queOfMessages.push_back(msg);
                return -1;
            }
        }
    }
}

//Validates rabbit properties. Will log if values are not within range
int Rabbit::validateRabbit() {
    string line;
    if(rabbitHp < 25 || rabbitHp > 100)
    {
        line = "Fail: Incorrect value: " + to_string(rabbitHp) + " not within Hp range: [25,100]\n";
        queOfMessages.push_back(line);
        return -1;
    }
    else
    {
        line = "Success: correct value " + to_string(rabbitHp) + " within Hp range: [25,100]\n";
        queOfMessages.push_back(line);
    }

    if(rabbitRate < 3 || rabbitRate > 10)
    {
        line = "Fail: Incorrect value: " + to_string(rabbitRate) + " not within the rate range:[3,10]\n";
        queOfMessages.push_back(line);
        return -1;
    }
    else
    {
        line = "Success: correct value " + to_string(rabbitRate) + " within rate range: [3,10]\n";
        queOfMessages.push_back(line);
    }
    if(rabbitBite < 60 || rabbitBite > 75)
    {
        line = "Fail: Incorrect value: " + to_string(rabbitBite) + " not within bite range: [60,75]\n";
        queOfMessages.push_back(line);
        return -1;
    }
    else
    {
        line = "Success: correct value " + to_string(rabbitBite) + " within bite range [60,75]\n";
        queOfMessages.push_back(line);
    }
    if(rabbitQuick < 10 || rabbitQuick > 20)
    {
        line = "Fail: Incorrect value: " + to_string(rabbitQuick) + " not within quick range: [10,20]\n";
        queOfMessages.push_back(line);
        return -1;
    }
    else
    {
        line = "Success: correct value " + to_string(rabbitQuick) + " within quick range: [10,20]\n";
        queOfMessages.push_back(line);
    }
    if(rabbitThroat < 5 || rabbitThroat > 20)
    {
        line = "Fail: Incorrect value: " + to_string(rabbitThroat) + " not within throat range: [5,20]\n";
        queOfMessages.push_back(line);
        return -1;
    }
    else
    {
        line = "Success: correct value " + to_string(rabbitThroat) + " within throat range: [5,20]\n";
        queOfMessages.push_back(line);
    }
    if(rabbitWeak < 1 || rabbitWeak > 9)
    {
        line = "Fail: Incorrect value: " + to_string(rabbitWeak) + " not within weak range [1,9]\n";
        queOfMessages.push_back(line);
        return -1;
    }
    else
    {
        line = "Success: correct value " + to_string(rabbitWeak) + " within weak range: [1,9]\n";
        queOfMessages.push_back(line);
    }
    if(rabbitStrong < 30 || rabbitStrong > 40)
    {
        line = "Fail: Incorrect value " + to_string(rabbitStrong) + " not within strong range: [30,40]\n";
        queOfMessages.push_back(line);
        return -1;
    }
    else
    {
        line = "Success: correct value " + to_string(rabbitStrong) + " within strong range: [30,40]\n";
        queOfMessages.push_back(line);
    }
    if(rabbitEvade < 5 || rabbitEvade > 95)
    {
        line = "Fail: Incorrect value: " + to_string(rabbitEvade) + " not within evade range: [5,95]\n";
        queOfMessages.push_back(line);
        return -1;
    }
    else
    {
        line = "Success: correct value " + to_string(rabbitEvade) + " within evade range: [5,95]\n";
        queOfMessages.push_back(line);
    }
    int percentage = rabbitBite + rabbitQuick + rabbitThroat;
    if(percentage > 100)
    {
        line = "Fail: Incorrect value: bite, quick, and throat must sum to 100%\n";
        queOfMessages.push_back(line);
        return -1;
    }
    return 0;
}
//display rabbit values values
void Rabbit::ToString()
{
    cout << "Rabbit hp: " << this->rabbitHp << "\n";
    cout << "Rabbit rate: " << this->rabbitRate << "\n";
    cout << "Rabbit bite: " << this->rabbitBite << "\n";
    cout << "Rabbit quick: " << this->rabbitQuick << "\n";
    cout << "Rabbit throat: " << this->rabbitThroat << "\n";
    cout << "Rabbit weak: " << this->rabbitWeak << "\n";
    cout << "Rabbit strong: " << this->rabbitStrong << "\n";
    cout << "Rabbit evade: " << this->rabbitEvade << "\n";
}