#include <iostream>
#include <vector>

//squashes the vector in the given range
bool proc_num_two(std::vector<int>& v, int bi, int ei) {
  bool match = 0;

  //compares consecutive numbers
  for (int j = bi; j < ei; j++) {
    //merges if the two numbers are the same
    for (int i = bi; i < ei - 1; i++) {
      if ((v[i] == v[i+1]) && (v[i] != 0)) {
        v[i] = 2 * v[i+1];
        v[i+1] = 0;
        match = 1;
      }
      //swaps if the number on the left if 0
      else if((v[i] == 0) && (v[i+1] != 0)) {
        v[i] = v[i+1];
        v[i+1] = 0;
        match = 1;
      }
    }
  }

  //returns wether a valid move was made
  return match;
}

int main(){
  std::vector<int> v;

  v.push_back(0);
  v.push_back(2);
  v.push_back(2);
  v.push_back(2);
  v.push_back(0);

  std::cout << proc_num_two(v, 0, v.size()) << std::endl;

  for (int i = 0; i < v.size(); i++) {
    std::cout << v[i];
  }
  std::cout << std::endl;

  return 0;
}
