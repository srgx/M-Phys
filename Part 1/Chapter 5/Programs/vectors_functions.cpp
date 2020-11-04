#include "vectors_functions.h"
#include <cmath>

using std::vector;

vector<float> addVectors(const vector<float> & v1, const vector<float> & v2){
  if(v1.size()!=v2.size()){
    return {};
  }else{
    vector<float> vec;
    for(int i=0;i<v1.size();i++){
      vec.push_back(v1.at(i)+v2.at(i));
    }
    return vec;
  }
}

vector<float> subVectors(const std::vector<float> & v1, const std::vector<float> & v2){
  return addVectors(v1,oppositeVector(v2));
}


vector<float> scaleVector(const vector<float> & vec, float scale){
  vector<float> nVec;
  for(int i=0;i<vec.size();i++){
    nVec.push_back(vec.at(i) * scale);
  }
  return nVec;
}


float magnitude(const vector<float> & vec){
  float s = 0;
  for(int i=0;i<vec.size();i++){
    s += pow(vec.at(i),2);
  }
  return sqrt(s);
}

vector<float> norm(const vector<float> & vec){
  float m = magnitude(vec);
  if(m==0){
    // You cant normalize zero vector
    return {};
  }else{
    return scaleVector(vec,1/m);
  }
}

float angleBetween(const std::vector<float> & v1, const std::vector<float> & v2){
  vector<float> v3 = subVectors(v1,v2);
  float m1 = magnitude(v1);
  float m2 = magnitude(v2);
  float m3 = magnitude(v3);

  // Zero vector or vectors are equal
  if((0==m1||0==m2)||0==m3){
    return 0;
  }else{
    return acos((pow(m1,2) + pow(m2,2) - pow(m3,2))/(2*m1*m2));
  }
}

vector<float> oppositeVector(const std::vector<float> & vec){
  vector<float> vctr;
  for(auto i=vec.begin();i!=vec.end();i++){
    vctr.push_back(-(*i));
  }
  return vctr;
}
