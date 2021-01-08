#include <iostream>
#include <array>

std::pair<std::array<float,2>,float> javelin(float throwAngle,
                                             float throwSpeed, float time);

int main(){
  auto result = javelin(3,4,5);
  auto z = result.second;
  std::cout << z << std::endl;
}

std::pair<std::array<float,2>,float> javelin(float throwAngle,
                                             float throwSpeed, float time){
  
  return std::make_pair(std::array<float,2>({5,6}),12);
  
}
