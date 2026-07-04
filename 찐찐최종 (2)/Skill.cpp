#include "Skill.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>

using namespace std;

void Skill::printExtraPlayerStatus(Player& player) const {
}

int applySkillElementMatchup(int damage, Element attackElem, Element defendElem) {
    if (attackElem == Element::NONE || defendElem == Element::NONE) {
        return damage;
    }

    if ((attackElem == Element::FIRE && defendElem == Element::NATURE) ||
        (attackElem == Element::NATURE && defendElem == Element::WATER) ||
        (attackElem == Element::WATER && defendElem == Element::FIRE)) {
        cout << "[상성 우위] 효과가 뛰어납니다!! (피해량 1.5배)\n";
        return static_cast<int>(damage * 1.5);
    }

    if ((attackElem == Element::FIRE && defendElem == Element::WATER) ||
        (attackElem == Element::NATURE && defendElem == Element::FIRE) ||
        (attackElem == Element::WATER && defendElem == Element::NATURE)) {
        cout << "[상성 열세] 효과가 별로입니다... (피해량 반감)\n";
        return static_cast<int>(damage * 0.5);
    }

    return damage;
}

std::string StrikeSkill::getDescription() const {
    return "타격 - 공격 6";
}

Skill* StrikeSkill::clone() const {
    return new StrikeSkill(*this);
}

void StrikeSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(6);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "타격! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
}

std::string PowerStrikeSkill::getDescription() const {
    return "강타 - 공격 4, 취약 2 부여";
}

Skill* PowerStrikeSkill::clone() const {
    return new PowerStrikeSkill(*this);
}

void PowerStrikeSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(4);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "강타! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addVulnerable(2);
}

std::string FlameSlashSkill::getDescription() const {
    return "이그나이트 브레이크 - 피해 8, 화상 3";
}

Skill* FlameSlashSkill::clone() const {
    return new FlameSlashSkill(*this);
}

void FlameSlashSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(8);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "이그나이트 브레이크 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addBurn(3);
}

std::string RageSkill::getDescription() const {
    return "플레임 차지 - 힘 3 증가";
}

Skill* RageSkill::clone() const {
    return new RageSkill(*this);
}

void RageSkill::printExtraPlayerStatus(Player& player) const {
    cout << " | 힘: " << player.getStatus().getStrength();
}

void RageSkill::use(Player& player, Monster& monster, Element weaponElement) {
    player.getStatus().addStrength(3);
    cout << "플레임 차지 사용! 힘이 3 증가했습니다.\n";
}

std::string IcicleSkill::getDescription() const {
    return "서리한의 격노 - 피해 6, 손상 2";
}

Skill* IcicleSkill::clone() const {
    return new IcicleSkill(*this);
}

void IcicleSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(6);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "서리한의 격노 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addDamaged(2);
}

std::string FrostShieldSkill::getDescription() const {
    return "무기 파괴- 피해 3, 방어 5";
}

Skill* FrostShieldSkill::clone() const {
    return new FrostShieldSkill(*this);
}

void FrostShieldSkill::printExtraPlayerStatus(Player& player) const {
}

void FrostShieldSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(3);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "무기 파괴 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    player.addBlock(5);
}

std::string FireBladeSkill::getDescription() const {
    return "기염만상 - 피해 7, 화상 2";
}

Skill* FireBladeSkill::clone() const {
    return new FireBladeSkill(*this);
}

void FireBladeSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(7);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "화염 베기 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addBurn(2);
}

std::string FlameGuardSkill::getDescription() const {
    return " 염화 반사- 피해 4, 방어 6";
}

Skill* FlameGuardSkill::clone() const {
    return new FlameGuardSkill(*this);
}

void FlameGuardSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(4);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "염화 반사 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    player.addBlock(6);
}

std::string FireballSkill::getDescription() const {
    return "메테오 - 피해 9, 화상 4";
}

Skill* FireballSkill::clone() const {
    return new FireballSkill(*this);
}

void FireballSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(9);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "메테오 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addBurn(4);
}

