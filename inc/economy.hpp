#pragma once

class Economy {
    public:
    Economy();   
    Economy(Economy&);
    Economy(Economy&&);
    Economy operator=(Economy&);
    ~Economy();
};