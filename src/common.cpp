#include <random>
#include <stack>
#include "common.hpp"

//mersenne twister
int randomInt(int to, int from){
int rand;
std::random_device rd{};
std::mt19937 engine{rd()};
std::uniform_real_distribution<float> dist{from, to};
rand = dist(engine);

return rand;
}

std::stack<char>* uitoas(unsigned long i){
  static std::stack<char> as;

  if(!as.empty())
    std::stack<char>().swap(as);

  do{
    as.push((char)((i % 10) + 48));
    i = i / 10;
  }while(i != 0);

  return &as;
};

long int atoui(char *a){
  long int i = 0;

  for(int j = 0; a[j] != '\0'; j ++){
    i += i * 10 + a[j] - 48;
  }

  return i;
}

bool atoiCheck(char *a){
  for(int j = 0; a[j] != '\0'; j ++){
    if(a[j] < 48 || a[j] > 57)
      return 0;
  }

  return 1;
}
