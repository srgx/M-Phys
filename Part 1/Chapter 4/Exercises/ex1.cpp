#include <iostream>
#include <array>

typedef std::array<float,6> triangleInfo;
using std::cout;

triangleInfo solveTriangle(const triangleInfo & data);

int main(){
  triangleInfo trData({1,2,3,4,5,6});
  solveTriangle(trData);
}

triangleInfo solveTriangle(const triangleInfo & data){
  for(const auto & v : data){
    cout << v << "|";
  }
  cout << "\n";
}
