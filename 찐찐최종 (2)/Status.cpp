#include "Status.h"
#include <iostream>
using namespace std;

Status::Status() {
    reset();
}

void Status::reset() {
    strength = 0;
    vulnerable = 0;
    weak = 0;
    poison = 0;
    burn = 0;
    parasite = 0;
}

int Status::getStrength() const {
    return strength;
}

int Status::getVulnerable() const {
    return vulnerable;
}

int Status::getWeak() const {
    return weak;
}

int Status::getPoison() const {
    return poison;
}

int Status::getBurn() const {
    return burn;
}

int Status::getParasite() const {
    return parasite;
}

void Status::addStrength(int amount) {
    strength += amount;
}

void Status::addVulnerable(int turn) {
    vulnerable += turn;
}

void Status::addWeak(int turn) {
    weak += turn;
}

void Status::addPoison(int amount) {
    poison += amount;
}

void Status::addBurn(int amount) {
    burn += amount;

    if (burn > 99) {
        burn = 99;
    }
}

void Status::addParasite(int amount) {
    parasite += amount;
}

void Status::removeVulnerable(int amount) {
    vulnerable = (vulnerable - amount < 0) ? 0 : vulnerable - amount;
}

void Status::removeWeak(int amount) {
    weak = (weak - amount < 0) ? 0 : weak - amount;
}

void Status::doublePoison() {
    if (poison > 0) {
        poison *= 2;
    }
}

void Status::decreasePoison() {
    if (poison > 0) {
        poison--;
    }
}

void Status::decreaseBurn() {
    if (burn > 0) {
        burn--;
    }
}

void Status::decreaseParasite() {
    if (parasite > 0) {
        parasite--;
    }
}

void Status::clearParasite() {
    parasite = 0;
}

int Status::calculateAttackDamage(int baseDamage) const {
    int damage = baseDamage + strength;

    if (weak > 0) {
        damage -= damage / 4;
    }

    return damage;
}

void Status::decreaseDebuffs() {
    if (vulnerable > 0) {
        vulnerable--;
    }

    if (weak > 0) {
        weak--;
    }
}

void Status::clearBurn() {
    burn = 0;
}