//
// Created by Josh Petite on 2019-03-03.
//

#ifndef BURAKU_COMMON_H
#define BURAKU_COMMON_H

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

enum class suit { clubs, diamonds, hearts, spades };

static const suit AllSuits[] = { suit::clubs, suit::diamonds, suit::hearts, suit::spades };

#endif //BURAKU_COMMON_H
