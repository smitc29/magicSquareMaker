/*
Christopher Smith		01-Sep-2017		CSCI 223
This code is meant to solve a Magic Square of any provided size.
*/
#include <iostream>
#include <string>
#include <vector>

//#include <string> 
using namespace std;

/* Sorts values into 2D array based on provided range */
vector<vector<int>> siameseMethod(vector < vector<int> > board, int width, int startRange, int endRange, int row, int col, int offsetX = 0, int offsetY = 0)
{
	board[row][col] = startRange;

	for (int i = startRange; i < endRange; i++)  // Begin placing items in nodes
	{

		if (i % width == 0)
		{
			row++;
			// cout << "\n  Bringing next one down a row... ";
		}
		else
		{
			row--;
			col++;
			// cout << "\n  Going up and right one spot...";
		}

		if ((row) >= (width + offsetY)) // If node value is too low
			row = offsetY; // ...set it up one value

		if ((row) < offsetY) // If node value is too high
			row = (width + offsetY) - 1; // ...set to lowest value in current grid

		if ((col) >= (width + offsetX)) // If node value is too far right
			col = offsetX; // ...sets to farthest left nodes

		// cout << "\n Placing " << i + 1 << "... ";

		board[row][col] = i + 1;
	}  // End odd square sort

	return board;
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
	count = int(pow(value,2));
	//cout << "\n " << count;
	cout << "\n ";

	// Preset basic board with 3x3, cannot make magic circle with less
	vector<vector<int>> board
	{
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	};

	while (int(board.size()) < value)
	{
		board.push_back({0,0,0});
	}

	for (int i = 0; i < value; i++)
	{
		while (int(board[i].size()) < value)
		{
			board[i].push_back(0);
		}
	}

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
			board = siameseMethod(board, value, 1, count, row, col);
 
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

				int row = 0; // Row always starts at the top
				int col = value / 4; // Column must start quarter-way through top row
				board = siameseMethod(board, value/2, 1, count/4, row, col); // Top-left

				row = (value / 2); // Bottom-right section is placed 2nd
				col = value * 0.75;
				board = siameseMethod(board, value / 2, (count / 4) + 1, count / 2, row, col, value / 2, value / 2); // Bottom-right

				row = 0; // Top-right section is placed 3rd
				col = value * 0.75;
				board = siameseMethod(board, value / 2, (count / 2) + 1, count * 0.75, row, col, value / 2); // Top-right

				row = (value / 2) - 1; //Bottom left section placed last
				col = value / 4; 
				board = siameseMethod(board, value / 2, count * 0.75, count, row, col, 0, value / 2); // Bottom-left

				/* After setting up the initial board, a few tiles need to be swapped */


				int targets = ((value - 6) / 4) + 1;
				cout << targets << "\n "; // Number of columns that need to be re-arranged

				for (int i = 0; i < value / 2; i++)
				{
					for (int j = 0; j < targets; j++) // Go through every column... (0-target)
					{
						// Swap the 2 values until we reach the required outcome
						if (i != (value / 4))
						{
							board[i][j] = board[i][j] + board[i + (value / 2)][j];
							board[i + (value / 2)][j] = board[i][j] - board[i + (value / 2)][j];
							board[i][j] = board[i][j] - board[i + (value / 2)][j];
						}
						else
						{
							board[i][j + 1] = board[i][j + 1] + board[i + (value / 2)][j + 1];
							board[i + (value / 2)][j + 1] = board[i][j + 1] - board[i + (value / 2)][j + 1];
							board[i][j + 1] = board[i][j + 1] - board[i + (value / 2)][j + 1];
						}
						
					} // End inner loop for left side of grid

				} // End outer For loop, rearranging left side of grid

				targets--;

				for (int i = 0; i < value / 2; i++) // Every row...
				{
					for (int j = value - targets; j < value; j++) // Go through every column... (value-n to value)
					{
						// Swap the 2 values until we reach the required outcome
						board[i][j] = board[i][j] + board[i + (value / 2)][j];
						board[i + (value / 2)][j] = board[i][j] - board[i + (value / 2)][j];
						board[i][j] = board[i][j] - board[i + (value / 2)][j];
						
					} // End inner loop for right side of grid

				} // End outer For loop, rearranging right side of grid


			} // End single division even number
				
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