#include "Editor.h"
#include "Factory.h"
#include <iostream>
#include <fstream>
#include <limits>

static bool isNameUnique(const std::vector<std::unique_ptr<NPC>>& npcs,
                         const std::string& name)
{
    for (const auto& ptr : npcs) {
        if (ptr->getName() == name)
            return false;
    }
    return true;
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printNPC(const NPC& npc) {
    std::cout << npc.getName()
              << " (" << npc.getTypeName() << ")"
              << " x=" << npc.getX()
              << " y=" << npc.getY()
              << (npc.isAlive() ? " [alive]" : " [dead]")
              << std::endl;
}

void printAll(const std::vector<std::unique_ptr<NPC>>& npcs) {
    if (npcs.empty()) {
        std::cout << "Список NPC пуст.\n";
        return;
    }
    for (const auto& n : npcs) {
        printNPC(*n);
    }
}

void saveToFile(const std::vector<std::unique_ptr<NPC>>& npcs,
                const std::string& filename)
{
    std::ofstream out(filename);
    if (!out) {
        std::cout << "Не удалось открыть файл для записи\n";
        return;
    }
    for (const auto& n : npcs) {
        out << n->getTypeName() << " "
            << n->getName() << " "
            << n->getX() << " "
            << n->getY() << "\n";
    }
    std::cout << "Сохранено в файл " << filename << std::endl;
}

void loadFromFile(std::vector<std::unique_ptr<NPC>>& npcs,
                  const std::string& filename)
{
    std::ifstream in(filename);
    if (!in) {
        std::cout << "Не удалось открыть файл для чтения\n";
        return;
    }

    npcs.clear();
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto npc = NPCFactory::createFromString(line);
        if (npc) {
            npcs.push_back(std::move(npc));
        }
    }

    std::cout << "Загружено из файла " << filename << std::endl;
}

void addNPC(std::vector<std::unique_ptr<NPC>>& npcs) {
    std::cout << "Выберите тип NPC:\n";
    std::cout << "1 - Принцесса\n";
    std::cout << "2 - Дракон\n";
    std::cout << "3 - Странствующий рыцарь\n";
    int typeInt;
    std::cin >> typeInt;
    if (!std::cin || typeInt < 1 || typeInt > 3) {
        std::cout << "Неверный тип.\n";
        clearInput();
        return;
    }
    NPCType type = static_cast<NPCType>(typeInt);

    std::string name;
    std::cout << "Введите имя (без пробелов): ";
    std::cin >> name;

    if (!isNameUnique(npcs, name)) {
        std::cout << "Имя уже занято.\n";
        return;
    }

    int x, y;
    std::cout << "Введите координаты x y (0..500): ";
    std::cin >> x >> y;
    if (!std::cin || x < 0 || x > 500 || y < 0 || y > 500) {
        std::cout << "Координаты вне диапазона.\n";
        clearInput();
        return;
    }

    auto npc = NPCFactory::create(type, name, x, y);
    if (npc) {
        npcs.push_back(std::move(npc));
        std::cout << "NPC добавлен.\n";
    } else {
        std::cout << "Ошибка создания NPC.\n";
    }
}
