//
// Created by Josh Petite on 2019-03-02.
//

#ifndef BURAKU_FACEVALUE_H
#define BURAKU_FACEVALUE_H

enum class faceValue
{
  Ace,
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King
};

static const faceValue AllFaceValues[] = {
    faceValue::Ace, faceValue::Two, faceValue::Three, faceValue::Four,
    faceValue::Five, faceValue::Six, faceValue::Seven, faceValue::Eight,
    faceValue::Nine, faceValue::Ten, faceValue::Jack, faceValue::Queen,
    faceValue::King
};

#endif //BURAKU_FACEVALUE_H
