#pragma once
#include "inc/resource.hpp"

#include <unordered_map>

class Economy {
    public:
    int wood;
    int food;

    Economy();   
    Economy(Economy&);
    Economy(Economy&&);
    Economy operator=(Economy&);
    ~Economy();
    void produce(std::unordered_map<Resource, uint32_t>&);
    void print() const;
};