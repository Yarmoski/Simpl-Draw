#include "grid.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cassert>

using namespace std;

//Declaring constant variables that are used in functions
const int HORIZ = 0;
const int VERT = 1;

const int FG = 0;
const int BG = 1;

//function prototypes for plotLine and performCommands
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg);
int performCommands(string commandString, char& plotChar, int& mode, int& badPos);

int main()
{
	setSize(20, 30);
	char currentChar = '*';
	int currentMode = FG;


	for (;;)
	{
		cout << "Enter a command string: ";
		string cmd;
		getline(cin, cmd);
		if (cmd == "")
			break;
		int position;
		int status = performCommands(cmd, currentChar, currentMode, position);
		switch (status)
		{
		case 0:
			draw();
			break;
		case 1:
			cout << "Syntax error at position " << position + 1 << endl;
			break;
		case 2:
			cout << "Cannot perform command at position " << position + 1 << endl;
			break;
		default:
			// It should be impossible to get here.
			cerr << "performCommands returned " << status << "!" << endl;
		}
	}
}



bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg)
{
	if (!isprint(plotChar))
		return false;

	if (dir == 1 or dir == 0)
		;
	else
	{
		return false;
	}
		

	if (fgbg == 1 or fgbg == 0)
		;
	else
	{
		return false;
	}
		

	//Check if points will be plotted out of bounds, if so return false
	for (int i = 0; i <= abs(distance); i++)
	{
		if (r < 1 or r > MAXROWS) //initial and extra safety check
		{
			return false;
		}

		if (c < 1 or c > MAXCOLS) //initial and extra safety check
		{
			return false;
		}

		if (dir == 0 and distance < 0 and c - i < 1) //if left horizontal and goes out of bounds return false
		{
			return false;
		}

		if (dir == 0 and distance > 0 and c + i > getCols()) //if right horizontal and goes out of bounds return false
		{
			return false;
		}

		if (dir == 1 and distance < 0 and r - i < 1) //if up vertical and goes out of bounds return false
		{
			return false;
		}

		if (dir == 1 and distance > 0 and r + i > getRows()) //if down vertical and goes out of bounds return false
		{
			return false;
		}

	}

	
	if (distance == 0)
		//set current point to user's char
		setChar(r, c, plotChar);

	if (dir == HORIZ) //if HORIZ
	{
		if (distance > 0) //if right
		{
			for (int i = 0; i <= distance; i++) //execute loop once for every distance
			{
				
				if (fgbg == FG)
				{
					setChar(r, c + i, plotChar);
				}
				else //fgbg == 1
				{
					//only replace characters if they are space characters
					if (getChar(r, c + i) == ' ')
						setChar(r, c + i, plotChar);
				}
			}
		}

		if (distance < 0) //if left
		{
			for (int i = 0; i >= distance; i--)
			{
				if (fgbg == FG)
				{
					setChar(r, c + i, plotChar);
				}
				else //fgbg == 1
				{
					if (getChar(r, c + i) == ' ')
						setChar(r, c + i, plotChar);
				}
			}
		}
	}
	if (dir == VERT) //if VERT
	{
		if (distance > 0) //if down
		{
			for (int i = 0; i <= distance; i++)
			{
				if (fgbg == FG)
				{
					setChar(r + i, c, plotChar);
				}
				else //fgbg == 1
				{
					if (getChar(r + i, c) == ' ')
						setChar(r + i, c, plotChar);
				}
			}
		}

		if (distance < 0) //if up
		{
			for (int i = 0; i >= distance; i--)
			{
				if (fgbg == FG)
				{
					setChar(r + i, c, plotChar);
				}
				else //fgbg == 1
				{
					if (getChar(r + i, c) == ' ')
						setChar(r + i, c, plotChar);
				}
			}
		}
	}


	//if successful, return true
	return true;

}

