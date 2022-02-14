#ifndef FLOWERBED_FLOWERBED_H
#define FLOWERBED_FLOWERBED_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>

enum Forms
{
    CIRCLE,
    SQUARE,
    RHOMBUS,
};

class Flowerbed
{
protected:
    int number;
    int form;
    std::vector<std::string> flowers;
public:
    Flowerbed() = default;

    ~Flowerbed() = default;

    int GetNumber() const;

    std::string GetForm() const;

    std::vector<std::string> GetFlowers() const;

    void AddFlowerToFlowerbed(std::string flower);

    void Read(std::istringstream&);

};
std::ostream& operator<<(std::ostream& out, Flowerbed& flowerbed);

#endif //FLOWERBED_FLOWERBED_H
