#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"

FormulaParser::FormulaParser(std::string ln): tknzr {new Tokenizer{ln}} {}

TreeNode *FormulaParser::parseConjTerm() {
  if (!tknzr->hasToken()) throw "Error: invalid input";
  TreeNode *resNode = parseTerm();
  if (tknzr->hasToken()) {
    Token curToken = tknzr->getToken();
    std::string content = curToken.content;
    if (content == "+" || content == ")") {
      return resNode;
    }
    if (content != "*") {
      delete resNode;
      throw "Error: invalid input";
    }
    tknzr->advanceToken();
    TreeNode *scdT = parseConjTerm();
    TreeNode *opPtr = new OperatorNode{ "*" };
    opPtr->updateChildren(resNode, scdT);
    resNode = opPtr;
  }
  return resNode;
}

TreeNode *FormulaParser::parseTerm() {
  if (!tknzr->hasToken()) throw "Error: invalid input";
  TreeNode *resNode = nullptr;
  Token curToken = tknzr->getToken();
  std::string type = curToken.type;
  std::string content = curToken.content;

  if (type == "varName") {
    resNode = new VariableNode{ content };
    tknzr->advanceToken();
  } else if (content == "-") {
    tknzr->advanceToken();
    TreeNode *operand = parseTerm();
    resNode = new OperatorNode{ "-" };
    resNode->updateLeftChild(operand);
  } else if (content == "(") {
    tknzr->advanceToken();
    resNode = parseFormula();
    if (!tknzr->hasToken()) {
      delete resNode;
      throw "Error: invalid input"; // test case
    }
    curToken = tknzr->getToken();
    if (curToken.content != ")") {
      delete resNode;
      throw "Error: invalid input"; // test case
    }
    tknzr->advanceToken();
  } else {
    throw "Error: invalid input";
  }
  return resNode;
}

TreeNode *FormulaParser::parseFormula() {
  if (!tknzr->hasToken()) throw "Error: invalid input";
  TreeNode *resNode = parseConjTerm();
  if (tknzr->hasToken()) {
    Token curToken = tknzr->getToken();
    std::string content = curToken.content;
    if (content == ")") {
      return resNode;
    }
    if (content != "+") {
      delete resNode;
      throw "Error: invalid input";
    }
    tknzr->advanceToken();
    TreeNode *scdCT = parseFormula();
    TreeNode *opPtr = new OperatorNode{ "+" };
    opPtr->updateChildren(resNode, scdCT);
    resNode = opPtr;
  }
  return resNode;
}

TreeNode * FormulaParser::getTreeRoot() {
  tknzr->advanceToken();
  TreeNode *root = parseFormula();
  if (tknzr->hasToken()) {
    delete root;
    throw "Error: invalid input"; // error handling for formula ending with an extra ")"
  }
  return root;
}

FormulaParser::~FormulaParser() {delete tknzr;}

//AssignmentParser::AssignmentParser(std::string ln): tknzr {new Tokenizer{ln}} {}

//std::map<std::string, bool> AssignmentParser::parseAssignment() {
//   std::map<std::string, bool> results;
//   // if (!tknzr->advanceToken()) return results;
//   while (true) {
//     if (!tknzr->advanceToken()) break;
//     Token curToken = tknzr->getToken();
//     std::string type = curToken.type;
//     std::string variable = curToken.content;
//     if (type != "varName") {
//       throw "Error: invalid input";
//     }
//     if (!tknzr->advanceToken() || (tknzr->getToken()).content != ":") {
//       throw "Error: invalid input";
//     }
//     if (!tknzr->advanceToken() || (tknzr->getToken()).type != "constant") {
//       throw "Error: invalid input";
//     }
//     bool truthValue = stoi((tknzr->getToken()).content);
//     if (results.find(variable) == results.end()) {
//       results[variable] = truthValue;
//     } else {
//       if (results[variable] != truthValue) {
//         throw "Error: contradicting assignment";
//       }
//     }
//     if (!tknzr->advanceToken()) break;
//     curToken = tknzr->getToken();
//     if (curToken.content != ",") {
//       throw "Error: invalid input";
//     }
//   }
//   return results;
// }

//AssignmentParser::~AssignmentParser() {delete tknzr;}
