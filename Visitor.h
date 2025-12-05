#pragma once

class Princess;
class Dragon;
class Knight;

class INPCVisitor {
public:
    virtual ~INPCVisitor() = default;
    virtual void visit(Princess& p) = 0;
    virtual void visit(Dragon& d) = 0;
    virtual void visit(Knight& k) = 0;
};
