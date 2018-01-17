Finds each configuration where there can be 8 queens on an 8 x 8 chess board without the queens attacking each other.

There are 8 for loops in the main function. They are nested and only goes into the next for loop if it is able to place a queen.
If you pass the condition at the eighth for loop, you have placed all 8 queens. Prints the row and col of each queen.

When a queen is placed, mark queen is called which marks all the spots that another queen cannot go.
When a for loop terminates, unmarks all the spots that queen blocked.

reset() resets every spot on the board to 0
prints the number of the solution at the beginning of the print statement when printing a solution. Also separates the row and column using a space and comma for readability.

Cuts off all solutions after 94 because they are wrong. 
