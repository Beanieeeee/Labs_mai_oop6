#include "NPC.h"

void Princess::accept(INPCVisitor& v) {
    v.visit(*this);
}

void Dragon::accept(INPCVisitor& v) {
    v.visit(*this);
}

void Knight::accept(INPCVisitor& v) {
    v.visit(*this);
}
