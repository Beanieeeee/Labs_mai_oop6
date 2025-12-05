#pragma once
#include <string>
#include "Visitor.h"

class NPC {
protected:
    std::string name;
    int x;
    int y;
    bool alive;

public:
    NPC(const std::string& n, int x_, int y_)
        : name(n), x(x_), y(y_), alive(true) {}

    virtual ~NPC() = default;

    const std::string& getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    bool isAlive() const { return alive; }
    void kill() { alive = false; }

    virtual std::string getTypeName() const = 0;
    virtual void accept(INPCVisitor& v) = 0;
};

class Princess : public NPC {
public:
    Princess(const std::string& n, int x, int y) : NPC(n, x, y) {}
    std::string getTypeName() const override { return "Princess"; }
    void accept(INPCVisitor& v) override;
};

class Dragon : public NPC {
public:
    Dragon(const std::string& n, int x, int y) : NPC(n, x, y) {}
    std::string getTypeName() const override { return "Dragon"; }
    void accept(INPCVisitor& v) override;
};

class Knight : public NPC {
public:
    Knight(const std::string& n, int x, int y) : NPC(n, x, y) {}
    std::string getTypeName() const override { return "Knight"; }
    void accept(INPCVisitor& v) override;
};
