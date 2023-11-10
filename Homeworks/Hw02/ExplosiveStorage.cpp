//
// Created by glycerolveinz on 5.11.23.
//

#include "storageUtils.h"
#include "Storage.h"

int main() {
    Storage explosiveStorage = readInput();
    recursivePlace(&explosiveStorage, 0, 0);
    printResult(&explosiveStorage);

    return 0;
}
