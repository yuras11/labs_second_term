#ifndef FLOWERBED_FLOWERBED_MANAGER_H
#define FLOWERBED_FLOWERBED_MANAGER_H

#include "flowerbed.h"

class FlowerbedManager
{
protected:
    std::vector<Flowerbed> vector_of_flowerbeds;
    std::multimap<std::string, Flowerbed> multimap_of_flowerbeds;
public:
    FlowerbedManager() = default;

    ~FlowerbedManager() = default;

    std::vector<Flowerbed> GetVectorOfFlowerbeds();

    std::string FromEnumToString(int number);

    void ReadFromFileToVector(std::string name_of_file);

    void PrintVector(const std::vector<Flowerbed>& flowerbeds);

    void SortByForm();

    void FromVectorToMultimap();

    void PrintMultimap();

    void DifferentFormsOfFlowerbeds();

    void FlowersOfADefiniteFlowerbed(int number_of_flowerbed);

    void FlowerbedWithTheBiggestAmountOfFlowers();

    void FlowerbedsWithADefiniteFlower(std::string flower);

    void FindFlowerbedByFormUsingLambdas(int int_form);

    void FindFlowerbedByFormUsingFunctors(FlowerbedManager& flowerbedManager, int int_form);

    std::vector<Flowerbed> operator()(int int_form);

    void FindFlowerbedByForm(int int_form);

    void FindFlowerbedsWithADefiniteNumberOfFlowers(int number);

    void NumberOfFlowersOnCircleFlowerbeds();
};
void solution();

#endif //FLOWERBED_FLOWERBED_MANAGER_H
