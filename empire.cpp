#include "inc/empire.hpp"
#include "inc/economy.hpp"
#include "inc/constants.hpp"

#include <iostream>
#include <vector>

Empire::Empire() : foodOverhead(50) {
    economy = std::make_unique<Economy>();
    population = 10;
    money = 10;
}

void Empire::simulate(unsigned long long ticks) {
    std::vector<Constants::ResourceIndex> assignedJobs;
    if (economy->food < foodOverhead * population) {
        uint32_t foodPeople = population * 0.8;
        uint32_t rest = population - foodPeople;
    }
    std::unordered_map<Resource, uint32_t> peopleAllocation;

    if (ticks % 240 == 0) {
        economy->produce(peopleAllocation);
        economy->print();
    }
}

Empire::~Empire() {
}