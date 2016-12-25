#pragma once
#include "pugixml.hpp"
#include "Context.h"
#include <string>
#include <iostream>

class io {
public:
    io(Context *c);
    void save();
    void load();
private:
    Context *context;
};
