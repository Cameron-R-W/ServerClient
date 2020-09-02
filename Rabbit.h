//
// Created by Camtheconqueror on 5/4/2020.
//

#ifndef HW7CLIENT_RABBIT_H
#define HW7CLIENT_RABBIT_H
#include <string>
#include <vector>

using namespace std;

class Rabbit {
public:
    string rabbitFileName;
    std::vector<string> queOfMessages;
    int rabbitHp;
    int rabbitRate;
    int rabbitBite;
    int rabbitQuick;
    int rabbitThroat;
    int rabbitWeak;
    int rabbitStrong;
    int rabbitEvade;
    bool rabbitAlive = true;
    int rabbitPriority;
    bool priority = false;
    //validate key:value format
    int openRabbitFile();
    //validate the values
    int validateRabbit();
    //Display Rabbit properties
    void ToString();
};


#endif //HW7CLIENT_RABBIT_H