int performCommands(string commandString, char& plotChar, int& mode, int& badPos)
{
	//used to track current position of brush
	int r = 1;
	int c = 1;

	//used to track non-syntax errors
	bool error2 = false;
	int error2Loc = 0;

	// Loop through command string
	for (int i = 0; i < int(commandString.size());)
	{
		//If empty command string, return with no errors
		if (commandString == "")
			return 0;

		//clear command
		else if (tolower(commandString[i]) == 'c')
		{
			clearGrid();
			plotChar = '*';
			mode = FG;
			i ++;
			r = 1;
			c = 1;
		}

		//foreground change brush command
		else if (tolower(commandString[i]) == 'f')
		{
			// is followed by prinatble char
			if (isprint(commandString[i + 1]))
			{
				plotChar = commandString[i + 1];
				mode = FG;
				i += 2;
			}
			else // is not followed by printable char
			{
				badPos = i + 1;
				return 1;
			}
			
		}

		//background change brush command
		else if (tolower(commandString[i]) == 'b')
		{
			// is followed by prinatble char
			if (isprint(commandString[i + 1]))
			{
				plotChar = commandString[i + 1];
				mode = BG;
				i += 2;
			}
			else // is not followed by printable char
			{
				badPos = i + 1;
				return 1;
			}
		}

		//horiz line command
		else if (tolower(commandString[i]) == 'h')
		{
			//If negative
			if (commandString[i + 1] == '-')
			{
				//if char following - is a digit
				if (isdigit(commandString[i + 2]))
				{
					if (isdigit(commandString[i + 3])) //two -digits
					{
						//Convert chars to ints and find the distance
						int tempDist = -int( ((commandString[i + 2] - '0') * 10) + (commandString[i + 3] - '0') );
						//if plot line fails, set the performance error location
						if (!plotLine(r, c, tempDist, HORIZ, plotChar, mode))
						{
							if (error2 != true)
							{
								error2Loc = i;
								error2 = true;
							}
						}
						
						//advance iteration through the string to the point after the command, add the distance to the columns
						i += 4;
						c += tempDist;
					}
					else //only one -digit
					{
						//Convert chars to ints and find the distance
						int tempDist = -int(commandString[i + 2] - '0');
						//if plot line fails, set the performance error location
						if (!plotLine(r, c, tempDist, HORIZ, plotChar, mode))
						{
							if (error2 != true)
							{
								error2Loc = i;
								error2 = true;
							}
						}
						i += 3;
						//advance iteration through the string to the point after the command, add the distance to the columns
						c += tempDist;
					}
				}
				else
				{
					//if - not followed by digit, set badPos for syntax error and iterate
					badPos = i + 2;
					i++;
					return 1;
				}
			}
			//Same logic as above, except one char less because no '-' char
			else if (isdigit(commandString[i + 1]))
			{
				if (isdigit(commandString[i + 2])) //two digits
				{
					int tempDist = int(((commandString[i + 1] - '0') * 10) + (commandString[i + 2] - '0'));
					if (!plotLine(r, c, tempDist, HORIZ, plotChar, mode))
					{
						if (error2 != true)
						{
							error2Loc = i;
							error2 = true;
						}
					}
					i += 3;
					c += tempDist;
				}
				else //only one digit
				{
					int tempDist = int(commandString[i + 1] - '0');
					if (!plotLine(r, c, tempDist, HORIZ, plotChar, mode))
					{
						if (error2 != true)
						{
							error2Loc = i;
							error2 = true;
						}
						
					}
					i += 2;
					c += tempDist;
				}
			}
			else
			{
				badPos = i + 1;
				i++;
				return 1;//error h followed by not - or digit
			}
			

		}

		//veritcal line command (same logic as above except using rows instead of columns
		else if (tolower(commandString[i]) == 'v')
		{
			if (commandString[i + 1] == '-')
			{
				if (isdigit(commandString[i + 2]))
				{
					if (isdigit(commandString[i + 3])) //two -digits
					{
						int tempDist = -int(((commandString[i + 2] - '0') * 10) + (commandString[i + 3] - '0'));
						if (! plotLine(r, c, tempDist, VERT, plotChar, mode))
						{
							if (error2 != true)
							{
								error2Loc = i;
								error2 = true;
							}
						}
						i += 4;
						r += tempDist;
					}
					else //only one -digit
					{
						int tempDist = -int(commandString[i + 2] - '0');
						if (!plotLine(r, c, tempDist, VERT, plotChar, mode))
						{
							if (error2 != true)
							{
								error2Loc = i;
								error2 = true;
							}
						}
						i += 3;
						r += tempDist;
					}
				}
				else
				{
					badPos = i + 2;
					i++;
					return 1;//error - followed by not digit
				}
			}
			else if (isdigit(commandString[i + 1]))
			{
				if (isdigit(commandString[i + 2])) //two digits
				{
					int tempDist = int(((commandString[i + 1] - '0') * 10) + (commandString[i + 2] - '0'));
					if (!plotLine(r, c, tempDist, VERT, plotChar, mode))
					{
						if (error2 != true)
						{
							error2Loc = i;
							error2 = true;
						}
					}
					i += 3;
					r += tempDist;
				}
				else //only one digit
				{
					int tempDist = int(commandString[i + 1] - '0');
					if (!plotLine(r, c, tempDist, VERT, plotChar, mode))
					{
						if (error2 != true)
						{
							error2Loc = i;
							error2 = true;
						}
					}
					i += 2;
					r += tempDist;
				}
			}
			else
			{
				badPos = i + 1;
				i++;
				return 1;//error h followed by not - or digit
			}


		}
		else
		{
			badPos = i;
			i++;
			return 1;
		}


	}
	
	if (error2) //if no syntax errors and there is "cannot perform" error (since syntax errors take priority over performance errors)
	{
		badPos = error2Loc;
		return 2;
	}
		
	//If everything went smoothly, return 0 for normal operation
	return 0;

}

