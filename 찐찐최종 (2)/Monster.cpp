#include "Monster.h"
#include "Player.h"
#include "Weapon.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Monster::takeDamage(int damage) {
    if (vulnerable > 0) {
        damage += damage / 2;
    }

    if (damaged > 0) {
        damage += damaged;
    }

    int remainDamage = damage - block;

    if (remainDamage < 0) {
        block -= damage;
        remainDamage = 0;
    }
    else {
        block = 0;
    }

    hp -= remainDamage;

    if (hp < 0) {
        hp = 0;
    }

    cout << name << "이(가) " << remainDamage << " 피해를 받았습니다.\n";
}

void Monster::addBlock(int amount) {
    int realBlock = amount;

    if (damaged > 0) {
        realBlock = amount / 2;
        cout << name << "은(는) 손상 상태라 방어 획득량이 절반으로 감소했습니다.\n";
    }

    block += realBlock;
    cout << name << "이(가) 방어 " << realBlock << "을 얻었습니다.\n";
}

void Monster::addVulnerable(int turn) {
    vulnerable += turn;
    cout << name << "이(가) 취약 " << turn << "을 얻었습니다. 현재 취약: " << vulnerable << "\n";
}

void Monster::addBurn(int amount) {
    burn += amount;
    if (burn > 99) burn = 99;

    cout << name << "이(가) 화상 " << amount << "을 얻었습니다. 현재 화상: " << burn << "\n";
}

void Monster::addDamaged(int amount) {
    damaged += amount;
    cout << name << "이(가) 손상 " << amount << "을 얻었습니다. 현재 손상: " << damaged << "\n";
}

void Monster::applyBurnDamage() {
    if (burn <= 0) return;

    cout << name << "이(가) 화상으로 " << burn << " 피해를 받았습니다.\n";
    hp -= burn;
    if (hp < 0) hp = 0;

    burn--;
    cout << "화상 수치가 1 감소했습니다. 현재 화상: " << burn << "\n";
}

void Monster::clearBlock() {
    block = 0;
}

// ======================================
// 1. 평원 몬스터
// ======================================

JawWorm::JawWorm() : Monster("턱벌레", 30, Element::NATURE) {
    patternIndex = 0;
}

void JawWorm::decideIntent() {
    if (patternIndex == 0) {
        intent = INTENT_ATTACK;
    }
    else if (patternIndex == 1) {
        intent = INTENT_BLOCK;
    }
    else {
        intent = INTENT_BUFF;
    }

    patternIndex++;

    if (patternIndex >= 3) {
        patternIndex = 0;
    }
}

void JawWorm::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_ATTACK) {
        cout << "공격 - " << 7 + strength << " 피해\n";
    }
    else if (intent == INTENT_BLOCK) {
        cout << "수비 - 방어 10\n";
    }
    else if (intent == INTENT_BUFF) {
        cout << "강화 - 공격 피해 +3\n";
    }
}

void JawWorm::executeIntent(Player& player) {
    if (intent == INTENT_ATTACK) {
        int damage = 7 + strength;
        cout << "턱벌레가 공격합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);
    }
    else if (intent == INTENT_BLOCK) {
        cout << "턱벌레가 수비합니다.\n";
        addBlock(10);
    }
    else if (intent == INTENT_BUFF) {
        strength += 3;
        cout << "턱벌레가 강화합니다. 공격력이 3 증가했습니다.\n";
    }
}

BallBug::BallBug() : Monster("공벌레", 38, Element::NATURE) {
    curlUsed = false;
    patternIndex = 0;
}

void BallBug::takeDamage(int damage) {
    if (!curlUsed) {
        curlUsed = true;
        block += 10;
        cout << "공벌레의 공말기 발동! 방어 10을 얻었습니다.\n";
    }

    Monster::takeDamage(damage);
}

void BallBug::decideIntent() {
    if (patternIndex == 0) {
        intent = INTENT_ATTACK;
    }
    else if (patternIndex == 1) {
        intent = INTENT_DEBUFF;
    }
    else {
        intent = INTENT_BLOCK;
    }

    patternIndex++;

    if (patternIndex >= 3) {
        patternIndex = 0;
    }
}

void BallBug::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_ATTACK) {
        cout << "공격 - 6 피해\n";
    }
    else if (intent == INTENT_DEBUFF) {
        cout << "실뿜기 - 약화 2 부여\n";
    }
    else if (intent == INTENT_BLOCK) {
        cout << "수비 - 방어 6\n";
    }
}

void BallBug::executeIntent(Player& player) {
    if (intent == INTENT_ATTACK) {
        cout << "공벌레가 공격합니다. 피해: 6\n";
        player.takeDamage(6);
    }
    else if (intent == INTENT_DEBUFF) {
        cout << "공벌레가 실뿜기를 사용합니다. 플레이어에게 약화 2를 부여합니다.\n";
        player.getStatus().addWeak(2);
    }
    else if (intent == INTENT_BLOCK) {
        cout << "공벌레가 수비합니다.\n";
        addBlock(6);
    }
}

SporeFungus::SporeFungus() : Monster("버섯포자", 24, Element::NATURE) {
    growth = 0;
    patternIndex = 0;
}

void SporeFungus::onTurnStart() {
    Monster::onTurnStart();

    growth += 2;
    cout << "버섯포자의 특수능력 성장으로 성장 수치가 2 증가했습니다. 현재 성장: " << growth << "\n";
}

void SporeFungus::decideIntent() {
    if (patternIndex == 0) {
        intent = INTENT_BUFF;
    }
    else if (patternIndex == 1) {
        intent = INTENT_ATTACK;
    }
    else {
        intent = INTENT_BLOCK;
    }

    patternIndex++;

    if (patternIndex >= 3) {
        patternIndex = 0;
    }
}

void SporeFungus::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_BUFF) {
        cout << "성장 - 성장 수치 +3\n";
    }
    else if (intent == INTENT_ATTACK) {
        cout << "공격 - 5 피해, 취약 1 부여\n";
    }
    else if (intent == INTENT_BLOCK) {
        cout << "수비 - 방어 5\n";
    }
}

void SporeFungus::printExtraStatus() const {
    cout << " | 성장: " << growth;
}

void SporeFungus::executeIntent(Player& player) {
    if (intent == INTENT_BUFF) {
        growth += 3;
        cout << "버섯포자가 성장합니다. 성장 수치가 3 증가했습니다. 현재 성장: " << growth << "\n";
    }
    else if (intent == INTENT_ATTACK) {
        cout << "버섯포자가 공격합니다. 피해: 5, 취약 1 부여\n";
        player.takeDamage(5);
        player.getStatus().addVulnerable(1);
    }
    else if (intent == INTENT_BLOCK) {
        cout << "버섯포자가 수비합니다.\n";
        addBlock(5);
    }
}

void SporeFungus::onDeath(Player& player) {
    if (growth > 0) {
        cout << "버섯포자가 죽으며 자폭합니다. 피해: " << growth << "\n";
        player.takeDamage(growth);
    }
}

Mosquito::Mosquito() : Monster("모기", 35, Element::NATURE) {
    patternIndex = 0;
    blood = 0;
    flyingGuard = false;
}

void Mosquito::takeDamage(int damage) {
    if (flyingGuard) {
        damage /= 2;
        flyingGuard = false;

        cout << "모기의 비행 효과로 받는 피해가 절반으로 감소합니다.\n";
    }

    Monster::takeDamage(damage);
}

void Mosquito::decideIntent() {
    if (patternIndex == 0) {
        intent = INTENT_ATTACK;
    }
    else if (patternIndex == 1) {
        intent = INTENT_BLOOD_BUFF;
    }
    else {
        intent = INTENT_FLIGHT;
    }

    patternIndex++;

    if (patternIndex >= 3) {
        patternIndex = 0;
    }
}

