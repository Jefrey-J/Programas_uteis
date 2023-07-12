#include <iostream>
#include <regex>

bool inicia_com_letra(std::string str) {
	std::regex re("^[a-zA-Z]");
	std::smatch match; 
	return std::regex_search(str, match, re); 
}

int main(int argc, char** argv) {
	std::string str = "1Teste"; 
	if(inicia_com_letra(str)) {
		std::cout << "Inicia com letra!" << "\n"; 
	} else {
		std::cout << "Não inicia com letra!" << "\n"; 
	}
	
	return 0; 
}
