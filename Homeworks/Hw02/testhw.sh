#!/bin/bash


for file in ./datapub/*.in
do
    result=$(./cmake-build-debug/Hw02 < "$file")
    expected=$(cat "${file%.*}.out")
    time ./cmake-build-debug/Hw02 < "$file"
    if [ "$result" == "$expected" ]
    then
        echo "Test passed for $file"
    else
        echo "Test failed for $file"
        echo "Expected: $expected"
        echo "Got: $result"
    fi
done




