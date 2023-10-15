#!/bin/bash


for file in ./datapub/*.in
do
    result=$(./cmake-build-debug/Hw01 < "$file")
    shouldbe=$(cat "${file%.*}.out")
    time ./cmake-build-debug/Hw01 < "$file"
    if [ "$result" == "$shouldbe" ]
    then
        echo "Test passed for $file"
    else
        echo "Test failed for $file"
        echo "Expected: $shouldbe"
        echo "Got: $result"
    fi
done




