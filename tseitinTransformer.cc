#include "tseitinTransformer.h"

TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot{root} {}

int TseitinTransformer::transSubformula(TreeNode* subRoot) {
// Check if the subformula is a leaf node
if (subRoot->getLeftChild() == nullptr && subRoot->getRightChild() == nullptr) {
// Check if the variable has already been assigned an ID
auto it = varIdTable.find(subRoot->getContent());
if (it != varIdTable.end()) {
// Return the existing ID if it has been assigned
return it->second;
} else {
// Assign a new ID and store it in the table if it has not been assigned
int id = varIdCounter++;
varIdTable[subRoot->getContent()] = id;
return id;
}
}

// Create a new variable ID for the subformula
int curID = varIdCounter++;

// Add the appropriate clause to the CNF formula based on the operator
std::string root_node = subRoot->getContent();
 if(root_node.compare("*") == 0){
  int leftID = transSubformula(subRoot->getLeftChild());
  int rightID = transSubformula(subRoot->getRightChild());
  addAndEq(curID, leftID, rightID);
 }
 else if(root_node.compare("+") == 0){
  int leftID = transSubformula(subRoot->getLeftChild());
  int rightID = transSubformula(subRoot->getRightChild());
  addOrEq(curID, leftID, rightID);
 }
 else if(root_node.compare("-") == 0){
  int leftID = transSubformula(subRoot->getLeftChild());
  addNegEq(curID, leftID);
 }
return curID;
}



// #include "tseitinTransformer.h"



// // recursive function called on each subformula
// int TseitinTransformer::transSubformula(TreeNode* subRoot) {
// // your code starts here
//       //subroot: operator
//       //transSubformula: number

// // std::string subLC = subRoot->getLeftChild();
// // std::string subRC = subRoot->getRightChild();
// // if (varIdTable.find(subLC)) {
// //   return 0;
// // } else {
// //   varIdTable.insert< 
// // }


//   std::string content = subRoot->getContent();

// //if root is operators;

//   if (content == "-" || content == "*" || content == "+"){

//     int curID = varIdCounter;
//     varIdCounter++;
//     int leftID = transSubformula(subRoot->getLeftChild());
//     int rightID = transSubformula(subRoot->getRightChild());

//     if (content == "-") {
//       addNegEq(curID, leftID);
//     }

//     else (content == "*") {
//       addOrEq(curID, leftID, rightID);
//     }

//     else if (content == "+") {
//       addAndEq(curID, leftID, rightID);
//     }
//   }

// //if root is literal

//   if (content != "-" && content != "*" && content != "+"){

//     if (varIdTable.find(content) == varIdTable.end()){
//       varIdTable[content] = varIdCounter;
//       varIdCounter++;
//     }
//     return varIdTable[content];
//   }

// }


// add clauses for a negation subformula
//changed childID to leftID
void TseitinTransformer::addNegEq(int curID, int leftID) {
  // your code starts here
  std::vector<int> clause1;
  clause1.push_back(-curID);
  clause1.push_back(-leftID);
  cnf.push_back(clause1);

  std::vector<int> clause2;
  clause2.push_back(curID);
  clause2.push_back(leftID);
  cnf.push_back(clause2);

}
// add clauses for an or subformula (+, V, ||)
void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
  std::vector<int> clause1;
  clause1.push_back(-curID);
  clause1.push_back(leftID);
  clause1.push_back(rightID);
  cnf.push_back(clause1);

  std::vector<int> clause2;
  clause2.push_back(curID);
  clause2.push_back(-leftID);
  cnf.push_back(clause2);

  std::vector<int> clause3;
  clause3.push_back(curID);
  clause3.push_back(-rightID);
  cnf.push_back(clause3);


}


// add clauses for an AND subformula (*, ^, &&)
void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
  std::vector<int> clause1;
  clause1.push_back(-curID);
  clause1.push_back(leftID);
  cnf.push_back(clause1);

  std::vector<int> clause2;
  clause2.push_back(-curID);
  clause2.push_back(rightID);
  cnf.push_back(clause2);

  std::vector<int> clause3;
  clause3.push_back(curID);
  clause3.push_back(-leftID);
  clause3.push_back(-rightID);
  cnf.push_back(clause3);

}

std::vector<std::vector<int>> TseitinTransformer::transform() {
  // your code starts here [(1,2,3)] 
  int aaa=transSubformula(formulaRoot);
  std::vector<int> aaav;
  aaav.push_back(aaa);
  cnf.push_back(aaav);

  return cnf;
}

std::string TseitinTransformer::cnfString() const {
  std::string result = "";
  for (int i=0; i<cnf.size(); i++){
    result.append("[");
    for(int j=0; j<cnf[i].size(); j++){
    result.append(std::to_string(cnf[i][j])+", ");
    }
    result.pop_back();
    result.pop_back();
    result.append("]");
  } 
  
  return result;
}

unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
  return varIdCounter;
}
