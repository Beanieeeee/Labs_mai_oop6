#pragma once
#include <string>
#include <fstream>
#include <iostream>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onKill(const std::string& killer,
                        const std::string& victim) = 0;
};

class ConsoleObserver : public IObserver {
public:
    void onKill(const std::string& killer,
                const std::string& victim) override {
        std::cout << "[LOG] " << killer << " убивает " << victim << std::endl;
    }
};

class FileObserver : public IObserver {
public:
    void onKill(const std::string& killer,
                const std::string& victim) override {
        std::ofstream out("log.txt", std::ios::app);
        if (out) {
            out << killer << " убивает " << victim << "\n";
        }
    }
};
