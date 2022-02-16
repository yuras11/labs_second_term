#include "flowerbed_manager.h"

std::vector<Flowerbed> FlowerbedManager::GetVectorOfFlowerbeds()
{
    return vector_of_flowerbeds;
}

std::string FlowerbedManager::FromEnumToString(int number)
{
    if(number == CIRCLE){return "circle";}
    else if(number == SQUARE){return "square";}
    else if(number == RHOMBUS){return "rhombus";}
    else {return "undefined";}
}

void FlowerbedManager::ReadFromFileToVector(std::string name_of_file)
{
    std::ifstream fin(name_of_file);
    if(!fin.is_open())
    {
        throw std::runtime_error("File isn\'t opened");
    }
    else
    {
        while(!fin.eof())
        {
            Flowerbed flowerbed;
            std::string str;
            std::getline(fin, str);
            std::istringstream stream(str);
            flowerbed.Read(stream);
            vector_of_flowerbeds.push_back(flowerbed);
        }
    }
}

void FlowerbedManager::PrintVector(const std::vector<Flowerbed>& flowerbeds)
{
    for(int i = 0; i < flowerbeds.size(); i++)
    {
        Flowerbed flowerbed = flowerbeds[i];
        std::cout << flowerbed;
    }
}

void FlowerbedManager::SortByForm()
{
    std::sort(vector_of_flowerbeds.begin(), vector_of_flowerbeds.end(),
              [](Flowerbed& flowerbed1, Flowerbed& flowerbed2)
              {
                  return flowerbed1.GetForm() < flowerbed2.GetForm();
              });
}

void FlowerbedManager::FromVectorToMultimap()
{
    for (int i = 0; i < vector_of_flowerbeds.size(); i++)
    {
        multimap_of_flowerbeds.insert(std::pair<std::string, Flowerbed>
                (vector_of_flowerbeds[i].GetForm(), vector_of_flowerbeds[i]));
    }
}

void FlowerbedManager::PrintMultimap()
{
    for (std::multimap<std::string, Flowerbed>::iterator it = multimap_of_flowerbeds.begin();
         it != multimap_of_flowerbeds.end(); it++)
    {
        std::cout << it->first << "\t" << it->second << '\n';
    }
}

void FlowerbedManager::DifferentFormsOfFlowerbeds()
{
    std::cout << "Forms of flowerbeds and their amount:\n";
    int number_of_circle_flowerbeds = multimap_of_flowerbeds.count("circle");
    if(number_of_circle_flowerbeds > 0)
    {
        std::cout << number_of_circle_flowerbeds << " " << "circle" << '\n';
    }
    int number_of_square_flowerbeds = multimap_of_flowerbeds.count("square");
    if(number_of_circle_flowerbeds > 0)
    {
        std::cout << number_of_square_flowerbeds << " " << "square" << '\n';
    }
    int number_of_rhombus_flowerbeds = multimap_of_flowerbeds.count("rhombus");
    if(number_of_rhombus_flowerbeds > 0)
    {
        std::cout << number_of_rhombus_flowerbeds << " " << "rhombus" << '\n';
    }
    int number_of_flowerbeds_with_undefined_form = multimap_of_flowerbeds.count("undefined");
    if(number_of_flowerbeds_with_undefined_form > 0)
    {
        std::cout << number_of_flowerbeds_with_undefined_form << " " << "flowerbeds with undefined form" << '\n';
    }
}

void FlowerbedManager::FlowersOfADefiniteFlowerbed(int number_of_flowerbed)
{
    std::cout << "Flowers of a flowerbed number " << number_of_flowerbed << ":\n";
    for(std::multimap<std::string, Flowerbed>::iterator it = multimap_of_flowerbeds.begin();
        it != multimap_of_flowerbeds.end(); it++)
    {
        Flowerbed flowerbed = it->second;
        if(flowerbed.GetNumber() == number_of_flowerbed)
        {
           for (int i = 0; i < flowerbed.GetFlowers().size(); i++)
           {
               std::cout << flowerbed.GetFlowers()[i] << " ";
           }
        }
    }
}

void FlowerbedManager::FlowerbedWithTheBiggestAmountOfFlowers()
{
    std::cout << "Flowerbed with the biggest amount of flowers is: \n";
    std::vector<int> number_of_flowers;
    for (std::multimap<std::string, Flowerbed>::iterator it = multimap_of_flowerbeds.begin();
    it != multimap_of_flowerbeds.end(); it++)
    {
        Flowerbed flowerbed = it->second;
        number_of_flowers.push_back(flowerbed.GetFlowers().size() - 1);
    }
    std::vector<int>::iterator result;
    result = std::max_element(number_of_flowers.begin(), number_of_flowers.end());
    for (std::multimap<std::string, Flowerbed>::iterator it = multimap_of_flowerbeds.begin();
    it != multimap_of_flowerbeds.end(); it++)
    {
        Flowerbed flowerbed = it->second;
        if ((flowerbed.GetFlowers().size() - 1) ==
        number_of_flowers[std::distance(number_of_flowers.begin(), result)])
        {
            std::cout << flowerbed;
        }
    }
}

