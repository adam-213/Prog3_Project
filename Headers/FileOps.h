#pragma once

#include <fstream>

#include "Fridge.h"

class FileOps
{
public:

    static bool FridgeToFile(std::string filename, Fridge &fridge);

    static Fridge FridgeFromFile(std::string filename);
};

