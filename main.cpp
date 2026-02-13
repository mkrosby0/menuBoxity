#include "headers/libMenuBoxity.h"
#include <iostream>

int main() {
	TextReturn output;
	tb_init();

	makeMenu(MenuLines {"Main Menu", std::vector<std::string> {"One", "Two", "Three"}, 6});
	output = makeTextInMenu(MenuLines {"Main Menu", std::vector<std::string> {"Four", "Five", "Six", "Exit"}, 4}, std::vector<int> {0, 1, 2});
	
	tb_shutdown();
	std::cout << output.buttonChoice << std::endl;
	for (std::string out : output.textInput) std::cout << out << std::endl;
	return 0;
}
