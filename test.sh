#!/bin/bash
assert() {
    expected="$1"
    input="$2"

    ./9cc "$input" > tmp.s
    cc -o tmp tmp.s
    ./tmp
    actual="$?"

    if [ "$actual" = "$expected" ]; then
        echo "$input => $actual"
    else
        echo "$input => $expected expected, but got $actual"
        exit 1
    fi
}

assert  0 "return 0;"
assert 42 "return 42;"
assert 21 "return 5+20-4;"
assert 41 "return 12 + 34 - 5 ;"
assert 47 "return 5+6*7;"
assert 15 "return 5*(9-6);"
assert  5 "return 15/3;"
assert  4 "return (3+5)/2;"
assert  2 "return -3+5;"
assert  6 "return +2+4;"
assert  1 "return 3 == 3;"
assert  0 "return 3 == (2+5);"
assert  1 "return 3 != 1;"
assert  1 "return 3 > 1;"
assert  0 "return 3 > 3;"
assert  0 "return 3 < 1;"
assert  1 "return 3 >= 3;"
assert  1 "return 3 <= 3;"
assert  1 "return (2+4) <= 3*5;"
assert 10 "return 10;"
assert 20 "return 10*2;"
assert  3 "a=3;return a;"
assert  7 "a=2;b=5;return a+b;"

echo OK