std::string IgniteSkill::getDescription() const {
    return "이그나이트 - 피해 3, 화상 5";
}

Skill* IgniteSkill::clone() const {
    return new IgniteSkill(*this);
}

void IgniteSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(3);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "이그나이트 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addBurn(5);
}

std::string CrimsonArrowSkill::getDescription() const {
    return "플레임 샷 - 피해 6, 화상 3";
}

Skill* CrimsonArrowSkill::clone() const {
    return new CrimsonArrowSkill(*this);
}

void CrimsonArrowSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(6);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "플레임 샷 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addBurn(3);
}

std::string BurningVolleySkill::getDescription() const {
    return "파이어 레인 - 피해 4, 취약 1, 화상 2";
}

Skill* BurningVolleySkill::clone() const {
    return new BurningVolleySkill(*this);
}

void BurningVolleySkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(4);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "파이어 레인 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) {
        monster.addVulnerable(1);
        monster.addBurn(2);
    }
}

std::string FrostArrowSkill::getDescription() const {
    return "프로스트 샷 - 피해 7, 손상 2";
}

Skill* FrostArrowSkill::clone() const {
    return new FrostArrowSkill(*this);
}

void FrostArrowSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(5);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "프로스트 샷 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addDamaged(2);
}

std::string ColdFocusSkill::getDescription() const {
    return "콜드 스나이핑 - 힘 3";
}

Skill* ColdFocusSkill::clone() const {
    return new ColdFocusSkill(*this);
}

void ColdFocusSkill::printExtraPlayerStatus(Player& player) const {
    cout << " | 힘: " << player.getStatus().getStrength();
}

void ColdFocusSkill::use(Player& player, Monster& monster, Element weaponElement) {
    player.getStatus().addStrength(3);
    cout << "콜드 스나이핑 사용! 힘을 3 얻었습니다.\n";
}

std::string IceBoltSkill::getDescription() const {
    return "글레이셜 볼트 - 피해 7, 손상 1";
}

Skill* IceBoltSkill::clone() const {
    return new IceBoltSkill(*this);
}

void IceBoltSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(7);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "글레이셜 볼트 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addDamaged(1);
}

std::string IceBarrierSkill::getDescription() const {
    return "아이스 월 - 피해 2, 방어 7";
}

Skill* IceBarrierSkill::clone() const {
    return new IceBarrierSkill(*this);
}

void IceBarrierSkill::printExtraPlayerStatus(Player& player) const {
}

void IceBarrierSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(2);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "얼음 장벽 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    player.addBlock(7);
}

std::string DeepPierceSkill::getDescription() const {
    return "심연 관통 - 피해 8, 손상 2";
}

Skill* DeepPierceSkill::clone() const {
    return new DeepPierceSkill(*this);
}

void DeepPierceSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(8);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "심연 관통 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addDamaged(2);
}

std::string TideGuardSkill::getDescription() const {
    return "해신의 수호 - 힘3";
}

Skill* TideGuardSkill::clone() const {
    return new TideGuardSkill(*this);
}

void TideGuardSkill::use(Player& player, Monster& monster, Element weaponElement) {
    player.getStatus().addStrength(3);
    cout << "해신의 수호 사용! 힘을 3 얻었습니다." << "\n";
}

std::string VineWhipSkill::getDescription() const {
    return "와일드 바인 - 피해 6, 취약 1, 손상 1";
}

Skill* VineWhipSkill::clone() const {
    return new VineWhipSkill(*this);
}

void VineWhipSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(6);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "와일드 바인 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) {
        monster.addVulnerable(1);
        monster.addDamaged(1);
    }
}

std::string RootBindSkill::getDescription() const {
    return "루트 바인드 - 피해 4, 손상 3";
}

Skill* RootBindSkill::clone() const {
    return new RootBindSkill(*this);
}

void RootBindSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(4);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "루트 바인드 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addDamaged(3);
}

std::string NatureBoltSkill::getDescription() const {
    return "에메랄드 버스트 - 피해 7, 취약 2";
}

