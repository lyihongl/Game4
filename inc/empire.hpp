#pragma once
#include <memory>
#include "economy.hpp"

class Empire{
    int population;
    double money;
    std::unique_ptr<Economy> economy;

    public:
    Empire();
    Empire(const Empire&) = delete;
    Empire operator=(const Empire&) = delete;
    Empire(Empire&&);
    ~Empire();
};