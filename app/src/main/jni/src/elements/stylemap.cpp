#include "stylemap.h"

namespace scenevr {

Stylemap::Stylemap(const string css) : cssText(css) {
  tokenize();
}

string Stylemap::getPropertyValue(string key) {
  return rules[key];
}

int Stylemap::length() {
  return rules.size();
}

void Stylemap::tokenize() {
  istringstream ss(cssText);

  bool parsing = true;
  
  while (parsing) {
    string key;
    parsing = std::getline(ss, key, ':');

    string value;
    parsing = std::getline(ss, value, ';');

    rules[key] = value;
  }
}

}