# 7SnakeProblem

The problem consistis in finding a pair (two) of 7-Snakes A and B that has the property that the sum of the integers in 7-Snake A is exactly the same as the sum of integers in 7-Snake B in a grid (matrix) of integers.

Notes:
i) The two 7-Snakes must be distinct. They cannot share cells.
ii) In general there may be more than one pair of 7-Snakes with the required property. The program need only find one pair.
iii) If no such pair exists the program should output ‘FAIL’. Otherwise it should output the first pair it finds that has the above property.
iv) The solution depends on your ability to enumerate the set of all pairs of distinnct 7-Snakes in the given grid.
v) In general, the input grid can be any (square) size. The grid should be stored in CSV format on disk and loaded by your solution. This will allow to test your solution on various test examples. The integers in each cell must range from 1 to 256.

# Solution

The solution is to find and store the sum of the integers of each snake. If the algorithm finds 2 valid snakes of the same sum, the program ends.

# How to run?

Assuming you have pre-installed g++ compiler you need run the command below to compile the program:

	g++ main.cpp -o main

Next, you need only run executable with the input:

(Windows)

	main grid.csv (Windows) 
  
(Linux)

	./main grid.csv (Windows) 