void Mosquito::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_ATTACK) {
        cout << "공격 - " << 13 + strength << " 피해\n";
    }
    else if (intent == INTENT_BLOOD_BUFF) {
        cout << "혈액강화 - 혈액 수치(" << blood << ")만큼 힘 증가\n";
    }
    else if (intent == INTENT_FLIGHT) {
        cout << "비행 - 다음 턴 받는 피해 절반\n";
    }
}

void Mosquito::executeIntent(Player& player) {
    if (intent == INTENT_ATTACK) {
        int damage = 13 + strength;

        cout << "모기가 공격합니다. 피해: " << damage << "\n";

        int beforeHP = player.getHP();
        player.takeDamage(damage);
        int afterHP = player.getHP();

        int actualDamage = beforeHP - afterHP;

        if (actualDamage > 0) {
            heal(actualDamage);
            blood += 1;
            player.getStatus().addWeak(1);

            cout << "모기의 흡혈 발동! " << actualDamage << " 회복했습니다.\n";
            cout << "모기의 혈액 수치가 1 증가했습니다. 현재 혈액: " << blood << "\n";
            cout << "플레이어에게 약화 1을 부여했습니다.\n";
        }
    }
    else if (intent == INTENT_BLOOD_BUFF) {
        strength += blood;
        cout << "모기가 혈액강화를 사용합니다. 혈액 수치 " << blood << "만큼 공격력이 증가했습니다.\n";
        cout << "현재 모기 추가 공격력: " << strength << "\n";
    }
    else if (intent == INTENT_FLIGHT) {
        flyingGuard = true;
        cout << "모기가 비행합니다. 다음 턴 받는 피해가 절반이 됩니다.\n";
    }
}

InfectedHost::InfectedHost() : Monster("감염체", 30, Element::NATURE) {
    patternIndex = 0;
    cout << "감염체가 감염 버프를 가진 채로 등장했습니다.\n";
}

void InfectedHost::decideIntent() {
    // 패턴: 2 -> 1
    if (patternIndex == 0) {
        intent = INTENT_PARASITE;
    }
    else {
        intent = INTENT_ATTACK;
    }

    patternIndex++;

    if (patternIndex >= 2) {
        patternIndex = 0;
    }
}

void InfectedHost::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_PARASITE) {
        cout << "기생 - 전투 종료까지 유지되는 기생 1 부여\n";
    }
    else if (intent == INTENT_ATTACK) {
        cout << "연속 공격 - 4 피해 x 4\n";
    }
}

void InfectedHost::executeIntent(Player& player) {
    if (intent == INTENT_PARASITE) {
        cout << "감염체가 기생을 사용합니다. 플레이어에게 기생 1을 부여합니다.\n";
        player.getStatus().addParasite(1);
    }
    else if (intent == INTENT_ATTACK) {
        cout << "감염체가 연속 공격을 사용합니다. 4 피해로 4번 공격합니다.\n";

        for (int i = 0; i < 4; i++) {
            player.takeDamage(4);
        }
    }
}

Monster* InfectedHost::getNextMonsterOnDeath() {
    cout << "\n감염체의 몸이 갈라지며 안에서 기생체가 튀어나왔습니다!\n";
    return new Parasite();
}

Parasite::Parasite() : Monster("기생체", 30, Element::NATURE) {
    patternIndex = 0;
}

void Parasite::decideIntent() {
    // 패턴: 1 -> 2 -> 3
    if (patternIndex == 0) {
        intent = INTENT_ATTACK;
    }
    else if (patternIndex == 1) {
        intent = INTENT_PREPARE;
    }
    else {
        intent = INTENT_EXPLODE;
    }

    patternIndex++;

    if (patternIndex >= 3) {
        patternIndex = 0;
    }
}

void Parasite::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_ATTACK) {
        cout << "공격 - 5 피해\n";
    }
    else if (intent == INTENT_PREPARE) {
        cout << "준비단계 - 이번 턴 아무 행동도 하지 않음\n";
    }
    else if (intent == INTENT_EXPLODE) {
        cout << "기생체 폭발 - 기생 수치의 3배 피해\n";
    }
}

void Parasite::executeIntent(Player& player) {
    if (intent == INTENT_ATTACK) {
        cout << "기생체가 공격합니다. 피해: 5\n";
        player.takeDamage(5);
    }
    else if (intent == INTENT_PREPARE) {
        cout << "기생체가 폭발을 준비합니다. 이번 턴에는 아무 행동도 하지 않습니다.\n";
    }
    else if (intent == INTENT_EXPLODE) {
        int parasite = player.getStatus().getParasite();
        int damage = parasite * 3;

        cout << "기생체가 폭발합니다! 기생 수치 " << parasite << "의 3배 피해: " << damage << "\n";
        player.takeDirectDamage(damage);
    }
}

// ======================================
// 보스 몬스터: 장수말벌
// ======================================

GiantHornet::GiantHornet() : Monster("장수말벌", 50, Element::NATURE) {
    patternIndex = 0;
    flyingGuard = false;
}

void GiantHornet::takeDamage(int damage) {
    if (flyingGuard) {
        damage /= 2;
        flyingGuard = false;

        cout << "장수말벌의 비행 효과로 받는 피해가 절반으로 감소합니다.\n";
    }

    Monster::takeDamage(damage);
}

void GiantHornet::decideIntent() {
    if (patternIndex == 0) {
        intent = INTENT_FLIGHT;
    }
    else if (patternIndex == 1) {
        intent = INTENT_POISON_ATTACK;
    }
    else if (patternIndex == 2) {
        intent = INTENT_DOUBLE_POISON;
    }
    else {
        intent = INTENT_BUFF;
    }

    patternIndex++;

    if (patternIndex >= 4) {
        patternIndex = 0;
    }
}

void GiantHornet::showIntent() const {
    cout << "보스 행동 예고: ";

    if (intent == INTENT_FLIGHT) {
        cout << "비행 - 방어 10 획득, 다음 턴 받는 일반 피해 절반\n";
    }
    else if (intent == INTENT_POISON_ATTACK) {
        cout << "독찌르기 - " << 10 + strength << " 피해, 피해를 입으면 독 5 부여\n";
    }
    else if (intent == INTENT_DOUBLE_POISON) {
        cout << "맹독 - 플레이어의 독 수치 2배\n";
    }
    else if (intent == INTENT_BUFF) {
        cout << "강화 - 공격 피해 +5\n";
    }
}

void GiantHornet::executeIntent(Player& player) {
    if (intent == INTENT_FLIGHT) {
        cout << "장수말벌이 공중으로 날아오릅니다. 방어 10을 얻고 다음 턴 받는 피해가 절반이 됩니다.\n";
        addBlock(10);
        flyingGuard = true;
    }
    else if (intent == INTENT_POISON_ATTACK) {
        int beforeHP = player.getHP();
        int damage = 10 + strength;

        cout << "장수말벌이 독찌르기를 사용합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);

        int afterHP = player.getHP();

        if (afterHP < beforeHP) {
            player.getStatus().addPoison(5);
            cout << "독찌르기 피해를 받아 플레이어에게 독 5가 부여되었습니다.\n";
        }
        else {
            cout << "독찌르기를 완전히 막아 독에 걸리지 않았습니다.\n";
        }
    }
    else if (intent == INTENT_DOUBLE_POISON) {
        if (player.getStatus().getPoison() > 0) {
            player.getStatus().doublePoison();
            cout << "장수말벌이 맹독을 사용합니다. 플레이어의 독 수치가 2배가 되었습니다.\n";
            cout << "현재 독 수치: " << player.getStatus().getPoison() << "\n";
        }
        else {
            cout << "장수말벌이 맹독을 사용했지만, 플레이어에게 독이 없어 아무 일도 일어나지 않았습니다.\n";
        }
    }
    else if (intent == INTENT_BUFF) {
        strength += 5;
        cout << "장수말벌이 강화합니다. 공격력이 5 증가했습니다.\n";
    }
}

