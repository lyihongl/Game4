#include "inc/economy.hpp"
#include "inc/constants.hpp"

#include <iostream>
#include <vector>

Economy::Economy() {
    wood = 0;
    food = 10;
}

Economy::Economy(Economy &e){

}

Economy::Economy(Economy &&e){

}

Economy Economy::operator=(Economy &e){
    return {};
}

Economy::~Economy(){}

void Economy::produce(std::unordered_map<Resource, uint32_t> &people) {
}

void Economy::print() const {
    std::cout<<"== economy ==\n";
    std::cout<<"wood: "<<wood<<"\n";
    std::cout<<"food: "<<food<<"\n";
    std::cout<<std::endl;
}