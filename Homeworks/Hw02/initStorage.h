//
// Created by glycerolveinz on 5.11.23.
//

#ifndef HW02_INITSTORAGE_H
#define HW02_INITSTORAGE_H

#include "Storage.h"
#include <vector>
#include <iostream>

Storage readInput();
std::queue<int> readPackages(int boxesCount);
Storage readRooms(int numberOfRooms);

#endif //HW02_INITSTORAGE_H