Skill* NatureBoltSkill::clone() const {
    return new NatureBoltSkill(*this);
}

void NatureBoltSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(7);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "에메랄드 버스트 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addVulnerable(2);
}

std::string HealingSproutSkill::getDescription() const {
    return "생명의 싹 - 회복 6, 방어 4";
}

Skill* HealingSproutSkill::clone() const {
    return new HealingSproutSkill(*this);
}

void HealingSproutSkill::use(Player& player, Monster& monster, Element weaponElement) {
    player.heal(6);
    player.addBlock(4);
    cout << "생명의 싹 사용! 체력 6을 회복하고 방어 4를 얻었습니다.\n";
}

std::string ForestArrowSkill::getDescription() const {
    return "실프 에로우 - 피해 6, 취약 2";
}

Skill* ForestArrowSkill::clone() const {
    return new ForestArrowSkill(*this);
}

void ForestArrowSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(6);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "실프 에로우 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addVulnerable(2);
}

std::string ThornVolleySkill::getDescription() const {
    return "브램블 샷 - 피해 5, 손상 2";
}

Skill* ThornVolleySkill::clone() const {
    return new ThornVolleySkill(*this);
}

void ThornVolleySkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(5);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "브램블 샷 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addDamaged(2);
}

std::string SpiritSlashSkill::getDescription() const {
    return "엘리멘탈 슬래쉬 - 피해 8, 취약 1";
}

Skill* SpiritSlashSkill::clone() const {
    return new SpiritSlashSkill(*this);
}

void SpiritSlashSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(8);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "엘리멘탈 슬래쉬 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addVulnerable(1);
}

std::string SpiritBlessingSkill::getDescription() const {
    return "엘리멘탈 블레싱 - 힘 2, 방어 5";
}

Skill* SpiritBlessingSkill::clone() const {
    return new SpiritBlessingSkill(*this);
}

void SpiritBlessingSkill::printExtraPlayerStatus(Player& player) const {
    cout << " | 힘: " << player.getStatus().getStrength();
}

void SpiritBlessingSkill::use(Player& player, Monster& monster, Element weaponElement) {
    player.getStatus().addStrength(2);
    player.addBlock(5);
    cout << "엘리멘탈 블레싱 사용! 힘이 2 증가하고 방어 5를 얻었습니다.\n";
}

std::string HammerStrikeSkill::getDescription() const {
    return "파워 스트라이크 - 피해 9";
}

Skill* HammerStrikeSkill::clone() const {
    return new HammerStrikeSkill(*this);
}

void HammerStrikeSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(9);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "파워 스트라이크 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
}

std::string ArmorBreakSkill::getDescription() const {
    return "아머 브레이크 - 피해 5, 취약 3";
}

Skill* ArmorBreakSkill::clone() const {
    return new ArmorBreakSkill(*this);
}

void ArmorBreakSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(5);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "아머 브레이크 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addVulnerable(3);
}

std::string MaceBlowSkill::getDescription() const {
    return "크러쉬 블로우 - 피해 7, 손상 2";
}

Skill* MaceBlowSkill::clone() const {
    return new MaceBlowSkill(*this);
}

void MaceBlowSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(7);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "크러쉬 블로우 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addDamaged(2);
}

std::string CrushingStrikeSkill::getDescription() const {
    return "쉐더링 스트라이크 - 피해 6, 취약 2";
}

Skill* CrushingStrikeSkill::clone() const {
    return new CrushingStrikeSkill(*this);
}

void CrushingStrikeSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(6);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "쉐더링 스트라이크 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addVulnerable(2);
}

std::string SpearThrustSkill::getDescription() const {
    return "드래곤 쓰러스트 - 피해 8";
}

Skill* SpearThrustSkill::clone() const {
    return new SpearThrustSkill(*this);
}

void SpearThrustSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = player.calculateAttackDamage(8);
    damage = applySkillElementMatchup(damage, weaponElement, monster.getElement());
    cout << "드래곤 쓰러스트 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
}

