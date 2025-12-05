#pragma once
#include <vector>
#include <memory>
#include <string>
#include "NPC.h"

void addNPC(std::vector<std::unique_ptr<NPC>>& npcs);
void printAll(const std::vector<std::unique_ptr<NPC>>& npcs);
void saveToFile(const std::vector<std::unique_ptr<NPC>>& npcs,
                const std::string& filename);
void loadFromFile(std::vector<std::unique_ptr<NPC>>& npcs,
                  const std::string& filename);

void clearInput(); // для очистки ввода в main
