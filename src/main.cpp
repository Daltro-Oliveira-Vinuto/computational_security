#include <iostream>
#include <string>
#include <unordered_map>
#include "Vigenere.h"
#include "Funcoes.h"



int main(int argc, char **argv) {
	std::string plainPath;
	std::string hiddenPath; 
	std::string key = "";
	std::string language;

	Load(argc, argv, plainPath, hiddenPath, language);

	std::cout << plainPath << " , " << hiddenPath << " , ";
	std::cout << language << " , " << std::endl;
	
	Vigenere* vigenere = new Vigenere(plainPath, hiddenPath, key, language);

	Run(vigenere);
	
	delete vigenere;

	return 0;
}