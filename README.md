# Simpl-Draw
An art creation tool made in C++.

## Quickstart
Run the .exe file! Use the Command List below to draw! Chain commands in the same line (no spaces) to create complex drawings.

## CommandList

### Horizontal Line command (H) (- for left, + for right)
This command consists of an upper or lower case H immediately followed by a one to two digit number (positive or negative to indicate direction).

If the current mode is foreground mode, the character in the grid at every position in the line is replaced by the current character. If the current mode is background mode, only the space characters in the grid that are at positions in the line are replaced by the current character. After this plotting command is performed, the current position is the position of the other endpoint of the line.

### Vertical Line command (V) (- for up, + for down)
This command consists of an upper or lower case V immediately followed by a one to two digit number (positive or negative to indicate direction).

If the current mode is foreground mode, the character in the grid at every position in the line is replaced by the current character. If the current mode is background mode, only the space characters in the grid that are at positions in the line are replaced by the current character. After this plotting command is performed, the current position is the position of the other endpoint of the line.

### Foreground command (F)
This command sets the mode to foreground mode and the current character to the character that follows the upper or lower case F.

### Background command (B)
This command sets the mode to background mode and the current character to the character that follows the upper or lower case B.

### Clear command (C)
This command sets every character of the grid to be a space character and sets the current position to (1, 1), the current character to \*, and the current mode to foreground mode.

## Design Descrition

The main function begins by setting the size of the grid to (20, 30), the character to ‘*’ and the mode to foreground (FG). It then loops infinitely, prompting the user to input commands which are fed to the performCommands function. 

The performCommands function returns an integer which is used in the switch statement which can do one of three things: draw the grid after a successful command string, alert the user of a syntax error in the command string, or alert the user of a non-syntax error in the command string (e.g. attempting to plot a point not within the grid.)


### plotLine function:

check if function inputs are valid, if not return false
check if points will be plotted out of bounds, if so, return false

if distance is 0, set current point to user’s choice of char

if distance greater than 0:
- check whether horizontal or vertical
	- check whether up/down(vertical) or right/left(horizontal)
		- loop “distance” amount of times, setting each character in specified direction (horiz/vert) to the user’s choice of char
			- check whether FG (replace all characters) mode or BG (replace only space characters mode)

### performCommands function:

If syntax error is detected, function returns and stores the position of the syntax error in the badPos variable
If no syntax error is detected but a performance error is detected (non-syntax error), the function returns the error at the end since syntax errors take priority

initialize 2 variables to track current row/column
read each character in input string, after every command advance iteration to after last character of command:
- if empty, return normally
- if c, perform clear command (set char, position, mode back to defaults)
- if f, set brush character to the character following f, change mode to FG
	- if f not followed by printable char, return syntax error
- if b, set brush character to the character following b, change mode to BG
	- if b not followed by printable char, return syntax error
- check if h (horizontal) or v (vertical)
	- check if followed by ‘-‘ (negative)
		- check if valid (one or two digits following)
			- find distance, call plotLine
				- if plotLine false, flag location for performance error
		- add distance to row/column variables
- return normally if successfully traversed string without errors

#### Thank you
Thank you to Dr. Smallberg at UCLA for starting help!