// ======================================
// 2. 설원 몬스터
// ======================================

Snowman::Snowman() : Monster("스노우맨", 30, Element::WATER) {
    patternIndex = 0;
    freezeApplied = false;
    block = 15;
}

void Snowman::clearBlock() {
    // 스노우맨은 턴이 끝나도 방어도를 잃지 않음
}

void Snowman::onPlayerActionEnd(Player& player) {
    if (!freezeApplied) {
        return;
    }

    int stealBlock = player.getBlock() / 2;

    if (stealBlock > 0) {
        cout << "\n[빙결] 플레이어의 방어도 " << stealBlock << "이 얼어붙어 스노우맨의 방어도로 전환됩니다.\n";
        player.removeBlock(stealBlock);
        addBlock(stealBlock);
    }
}

void Snowman::decideIntent() {
    // 패턴: 1 > 2 > 3
    if (patternIndex == 0) {
        intent = INTENT_FREEZE;
    }
    else if (patternIndex == 1) {
        intent = INTENT_BLOCK;
    }
    else {
        intent = INTENT_ATTACK;
    }

    patternIndex++;

    if (patternIndex >= 3) {
        patternIndex = 0;
    }
}

void Snowman::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_FREEZE) {
        cout << "빙결 부여 - 전투 동안 플레이어 행동 종료마다 방어 절반 흡수\n";
    }
    else if (intent == INTENT_BLOCK) {
        cout << "압축 - 방어 20\n";
    }
    else if (intent == INTENT_ATTACK) {
        cout << "몸통박치기 - 현재 스노우맨 방어도만큼 피해\n";
    }
}

void Snowman::printExtraStatus() const {
    if (freezeApplied) {
        cout << " | 빙결 유지 중";
    }
}

void Snowman::executeIntent(Player& player) {
    if (intent == INTENT_FREEZE) {
        cout << "스노우맨이 빙결을 부여합니다.\n";
        cout << "전투가 끝날 때까지 플레이어 행동 종료마다 방어도 절반을 흡수합니다.\n";
        freezeApplied = true;
    }
    else if (intent == INTENT_BLOCK) {
        cout << "스노우맨이 몸을 압축합니다. 방어 20을 얻습니다.\n";
        addBlock(20);
    }
    else if (intent == INTENT_ATTACK) {
        int damage = block;
        cout << "스노우맨이 몸통박치기를 사용합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);
    }
}

SeaAnemone::SeaAnemone() : Monster("말미잘", 40, Element::WATER) {
    patternIndex = 0;
}

void SeaAnemone::decideIntent() {
    // 패턴: 3 > 1 > 2
    if (patternIndex == 0) {
        intent = INTENT_POISON_ATTACK;  // 독바르기
    }
    else if (patternIndex == 1) {
        intent = INTENT_ATTACK;         // 독침
    }
    else {
        intent = INTENT_DOUBLE_POISON;  // 맹독
    }

    patternIndex++;

    if (patternIndex >= 3) {
        patternIndex = 0;
    }
}

void SeaAnemone::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_POISON_ATTACK) {
        cout << "독바르기 - 독 5 부여\n";
    }
    else if (intent == INTENT_ATTACK) {
        cout << "독침 - " << 10 + strength << " 피해, 막히지 않으면 독 10 부여\n";
    }
    else if (intent == INTENT_DOUBLE_POISON) {
        cout << "맹독 - 플레이어의 독을 3배로 만듦\n";
    }
}

void SeaAnemone::executeIntent(Player& player) {
    if (intent == INTENT_POISON_ATTACK) {
        cout << "말미잘이 독바르기를 사용합니다. 독 5를 부여합니다.\n";
        player.getStatus().addPoison(5);
    }
    else if (intent == INTENT_ATTACK) {
        int damage = 10 + strength;
        int beforeHP = player.getHP();

        cout << "말미잘이 독침을 사용합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);

        if (player.getHP() < beforeHP) {
            cout << "독침이 방어를 뚫고 들어가 독 10을 부여합니다.\n";
            player.getStatus().addPoison(10);
        }
        else {
            cout << "독침이 전부 막혀 독이 부여되지 않았습니다.\n";
        }
    }
    else if (intent == INTENT_DOUBLE_POISON) {
        if (player.getStatus().getPoison() > 0) {
            cout << "말미잘이 맹독을 사용합니다. 독이 3배가 됩니다.\n";
            player.getStatus().doublePoison();
            player.getStatus().doublePoison();
        }
        else {
            cout << "플레이어에게 독이 없어 맹독이 실패했습니다.\n";
        }
    }
}

Yeti::Yeti() : Monster("예티", 100, Element::WATER) {
    patternIndex = 0;
}

void Yeti::takeDamage(int damage) {
    if (burn > 0) {
        cout << "[예티 특수 효과] 화상 상태라 받는 피해가 50% 증가합니다!\n";
        damage += damage / 2;
    }

    Monster::takeDamage(damage);
}

void Yeti::decideIntent() {
    // 패턴: 1 > 2 > 4 > 3
    if (patternIndex == 0) {
        intent = INTENT_ATTACK;
    }
    else if (patternIndex == 1) {
        intent = INTENT_DEBUFF;
    }
    else if (patternIndex == 2) {
        intent = INTENT_BLOCK;
    }
    else {
        intent = INTENT_BUFF;
    }

    patternIndex++;

    if (patternIndex >= 4) {
        patternIndex = 0;
    }
}

void Yeti::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_ATTACK) {
        cout << "휘두르기 - " << 18 + strength << " 피해\n";
    }
    else if (intent == INTENT_DEBUFF) {
        cout << "얼음 던지기 - " << 14 + strength << " 피해, 취약 5 부여\n";
    }
    else if (intent == INTENT_BLOCK) {
        cout << "가드 - 방어 10\n";
    }
    else if (intent == INTENT_BUFF) {
        cout << "광폭화 - 힘 2 증가\n";
    }
}

void Yeti::executeIntent(Player& player) {
    if (intent == INTENT_ATTACK) {
        int damage = 18 + strength;
        cout << "예티가 휘두르기를 사용합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);
    }
    else if (intent == INTENT_DEBUFF) {
        int damage = 14 + strength;
        cout << "예티가 얼음 던지기를 사용합니다. 피해: " << damage << ", 취약 5 부여\n";
        player.takeDamage(damage);
        player.getStatus().addVulnerable(5);
    }
    else if (intent == INTENT_BLOCK) {
        cout << "예티가 가드합니다.\n";
        addBlock(10);
    }
    else if (intent == INTENT_BUFF) {
        cout << "예티가 광폭화합니다. 힘이 2 증가합니다.\n";
        strength += 2;
    }
}

WolfSpirit::WolfSpirit() : Monster("늑대영혼", 60, Element::WATER) {
    patternIndex = 0;
    etherealCount = 0;
}

void WolfSpirit::takeDamage(int damage) {
    if (etherealCount > 0) {
        cout << "[영체화] 늑대영혼이 피해를 받지 않습니다!\n";
        return;
    }

    Monster::takeDamage(damage);
}

void WolfSpirit::onTurnStart() {
    Monster::onTurnStart();

    if (etherealCount > 0) {
        etherealCount--;
    }
}

void WolfSpirit::decideIntent() {
    // 패턴: 1 > 2 > 3 > 4
    if (patternIndex == 0) {
        intent = INTENT_ATTACK;
    }
    else if (patternIndex == 1) {
        intent = INTENT_FLIGHT;
    }
    else if (patternIndex == 2) {
        intent = INTENT_BUFF;
    }
    else {
        intent = INTENT_DEBUFF;
    }

    patternIndex++;

    if (patternIndex >= 4) {
        patternIndex = 0;
    }
}

