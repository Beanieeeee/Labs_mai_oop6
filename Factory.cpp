#include "Factory.h"
#include <sstream>

std::unique_ptr<NPC> NPCFactory::create(NPCType type,
                                        const std::string& name,
                                        int x, int y)
{
    switch (type) {
        case NPCType::PRINCESS:
            return std::make_unique<Princess>(name, x, y);
        case NPCType::DRAGON:
            return std::make_unique<Dragon>(name, x, y);
        case NPCType::KNIGHT:
            return std::make_unique<Knight>(name, x, y);
        default:
            return nullptr;
    }
}

std::unique_ptr<NPC> NPCFactory::createFromString(const std::string& line) {
    std::istringstream iss(line);
    std::string typeStr;
    std::string name;
    int x, y;
    if (!(iss >> typeStr >> name >> x >> y)) {
        return nullptr;
    }

    NPCType type;
    if (typeStr == "Princess") type = NPCType::PRINCESS;
    else if (typeStr == "Dragon") type = NPCType::DRAGON;
    else if (typeStr == "Knight") type = NPCType::KNIGHT;
    else return nullptr;

    return create(type, name, x, y);
}
