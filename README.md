
# Tseitin’s Transformation

## Objective
The purpose of this project is to transform a Boolean formula F into an equisatisfiable formula F′ in CNF using Tseitin’s Transformation. The program is expected to output the satisfiability result of F by use of an SAT solver on F′.


### Context-free Grammar for Valid Inputs

One valid input formula shall be a string generated from the Context-Free Grammar below:
Formula ::= ConjTerm | ConjTerm ’+’ Formula
ConjTerm ::= Term | Term ’*’ ConjTerm
Term ::= VarName | ’-’Term | ’(’ Formula ’)’
VarName ::= a continuous sequence of letters (upper- or lowercase) or digits (0-9);
the first character cannot be a digit; the total length shall be no longer than 10

### Semantics of the Input
One valid input is a string representation of a Boolean formula SF in conformity with the aforementioned CFG. In SF , a Boolean variable is a sequence of letters (either in upper- or lowercase) or digits (0-9); however, the variable name cannot start with a digit and its total length cannot be longer than 10. ”+” represents the 2-argument infix Boolean function OR; ”∗” represents the 2-argument infix Boolean function AND; ”−” represents the prefix 1-argument Boolean function NOT. The order of operations is: parenthesis > NOT > AND > OR.

### Transformation Example
(a)
Input SF :
c + d
CNF F′:
[−1, 2, 3][−2, 1][−3, 1][1]
Comments:
2 represents variable c and 3 represents variable d in this example.

(b)
Input SF :
c ∗ (d + c)
CNF F′:
[−3, 4, 2][−4, 3][−2, 3][−1, 2][−1, 3][−2,−3, 1][1]
Comments:
4 represents variable d and 2 represents variable c in this example.
