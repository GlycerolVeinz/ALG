#!/bin/bash


fails=0
passes=0

for file in ./datapub/*.in
do
    echo "------------------------------------"
    result=$(./cmake-build-debug/Hw03 < "$file")
    shouldbe=$(cat "${file%.*}.out")
    time ./cmake-build-debug/Hw03 < "$file"
    if [ "$result" == "$shouldbe" ]
    then
        passes=$((passes+1))
        echo "Test passed for $file"
    else
        fails=$((fails+1))
        echo "Test failed for $file"
        echo "Expected: $shouldbe"
        echo "Got: $result"
    fi
    echo "------------------------------------"
done

echo "Passed $passes tests"
echo "Failed $fails tests"



