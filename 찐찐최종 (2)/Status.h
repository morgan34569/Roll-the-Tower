#ifndef STATUS_H
#define STATUS_H

class Status {
private:
    int strength;
    int vulnerable;
    int weak;
    int poison;
    int burn;
    int parasite;

public:
    Status();

    int getStrength() const;
    int getVulnerable() const;
    int getWeak() const;
    int getPoison() const;
    int getBurn() const;
    int getParasite() const;

    void addStrength(int amount);
    void addVulnerable(int turn);
    void addWeak(int turn);
    void addPoison(int amount);
    void addBurn(int amount);
    void addParasite(int amount);

    void removeVulnerable(int amount);
    void removeWeak(int amount);
    void doublePoison();
    void decreasePoison();
    void decreaseBurn();
    void decreaseParasite();
    void clearBurn();
    void clearParasite();

    void setStrength(int v) { strength = v; }
    void setVulnerable(int v) { vulnerable = v; }
    void setWeak(int v) { weak = v; }
    void setPoison(int v) { poison = v; }
    void setParasite(int v) { parasite = v; }

    int calculateAttackDamage(int baseDamage) const;
    void decreaseDebuffs();
    void reset();
};
#endif
