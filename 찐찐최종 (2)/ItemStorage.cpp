#include "ItemStorage.h"
#include "Potion.h"
#include "ThrowPotion.h"
#include "Armor.h"
#include "Weapon.h"

ItemStorage::ItemStorage() {
    addItem(new Weapon(1001, "기본검", 0, 1)); //코드, 이름, 가격, 공격력, 속성, 스킬1, 스킬2
    addItem(new Weapon(1002, "이그니스 브레이커", 120, 3, Element::FIRE, new FlameSlashSkill(), new RageSkill()));
    addItem(new Weapon(1003, "서리한", 150, 2, Element::WATER, new IcicleSkill(), new FrostShieldSkill()));
    addItem(new Weapon(1004, "홍련도", 130, 2, Element::FIRE, new FireBladeSkill(), new FlameGuardSkill()));
    addItem(new Weapon(1005, "인페르널 스태프", 160, 1, Element::FIRE, new FireballSkill(), new IgniteSkill()));
    addItem(new Weapon(1006, "피닉스 윙", 140, 2, Element::FIRE, new CrimsonArrowSkill(), new BurningVolleySkill()));
    addItem(new Weapon(1007, "프로스트 레인저", 140, 2, Element::WATER, new FrostArrowSkill(), new ColdFocusSkill()));
    addItem(new Weapon(1008, "크리스탈 스태프", 160, 1, Element::WATER, new IceBoltSkill(), new IceBarrierSkill()));
    addItem(new Weapon(1009, "레비아탄 트라이던트", 180, 3, Element::WATER, new DeepPierceSkill(), new TideGuardSkill()));
    addItem(new Weapon(1010, "월드루트 바인", 130, 2, Element::NATURE, new VineWhipSkill(), new RootBindSkill()));
    addItem(new Weapon(1011, "엘더우드 스태프", 160, 1, Element::NATURE, new NatureBoltSkill(), new HealingSproutSkill()));
    addItem(new Weapon(1012, "실바니아 보우", 140, 2, Element::NATURE, new ForestArrowSkill(), new ThornVolleySkill()));
    addItem(new Weapon(1013, "이그드라실의 검", 170, 3, Element::NATURE, new SpiritSlashSkill(), new SpiritBlessingSkill()));
    addItem(new Weapon(1014, "타이탄 해머", 120, 3, Element::NONE, new HammerStrikeSkill(), new ArmorBreakSkill()));
    addItem(new Weapon(1015, "워메이스 그란트", 110, 2, Element::NONE, new MaceBlowSkill(), new CrushingStrikeSkill()));
    addItem(new Weapon(1016, "드래곤 랜스", 100, 2, Element::NONE, new SpearThrustSkill(), new PiercingStanceSkill()));
    addItem(new Weapon(1017, "멸염검 바르카노스", 260, 4, Element::FIRE, new HeavenFlameSlashSkill(), new CrimsonExplosionSkill()));
    addItem(new Weapon(1018, "주작선 적화", 200, 2, Element::FIRE, new VermilionWindSkill(), new RedWingDanceSkill()));
    addItem(new Weapon(1019, "마그마 피스트", 210, 3, Element::FIRE, new MagmaBreakSkill(), new VolcanoBurstSkill()));
    addItem(new Weapon(1020, "빙월낫 서리월", 220, 3, Element::WATER, new FrostReapSkill(), new BlizzardTempestSkill()));
    addItem(new Weapon(1021, "심해쌍검 아비스", 230, 3, Element::WATER, new WaveSlashSkill(), new AbyssDanceSkill()));
    addItem(new Weapon(1022, "빙정구 크리스탈리아", 210, 1, Element::WATER, new AquaBurstSkill(), new HolyWaterWaveSkill()));
    addItem(new Weapon(1023, "세계수창 이그드라실", 230, 3, Element::NATURE, new LifePierceSkill(), new EarthBindSkill()));
    addItem(new Weapon(1024, "브램블 건틀릿", 200, 2, Element::NATURE, new BramblePunchSkill(), new ThornRushSkill()));
    addItem(new Weapon(1025, "에버그린 롱보우", 220, 2, Element::NATURE, new ThousandSightSkill(), new EmeraldBlessingSkill()));
    addItem(new Weapon(1026, "백호쌍아", 230, 3, Element::NONE, new TwinFangSlashSkill(), new WhiteTigerDanceSkill()));
    addItem(new Weapon(1027, "용살검 카르나크", 260, 5, Element::NONE, new DragonCrushSkill(), new DragonSlayerSkill()));
    addItem(new Weapon(1028, "천궁노", 210, 2, Element::NONE, new IronPierceSkill(), new HeavenlyShotSkill()));

    addItem(new Armor(2001, "가죽 갑옷", 50, 1));
    addItem(new Armor(2002, "철갑옷", 100, 2));
    addItem(new Armor(2003, "강철 갑옷", 150, 3));
    addItem(new Armor(2004, "기사의 갑옷", 220, 4));
    addItem(new Armor(2005, "백은 갑옷", 280, 5));
    addItem(new Armor(2006, "수호자의 중갑", 350, 6));
    addItem(new Armor(2007, "용비늘 갑옷", 400, 7));
    addItem(new Armor(2008, "성기사의 갑주", 460, 8));
    addItem(new Armor(2009, "불멸자의 갑옷", 550, 9));
    addItem(new Armor(2010, "황룡의 왕갑", 620, 12));
    addItem(new Armor(2011, "천년수호 갑주", 700, 14));
    addItem(new Armor(2012, "제왕의 금갑", 800, 16));

    addItem(new Potion(3001, "소형 체력 포션", 50, 20)); //코드, 이름, 가격, 힐량, 취약 해제, 약화 해제, 힘 추가, 방어력 추가
    addItem(new Potion(3002, "중형 체력 포션", 100, 40));
    addItem(new Potion(3007, "대형 체력 포션", 150, 50));
    addItem(new Potion(3003, "만병통치약", 200, 10, 2, 2));
    addItem(new Potion(3004, "정화의 물약", 120, 0, 3, 3));
    addItem(new Potion(3006, "힘의 포션", 150, 0, 0, 0, 1));
    addItem(new ThrowPotion(3101, "화염 투척 포션", 100, 10, 1, 0, 0, Element::FIRE));
    addItem(new ThrowPotion(3103, "폭발성 화염병", 250, 25, 5, 0, 0, Element::FIRE));
    addItem(new Potion(3012, "생명의 이슬", 400, 100, 2, 2, 1, 10, 10));
    addItem(new Potion(3011, "각성의 묘약", 180, 0, 5, 5, 1));
    addItem(new Potion(3010, "난공불락의 물약", 300, 0, 0, 0, 0, 20, 20));
    addItem(new Potion(3009, "성기사의 축복", 250, 30, 0, 0, 0, 15));
    addItem(new Potion(3008, "용사의 비약", 220, 20, 0, 0, 2));
    addItem(new Potion(3005, "광전사의 비약", 200, 0, 0, 0, 3));
    addItem(new ThrowPotion(3112, "작열하는 화염병", 150, 20, 5, 0, 0, Element::FIRE));
    addItem(new ThrowPotion(3113, "범람하는 물구슬", 150, 20, 0, 0, 2, Element::WATER));
    addItem(new ThrowPotion(3114, "맹독 가시탄", 150, 20, 0, 3, 0, Element::NATURE));
    addItem(new ThrowPotion(3109, "쇠약의 저주병", 250, 0, 0, 4, 4));
    addItem(new ThrowPotion(3108, "액체 서리", 180, 15, 0, 0, 2, Element::WATER));
    addItem(new ThrowPotion(3105, "고대 수류탄", 300, 30, 5, 0, 0));
    addItem(new ThrowPotion(3102, "산성 플라스크", 150, 5, 0, 3, 0));
    addItem(new ThrowPotion(3104, "잿빛 눈가루", 120, 0, 0, 0, 4));
    addItem(new ThrowPotion(3107, "부패한 독병", 180, 0, 4, 2, 0));
    addItem(new ThrowPotion(3110, "응축된 벼락", 300, 40, 0, 0, 0));
}

ItemStorage::~ItemStorage() {
    for (auto item : items) delete item;
}

void ItemStorage::addItem(Item* item) { items.push_back(item); }
int ItemStorage::getCount() const { return (int)items.size(); }
Item* ItemStorage::getItem(int index) const { return items[index]; }

Item* ItemStorage::findByCode(int code) const {
    for (Item* item : items) {
        if (item->getCode() == code) {
            return item;
        }
    }
    return nullptr;
}