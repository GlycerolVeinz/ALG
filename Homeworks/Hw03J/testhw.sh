#!/bin/bash

failed=0
passed=0

for file in ./datapub/*.in
do
    echo "-------------------"
    result=$(java alg/Main < "$file")
    expected=$(cat "${file%.*}.out")
    time java alg/Main < "$file"
    if [ "$result" == "$expected" ]
    then
        passed=$((passed+1))
        echo "Test passed for $file"
    else
        failed=$((failed+1))
        echo "Test failed for $file"
        echo "Expected: $expected"
        echo "Got: $result"
        echo "-------------------"
    fi
done

echo "Passed: $passed tests"
echo "Failed: $failed tests"