void WolfSpirit::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_ATTACK) {
        cout << "얼음엄니 - " << 17 + strength << " 피해, 취약 5 부여\n";
    }
    else if (intent == INTENT_FLIGHT) {
        cout << "영체화 - 다음 두 번의 턴 동안 피해를 받지 않음\n";
    }
    else if (intent == INTENT_BUFF) {
        cout << "이빨갈기 - 힘 4 증가\n";
    }
    else if (intent == INTENT_DEBUFF) {
        cout << "하울링 - 약화 2 부여\n";
    }
}

void WolfSpirit::printExtraStatus() const {
    if (etherealCount > 0) {
        cout << " | 영체화: " << etherealCount << "턴";
    }
}

void WolfSpirit::executeIntent(Player& player) {
    if (intent == INTENT_ATTACK) {
        int damage = 17 + strength;
        cout << "늑대영혼이 얼음엄니를 사용합니다. 피해: " << damage << ", 취약 5 부여\n";
        player.takeDamage(damage);
        player.getStatus().addVulnerable(5);
    }
    else if (intent == INTENT_FLIGHT) {
        cout << "늑대영혼이 영체화합니다. 다음 두 번의 턴 동안 피해를 받지 않습니다.\n";
        etherealCount = 2;
    }
    else if (intent == INTENT_BUFF) {
        cout << "늑대영혼이 이빨을 갑니다. 힘이 4 증가합니다.\n";
        strength += 4;
    }
    else if (intent == INTENT_DEBUFF) {
        cout << "늑대영혼이 하울링합니다. 약화 2를 부여합니다.\n";
        player.getStatus().addWeak(2);
    }
}

EarthTurtle::EarthTurtle() : Monster("대지거북", 80, Element::NATURE) {
    patternIndex = 0;
}

void EarthTurtle::decideIntent() {
    // 패턴: 2 > 1 > 3 > 4
    if (patternIndex == 0) {
        intent = INTENT_DEBUFF;
    }
    else if (patternIndex == 1) {
        intent = INTENT_ATTACK;
    }
    else if (patternIndex == 2) {
        intent = INTENT_BUFF;
    }
    else {
        intent = INTENT_BLOCK;
    }

    patternIndex++;

    if (patternIndex >= 4) {
        patternIndex = 0;
    }
}

void EarthTurtle::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_DEBUFF) {
        cout << "지진 - " << 10 + strength << " 피해, 취약 2, 약화 2 부여\n";
    }
    else if (intent == INTENT_ATTACK) {
        cout << "돌진 - " << 20 + strength << " 피해\n";
    }
    else if (intent == INTENT_BUFF) {
        cout << "광합성 - 체력 15 회복\n";
    }
    else if (intent == INTENT_BLOCK) {
        cout << "껍질에 숨기 - 방어 10\n";
    }
}

void EarthTurtle::executeIntent(Player& player) {
    if (intent == INTENT_DEBUFF) {
        int damage = 10 + strength;
        cout << "대지거북이 지진을 일으킵니다. 피해: " << damage << ", 취약 2, 약화 2 부여\n";
        player.takeDamage(damage);
        player.getStatus().addVulnerable(2);
        player.getStatus().addWeak(2);
    }
    else if (intent == INTENT_ATTACK) {
        int damage = 20 + strength;
        cout << "대지거북이 돌진합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);
    }
    else if (intent == INTENT_BUFF) {
        cout << "대지거북이 광합성으로 체력 15를 회복합니다.\n";
        heal(15);
    }
    else if (intent == INTENT_BLOCK) {
        cout << "대지거북이 껍질에 숨습니다. 방어 10을 얻습니다.\n";
        addBlock(10);
    }
}

ElementalBoss::ElementalBoss() : Monster("정령", 270, Element::WATER) {
    patternIndex = 0;
    icePassive = false;
    waterPassive = false;
}

void ElementalBoss::takeDamage(int damage) {
    if (icePassive) {
        cout << "[냉기 패시브] 받는 피해가 30% 감소합니다.\n";
        damage = damage * 70 / 100;
    }

    Monster::takeDamage(damage);
}

void ElementalBoss::decideIntent() {
    // 패턴: 1 > 2 > 3 > 4 > 5 > 6
    if (patternIndex == 0) {
        intent = INTENT_BLOCK;
    }
    else if (patternIndex == 1) {
        intent = INTENT_ATTACK;
    }
    else if (patternIndex == 2) {
        intent = INTENT_DEBUFF;
    }
    else if (patternIndex == 3) {
        intent = INTENT_BUFF;
    }
    else if (patternIndex == 4) {
        intent = INTENT_POISON_ATTACK;
    }
    else {
        intent = INTENT_EXPLODE;
    }

    patternIndex++;

    if (patternIndex >= 6) {
        patternIndex = 0;
    }
}

void ElementalBoss::showIntent() const {
    int bonusPercent = waterPassive ? 110 : 100;

    cout << "적 행동 예고: ";

    if (intent == INTENT_BLOCK) {
        cout << "냉기의 힘 - 방어 15, 냉기 패시브 획득\n";
    }
    else if (intent == INTENT_ATTACK) {
        cout << "서리 창 - " << (20 + strength) * bonusPercent / 100 << " 피해, 취약 4 부여\n";
    }
    else if (intent == INTENT_DEBUFF) {
        cout << "얼다바람 - " << (15 + strength) * bonusPercent / 100 << " 피해\n";
    }
    else if (intent == INTENT_BUFF) {
        cout << "물의 힘 - 힘 5 증가, 물 패시브 획득\n";
    }
    else if (intent == INTENT_POISON_ATTACK) {
        cout << "탁류 - " << (20 + strength) * bonusPercent / 100 << " 피해, 약화 2 부여\n";
    }
    else if (intent == INTENT_EXPLODE) {
        cout << "물대포 - " << (30 + strength) * bonusPercent / 100 << " 피해\n";
    }
}

void ElementalBoss::printExtraStatus() const {
    if (icePassive) {
        cout << " | 냉기 패시브";
    }

    if (waterPassive) {
        cout << " | 물 패시브";
    }
}

void ElementalBoss::executeIntent(Player& player) {
    int bonusPercent = waterPassive ? 110 : 100;

    if (intent == INTENT_BLOCK) {
        cout << "정령이 냉기의 힘을 사용합니다. 방어 15를 얻고 냉기 패시브를 획득합니다.\n";
        addBlock(15);
        icePassive = true;
    }
    else if (intent == INTENT_ATTACK) {
        int damage = (20 + strength) * bonusPercent / 100;
        cout << "정령이 서리 창을 던집니다. 피해: " << damage << ", 취약 4 부여\n";
        player.takeDamage(damage);
        player.getStatus().addVulnerable(4);
    }
    else if (intent == INTENT_DEBUFF) {
        int damage = (15 + strength) * bonusPercent / 100;
        cout << "정령이 얼다바람을 사용합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);
    }
    else if (intent == INTENT_BUFF) {
        cout << "정령이 물의 힘을 사용합니다. 힘 5 증가, 물 패시브 획득.\n";
        strength += 5;
        waterPassive = true;
    }
    else if (intent == INTENT_POISON_ATTACK) {
        int damage = (20 + strength) * bonusPercent / 100;
        cout << "정령이 탁류를 일으킵니다. 피해: " << damage << ", 약화 2 부여\n";
        player.takeDamage(damage);
        player.getStatus().addWeak(2);
    }
    else if (intent == INTENT_EXPLODE) {
        int damage = (30 + strength) * bonusPercent / 100;
        cout << "정령이 물대포를 발사합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);
    }
}

// ======================================
// 3. 화산 몬스터
// ======================================

