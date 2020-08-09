## N-queen solver

#### Source code
1. nqueen.cpp: recursion solver
```
$ make rec N=<number>
```
2. cnf.cpp: translate into CNF. (Output .cnf file)
```
$ make cnf N=<number> FNAME=<CNFfilename>
```
With MacOS,
```
$ cryptominisat5 <CNFfilename>
```
You may need to install cryptominisat with brew.   
With WSL, replace cryptominisat as minisat, which can be installed by apt.

#### Reference
- https://leetcode.com/problems/n-queens/
- http://vivi.dyndns.org/tech/puzzle/NQueen.html
- https://sites.google.com/site/haioushen/search-algorithm/solvean-queensproblemusingsatsolver