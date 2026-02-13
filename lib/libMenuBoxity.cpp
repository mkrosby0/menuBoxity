#define TB_IMPL
#define WIDGETS_IMPL
#define STB_DS_IMPLEMENTATION
#include "../headers/libMenuBoxity.h"
#include <algorithm>

int makeMenu(MenuLines myMenu, int background, int foreground, int highlight) {
	struct tb_event ev {0};
	struct input input;
	struct widget_points box;
	int returnValue = -1;
	int selectedItem = 0;


	if (global.initialized) {
		tb_set_input_mode(TB_INPUT_ALT);
		setlocale(LC_ALL, "");
		if (!input_init(&input, TB_DEFAULT, false)) {
			do {
				// size internal boxes
				if (ev.type == 0 || ev.type == 2) {
					tb_clear();

					// Box
					box = { global.width / 5, global.width * 4 / 5,
							global.height / 5, global.height * 4 / 5 };
					border_redraw(&box, foreground, background);

					// Labels
					tb_printf(
							(global.width - myMenu.storeName.length()) / 2,
							box.y1 - 3,
							foreground,
							background,
							myMenu.storeName.c_str()
							);
					tb_printf(
							(global.width - myMenu.menuName.length()) / 2,
							box.y1 - 2,
							foreground,
							background,
							myMenu.menuName.c_str()
							);
				}

				// make menu listing; highlight selected item
			   	tb_printf(10, 10, TB_BLACK, highlight,
			   			"type: %d, key: %d, ch: %c, w: %d, h: %d",
						ev.type, ev.key, ev.ch, global.width, global.height);
			   	tb_printf(10, 9, TB_BLACK, highlight,
			   			"Selected item %d", selectedItem);

			   	// menu lines printout
			   	for (int y = 0; y < myMenu.menuLines.size(); y++) {
			   		tb_printf(box.x1 + 2, box.y1 + y + 2,
			   				(y == selectedItem) ? TB_BLACK : foreground,
			   				(y == selectedItem) ? highlight : background,
			   				myMenu.menuLines.at(y).c_str());
			   	}

			   	// update screen before input
			   	tb_present();
			   	clear_line(box.y2 + 2); // Notification line

				// poll for menu navigation; ensure an option is selected when enter is pressed
			   	tb_poll_event(&ev); // Get key input

			   	switch (ev.key) { // Key type: 0 for char, 13 for enter, 655xx for arrow keys
			   	case 0:
			   	switch (ev.ch) {
			   	case '0':
			   		selectedItem = myMenu.menuLines.size() - 1;
			   		break;
			   	default:
			   		if (ev.ch >= '1' && ev.ch <= myMenu.menuLines.size() + 48) {
			   			selectedItem = ev.ch - 49;
			   		}
			   		else tb_printf( // Use notif line to correct user
			   				box.x1 + 1,
			   				box.y2 + 2,
							foreground,
							background,
							"Invalid input"
							);
			   	}
			   	break;
			   	case 13:
			   		returnValue = selectedItem;
			   		break;
			   	case 65517:
			   		selectedItem = (selectedItem > 0) ? selectedItem - 1 : myMenu.menuLines.size() - 1;
			   		break;
			   	case 65516:
			   		selectedItem = (selectedItem < myMenu.menuLines.size() - 1) ? selectedItem + 1 : 0;
			   		break;
			   	}
			} while (ev.key != 13);
		}
	}

	return returnValue;
}