LavaSlime::LavaSlime() : Monster("용암 슬라임", 40, Element::FIRE) {
    patternIndex = 0;
    damageTakenPercent = 100;
    melted = false;
}

void LavaSlime::takeDamage(int damage) {
    damage = damage * damageTakenPercent / 100;

    Monster::takeDamage(damage);
}

void LavaSlime::decideIntent() {
    // 패턴 순서: 2 > 1 > 3 > 1
    if (patternIndex == 0) {
        intent = INTENT_BUFF;      // 녹기
    }
    else if (patternIndex == 1) {
        intent = INTENT_ATTACK;    // 몸통 박치기
    }
    else if (patternIndex == 2) {
        intent = INTENT_BLOCK;     // 굳기
    }
    else {
        intent = INTENT_ATTACK;    // 몸통 박치기
    }

    patternIndex++;

    if (patternIndex >= 4) {
        patternIndex = 0;
    }
}

void LavaSlime::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_BUFF) {
        cout << "녹기 - 힘 5 증가, 받는 피해 50% 증가\n";
    }
    else if (intent == INTENT_ATTACK) {
        cout << "몸통 박치기 - " << 12 + strength << " 피해, 화상 3 부여\n";
    }
    else if (intent == INTENT_BLOCK) {
        cout << "굳기 - 힘 5 감소, 받는 피해 50% 감소\n";
    }
}

void LavaSlime::printExtraStatus() const {
    cout << " | 받는 피해: " << damageTakenPercent << "%";

    if (melted) {
        cout << " | 녹은 상태";
    }
    else if (damageTakenPercent == 50) {
        cout << " | 굳은 상태";
    }
}

void LavaSlime::executeIntent(Player& player) {
    if (intent == INTENT_BUFF) {
        cout << "용암 슬라임이 몸을 녹입니다.\n";
        cout << "힘이 5 증가하고, 받는 피해가 50% 증가합니다.\n";

        strength += 5;
        damageTakenPercent = 150;
        melted = true;
    }
    else if (intent == INTENT_ATTACK) {
        int damage = 12 + strength;

        cout << "용암 슬라임이 몸통 박치기를 사용합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);

        cout << "용암 슬라임의 뜨거운 몸체가 플레이어에게 화상 3을 부여합니다.\n";
        player.getStatus().addBurn(3);
    }
    else if (intent == INTENT_BLOCK) {
        cout << "용암 슬라임이 몸을 굳힙니다.\n";
        cout << "녹기로 얻었던 힘 5를 잃고, 받는 피해가 원래 기준 50% 감소 상태가 됩니다.\n";

        if (melted) {
            strength -= 5;

            if (strength < 0) {
                strength = 0;
            }
        }

        damageTakenPercent = 50;
        melted = false;
    }
}

FireBat::FireBat() : Monster("화염 박쥐", 40, Element::FIRE) {
    patternIndex = 0;
    halfDamageNextTurn = false;
}

void FireBat::takeDamage(int damage) {
    if (halfDamageNextTurn) {
        cout << "[화염 박쥐] 비행 상태로 인해 받는 피해가 절반이 됩니다!\n";
        damage /= 2;
    }

    Monster::takeDamage(damage);
}

void FireBat::onTurnStart() {
    // 비행 효과는 플레이어의 다음 턴 동안만 유지되고,
    // 화염 박쥐의 다음 행동 턴이 시작되면 사라진다.
    if (halfDamageNextTurn) {
        halfDamageNextTurn = false;
    }
}

void FireBat::decideIntent() {
    // 패턴 순서: 2 > 1 > 3
    if (patternIndex == 0) {
        intent = INTENT_FLIGHT;   // 비행
    }
    else if (patternIndex == 1) {
        intent = INTENT_ATTACK;    // 불싸르기
    }
    else {
        intent = INTENT_BUFF;     // 화염 흡혈
    }

    patternIndex++;

    if (patternIndex >= 3) {
        patternIndex = 0;
    }
}

void FireBat::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_FLIGHT) {
        cout << "비행 - 다음 턴 받는 피해 절반\n";
    }
    else if (intent == INTENT_ATTACK) {
        cout << "불싸르기 - " << 15 + strength << " 피해, 막히지 않은 피해를 입히면 화상 7 부여\n";
    }
    else if (intent == INTENT_BUFF) {
        cout << "화염 흡혈 - " << 10 + strength << " 피해, 막히지 않은 피해를 입히면 플레이어 화상을 흡수해 회복\n";
    }
}

void FireBat::printExtraStatus() const {
    if (halfDamageNextTurn) {
        cout << " | 비행: 받는 피해 절반";
    }
}

void FireBat::executeIntent(Player& player) {
    if (intent == INTENT_FLIGHT) {
        cout << "화염 박쥐가 높이 날아오릅니다!\n";
        cout << "다음 턴 받는 피해가 절반이 됩니다.\n";

        halfDamageNextTurn = true;
    }
    else if (intent == INTENT_ATTACK) {
        int damage = 15 + strength;
        int beforeHP = player.getHP();

        cout << "화염 박쥐가 불싸르기를 사용합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);

        int afterHP = player.getHP();

        if (afterHP < beforeHP) {
            cout << "불길이 방어를 뚫고 플레이어에게 닿았습니다!\n";
            cout << "플레이어에게 화상 7을 부여합니다.\n";
            player.getStatus().addBurn(7);
        }
        else {
            cout << "공격이 전부 막혀 화상이 부여되지 않았습니다.\n";
        }
    }
    else if (intent == INTENT_BUFF) {
        int damage = 10 + strength;
        int beforeHP = player.getHP();

        cout << "화염 박쥐가 화염 흡혈을 사용합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);

        int afterHP = player.getHP();

        if (afterHP < beforeHP) {
            int burnAmount = player.getStatus().getBurn();

            if (burnAmount > 0) {
                cout << "화염 박쥐가 플레이어에게 남아 있던 화상 " << burnAmount << "을 흡수합니다!\n";
                cout << "플레이어의 화상이 모두 사라지고, 화염 박쥐가 " << burnAmount << " 회복합니다.\n";

                player.getStatus().clearBurn();

                hp += burnAmount;
            }
            else {
                cout << "플레이어에게 화상이 없어 흡혈 회복은 발생하지 않았습니다.\n";
            }
        }
        else {
            cout << "공격이 전부 막혀 화상을 흡수하지 못했습니다.\n";
        }
    }
}

FireImp::FireImp() : Monster("화염 임프", 50, Element::FIRE) {
    patternIndex = 0;
}

void FireImp::decideIntent() {
    // 패턴 순서: 1 > 2 > 3 > 4
    if (patternIndex == 0) {
        intent = INTENT_DEBUFF;    // 공포의 시선
    }
    else if (patternIndex == 1) {
        intent = INTENT_PREPARE;   // 영창
    }
    else if (patternIndex == 2) {
        intent = INTENT_ATTACK;    // 화염구
    }
    else {
        intent = INTENT_BUFF;      // 힘 기르기
    }

    patternIndex++;

    if (patternIndex >= 4) {
        patternIndex = 0;
    }
}

void FireImp::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_DEBUFF) {
        cout << "공포의 시선 - 약화 3, 취약 3 부여\n";
    }
    else if (intent == INTENT_PREPARE) {
        cout << "영창 - 다음 턴에 거대한 공격을 준비합니다\n";
    }
    else if (intent == INTENT_ATTACK) {
        cout << "화염구 - " << 35 + strength << " 피해\n";
    }
    else if (intent == INTENT_BUFF) {
        cout << "힘 기르기 - 힘 5 증가\n";
    }
}

