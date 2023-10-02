#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#ifndef VIGENERE_H
#define VIGENERE_H

class Vigenere {
public:
	Vigenere(const std::string&, const std::string& ,
		const std::string&, const std::string& );

	~Vigenere();

	void Encrypt();
	void Decrypt();

	std::string GetKey();
	void SetKey(const std::string&);
	std::string FindKey(unsigned);
	unsigned FindKeyLength(const std::vector<char>&);

	char BreakCaesarCipher(std::vector<char>&);

	std::vector<unsigned> GetFactors();

	std::string vigenere_key;

private:
	std::string key;
	std::string plainText;
	std::string hiddenText;
	std::unordered_map<char, double> alphabet;

	bool readFile(const std::string& , std::vector<std::string>&);
	bool writeFile(const std::string&, std::vector<std::string>&);
	std::vector<unsigned> factors;
};


#endif