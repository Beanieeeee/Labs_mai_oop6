#include "Battle.h"
#include "Visitor.h"
#include <cmath>
#include <algorithm>

// Visitor, который определяет, убивает ли атакующий защитника
class BattleVisitor : public INPCVisitor {
    NPC& attacker;
    NPC& defender;
    bool attackerKills = false;

public:
    BattleVisitor(NPC& a, NPC& d) : attacker(a), defender(d) {}

    void visit(Princess& /*p*/) override {
        // Принцесса никого не трогает
        attackerKills = false;
    }

    void visit(Dragon& /*d*/) override {
        // Дракон ест принцесс
        if (defender.getTypeName() == "Princess")
            attackerKills = true;
    }

    void visit(Knight& /*k*/) override {
        // Рыцарь ест драконов
        if (defender.getTypeName() == "Dragon")
            attackerKills = true;
    }

    bool doesAttackerKill() const { return attackerKills; }
};

static double distance(const NPC& a, const NPC& b) {
    int dx = a.getX() - b.getX();
    int dy = a.getY() - b.getY();
    return std::sqrt(dx * dx + dy * dy);
}

void battle(std::vector<std::unique_ptr<NPC>>& npcs,
            double maxDistance,
            std::vector<std::unique_ptr<IObserver>>& observers)
{
    if (npcs.size() < 2) {
        std::cout << "Недостаточно NPC для боя.\n";
        return;
    }

    // каждый с каждым
    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            NPC& A = *npcs[i];
            NPC& B = *npcs[j];

            if (!A.isAlive() || !B.isAlive()) continue;

            double d = distance(A, B);
            if (d > maxDistance) continue;

            // A атакует B
            BattleVisitor v1(A, B);
            A.accept(v1);
            bool aKillsB = v1.doesAttackerKill();

            // B атакует A
            BattleVisitor v2(B, A);
            B.accept(v2);
            bool bKillsA = v2.doesAttackerKill();

            if (aKillsB) {
                B.kill();
                for (auto& obs : observers)
                    obs->onKill(A.getName(), B.getName());
            }
            if (bKillsA) {
                A.kill();
                for (auto& obs : observers)
                    obs->onKill(B.getName(), A.getName());
            }
        }
    }

    // удаляем погибших
    npcs.erase(
        std::remove_if(npcs.begin(), npcs.end(),
            [](const std::unique_ptr<NPC>& n) { return !n->isAlive(); }),
        npcs.end()
    );

    std::cout << "Бой завершён.\n";
}