std::string PiercingStanceSkill::getDescription() const {
    return "드래곤 차지 - 힘 3";
}

Skill* PiercingStanceSkill::clone() const {
    return new PiercingStanceSkill(*this);
}

void PiercingStanceSkill::printExtraPlayerStatus(Player& player) const {
    cout << " | 힘: " << player.getStatus().getStrength();
}

void PiercingStanceSkill::use(Player& player, Monster& monster, Element weaponElement) {
    cout << "드래곤 차지 사용! 힘을 3 얻었습니다." << "\n";
    player.getStatus().addStrength(3);
}
std::string HeavenFlameSlashSkill::getDescription() const { return "천화멸섬 - 피해 12"; }
Skill* HeavenFlameSlashSkill::clone() const { return new HeavenFlameSlashSkill(*this); }
void HeavenFlameSlashSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = applySkillElementMatchup(player.calculateAttackDamage(12), weaponElement, monster.getElement());
    cout << "천화멸섬 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);

}

std::string CrimsonExplosionSkill::getDescription() const { return "진홍폭염 - 피해 8, 화상 5"; }
Skill* CrimsonExplosionSkill::clone() const { return new CrimsonExplosionSkill(*this); }
void CrimsonExplosionSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = applySkillElementMatchup(player.calculateAttackDamage(8), weaponElement, monster.getElement());
    cout << "진홍폭염 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addBurn(5);
}

std::string VermilionWindSkill::getDescription() const { return "주작열풍 - 피해 8"; }
Skill* VermilionWindSkill::clone() const { return new VermilionWindSkill(*this); }
void VermilionWindSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = applySkillElementMatchup(player.calculateAttackDamage(6), weaponElement, monster.getElement());
    cout << "주작열풍 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);

}

std::string RedWingDanceSkill::getDescription() const { return "적익난무 - 힘 2, 화상 3"; }
Skill* RedWingDanceSkill::clone() const { return new RedWingDanceSkill(*this); }
void RedWingDanceSkill::printExtraPlayerStatus(Player& player) const {
    cout << " | 힘: " << player.getStatus().getStrength();
}
void RedWingDanceSkill::use(Player& player, Monster& monster, Element weaponElement) {
    player.getStatus().addStrength(2);
    if (!monster.isDead()) monster.addBurn(3);
    cout << "적익난무 사용! 힘이 2 증가하고 적에게 화상 3을 부여했습니다.\n";
}

std::string MagmaBreakSkill::getDescription() const { return "마그마 브레이크 - 피해 9"; }
Skill* MagmaBreakSkill::clone() const { return new MagmaBreakSkill(*this); }
void MagmaBreakSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = applySkillElementMatchup(player.calculateAttackDamage(7), weaponElement, monster.getElement());
    cout << "마그마 브레이크 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);

}

std::string VolcanoBurstSkill::getDescription() const { return "볼케이노 버스트 - 피해 4, 화상 3"; }
Skill* VolcanoBurstSkill::clone() const { return new VolcanoBurstSkill(*this); }
void VolcanoBurstSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = applySkillElementMatchup(player.calculateAttackDamage(4), weaponElement, monster.getElement());
    cout << "볼케이노 버스트 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addBurn(3);
}

std::string FrostReapSkill::getDescription() const { return "서리수확 - 피해 8, 손상 2"; }
Skill* FrostReapSkill::clone() const { return new FrostReapSkill(*this); }
void FrostReapSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = applySkillElementMatchup(player.calculateAttackDamage(8), weaponElement, monster.getElement());
    cout << "서리수확 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addDamaged(2);
}

std::string BlizzardTempestSkill::getDescription() const { return "블리자드 템페스트 - 피해 6, 손상 4"; }
Skill* BlizzardTempestSkill::clone() const { return new BlizzardTempestSkill(*this); }
void BlizzardTempestSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = applySkillElementMatchup(player.calculateAttackDamage(6), weaponElement, monster.getElement());
    cout << "블리자드 템페스트 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addDamaged(4);
}

