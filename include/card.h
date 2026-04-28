#pragma once
#include <string>
#include "json.hpp"
using namespace std;

struct card {
  string name_card;
  string type_card;
  int value;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(card, name_card, type_card)
