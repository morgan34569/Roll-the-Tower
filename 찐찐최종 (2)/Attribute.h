#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

// 속성 종류를 명확히 구분하기 위해 열거형(enum class) 사용
enum class Element {
    NONE,       // 무속성
    FIRE,       // 불
    WATER,      // 물
    NATURE      // 자연(풀)
};

class Attribute {
private:
    Element type;

public:
    Attribute(Element type = Element::NONE);

    Element getType() const;

    // 공격 속성(나)이 방어 속성(상대)을 때렸을 때의 데미지 배율 반환
    float getDamageMultiplier(Element targetType) const;
};

#endif
