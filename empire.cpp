#include "inc/empire.hpp"
#include "inc/economy.hpp"

Empire::Empire(){
    economy = std::make_unique<Economy>(Economy());
}