/*
Christopher Smith		01-Sep-2017		CSCI 223
This code is meant to solve a Magic Square of any provided size.
*/
#include <iostream>
#include <string>

//#include <string> 
using namespace std;

/* Sorts values into 2D array based on provided range */
void siameseMethod(int board[32][32], int width, int startRange, int endRange, int row, int col)
{
	board[row][col] = startRange;

	for (int i = startRange; i < endRange; i++)  // Begin placing items in nodes
	{

		if (i % width == 0)
		{
			row++;
			cout << "\n  Bringing next one down a row... ";
		}
		else
		{
			row--;
			col++;
			cout << "\n  Going up and right one spot...";
		}

		if ((row) >= width) // If node value is too low
			row = 0; // ...set it up one value

		if ((row) < 0) // If node value is too high
			row = width - 1; // ...set to lowest value in current grid

		if ((col) >= width) // If node value is too far right
			col = 0; // ...sets to farthest left nodes

		cout << "\n Placing " << i + 1 << "... ";

		if ((row == 0) && (col == 0))
			cout << "\n - Top left unit has been placed! ";

		if ((row == 0) && (col == width - 1))
			cout << "\n - Top right unit has been placed! ";

		if ((row == width - 1) && (col == 0))
			cout << "\n - Bottom left unit has been placed! ";

		if ((row == width - 1) && (col == width - 1))
			cout << "\n - Bottom right unit has been placed! ";

		board[row][col] = i + 1;
	}  // End odd square sort
}

/* If a value is less than the longest value's horizontal length, add spaces for better visibility */
void gridPrinter(int target, int count)
{

	string currentValue = to_string(target);
	int currentLength = currentValue.length();
	int targetLength = to_string(count).length(); 

	while (currentLength < targetLength)
	{
		currentValue = (" ") + currentValue;
		currentLength = currentValue.length();
	}

	cout << "| " << currentValue << " |";
}

void main()
{
	int value, count;
	cout << "\n Please type in the number of rows/columns for your square. (3-18)\n> ";
	cin >> value;
	count = pow(value,2);
	//cout << "\n " << count;
	cout << "\n ";

	int board[32][32]; // Max size of 32 x 32, or 1024 nodes


	for (int i = 0; i < 32; i++) // Sets each node to 0 within 'value' range, rows
	{
		for (int j = 0; j < 32; j++) // Sets each node to 0 within 'value' range, columns
		{
			if ((i >= value) || (j >= value)) // If current value is outside of value given (0 to value-1)
			{
				continue;
			}
			else // Node is within given value
			{
				board[i][j] = 0;
				cout << "#";
			}

		} // End inner j loop

		cout << "\n ";

	} // End inner i loop


	if (value <= 2)
	{
		cout << "\n I'm afraid this value is too little to be made into a magic square! ";
	}
	else
	{
		int row = 0; // Row always starts at the top
		int col = (value / 2); // Column must start halfway through top row

		if (value % 2 == 1) // Odd square logic
		{
			cout << "\n You have entered the odd number " << value << ", so let's see...\n ";

			/*    Utilizing Siamese method    */
			siameseMethod(board, value, 1, count, row, col);
 
		} // End odd square sort
		else // Magic square is even, requires additional logic
		{
			if (value % 4 == 0) // Doubly even logic
			{
				cout << "\n This number is doubly even. ";
				bool flag = false; // Determine if we're in an inverted zone

				/* When in corner or center sixteenths of the square, invert x/y axis location */
				for (int y = 0; y < value; y++)
				{
					for (int x = 0; x < value; x++)
					{
						flag = false; // Reset flag after every place check

						if ((x + 1) <= (value / 4)) // Left quarter of grid
						{
							if ((y + 1) <= (value / 4)) // Top-left region
							{
								board[y][x] = count;
								flag = true;
							}

							if ((y + 1) > (value * 0.75)) // Bottom-left region
							{
								board[y][x] = count;
								flag = true;
							}

						} // End of left quarter check
							
						if ((x + 1) > (value * 0.75)) // Right quarter of grid
						{
							if ((y + 1) <= (value / 4)) // Top-right region
							{
								board[y][x] = count;
								flag = true;
							}

							if ((y + 1) > (value * 0.75)) // Bottom-right region
							{
								board[y][x] = count;
								flag = true;
							}

						} // End of right quarter check

						if ((x + 1) > (value * 0.25) && (x + 1) <= (value * 0.75)) // X is between 1/4 and 3/4
						{
							if ((y + 1) > (value * 0.25) && (y + 1) <= (value * 0.75)) // Y is between 1/4 and 3/4
							{
								board[y][x] = count;
								flag = true;
							}

						} // End of center square check

						if (flag == false) // If current value wasn't in a swap zone...
						{
							int temp = pow(value,2);
							board[y][x] = (temp - count) + 1;
						}
						
						count--; // Decrement count for next loop iteration

					} // End of inner X loop

				}


			}
			else
			{
				cout << "\n This number is only even by one division. ";




			}
				



		} // End of valid input number range

		/* Time to output the square */

		cout << "\n\n This should be a valid magic square! ";
		count = pow(value, 2);

		/* Print out the value in a square grid */
		for (int i = 0; i < value; i++)
		{
			cout << "\n\n ";
			for (int j = 0; j < value; j++)
			{
				gridPrinter(board[i][j], count);
			}
		}

		cout << "\n\n ";

	} // End of valid 'value' else statement

} // end of Main()