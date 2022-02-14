#include "flowerbed.h"

int Flowerbed::GetNumber() const
{
    return number;
}

void Flowerbed::AddFlowerToFlowerbed(std::string flower)
{
    flowers.push_back(flower);
}

std::string Flowerbed::GetForm() const
{
    if(form == 0){ return "circle";}
    else if(form == 1){ return "square";}
    else if(form == 2){ return "rhombus";}
    else { return "undefined";}
}

std::vector<std::string> Flowerbed::GetFlowers() const
{
    return flowers;
}

void Flowerbed::Read(std::istringstream & in)
{
    std::string str1;
    in >> number >> str1;
    if(str1 == "circle"){form = CIRCLE;}
    else if(str1 == "square"){form = SQUARE;}
    else if(str1 == "rhombus"){form = RHOMBUS;}
    else{ form = -1;}
    std::string str;
    while (getline(in, str, ' '))
    {
        flowers.push_back(str);
    }
}

std::ostream& operator<<(std::ostream& out, Flowerbed& flowerbed) {
    out << "Number: " << flowerbed.GetNumber() << '\n'
        << "Form: " << flowerbed.GetForm() << '\n' << "Flowers: ";
    for (std::string i : flowerbed.GetFlowers())
    {
        out << i << " ";
    }
    out << '\n' << '\n';
    return out;
}