void FireImp::executeIntent(Player& player) {
    if (intent == INTENT_DEBUFF) {
        cout << "화염 임프가 공포의 시선을 보냅니다!\n";
        cout << "플레이어에게 약화 3, 취약 3을 부여합니다.\n";

        player.getStatus().addWeak(3);
        player.getStatus().addVulnerable(3);
    }
    else if (intent == INTENT_PREPARE) {
        cout << "화염 임프가 불길한 주문을 영창합니다.\n";
        cout << "다음 턴에 거대한 공격을 할 예정입니다.\n";
    }
    else if (intent == INTENT_ATTACK) {
        int damage = 35 + strength;

        cout << "화염 임프가 화염구를 발사합니다! 피해: " << damage << "\n";
        player.takeDamage(damage);
    }
    else if (intent == INTENT_BUFF) {
        cout << "화염 임프가 힘을 기릅니다.\n";
        cout << "힘이 5 증가합니다.\n";

        strength += 5;
    }
}

Demon::Demon() : Monster("악마", 70, Element::NONE) {
    patternIndex = 0;
    stolenGold = 0;
    escaped = false;
}

bool Demon::hasEscaped() const {
    return escaped;
}

void Demon::decideIntent() {
    // 패턴: 1 > 1 > 1 > 2 > 3
    if (patternIndex <= 2) {
        intent = INTENT_STEAL_GOLD;
    }
    else if (patternIndex == 3) {
        intent = INTENT_BLOCK;
    }
    else {
        intent = INTENT_ESCAPE;
    }

    patternIndex++;

    if (patternIndex >= 5) {
        patternIndex = 4;
    }
}

void Demon::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_STEAL_GOLD) {
        cout << "골드 강탈 - " << 15 + strength << " 피해, 30골드 강탈\n";
    }
    else if (intent == INTENT_BLOCK) {
        cout << "연막 - 방어 10\n";
    }
    else if (intent == INTENT_ESCAPE) {
        cout << "도망 - 전투를 강제 종료하고 보상을 남기지 않음\n";
    }
}

void Demon::printExtraStatus() const {
    if (stolenGold > 0) {
        cout << " | 강탈한 골드: " << stolenGold;
    }
}

void Demon::executeIntent(Player& player) {
    if (intent == INTENT_STEAL_GOLD) {
        int damage = 15 + strength;

        cout << "악마가 골드 강탈을 사용합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);

        int stealAmount = 30;

        if (player.spendGold(stealAmount)) {
            stolenGold += stealAmount;
            cout << "악마가 30골드를 강탈했습니다.\n";
        }
        else {
            cout << "플레이어의 골드가 부족하여 강탈하지 못했습니다.\n";
        }
    }
    else if (intent == INTENT_BLOCK) {
        cout << "악마가 연막을 펼칩니다.\n";
        addBlock(10);
    }
    else if (intent == INTENT_ESCAPE) {
        cout << "악마가 훔친 골드를 들고 도망쳤습니다!\n";
        cout << "전투가 종료되며 보상은 없습니다.\n";
        escaped = true;
        hp = 0;
    }
}

SoulSword::SoulSword() : Monster("영혼이 깃든 검", 50, Element::NONE) {
    patternIndex = 0;
    finalMode = false;
}

void SoulSword::decideIntent() {
    if (finalMode) {
        intent = INTENT_ATTACK;
        return;
    }

    if (patternIndex == 0) {
        intent = INTENT_ATTACK;    // 합 겨루기
    }
    else if (patternIndex == 1) {
        intent = INTENT_DEBUFF;    // 습관 파악
    }
    else if (patternIndex == 2) {
        intent = INTENT_ATTACK;    // 합 겨루기
    }
    else if (patternIndex == 3) {
        intent = INTENT_BUFF;      // 명상
    }
    else if (patternIndex == 4) {
        intent = INTENT_ATTACK;    // 합 겨루기
    }
    else if (patternIndex == 5) {
        intent = INTENT_DEBUFF;    // 약점 파악
    }
    else {
        intent = INTENT_ATTACK;    // 승부 굳히기
        finalMode = true;
    }

    patternIndex++;
}

void SoulSword::showIntent() const {
    cout << "적 행동 예고: ";

    if (finalMode) {
        cout << "승부 굳히기 - " << 20 + strength << " 피해\n";
        return;
    }

    if (patternIndex == 1 || patternIndex == 3 || patternIndex == 5) {
        cout << "합 겨루기 - " << 10 + strength << " 피해\n";
    }
    else if (patternIndex == 2) {
        cout << "습관 파악 - 약화 50 부여\n";
    }
    else if (patternIndex == 4) {
        cout << "명상 - 힘 10 증가\n";
    }
    else if (patternIndex == 6) {
        cout << "약점 파악 - 취약 50 부여\n";
    }
    else {
        cout << "승부 굳히기 - " << 20 + strength << " 피해\n";
    }
}

void SoulSword::executeIntent(Player& player) {
    if (finalMode) {
        int damage = 20 + strength;
        cout << "영혼이 깃든 검이 승부 굳히기를 사용합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);
        return;
    }

    int actionNumber = patternIndex;

    if (actionNumber == 1 || actionNumber == 3 || actionNumber == 5) {
        int damage = 10 + strength;
        cout << "영혼이 깃든 검이 합 겨루기를 사용합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);
    }
    else if (actionNumber == 2) {
        cout << "영혼이 깃든 검이 습관 파악을 사용합니다. 약화 50을 부여합니다.\n";
        player.getStatus().addWeak(50);
    }
    else if (actionNumber == 4) {
        cout << "영혼이 깃든 검이 명상합니다. 힘이 10 증가합니다.\n";
        strength += 10;
    }
    else if (actionNumber == 6) {
        cout << "영혼이 깃든 검이 약점 파악을 사용합니다. 취약 50을 부여합니다.\n";
        player.getStatus().addVulnerable(50);
    }
    else {
        int damage = 20 + strength;
        cout << "영혼이 깃든 검이 승부 굳히기를 사용합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);
        finalMode = true;
    }
}

ObsidianGolem::ObsidianGolem() : Monster("흑요석 골렘", 300, Element::NONE) {
    patternIndex = 0;
    armor = 40;
}

void ObsidianGolem::takeDamage(int damage) {
    if (armor > 0) {
        int reducedDamage = damage / 10;

        cout << "[흑요석 갑주] 받는 피해가 90% 감소합니다. 실제 피해: " << reducedDamage << "\n";

        hp -= reducedDamage;

        if (hp < 0) {
            hp = 0;
        }

        armor -= damage;

        if (armor <= 0) {
            armor = 0;
            cout << "흑요석 골렘의 갑주가 파괴되어 코어가 노출되었습니다!\n";
        }

        return;
    }

    int amplifiedDamage = damage + damage / 2;

    cout << "[코어 노출] 받는 피해가 150%가 됩니다. 실제 피해: " << amplifiedDamage << "\n";
    Monster::takeDamage(amplifiedDamage);
}

void ObsidianGolem::decideIntent() {
    // 패턴: 1 > 2 > 3 > 4 > 5 > 6
    if (patternIndex == 0) {
        intent = INTENT_ARMOR;
    }
    else if (patternIndex == 1) {
        intent = INTENT_BLOCK;
    }
    else if (patternIndex == 2) {
        intent = INTENT_ATTACK;
    }
    else if (patternIndex == 3) {
        intent = INTENT_PREPARE;
    }
    else if (patternIndex == 4) {
        intent = INTENT_EXPLODE;
    }
    else {
        intent = INTENT_BUFF;
    }

    patternIndex++;

    if (patternIndex >= 6) {
        patternIndex = 0;
    }
}

void ObsidianGolem::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_ARMOR) {
        cout << "엔진 점화 - 갑주 20 획득\n";
    }
    else if (intent == INTENT_BLOCK) {
        cout << "철벽 - 방어 20\n";
    }
    else if (intent == INTENT_ATTACK) {
        cout << "땅울림 - " << 25 + strength << " 피해, 약화 1 부여\n";
    }
    else if (intent == INTENT_PREPARE) {
        cout << "에너지 충전 - 다음 턴 강력한 일격 준비\n";
    }
    else if (intent == INTENT_EXPLODE) {
        cout << "파괴광선 - " << 50 + strength << " 피해\n";
    }
    else if (intent == INTENT_BUFF) {
        cout << "냉각 - 힘 5 증가\n";
    }
}

