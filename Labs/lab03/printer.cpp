//
// Created by glycerolveinz on 10.10.23.
//

#include <iostream>

void printer(int n){
    if (n == 0) return;
    std::cout << "1";
    printer(n-1);
    std::cout << "22";
}

int main(){

    printer(2);
    return 0;
}
