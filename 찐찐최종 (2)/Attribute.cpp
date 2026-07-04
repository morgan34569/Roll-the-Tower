#include "Attribute.h"

Attribute::Attribute(Element type) : type(type) {}

Element Attribute::getType() const { return type; }

float Attribute::getDamageMultiplier(Element targetType) const {
    if (type == Element::NONE || targetType == Element::NONE) return 1.0f;

    // 간단한 가위바위보 상성 (불 > 자연 > 물 > 불)
    if (type == Element::FIRE && targetType == Element::NATURE) return 1.5f; // 1.5배 피해
    if (type == Element::FIRE && targetType == Element::WATER) return 0.5f;  // 반감

    if (type == Element::WATER && targetType == Element::FIRE) return 1.5f;
    if (type == Element::NATURE && targetType == Element::WATER) return 1.5f;

    return 1.0f; // 기본 배율
}