std::string WaveSlashSkill::getDescription() const { return "해랑참 - 피해 4 x 2, 손상 2"; }
Skill* WaveSlashSkill::clone() const { return new WaveSlashSkill(*this); }
void WaveSlashSkill::use(Player& player, Monster& monster, Element weaponElement) {
    for (int i = 0; i < 2; i++) {
        int damage = applySkillElementMatchup(player.calculateAttackDamage(4), weaponElement, monster.getElement());
        cout << "해랑참 " << i + 1 << "타! 최종 피해: " << damage << "\n";
        monster.takeDamage(damage);
        if (monster.isDead()) break;
    }
    if (!monster.isDead()) monster.addDamaged(2);
}

std::string AbyssDanceSkill::getDescription() const { return "심해난도 - 피해 3 x 4"; }
Skill* AbyssDanceSkill::clone() const { return new AbyssDanceSkill(*this); }
void AbyssDanceSkill::use(Player& player, Monster& monster, Element weaponElement) {
    for (int i = 0; i < 4; i++) {
        int damage = applySkillElementMatchup(player.calculateAttackDamage(3), weaponElement, monster.getElement());
        cout << "심해난도 " << i + 1 << "타! 최종 피해: " << damage << "\n";
        monster.takeDamage(damage);
        if (monster.isDead()) break;
    }
}

std::string AquaBurstSkill::getDescription() const { return "아쿠아 버스트 - 피해 7, 손상 2"; }
Skill* AquaBurstSkill::clone() const { return new AquaBurstSkill(*this); }
void AquaBurstSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = applySkillElementMatchup(player.calculateAttackDamage(7), weaponElement, monster.getElement());
    cout << "아쿠아 버스트 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addDamaged(2);
}

std::string HolyWaterWaveSkill::getDescription() const { return "성수의 물결 - 회복 8"; }
Skill* HolyWaterWaveSkill::clone() const { return new HolyWaterWaveSkill(*this); }
void HolyWaterWaveSkill::use(Player& player, Monster& monster, Element weaponElement) {
    player.heal(8);
    cout << "성수의 물결 사용! 체력 8을 회복했습니다.\n";
}

std::string LifePierceSkill::getDescription() const { return "생명관창 - 피해 8, 회복 3"; }
Skill* LifePierceSkill::clone() const { return new LifePierceSkill(*this); }
void LifePierceSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = applySkillElementMatchup(player.calculateAttackDamage(8), weaponElement, monster.getElement());
    cout << "생명관창 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    player.heal(3);
}

std::string EarthBindSkill::getDescription() const { return "대지속박 - 피해 5, 취약 3"; }
Skill* EarthBindSkill::clone() const { return new EarthBindSkill(*this); }
void EarthBindSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = applySkillElementMatchup(player.calculateAttackDamage(5), weaponElement, monster.getElement());
    cout << "대지속박 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addVulnerable(3);
}

std::string BramblePunchSkill::getDescription() const { return "브램블 펀치 - 피해 6, 취약 1"; }
Skill* BramblePunchSkill::clone() const { return new BramblePunchSkill(*this); }
void BramblePunchSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = applySkillElementMatchup(player.calculateAttackDamage(6), weaponElement, monster.getElement());
    cout << "브램블 펀치 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addVulnerable(1);
}

std::string ThornRushSkill::getDescription() const { return "가시난격 - 피해 3 x 3"; }
Skill* ThornRushSkill::clone() const { return new ThornRushSkill(*this); }
void ThornRushSkill::use(Player& player, Monster& monster, Element weaponElement) {
    for (int i = 0; i < 3; i++) {
        int damage = applySkillElementMatchup(player.calculateAttackDamage(3), weaponElement, monster.getElement());
        cout << "가시난격 " << i + 1 << "타! 최종 피해: " << damage << "\n";
        monster.takeDamage(damage);
        if (monster.isDead()) break;
    }
}

