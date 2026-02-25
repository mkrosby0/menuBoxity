#include "headers/libMenuBoxity.h"
#include <iostream>

int main() {
	menuBoxity::TextReturn output;
	tb_init();

	menuBoxity::makeMenu(menuBoxity::MenuLines {"Main Menu", std::vector<std::string> {"One", "Two", "Three"}, 6});
	output = menuBoxity::makeTextInMenu(menuBoxity::MenuLines {"Main Menu", std::vector<std::string> {"Four", "Five", "Six", "Exit"}, 4}, std::vector<int> {0, 1, 2});
	
	tb_shutdown();
	std::cout << output.buttonChoice << std::endl;
	for (std::string out : output.textInput) std::cout << out << std::endl;
	return 0;
}
