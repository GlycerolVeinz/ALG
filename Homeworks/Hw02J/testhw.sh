#!/bin/bash

failed=0
passed=0

for file in ./datapub/*.in
do
    result=$(java ExplosiveStorage < "$file")
    expected=$(cat "${file%.*}.out")
    time java ExplosiveStorage < "$file"
    if [ "$result" == "$expected" ]
    then
        passed=$((passed+1))
        echo "Test passed for $file"
    else
        failed=$((failed+1))
        echo "Test failed for $file"
        echo "Expected: $expected"
        echo "Got: $result"
    fi

    echo "Passed: $passed tests"
    echo "Failed: $failed tests"
done