std::string ThousandSightSkill::getDescription() const { return "천리안 - 피해 10"; }
Skill* ThousandSightSkill::clone() const { return new ThousandSightSkill(*this); }
void ThousandSightSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = applySkillElementMatchup(player.calculateAttackDamage(10), weaponElement, monster.getElement());
    cout << "천리안 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
}

std::string EmeraldBlessingSkill::getDescription() const { return "에메랄드 블레싱 - 힘 2, 방어 2"; }
Skill* EmeraldBlessingSkill::clone() const { return new EmeraldBlessingSkill(*this); }
void EmeraldBlessingSkill::printExtraPlayerStatus(Player& player) const {
    cout << " | 힘: " << player.getStatus().getStrength();
}
void EmeraldBlessingSkill::use(Player& player, Monster& monster, Element weaponElement) {
    player.getStatus().addStrength(2);
    player.addBlock(2);
    cout << "에메랄드 블레싱 사용! 힘 2 증가, 방어 2를 얻었습니다.\n";
}

std::string TwinFangSlashSkill::getDescription() const { return "쌍아연참 - 피해 4 x 2, 취약2"; }
Skill* TwinFangSlashSkill::clone() const { return new TwinFangSlashSkill(*this); }
void TwinFangSlashSkill::use(Player& player, Monster& monster, Element weaponElement) {
    for (int i = 0; i < 2; i++) {
        int damage = applySkillElementMatchup(player.calculateAttackDamage(4), weaponElement, monster.getElement());
        cout << "쌍아연참 " << i + 1 << "타! 최종 피해: " << damage << "\n";
        monster.takeDamage(damage);
        if (monster.isDead()) break;
    }
    if (!monster.isDead()) monster.addVulnerable(3);
}

std::string WhiteTigerDanceSkill::getDescription() const { return "백호난무 - 피해 3 x 4"; }
Skill* WhiteTigerDanceSkill::clone() const { return new WhiteTigerDanceSkill(*this); }
void WhiteTigerDanceSkill::use(Player& player, Monster& monster, Element weaponElement) {
    for (int i = 0; i < 4; i++) {
        int damage = applySkillElementMatchup(player.calculateAttackDamage(3), weaponElement, monster.getElement());
        cout << "백호난무 " << i + 1 << "타! 최종 피해: " << damage << "\n";
        monster.takeDamage(damage);
        if (monster.isDead()) break;
    }
}

std::string DragonCrushSkill::getDescription() const { return "멸룡참 - 피해 12, 취약 3"; }
Skill* DragonCrushSkill::clone() const { return new DragonCrushSkill(*this); }
void DragonCrushSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = applySkillElementMatchup(player.calculateAttackDamage(12), weaponElement, monster.getElement());
    cout << "멸룡참 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addVulnerable(3);
}

std::string DragonSlayerSkill::getDescription() const { return "드래곤 슬레이어 - 피해 15"; }
Skill* DragonSlayerSkill::clone() const { return new DragonSlayerSkill(*this); }
void DragonSlayerSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = applySkillElementMatchup(player.calculateAttackDamage(15), weaponElement, monster.getElement());
    cout << "드래곤 슬레이어 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
}

std::string IronPierceSkill::getDescription() const { return "철혈관통 - 피해 8, 취약 3"; }
Skill* IronPierceSkill::clone() const { return new IronPierceSkill(*this); }
void IronPierceSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = applySkillElementMatchup(player.calculateAttackDamage(8), weaponElement, monster.getElement());
    cout << "철혈관통 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
    if (!monster.isDead()) monster.addVulnerable(3);
}

std::string HeavenlyShotSkill::getDescription() const { return "천궁일섬 - 피해 12"; }
Skill* HeavenlyShotSkill::clone() const { return new HeavenlyShotSkill(*this); }
void HeavenlyShotSkill::use(Player& player, Monster& monster, Element weaponElement) {
    int damage = applySkillElementMatchup(player.calculateAttackDamage(12), weaponElement, monster.getElement());
    cout << "천궁일섬 사용! 최종 피해: " << damage << "\n";
    monster.takeDamage(damage);
}