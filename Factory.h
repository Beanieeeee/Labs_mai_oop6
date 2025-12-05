#pragma once
#include <memory>
#include <string>
#include "NPC.h"

enum class NPCType {
    PRINCESS = 1,
    DRAGON   = 2,
    KNIGHT   = 3
};

class NPCFactory {
public:
    static std::unique_ptr<NPC> create(NPCType type,
                                       const std::string& name,
                                       int x, int y);

    // создание из строки формата "Type Name x y"
    static std::unique_ptr<NPC> createFromString(const std::string& line);
};
