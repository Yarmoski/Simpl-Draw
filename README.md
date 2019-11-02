# Simpl-Draw
An art creation tool made in C++.

## Design Descrition

The main function begins by setting the size of the grid to (20, 30), the character to ‘*’ and the mode to foreground (FG). It then loops infinitely, prompting the user to input commands which are fed to the performCommands function. 

The performCommands function returns an integer which is used in the switch statement which can do one of three things: draw the grid after a successful command string, alert the user of a syntax error in the command string, or alert the user of a non-syntax error in the command string (e.g. attempting to plot a point not within the grid.)


plotLine function:

check if function inputs are valid, if not return false
check if points will be plotted out of bounds, if so, return false

if distance is 0, set current point to user’s choice of char

if distance greater than 0
check whether horizontal or vertical
		check whether up/down(vertical) or right/left(horizontal)
loop “distance” amount of times, setting each character in specified direction (horiz/vert) to the user’s choice of char
check whether FG (replace all characters) mode or BG (replace only space characters mode)
	performCommands function:
If syntax error is detected, function returns and stores the position of the syntax error in the badPos variable
If no syntax error is detected but a performance error is detected (non-syntax error), the function returns the error at the end since syntax errors take priority

	initialize 2 variables to track current row/column
read each character in input string, after every command advance iteration to after last character of command
	if empty, return normally
	if c, perform clear command (set char, position, mode back to defaults)
	if f, set brush character to the character following f, change mode to FG
		if f not followed by printable char, return syntax error
	if b, set brush character to the character following b, change mode to BG
		if b not followed by printable char, return syntax error
	check if h (horizontal) or v (vertical)
		check if followed by ‘-‘ (negative)
			check if valid (one or two digits following)
				find distance, call plotLine
					if plotLine false, flag location for performance error
				add distance to row/column variables
	return normally if successfully traversed string without errors
