#pragma once
#include <vector>
#include <memory>
#include "NPC.h"
#include "Observer.h"

void battle(std::vector<std::unique_ptr<NPC>>& npcs,
            double maxDistance,
            std::vector<std::unique_ptr<IObserver>>& observers);
