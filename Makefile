N = 1
FNAME = "example.cnf"

rec: nqueen.cpp
	g++-10 -Wall nqueen.cpp -o bin/nqueen -O2
	./bin/nqueen ${N}
cnf: cnf.cpp
	g++-10 -Wall cnf.cpp -o bin/cnf -O2
	./bin/cnf ${N} ${FNAME}
clean:
	rm bin/nqueen bin/cnf