void FlowerbedManager::FlowerbedsWithADefiniteFlower(std::string flower)
{
    std::cout << "Flowerbeds with a flower called " << flower << ":\n";
    for(std::multimap<std::string, Flowerbed>::iterator it = multimap_of_flowerbeds.begin();
    it != multimap_of_flowerbeds.end(); it++)
    {
        Flowerbed flowerbed = it->second;
        for(int i = 0; i < flowerbed.GetFlowers().size(); i++)
        {
            if(flowerbed.GetFlowers()[i] == flower)
            {
                std::cout << flowerbed;
            }
        }
    }
}

void FlowerbedManager::FindFlowerbedByFormUsingLambdas(int int_form)
{
    std::string form = FromEnumToString(int_form);
    std::cout << "Flowerbeds with " << form << " form:\n";
    std::for_each(multimap_of_flowerbeds.begin(), multimap_of_flowerbeds.end(),
                  [form](const std::pair<const std::string, Flowerbed>& fl)
                  {
                      Flowerbed flowerbed = fl.second;
                      if (flowerbed.GetForm() == form)
                      {
                          std::cout << flowerbed;
                          return true;
                      }
                      else
                      {
                          return false;
                      }
                  });
}

void FlowerbedManager::FindFlowerbedByFormUsingFunctors(FlowerbedManager& flowerbedManager, int int_form)
{
    PrintVector(flowerbedManager(int_form));
}

std::vector<Flowerbed> FlowerbedManager::operator()(int int_form)
{
    std::vector<Flowerbed> flowerbeds;
    std::string form = FromEnumToString(int_form);
    for(std::multimap<std::string, Flowerbed>::iterator it = multimap_of_flowerbeds.begin();
    it != multimap_of_flowerbeds.end(); it++)
    {
        Flowerbed flowerbed = it->second;
        if(flowerbed.GetForm() == form)
        {
            flowerbeds.push_back(flowerbed);
        }
    }
    return flowerbeds;
}

void FlowerbedManager::FindFlowerbedByForm(int int_form)
{
    std::string form = FromEnumToString(int_form);
    std::cout << "Flowerbeds with " << form << " form:\n";
    for(std::multimap<std::string, Flowerbed>::iterator it = multimap_of_flowerbeds.begin();
    it != multimap_of_flowerbeds.end(); it++)
    {
        Flowerbed flowerbed = it->second;
        if(flowerbed.GetForm() == form)
        {
            std::cout << flowerbed;
        }
    }
}

void FlowerbedManager::FindFlowerbedsWithADefiniteNumberOfFlowers(int number)
{
    std::cout << "Flowerbeds which have " << number << " flowers:\n";
    for(std::multimap<std::string, Flowerbed>::iterator it = multimap_of_flowerbeds.begin();
            it != multimap_of_flowerbeds.end(); it++)
    {
        Flowerbed flowerbed = it->second;
        if(flowerbed.GetFlowers().size()-1 == number)
        {
            std::cout << flowerbed;
        }
    }
}

void FlowerbedManager::NumberOfFlowersOnCircleFlowerbeds()
{
    std::cout << "Circle flowerbeds have following numbers of flowers:\n";
    for(std::multimap<std::string, Flowerbed>::iterator it = multimap_of_flowerbeds.begin();
    it != multimap_of_flowerbeds.end(); it++)
    {
        Flowerbed flowerbed = it->second;
        if(flowerbed.GetForm() == "circle")
        {
            std::cout << "Flowerbed number " << flowerbed.GetNumber() << " has " << flowerbed.GetFlowers().size()-1
            << " flowers\n";
        }
    }
}

void solution()
{
    FlowerbedManager flowerbedManager;
    flowerbedManager.ReadFromFileToVector("input.txt");
//    flowerbedManager.SortByForm();
//    flowerbedManager.PrintVector(flowerbedManager.GetVectorOfFlowerbeds());
    flowerbedManager.FromVectorToMultimap();
//    std::cout << std::endl;
//    flowerbedManager.PrintMultimap();
//    flowerbedManager.DifferentFormsOfFlowerbeds();
//    std::cout << std::endl;
//    flowerbedManager.FlowersOfADefiniteFlowerbed(111);
//    std::cout << std::endl;
//    std::cout << std::endl;
//    flowerbedManager.FlowerbedWithTheBiggestAmountOfFlowers();
//    flowerbedManager.FlowerbedsWithADefiniteFlower("daisy");
//     flowerbedManager.FindFlowerbedByFormUsingLambdas(RHOMBUS);
//    flowerbedManager.FindFlowerbedsWithADefiniteNumberOfFlowers(6);
//    flowerbedManager.NumberOfFlowersOnCircleFlowerbeds();
//    flowerbedManager.FindFlowerbedByFormUsingFunctors(flowerbedManager, SQUARE);
}
