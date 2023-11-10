//
// Created by glycerolveinz on 5.11.23.
//

#ifndef HW02_STORAGEUTILS_H
#define HW02_STORAGEUTILS_H

#include "Storage.h"
#include <vector>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

Storage readInput();
std::vector<int> readPackages(int boxesCount);
Storage readRooms(int numberOfRooms, std::vector<int> packages);

void recursivePlace(Storage *storage, int curPackageId, int curTime);
void printResult (Storage *storage);

#endif //HW02_STORAGEUTILS_H
