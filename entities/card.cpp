//
// Created by Josh Petite on 2019-03-02.
//

#include <iomanip>
#include "card.h"

faceValue card::getValue() const {
  return m_value;
}

suit card::getSuit() const {
  return m_suit;
}

int card::deriveScoreValue() const {
  switch(getValue()) {
    case faceValue::Ace:
      return 1;
    case faceValue::Two:
      return 2;
    case faceValue::Three:
      return 3;
    case faceValue::Four:
      return 4;
    case faceValue::Five:
      return 5;
    case faceValue::Six:
      return 6;
    case faceValue::Seven:
      return 7;
    case faceValue::Eight:
      return 8;
    case faceValue::Nine:
      return 9;
    case faceValue::Ten:
    case faceValue::Jack:
    case faceValue::Queen:
    case faceValue::King:
      return 10;
  }
}

std::string card::deriveValueForDisplay() const {
  switch(getValue()) {
    case faceValue::Ace:
      return "A";
    case faceValue::Two:
      return "2"; 
    case faceValue::Three:
      return "3"; 
    case faceValue::Four:
      return "4"; 
    case faceValue::Five:
      return "5"; 
    case faceValue::Six:
      return "6"; 
    case faceValue::Seven:
      return "7"; 
    case faceValue::Eight:
      return "8"; 
    case faceValue::Nine:
      return "9"; 
    case faceValue::Ten:
      return "10"; 
    case faceValue::Jack:
      return "J"; 
    case faceValue::Queen:
      return "Q"; 
    case faceValue::King:
      return "K"; 
  }
}

std::string card::deriveSuitForDisplay() const {
  switch(getSuit()) {
    case suit::clubs:
      return "\xe2\x99\xa7";
    case suit::diamonds:
      return "\xe2\x99\xa2";
    case suit::hearts:
      return "\xe2\x99\xa1";
    case suit::spades:
      return "\xe2\x99\xa4";
  }
}