void ObsidianGolem::printExtraStatus() const {
    if (armor > 0) {
        cout << " | 갑주: " << armor << " | 피해 90% 감소";
    }
    else {
        cout << " | 코어 노출: 받는 피해 150%";
    }
}

void ObsidianGolem::executeIntent(Player& player) {
    if (intent == INTENT_ARMOR) {
        cout << "흑요석 골렘이 엔진을 점화합니다. 갑주 20을 획득합니다.\n";
        armor += 20;
    }
    else if (intent == INTENT_BLOCK) {
        cout << "흑요석 골렘이 철벽을 사용합니다.\n";
        addBlock(20);
    }
    else if (intent == INTENT_ATTACK) {
        int damage = 25 + strength;
        cout << "흑요석 골렘이 땅울림을 사용합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);
        player.getStatus().addWeak(1);
    }
    else if (intent == INTENT_PREPARE) {
        cout << "흑요석 골렘이 에너지를 충전합니다. 다음 턴 파괴광선을 준비합니다.\n";
    }
    else if (intent == INTENT_EXPLODE) {
        int damage = 50 + strength;
        cout << "흑요석 골렘이 파괴광선을 발사합니다! 피해: " << damage << "\n";
        player.takeDamage(damage);
    }
    else if (intent == INTENT_BUFF) {
        cout << "흑요석 골렘이 냉각을 시작합니다. 힘이 5 증가합니다.\n";
        strength += 5;
    }
}

// ======================================
// 4. 재의 숲 몬스터
// ======================================

AshWolf::AshWolf() : Monster("재의 늑대", 40, Element::FIRE) {
}

void AshWolf::decideIntent() {
    intent = (rand() % 2 == 0) ? INTENT_ATTACK : INTENT_BLOCK;
}

void AshWolf::showIntent() const {
    cout << "적 행동: "
        << (intent == INTENT_ATTACK ? "불씨 물어뜯기 (피해 9)" : "재빠른 회피 (방어 6)")
        << "\n";
}

void AshWolf::executeIntent(Player& player) {
    if (intent == INTENT_ATTACK) {
        player.takeDamage(9 + strength);
    }
    else {
        addBlock(6);
    }
}

// ======================================
// 5. 바다 몬스터
// ======================================

SeaSerpent::SeaSerpent() : Monster("바다 뱀", 45, Element::WATER) {
}

void SeaSerpent::decideIntent() {
    intent = INTENT_ATTACK;
}

void SeaSerpent::showIntent() const {
    cout << "적 행동: 꼬리 치기 (피해 10)\n";
}

void SeaSerpent::executeIntent(Player& player) {
    player.takeDamage(10 + strength);
}

// ======================================
// 6. 사막 몬스터
// ======================================

GiantScorpion::GiantScorpion() : Monster("거대 전갈", 55, Element::NATURE) {
}

void GiantScorpion::decideIntent() {
    intent = (rand() % 2 == 0) ? INTENT_ATTACK : INTENT_BLOCK;
}

void GiantScorpion::showIntent() const {
    cout << "적 행동: "
        << (intent == INTENT_ATTACK ? "맹독 집게 (피해 12)" : "단단한 껍질 (방어 8)")
        << "\n";
}

void GiantScorpion::executeIntent(Player& player) {
    if (intent == INTENT_ATTACK) {
        player.takeDamage(12 + strength);
    }
    else {
        addBlock(8);
    }
}

// ======================================
// 7. 울창한 숲 몬스터
// ======================================

GiantMantis::GiantMantis() : Monster("거대 사마귀", 50, Element::NATURE) {
}

void GiantMantis::decideIntent() {
    intent = (rand() % 2 == 0) ? INTENT_ATTACK : INTENT_BLOCK;
}

void GiantMantis::showIntent() const {
    cout << "적 행동: "
        << (intent == INTENT_ATTACK ? "낫 휘두르기 (피해 13)" : "보호색 위장 (방어 10)")
        << "\n";
}

void GiantMantis::executeIntent(Player& player) {
    if (intent == INTENT_ATTACK) {
        player.takeDamage(13 + strength);
    }
    else {
        addBlock(10);
    }
}

// ======================================
// 8. 부패한 늪 몬스터
// ======================================

VenomSpider::VenomSpider() : Monster("맹독 거미", 45, Element::WATER) {
}

void VenomSpider::decideIntent() {
    intent = INTENT_ATTACK;
}

void VenomSpider::showIntent() const {
    cout << "적 행동: 독니 찌르기 (피해 10)\n";
}

void VenomSpider::executeIntent(Player& player) {
    player.takeDamage(10 + strength);
}

// ======================================
// 9. 심연 몬스터
// ======================================

AbyssCrawler::AbyssCrawler() : Monster("심연의 기어다니는 자", 55, Element::NONE) {
}

void AbyssCrawler::decideIntent() {
    intent = INTENT_ATTACK;
}

void AbyssCrawler::showIntent() const {
    cout << "적 행동: 어둠의 손길 (피해 11)\n";
}

void AbyssCrawler::executeIntent(Player& player) {
    player.takeDamage(11 + strength);
}


// ======================================
// 심연 보스 - 심연의 군주
// ======================================

AbyssLord::AbyssLord() : Monster("심연의 군주", 420, Element::NONE) {
    patternIndex = 0;
    shadowMerged = false;
}

void AbyssLord::takeDamage(int damage) {
    if (shadowMerged) {
        cout << "[그림자 동화] 심연의 군주가 그림자 속에 숨어 피해를 받지 않습니다!\n";
        return;
    }

    Monster::takeDamage(damage);
}

void AbyssLord::onTurnStart() {
    Monster::onTurnStart();

    if (shadowMerged) {
        shadowMerged = false;
    }
}

void AbyssLord::onBeforePlayerTurn(Player& player) {
    Weapon* weapon = player.getEquippedWeapon();
    Element weaponElement = Element::NONE;

    if (weapon != nullptr) {
        weaponElement = weapon->getElement();
    }

    if (weaponElement == Element::FIRE) {
        element = Element::WATER;
        cout << "\n[심연의 군주] 플레이어의 불 속성 무기에 대응해 물 속성으로 변합니다.\n";
    }
    else if (weaponElement == Element::WATER) {
        element = Element::NATURE;
        cout << "\n[심연의 군주] 플레이어의 물 속성 무기에 대응해 자연 속성으로 변합니다.\n";
    }
    else if (weaponElement == Element::NATURE) {
        element = Element::FIRE;
        cout << "\n[심연의 군주] 플레이어의 자연 속성 무기에 대응해 불 속성으로 변합니다.\n";
    }
    else {
        element = Element::NONE;
    }
}

void AbyssLord::decideIntent() {
    // 패턴: 1 > 2 > 3 > 4 > 5 > 6
    if (patternIndex == 0) {
        intent = INTENT_BUFF;      // 심연 태세
    }
    else if (patternIndex == 1) {
        intent = INTENT_DEBUFF;    // 암습
    }
    else if (patternIndex == 2) {
        intent = INTENT_FLIGHT;    // 그림자 동화
    }
    else if (patternIndex == 3) {
        intent = INTENT_ATTACK;    // 그림자 습격
    }
    else if (patternIndex == 4) {
        intent = INTENT_PREPARE;   // 준비 태세
    }
    else {
        intent = INTENT_ARMOR;     // 암흑
    }

    patternIndex++;

    if (patternIndex >= 6) {
        patternIndex = 0;
    }
}

