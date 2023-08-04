#include "tokenizer.h"


Tokenizer::Tokenizer(std::string ln): line{ln}, length{static_cast<int>(ln.length())} {}

bool Tokenizer::advanceToken() {
  while (++curPosition < length) {
    char curCh = line.at(curPosition);
    if (curCh == ' ') continue;
    // if (isalpha(curCh)) return true;
    // if (curCh == '+' || curCh == '-' || curCh == '*' || curCh == '(' || curCh == ')' || curCh == ':' || curCh == ',') return true; // may expand the list
    // if (curCh == '1' || curCh == '0') return true;
    // throw "Error: invalid input";
    return true;
  }
  return false;
}

bool Tokenizer::hasToken() const {
  return curPosition < length;
}

// only can be called when hasToken() is true
Token Tokenizer::getToken() {
  std::string curCh = line.substr(curPosition, 1);
  char ch = line.at(curPosition);
  Token resultToken;
  
  if (curCh == "+" || curCh == "-" || curCh == "*" || curCh == "(" || curCh == ")") resultToken = Token{curCh, "symbol"};
  else if (isalpha(ch)) {
    int varNLen = 1;
    while (curPosition + varNLen < length) {
      char c = line.at(curPosition + varNLen);
      if (!isalpha(c) && !isdigit(c)) break;
      varNLen++;
    }
    if (varNLen > 10) resultToken = Token{curCh, "error"};
    else resultToken = Token{line.substr(curPosition, varNLen), "varName"};
    curPosition = curPosition + varNLen - 1; // update the current position because of the length of variable name may longer than 1
  } else resultToken = Token{curCh, "error"};
  return resultToken;
}
