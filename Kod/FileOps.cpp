
#include "../Headers/FileOps.h"

std::string dateIntToString(int d, int m, int y)
{
    return Date(d, m, y).getDate();
}

bool FileOps::FridgeToFile(std::string filename, Fridge &fridge)
{
    std::ofstream file;
    file.open(filename);
    if (!file.is_open() || file.fail())
        return false;

    for (auto &shelf: fridge.getShelves())
    {
        file << shelf->getSpace() << ' ' << shelf->getNumber() << '\n';
    }
    file << '~' << '\n';
    for (auto &shelf: fridge.getShelves())
    {
        for (auto &item: shelf->getItems())
        {
            file << item->getName() << ' ' << item->getExpirationDate() << ' ' << item->outsideDays() << '\n';
        }
        file << '-' << '\n';
    }
    file << '~' << '\n';
    for (auto &item: fridge.getOverFlow())
    {
        file << item->getName() << ' ' << item->getExpirationDate() << ' ' << item->outsideDays() << '\n';
    }
    file << '~' << '\n';
    for (auto &pair: fridge.getOrders())
    {
        file << pair.first << ' ' << pair.second->getName() << ' ' << pair.second->getExpirationDate() << ' '
             << pair.second->outsideDays() << '\n';
    }
    file << '~' << '\n';

    file << fridge.getCurrentDate().getDate() << ' ' << fridge.getCounter();
    return true;
}

Fridge FileOps::FridgeFromFile(std::string filename)
{
    std::ifstream file;
    file.open(filename);
    if (!file.is_open() || file.fail())
        throw std::string("Something went wrong");
    std::string line;
    int tildeCounter = 0;
    std::vector<int> fridgeSpace;
    int shelfSpace;
    int shelfNum;
    char sep;
    char datedash1, datedash2;
    int d, m, y;
    bool init = false;
    int tempDaysOutside;
    std::string tempName;
    std::string tempArival;

    Fridge fridge;

    while (std::getline(file, line))
    {
        std::istringstream lineStream(line);
        if (line == "~")
        {
            tildeCounter++;
            continue;
        }
        switch (tildeCounter)
        {
            case 0:
            {
                if (lineStream >> shelfSpace)
                {
                    //if (sep != ' ') throw std::string("Something went wrong");
                    if (lineStream >> shelfNum)
                    {
                        fridgeSpace.emplace_back(shelfSpace);
                        continue;
                    }
                    throw std::string("Something went wrong");
                }
                throw std::string("Something went wrong");

            }
            case 1:
            {
                if (!init)
                {
                    fridge = Fridge(fridgeSpace, "11-11-1111");
                    shelfNum = 0;
                    init = true;
                }
                if (line == "-")
                {
                    shelfNum++;
                    continue;
                }
                if (lineStream >> tempName)
                {
                    //if (sep != ' ') throw std::string("Something went wrong");
                    if (lineStream >> d >> datedash1 >> m >> datedash2 >> y)
                    {
                        if (datedash1 != '-' || datedash2 != '-') throw std::string("Something went wrong");
                        //if (sep != ' ') throw std::string("Something went wrong");
                        if (lineStream >> tempDaysOutside)
                        {
                            fridge.put(tempName, dateIntToString(d, m, y), tempDaysOutside, shelfNum);
                            continue;
                        }
                        throw std::string("Something went wrong");
                    }
                    throw std::string("Something went wrong");
                }
                break;
            }
            case 2:
            {
                if (lineStream >> tempName)
                {
                    //if (sep != ' ') throw std::string("Something went wrong");
                    if (lineStream >> d >> datedash1 >> m >> datedash2 >> y)
                    {
                        if (datedash1 != '-' || datedash2 != '-') throw std::string("Something went wrong");
                        //if (sep != ' ') throw std::string("Something went wrong");
                        if (lineStream >> tempDaysOutside)
                        {
                            fridge.insertToOverflow(
                                    std::move(Item(tempName, dateIntToString(d, m, y), tempDaysOutside)));
                            continue;
                        }
                        throw std::string("Something went wrong");
                    }
                    throw std::string("Something went wrong");
                }
                break;
            }
            case 3:
            {
                if (lineStream >> tempArival)
                {
                    //if (sep != ' ') throw std::string("Something went wrong");
                    if (lineStream >> tempName)
                    {
                        //if (sep != ' ') throw std::string("Something went wrong");
                        if (lineStream >> d >> datedash1 >> m >> datedash2 >> y)
                        {
                            if (datedash1 != '-' || datedash2 != '-') throw std::string("Something went wrong");
                            //if (sep != ' ') throw std::string("Something went wrong");
                            if (lineStream >> tempDaysOutside)
                            {
                                auto pair = std::make_pair(tempArival,
                                                           Item(tempName, dateIntToString(d, m, y), tempDaysOutside));
                                fridge.insertToOrder(std::move(pair));
                                continue;
                            }
                            throw std::string("Something went wrong");
                        }
                        throw std::string("Something went wrong");
                    }
                    throw std::string("Something went wrong");
                }
                throw std::string("Something went wrong");
            }
            case 4:
            {
                if (lineStream >> d >> datedash1 >> m >> datedash2 >> y)
                {
                    if (datedash1 != '-' || datedash2 != '-') throw std::string("Something went wrong");
                    //if (sep != ' ') throw std::string("Something went wrong");
                    if (lineStream >> tempDaysOutside)// actually just action counter just stolen var
                    {
                        fridge.setCurrentDate(std::move(dateIntToString(d, m, y)));
                        fridge.setActionCounter(tempDaysOutside);
                        return fridge;
                    }
                    throw std::string("Something went wrong");
                }
                throw std::string("Something went wrong");
            }
            default:
                throw std::string("Something went wrong");
        }
    }
    throw std::string("Something went wrong");
}