TextReturn makeTextInMenu(MenuLines myMenu, std::vector<int> textOptionLines, int background, int foreground, int highlight) {
	char* inputBuf = NULL;
	struct tb_event ev {0};
	struct input input;
	struct widget_points box;
	struct widget_points inputBox;
	struct TextReturn returnValue = {-1, std::vector<std::string> {textOptionLines.size()}};
	int selectedItem = 0;
	int rows = 0;
	bool enterTextInput = false;
	std::vector<int>::iterator myIter;

	if (global.initialized) {
		tb_set_input_mode(TB_INPUT_ALT);
		setlocale(LC_ALL, "");
		if (!input_init(&input, TB_DEFAULT, false)) {
			do {
				// size internal boxes
				if (ev.type == 0 || ev.type == 2) {
					tb_clear();

					// Box
					box = { global.width / 5, global.width * 4 / 5,
							global.height / 5, global.height * 4 / 5 };
					border_redraw(&box, foreground, background);

					// Centre Line
					widget_clear(widget_points {(box.x1 + box.x2) / 2, (box.x1 + box.x2) / 2 + 1, box.y1 + 1, box.y2 - 2}, '|');

					// Labels
					tb_printf(
							(global.width - myMenu.storeName.length()) / 2,
							box.y1 - 3,
							foreground,
							background,
							myMenu.storeName.c_str()
							);
					tb_printf(
							(global.width - myMenu.menuName.length()) / 2,
							box.y1 - 2,
							foreground,
							background,
							myMenu.menuName.c_str()
							);
				}

				// make menu listing; highlight selected item
			   	tb_printf(10, 10, TB_BLACK, highlight,
			   			"type: %d, key: %d, ch: %c, w: %d, h: %d",
						ev.type, ev.key, ev.ch, global.width, global.height);
			   	tb_printf(10, 9, TB_BLACK, highlight,
			   			"Selected item %d", selectedItem);

			   	// menu lines printout
			   	for (int y = 0; y < myMenu.menuLines.size(); y++) {
			   		tb_printf(box.x1 + 2, box.y1 + y + 2,
			   				(y == selectedItem) ? TB_BLACK : foreground,
			   				(y == selectedItem) ? highlight : background,
			   				myMenu.menuLines.at(y).c_str());
			   		if ((myIter = std::find(textOptionLines.begin(), textOptionLines.end(), y)) != textOptionLines.end()) {
			   			widget_clear(widget_points { (box.x1 + box.x2) / 2 + 2, box.x2 - 1, box.y1 + y + 2, box.y1 + y + 2 });
			   			inputBuf = (y == selectedItem) ? input_buf(&input) : NULL;
			   			tb_printf((box.x1 + box.x2) / 2 + 2, box.y1 + y + 2,
			   					(y == selectedItem) ? TB_BLACK : foreground,
			   					(y == selectedItem) ? highlight : background,
			   					(y == selectedItem) ? ((inputBuf) ? inputBuf : returnValue.textInput[std::distance(textOptionLines.begin(), myIter)].c_str()) : returnValue.textInput[std::distance(textOptionLines.begin(), myIter)].c_str());
			   			if (inputBuf) free(inputBuf);
			   			inputBuf = NULL;
			   		}
			   	}

			   	// update screen before input
			   	tb_present();
			   	clear_line(box.y2 + 2); // Notification line

			   	// poll for menu navigation; ensure an option is selected when enter is pressed
				tb_poll_event(&ev); // Get key input

			   	if (enterTextInput) { // Process text input on the line
			   		inputBox = { box.x2 - 15, box.x2, box.y1 + selectedItem, box.y1 + selectedItem + 2};
			   		switch (ev.key) {
			   		case 0:
			   			if (ev.ch) input_handle_event(&input, INPUT_ADD, ev.ch);
			   			break;
			   		case TB_KEY_BACKSPACE:
			   		case TB_KEY_BACKSPACE2:
			   			input_handle_event(&input, INPUT_DELETE);
			   			break;
			   		case TB_KEY_ARROW_RIGHT:
			   			input_handle_event(&input, INPUT_RIGHT);
			   			break;
			   		case TB_KEY_ARROW_LEFT:
			   			input_handle_event(&input, INPUT_LEFT);
			   			break;
			   		case TB_KEY_ENTER:
			   			//Add string to vec according to identity in textOptionLines, go back to parent logic
			   			inputBuf = input_buf(&input);
			   			returnValue.textInput[std::distance(textOptionLines.begin(), std::find(textOptionLines.begin(), textOptionLines.end(), selectedItem))] = std::string { inputBuf ? inputBuf : "" };
			   			enterTextInput = false;
			   			ev.key = 0;
			   			free(inputBuf);
			   			inputBuf = NULL;
			   			input_handle_event(&input, INPUT_CLEAR); // Can't find a good place for this... Here, it only clears when you re-enter a field, which is more-or-less fine. Check the render block for how it doesn't erase stuff by accident, it's the longest line by far
			   			break;
			   		}
			   		//input_redraw(&input, &inputBox, &rows, true);
			   	}
			   	else {

					switch (ev.key) { // Key type: 0 for char
					case 0:
					switch (ev.ch) {
					case '0':
						selectedItem = myMenu.menuLines.size() - 1;
						break;
					default:
						if (ev.ch >= '1' && ev.ch <= myMenu.menuLines.size() + 48) {
							selectedItem = ev.ch - 49;
						}
						else tb_printf( // Use notif line to correct user
								box.x1 + 1,
								box.y2 + 2,
								foreground,
								background,
								"Invalid input"
								);
					}
					break;
					case TB_KEY_ENTER: // enter no longer assumes exit
						if (!(enterTextInput = std::find(textOptionLines.begin(), textOptionLines.end(), selectedItem) != textOptionLines.end()))
							returnValue.buttonChoice = selectedItem;
						break;
					case TB_KEY_ARROW_UP:
						selectedItem = (selectedItem > 0) ? selectedItem - 1 : myMenu.menuLines.size() - 1;
						break;
					case TB_KEY_ARROW_DOWN:
						selectedItem = (selectedItem < myMenu.menuLines.size() - 1) ? selectedItem + 1 : 0;
						break;
					}
			   	}
			} while (enterTextInput || ev.key != 13);
			input_finish(&input);
		}
	}

	return returnValue;
}

int widget_clear(const widget_points& widget, char replace) {
	int y, x, rv;
	uint32_t space = (uint32_t)replace;
	for (y = widget.y1; y <= widget.y2; y++) {
		for (x = widget.x1; x < widget.x2; x++) {
			if_err_return(rv,
			cell_set(&global.back.cells[y * global.width + x], &space, 1, global.fg, global.bg));
		}
	}
	return TB_OK;
}

int clear_line(int line, char replace) {
	if (line < global.height) {
	int x, rv;
	uint32_t space = (uint32_t)replace;
	for (x = 0; x < global.width; x++) {
		if_err_return(rv,
		cell_set(&global.back.cells[line * global.width + x], &space, 1, global.fg, global.bg));
	}
	}
	return TB_OK;
}

int clear_col(int col, char replace) {
	if (col < global.width) {
	int y, rv;
	uint32_t space = (uint32_t)replace;
	for (y = 0; y < global.height; y++) {
		if_err_return(rv,
		cell_set(&global.back.cells[y * global.width + col], &space, 1, global.fg, global.bg));
	}
	}
	return TB_OK;
}

