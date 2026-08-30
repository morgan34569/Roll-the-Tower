#include "ThrowPotion.h"
#include "Monster.h"
#include "Biomes.h"    
#include <iostream>

using namespace std;

// 외부(GameManager, Battle)에서 장착해둔 현재 지형 정보를 가져옵니다.
extern Biome* currentBattleBiome;

void ThrowPotion::Use(Player& player, Monster& monster) {
    cout << monster.getName() << "에게 " << getName() << " 투척!\n";

    if (damage > 0) {
        // 속성 객체를 만들어 몬스터와의 기본 상성 배율을 계산합니다.
        Attribute attr(element);
        float multiplier = attr.getDamageMultiplier(monster.getElement());
        int finalDamage = static_cast<int>(damage * multiplier);

        if (multiplier > 1.0f) cout << "[상성 우위] 효과가 뛰어납니다!! (피해량 증폭)\n";
        else if (multiplier < 1.0f) cout << "[상성 열위] 효과가 별로인 것 같습니다.. (피해량 반감)\n";

        // 최종 피해를 입히기 전, 현재 지형(화산, 바다 등)의 버프/너프를 한 번 더 적용합니다.
        if (currentBattleBiome != nullptr) {
            finalDamage = currentBattleBiome->modifyDamage(finalDamage, element);
        }

        monster.takeDamage(finalDamage);
        cout << "투척 최종 피해: " << finalDamage << "\n";
    }

    if (burn > 0) monster.addBurn(burn);
    if (vulnerable > 0) monster.addVulnerable(vulnerable);
    if (damaged > 0) monster.addDamaged(damaged);
}

Item* ThrowPotion::clone() const {
    return new ThrowPotion(*this);
}