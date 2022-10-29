#include <iostream>
#include <algorithm>

bool compf(int a , int b){
    return (a < b);
}

int main(){
    int v[] = { 9, 9, 7, 2, 5, 10, 11, 12, 1, 3, 6 };
    int *i;
    for(int i : v){
        for (int j : v){
            std::cout << j;
        }
    }
  
}

