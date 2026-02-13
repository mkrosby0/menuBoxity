#include "widgets.h"
#include <string>
#include <vector>

struct MenuLines {
	std::string menuName;								///< Menu Name
	std::vector<std::string> menuLines;					///< Menu Options
	int longestMenuLineLength;							///< Longest Line Length
	std::string initialInfoLine = "";                   ///< Info Line at bottom
	std::string storeName = "Project Bank";             ///< Name of Bank
};

struct TextReturn {
	int buttonChoice;
	std::vector<std::string> textInput;
};

/*
 * Clearing functions:
 *  Clear a widget, line or column.
 */
int widget_clear(const widget_points& widget, char replace = ' ');
int clear_line(int line, char replace = ' ');
int clear_col(int col, char replace = ' ');

/*
 * makeMenu:
 *  Makes menu using MenuLines information.
 */
int makeMenu(MenuLines myMenu, int background = 0, int foreground = TB_WHITE, int highlight = TB_CYAN);

/*
 * MakeTextInMenu:
 *  Makes menu with MenuLines, and selects options to make text input using
 *  textOptionLines. The final textOptionLines entry should be a negative
 *  int to delimit the end of the series.
 */
TextReturn makeTextInMenu(MenuLines myMenu, std::vector<int> textOptionLines, int background = 0, int foreground = TB_WHITE, int highlight = TB_CYAN);
