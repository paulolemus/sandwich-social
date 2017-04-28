get standard screens dims
	xMax, yMax

use those to determine the dims for the other windows
	send off for a depth and width function
	for the window we want

get those vals and send to a homemade window setup
	WINDOW* win_name = newwin ... 
	box(win_name, 0, 0)
	wrefresh(win_name)

selector
	switch statement based on wgetch(win_name)