void AbyssLord::showIntent() const {
    cout << "적 행동 예고: ";

    if (intent == INTENT_BUFF) {
        cout << "심연 태세 - 방어 15, 힘 3 증가\n";
    }
    else if (intent == INTENT_DEBUFF) {
        cout << "암습 - " << 14 + strength << " 피해, 약화 2 부여\n";
    }
    else if (intent == INTENT_FLIGHT) {
        cout << "그림자 동화 - " << 10 + strength << " 피해, 다음 턴 피해를 받지 않음\n";
    }
    else if (intent == INTENT_ATTACK) {
        cout << "그림자 습격 - " << 20 + strength << " 피해, 취약 3 부여\n";
    }
    else if (intent == INTENT_PREPARE) {
        cout << "준비 태세 - 힘 2 증가\n";
    }
    else if (intent == INTENT_ARMOR) {
        cout << "암흑 - 취약 50 부여\n";
    }
}

void AbyssLord::printExtraStatus() const {
    if (shadowMerged) {
        cout << " | 그림자 동화: 피해 무효";
    }
}

void AbyssLord::executeIntent(Player& player) {
    if (intent == INTENT_BUFF) {
        cout << "심연의 군주가 심연 태세를 취합니다. 방어 15, 힘 3을 얻습니다.\n";
        addBlock(15);
        strength += 3;
    }
    else if (intent == INTENT_DEBUFF) {
        int damage = 14 + strength;
        cout << "심연의 군주가 암습을 사용합니다. 피해: " << damage << ", 약화 2 부여\n";
        player.takeDamage(damage);
        player.getStatus().addWeak(2);
    }
    else if (intent == INTENT_FLIGHT) {
        int damage = 10 + strength;
        cout << "심연의 군주가 그림자 동화를 사용합니다. 피해: " << damage << "\n";
        player.takeDamage(damage);
        cout << "심연의 군주가 다음 턴 피해를 받지 않는 상태가 됩니다.\n";
        shadowMerged = true;
    }
    else if (intent == INTENT_ATTACK) {
        int damage = 20 + strength;
        cout << "심연의 군주가 그림자 습격을 사용합니다. 피해: " << damage << ", 취약 3 부여\n";
        player.takeDamage(damage);
        player.getStatus().addVulnerable(3);
    }
    else if (intent == INTENT_PREPARE) {
        cout << "심연의 군주가 준비 태세를 갖춥니다. 힘이 2 증가합니다.\n";
        strength += 2;
    }
    else if (intent == INTENT_ARMOR) {
        cout << "심연의 군주가 암흑을 퍼뜨립니다. 취약 50을 부여합니다.\n";
        player.getStatus().addVulnerable(50);
    }
}

// ======================================
// 10. 성역 몬스터
// ======================================

SanctuaryGuardian::SanctuaryGuardian() : Monster("성역의 수호자", 50, Element::NONE) {
}

void SanctuaryGuardian::decideIntent() {
    intent = (rand() % 2 == 0) ? INTENT_ATTACK : INTENT_BLOCK;
}

void SanctuaryGuardian::showIntent() const {
    cout << "적 행동: "
        << (intent == INTENT_ATTACK ? "빛의 심판 (피해 9)" : "신성한 방벽 (방어 10)")
        << "\n";
}

void SanctuaryGuardian::executeIntent(Player& player) {
    if (intent == INTENT_ATTACK) {
        player.takeDamage(9 + strength);
    }
    else {
        addBlock(10);
    }
}

// ======================================
// 11. 벼락 맞은 골짜기 몬스터
// ======================================

StormFalcon::StormFalcon() : Monster("폭풍 매", 40, Element::NONE) {
}

void StormFalcon::decideIntent() {
    intent = (rand() % 2 == 0) ? INTENT_ATTACK : INTENT_BLOCK;
}

void StormFalcon::showIntent() const {
    cout << "적 행동: "
        << (intent == INTENT_ATTACK ? "번개 강하 (피해 12)" : "바람 타기 (방어 8)")
        << "\n";
}

void StormFalcon::executeIntent(Player& player) {
    if (intent == INTENT_ATTACK) {
        player.takeDamage(12 + strength);
    }
    else {
        addBlock(8);
    }
}

// ======================================
// 12. 피의 투기장 몬스터
// ======================================

ObsidianGladiator::ObsidianGladiator() : Monster("칠흑의 검투사", 65, Element::NONE) {
}

void ObsidianGladiator::decideIntent() {
    intent = (rand() % 4 == 0) ? INTENT_BLOCK : INTENT_ATTACK;
}

void ObsidianGladiator::showIntent() const {
    cout << "적 행동: "
        << (intent == INTENT_ATTACK ? "무자비한 연격 (피해 14)" : "방패 밀치기 (방어 8)")
        << "\n";
}

void ObsidianGladiator::executeIntent(Player& player) {
    if (intent == INTENT_ATTACK) {
        player.takeDamage(14 + strength);
    }
    else {
        addBlock(8);
    }
}

// ======================================
// 13. ???의 방 몬스터
// ======================================

UnknownEntity::UnknownEntity() : Monster("형체를 알 수 없는 존재", 70, Element::NONE) {
}

void UnknownEntity::decideIntent() {
    intent = INTENT_ATTACK;
}

void UnknownEntity::showIntent() const {
    cout << "적 행동: 기괴한 울음소리 (피해 15)\n";
}

void UnknownEntity::executeIntent(Player& player) {
    player.takeDamage(15 + strength);
}

// ======================================
// 14. 저주받은 묘지 몬스터
// ======================================

CursedSkeleton::CursedSkeleton() : Monster("저주받은 해골", 50, Element::NONE) {
}

void CursedSkeleton::decideIntent() {
    intent = (rand() % 2 == 0) ? INTENT_ATTACK : INTENT_BLOCK;
}

void CursedSkeleton::showIntent() const {
    cout << "적 행동: "
        << (intent == INTENT_ATTACK ? "뼈다귀 던지기 (피해 10)" : "원념 뭉치기 (방어 8)")
        << "\n";
}

void CursedSkeleton::executeIntent(Player& player) {
    if (intent == INTENT_ATTACK) {
        player.takeDamage(10 + strength);
    }
    else {
        addBlock(8);
    }
}

// ======================================
// 15. 고대의 무기고 몬스터
// ======================================

ArmorySentinel::ArmorySentinel() : Monster("무기고 파수꾼", 60, Element::NONE) {
}

void ArmorySentinel::decideIntent() {
    intent = (rand() % 3 == 0) ? INTENT_BLOCK : INTENT_ATTACK;
}

void ArmorySentinel::showIntent() const {
    cout << "적 행동: "
        << (intent == INTENT_ATTACK ? "녹슨 대검 휘두르기 (피해 12)" : "방패 방어 (방어 10)")
        << "\n";
}

void ArmorySentinel::executeIntent(Player& player) {
    if (intent == INTENT_ATTACK) {
        player.takeDamage(12 + strength);
    }
    else {
        addBlock(10);
    }
}

// ======================================
// 16. 영원의 빙하 몬스터
// ======================================

GlacierGolem::GlacierGolem() : Monster("빙하 골렘", 80, Element::WATER) {
}

void GlacierGolem::decideIntent() {
    intent = (rand() % 3 == 0) ? INTENT_ATTACK : INTENT_BLOCK;
}

void GlacierGolem::showIntent() const {
    cout << "적 행동: "
        << (intent == INTENT_ATTACK ? "거대한 얼음 주먹 꽂기 (피해 13)" : "두꺼운 얼음 장벽 세우기 (방어 12)")
        << "\n";
}

void GlacierGolem::executeIntent(Player& player) {
    if (intent == INTENT_ATTACK) {
        player.takeDamage(13 + strength);
    }
    else {
        addBlock(12);
    }
}
