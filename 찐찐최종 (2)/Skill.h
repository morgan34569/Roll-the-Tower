#ifndef SKILL_H
#define SKILL_H

#include <string>
#include "Attribute.h"

class Player;
class Monster;

class Skill {
public:
    virtual ~Skill() {}
    virtual std::string getDescription() const = 0;
    virtual Skill* clone() const = 0;
    virtual void printExtraPlayerStatus(Player& player) const;
    virtual void use(Player& player, Monster& monster, Element weaponElement) = 0;
};

class StrikeSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class PowerStrikeSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class FlameSlashSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class RageSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void printExtraPlayerStatus(Player& player) const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class IcicleSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class FrostShieldSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void printExtraPlayerStatus(Player& player) const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class FireBladeSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class FlameGuardSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class FireballSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class IgniteSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class CrimsonArrowSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class BurningVolleySkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class FrostArrowSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class ColdFocusSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void printExtraPlayerStatus(Player& player) const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class IceBoltSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class IceBarrierSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void printExtraPlayerStatus(Player& player) const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class DeepPierceSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class TideGuardSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class VineWhipSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class RootBindSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class NatureBoltSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class HealingSproutSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class ForestArrowSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class ThornVolleySkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class SpiritSlashSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class SpiritBlessingSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void printExtraPlayerStatus(Player& player) const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class HammerStrikeSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class ArmorBreakSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class MaceBlowSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class CrushingStrikeSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class SpearThrustSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class PiercingStanceSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void printExtraPlayerStatus(Player& player) const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};
class HeavenFlameSlashSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class CrimsonExplosionSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class VermilionWindSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class RedWingDanceSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void printExtraPlayerStatus(Player& player) const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class MagmaBreakSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class VolcanoBurstSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class FrostReapSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class BlizzardTempestSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class WaveSlashSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class AbyssDanceSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class AquaBurstSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class HolyWaterWaveSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class LifePierceSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class EarthBindSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class BramblePunchSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class ThornRushSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class ThousandSightSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class EmeraldBlessingSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void printExtraPlayerStatus(Player& player) const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class TwinFangSlashSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class WhiteTigerDanceSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class DragonCrushSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class DragonSlayerSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class IronPierceSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};

class HeavenlyShotSkill : public Skill {
public:
    std::string getDescription() const override;
    Skill* clone() const override;
    void use(Player& player, Monster& monster, Element weaponElement) override;
};
#endif