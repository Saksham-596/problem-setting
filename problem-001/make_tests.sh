#!/bin/bash

# Create the tests directory if it doesn't exist
mkdir -p tests

echo "Compiling..."
g++ -O3 generator.cpp -o gen
g++ -O3 solution.cpp -o sol
echo "Compilation complete."

# Generate 50 test cases
for i in {1..50}
do
    # Format the number with a leading zero (e.g., 01, 02, ..., 50)
    printf -v num "%02d" $i
    
    echo "Generating test $num..."
    
    # Run the generator with 'i' as the random seed
    ./gen $i > tests/$num.in
    
    # Pass the input through the solution to get the output
    ./sol < tests/$num.in > tests/$num.out
done

echo "All 50 tests generated successfully in the tests/ directory."