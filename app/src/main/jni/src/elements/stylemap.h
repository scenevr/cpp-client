#ifndef STYLEMAP_H
#define STYLEMAP_H

#include <string>
#include <sstream>
#include <map>

namespace scenevr {

using namespace std;

// Copy the API from https://developer.mozilla.org/en-US/docs/Web/API/CSSStyleDeclaration
class Stylemap {
  public:
    Stylemap(const string);
    string getPropertyValue(const string key);
    int length();

  private:
    void tokenize();
    const string cssText;
    map<string, string> rules;
};

}

#endif
