#include <iostream>
#include <vector>
#include <memory>
#include "NPC.h"
#include "Observer.h"
#include "Editor.h"
#include "Battle.h"

int main() {
    std::vector<std::unique_ptr<NPC>> npcs;

    // наблюдатели (Observer)
    std::vector<std::unique_ptr<IObserver>> observers;
    observers.push_back(std::make_unique<ConsoleObserver>());
    observers.push_back(std::make_unique<FileObserver>());

    int choice;
    do {
        std::cout << "\n=== Редактор подzemелья (вариант 12) ===\n";
        std::cout << "1. Добавить NPC\n";
        std::cout << "2. Показать всех NPC\n";
        std::cout << "3. Сохранить NPC в файл\n";
        std::cout << "4. Загрузить NPC из файла\n";
        std::cout << "5. Запустить боевой режим\n";
        std::cout << "0. Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        if (!std::cin) {
            clearInput();
            continue;
        }

        switch (choice) {
            case 1:
                addNPC(npcs);
                break;
            case 2:
                printAll(npcs);
                break;
            case 3: {
                std::string filename;
                std::cout << "Имя файла: ";
                std::cin >> filename;
                saveToFile(npcs, filename);
                break;
            }
            case 4: {
                std::string filename;
                std::cout << "Имя файла: ";
                std::cin >> filename;
                loadFromFile(npcs, filename);
                break;
            }
            case 5: {
                double dist;
                std::cout << "Максимальная дистанция боя: ";
                std::cin >> dist;
                if (!std::cin || dist < 0) {
                    std::cout << "Некорректная дистанция.\n";
                    clearInput();
                    break;
                }
                battle(npcs, dist, observers);
                break;
            }
            case 0:
                std::cout << "Выход.\n";
                break;
            default:
                std::cout << "Неизвестный пункт.\n";
        }
    } while (choice != 0);

    return 0;
}
