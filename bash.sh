g++ -c -Wall -O2 -std=c++11 maptel.cc -o maptel.o
gcc -c -Wall -O2 maptel_test1.c -o maptel_test1.o
g++ -c -Wall -O2 -std=c++11 maptel_test2.cc -o maptel_test2.o
g++ maptel_test1.o maptel.o -o maptel_test1
g++ maptel_test2.o maptel.o -o maptel_test2


