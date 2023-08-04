#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <map>
#include <iostream>
#include <memory>


bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int>> &cnf) {
  // your code starts here

// // Create a new solver for minisat:
Minisat::Solver solver;
std::map<int, Minisat::Lit> minimap;

for (int i=1; i<numVar; i++){
  minimap.insert({i,  Minisat::mkLit(solver.newVar())});
}

  for (int i=0; i<cnf.size(); i++){
    Minisat::vec<Minisat::Lit> temp;
    for(int j=0; j<cnf[i].size(); j++){
      if (cnf[i][j]<0)
      {temp.push({~minimap[-1*cnf[i][j]]});
      }
      else {
        temp.push({minimap[cnf[i][j]]});
      }
    }
    solver.addClause(temp);
  }
  bool output=solver.solve();

// solver->addClause(a , b, c);

// solver->solve();


// Minisat::vec<Minisat::Lit> SomeVector;

// solver->addClause(SomeVector)

   //  std::unordered_map<Formula, int> variable_map;
    //  CNF cnf = tseitin(formula, variable_map);





// std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());

// Minisat::Lit l1, l2, l3, l4;
// Minisat::Lit b0, b1, b2;

// // create 4 positive literals over 4 new variables
// l1 = Minisat::mkLit(solver->newVar());
//     // (l1 || b0)
//     solver->addClause(l1, b0);
//     // (!b0 || l2 || b1)
//     solver->addClause(~b0, l2, b1);
// bool res = solver->solve();
//     std::cout << "The result is:ls " << res << "\n";
  return output;
}
