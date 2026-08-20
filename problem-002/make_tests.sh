#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

echo "🔨 Compiling problem files..."
g++ -O2 generator.cpp -o gen
g++ -O2 solution.cpp -o sol
g++ -O2 validator.cpp -o val

echo "📁 Creating tests directory..."
mkdir -p tests
rm -f tests/*.in tests/*.out

echo "🚀 Generating 50 test cases..."

for i in {1..50}; do
    TEST_NUM=$(printf "%02d" $i)
    IN_FILE="tests/${TEST_NUM}.in"
    OUT_FILE="tests/${TEST_NUM}.out"
    
    if [ $i -le 10 ]; then
        T=10
        SUM_N=50
        SUM_M=50
    elif [ $i -le 35 ]; then
        T=100
        SUM_N=5000
        SUM_M=5000
    else
        T=10000
        SUM_N=200000
        SUM_M=200000
    fi
    
    SEED=$((1337 + i * 42))

    echo "------------------------------------------------"
    echo "[Test $TEST_NUM] Running: ./gen $SEED $T $SUM_N $SUM_M"
    
    # 1. Generate Input
    ./gen $SEED $T $SUM_N $SUM_M > $IN_FILE
    
    # 2. Validate Input
    ./val < $IN_FILE
    
    # 3. Generate Output
    ./sol < $IN_FILE > $OUT_FILE
    
    echo "✅ Generated Test $TEST_NUM successfully!"
done

echo "🎉 All 50 test cases successfully generated and validated!"