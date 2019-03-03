//
// Created by Josh Petite on 2019-03-02.
//

#ifndef BURAKU_FACEVALUE_H
#define BURAKU_FACEVALUE_H

enum class FaceValue
{
  Ace = 1,
  Two = 2,
  Three = 3,
  Four = 4,
  Five = 5,
  Six = 6,
  Seven = 7,
  Eight = 8,
  Nine = 9,
  Ten = 10,
  Jack = 10,
  Queen = 10,
  King = 10
};

static const FaceValue AllFaceValues[] = {
    FaceValue::Ace, FaceValue::Two, FaceValue::Three, FaceValue::Four,
    FaceValue::Five, FaceValue::Six, FaceValue::Seven, FaceValue::Eight,
    FaceValue::Nine, FaceValue::Ten, FaceValue::Jack, FaceValue::Queen,
    FaceValue::King
};

#endif //BURAKU_FACEVALUE_H
