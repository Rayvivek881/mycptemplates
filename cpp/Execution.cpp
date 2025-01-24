#include<bits/stdc++.h>
using namespace std;
class ExecutionTime {
  clock_t start;
  const char* name;
public:
  inline void begin(const char* name) {
    this->name = name; 
    start = clock(); 
  }
  inline void end() const {
    double d = (double)(clock() - start) / CLOCKS_PER_SEC;
    cerr << name << " Execution Time: " << d << "s\n";
  }
}; 