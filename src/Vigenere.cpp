#include <ctype.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>

#include "Vigenere.h"


// OBSERVATION:
// if the key is only one letter than Vigenere cipher become cesar cipher


void addFactors(std::vector<unsigned>& factors, unsigned value) {
	unsigned maximum_length = factors.size();
	for(unsigned i = 2; i < maximum_length; i++) {
		if ((value % i)== 0) {
			unsigned index = i-2;
			factors[index] += 1;
		}
	}
} 

Vigenere::~Vigenere() {

}

double GetProduct(const std::vector<double>& vector_a,
				const std::vector<double>& vector_b) {

	double sum = 0;

	if (vector_a.size() == vector_b.size()) {
		unsigned size = vector_a.size();
		for(unsigned i = 0; i < size; i++) {
			sum+= vector_a[i]*vector_b[i];
		}

	}else {
		printf("Error vectors with different sizes!\n");
	}

	return sum;
}

template <class T>
void printVector(const std::vector<T>& vector,const std::string& string="") {
	for(unsigned i = 0; i < vector.size(); i++) {
		std::cout << vector[i]; std::cout << string;
	}

	std::cout << std::endl;
}


void printVectorDouble(const std::vector<double>& vector) {
	for(unsigned i = 0; i < vector.size(); i++) {
		if (i != vector.size()-1) {
			std::cout << vector[i] << " , ";
		} else {
			std::cout << vector[i];
		}
	}

	std::cout << "\n";
}

template <class T>
void printMatrix(const std::vector< std::vector<T> >& matrix) {

	for(unsigned i = 0; i < matrix.size(); i++) {
		std::cout << "Vector[" << i << "] = ";
		printVector<T>(matrix[i]);
	}
}


void printMatrixDouble(const std::vector<std::vector<double> >& matrix) {

	for(unsigned i = 0; i < matrix.size(); i++) {
		printVectorDouble(matrix[i]);
	}
}
bool Vigenere::readFile(const std::string& filePath,
						std::vector<std::string>& vector) {
	bool success = false;


		std::fstream file;
		file.open(filePath, std::ios::in);

		// read the file
		if (file.is_open()) {
			//printf("Opening file...\n");
			vector.clear();

			std::string line;
			while( getline(file, line) ) {
				line+= "\n";
				vector.push_back(line);
			}

			file.close(); // file closed
			//printf("file closed!\n");
			//printVector<std::string>(vector);

			// transform to lowercase 
			std::vector<std::string>  aux_lines;

			for(unsigned i = 0; i < vector.size(); i++) {
				std::string line = vector[i];
				std::string new_line="";

				for(unsigned j = 0; j < line.size(); j++){
					char letter = line[j];
		
					 if (letter >= 97 && letter <= 122) {
						new_line+= letter;
					} else if (letter >= 65 && letter <= 90) {
						new_line+= (char)(letter+32);
					} else {
						// characters that aren't letters 
						new_line+= letter;
					}
					
				}

				aux_lines.push_back(new_line);
			}

			vector.assign(aux_lines.begin(), aux_lines.end());
			aux_lines.clear();

			success = true;
		}	


	return success;
}

bool Vigenere::writeFile(const std::string& filePath,  
						std::vector<std::string>& vector) {


	bool success = false; 

	std::fstream file;
	file.open(filePath, std::ios::out);

	if (file.is_open()) {
		//printf("Writing file...\n");

		for(unsigned i = 0; i < vector.size(); i++) {
			std::string line = vector[i];

			file << line;

			/*
			if (line[line.size()-1] != "\n") {
				file << "\n";
			}
			*/
		}



		file.close();
		success = true;
	}

	return success;
}


Vigenere::Vigenere(const std::string& plainText,
				   const std::string& hiddenText,
				   const std::string& key="",
				   const std::string& language ="english") {

	this->key = key;
	this->plainText = plainText;
	this->hiddenText = hiddenText;


	if (language == "english") {
		alphabet['a'] = 8.167;
		alphabet['b'] = 1.492;
		alphabet['c'] =	2.782;
		alphabet['d'] =	4.253;
		alphabet['e'] =	12.702;
		alphabet['f'] =	2.228;
		alphabet['g'] =	2.015;
		alphabet['h'] =	6.094;
		alphabet['i'] =	6.966;
		alphabet['j'] =	0.153;
		alphabet['k'] =	0.772;
		alphabet['l'] =	4.025;
		alphabet['m'] =	2.406;
		alphabet['n'] =	6.749;
		alphabet['o'] =	7.507;
		alphabet['p'] =	1.929;
		alphabet['q'] =	0.095;
		alphabet['r'] =	5.987;
		alphabet['s'] =	6.327;
		alphabet['t'] =	9.056;
		alphabet['u'] =	2.758;
		alphabet['v'] =	0.978;
		alphabet['w'] =	2.360;
		alphabet['x'] =	0.150;
		alphabet['y'] =	1.974;
		alphabet['z'] =	0.074;
	} else if (language == "portuguese") {

		alphabet['a'] = 14.63;
		alphabet['b'] = 1.04;
		alphabet['c'] =	3.88;
		alphabet['d'] =	4.99;
		alphabet['e'] =	12.57;
		alphabet['f'] =	1.02;
		alphabet['g'] =	1.30;
		alphabet['h'] =	1.28;
		alphabet['i'] =	6.18;
		alphabet['j'] =	0.40;
		alphabet['k'] =	0.02;
		alphabet['l'] =	2.78;
		alphabet['m'] =	4.74;
		alphabet['n'] =	5.05;
		alphabet['o'] =	10.73;
		alphabet['p'] =	2.52;
		alphabet['q'] =	1.20;
		alphabet['r'] =	6.53;
		alphabet['s'] =	7.81;
		alphabet['t'] =	4.34;
		alphabet['u'] =	4.63;
		alphabet['v'] =	1.67;
		alphabet['w'] =	0.01;
		alphabet['x'] =	0.21;
		alphabet['y'] =	0.01;
		alphabet['z'] =	0.47;
	} else {
		printf("Error! language invalid!\n");
	}

}

void Vigenere::Encrypt() {

	if (key == "") {
		printf("Error! Please inform the key!\n");
	} else {
		std::vector<std::string> lines;
		printf("Encrypting...\n");


		if (readFile(plainText, lines)) {
			
			std::vector<std::string>  aux_lines;

			//printVector(lines);
			// Encrypting -----------------------------------
			unsigned k = 0;
			for(unsigned i = 0; i < lines.size(); i++) {
				std::string line = lines[i];
				std::string new_line = "";
				for(unsigned j = 0; j < line.size(); j++) {
					char letter = line[j];
					char new_letter = letter;

					if (letter >= 97 && letter <= 122) {
						//printf("d d d\n", letter, new_letter, key[k]);
						//printf("c c c\n", letter, new_letter, key[k]);
						// ASCII code for 'a' is 97
						new_letter = ((letter-'a')+(key[k]-'a'))%26 + 'a';

						k = (k+1)%key.size();

						//printf("d d d\n", letter, new_letter ,key[k]);
						//printf("c c c\n", letter, new_letter, key[k]);
					}


					new_line+= new_letter;

				}
				aux_lines.push_back(new_line);

			}

			lines.assign(aux_lines.begin(), aux_lines.end());
			aux_lines.clear();

			//printVector(lines);

			if (writeFile(hiddenText, lines)) {
				printf("Encryptation complete!\n");


			} else {
				printf("Error to save to hiddenText\n");
			}


		} else {
			printf("Error! Invalid plain text informed!\n");
		}
	}

}

void Vigenere::Decrypt() {

	if (key == "") {
		printf("Error! Please inform the key!\n");
	} else {
		printf("Decrypting...\n");

		std::vector<std::string> lines;

		if (readFile(hiddenText, lines)) {
			//printVector(lines);
			std::vector<std::string> aux_lines;

			aux_lines.clear();

			// Decrypting -----------------------------------
			unsigned k = 0;
			for(unsigned i = 0; i < lines.size(); i++) {
				std::string line = lines[i];
				std::string new_line = "";
				for(unsigned j = 0; j < line.size(); j++) {
					char letter = line[j];
					char new_letter = letter;

					if (letter >= 97 && letter <= 122) {
						//printf("d d d\n", letter, new_letter, key[k]);
						//printf("c c c\n", letter, new_letter, key[k]);
						// ASCII code for 'a' is 97
						new_letter = ((letter-'a')-(key[k]-'a'))%26;
						if (new_letter < 0) {
							new_letter+= 26;
						}
						new_letter+=  'a';

						k = (k+1)%key.size();

						//printf("d d d\n", letter, new_letter ,key[k]);
						//printf("c c c\n", letter, new_letter, key[k]);
					}


					new_line+= new_letter;

				}
				aux_lines.push_back(new_line);

			}

			lines.assign(aux_lines.begin(), aux_lines.end());
			aux_lines.clear();

			//printVector(lines);

			if (writeFile(plainText, lines)) {
				printf("Decrypting complete!\n");


			} else {
				printf("Error to save to hiddenText\n");
			}


		} else {
			printf("Error! Invalid hidden text informed!\n");
		}
	}
}


std::string Vigenere::GetKey() {
	return key;
}

void Vigenere::SetKey(const std::string& new_key) {
	this->key = new_key;
}

std::string Vigenere::FindKey(unsigned length = 0) {
	std::string key = "";
	unsigned key_length;

	std::vector<std::string> lines;

	bool success = readFile(hiddenText, lines);
	if (success) {

		//printVector<std::string>(lines);
		//key = BreakCaesarCipher(lines);

		// transform the lines into a vector of chars
		std::vector<char> letters;

		for(unsigned i = 0; i < lines.size(); i++) {
			std::string line = lines[i];
			for(unsigned j = 0; j < line.size(); j++) {
				char letter = line[j];
				if (letter >= 97 && letter <= 122) {
					letters.push_back(letter);
				}
			}
		}		

		//std::cout << "letters size: "<< letters.size() << " ";
		//std::cout << " letters : " ; printVector<char>(letters);

		
		if (length  == 0) {
			key_length = FindKeyLength(letters);
		} else if (length != 0){
			key_length = length;
		}
		

		//key_length = FindKeyLength(letters);

		// create matrix(vector of vectors of strings)
		std::vector< std::vector<char> > matrix;
		for(unsigned i = 0; i < key_length; i++) {
			std::vector<char> new_vector;
			matrix.push_back(new_vector);
		}

		
		// fill the matrix
		for(unsigned i = 0; i < key_length; i++) {
	
			for(unsigned j = i; j < letters.size(); j+=key_length) {
				char letter = letters[j];
				matrix[i].push_back(letter);
			}
		}
		
		//printMatrix<char>(matrix);
		//printVector<char>(matrix[0]);

		// Find the key of each vector(line of the matrix)
		// using the BreakCaesarCipher method
		key = "";
		for(unsigned i = 0; i < key_length; i++) {
			key+= BreakCaesarCipher(matrix[i]);
		}
		
		//std::cout << "Key: " << key << std::endl;

	} else {
		printf("Error to open hidden text!\n");
	}
	

	this->vigenere_key = key;
	return key;
}


unsigned Vigenere::FindKeyLength(const std::vector<char>& letters) {
	unsigned length = 1;

	//std::cout << "letters: "; printVector<char>(letters);

	unsigned maximum_length = 30;
	std::vector<unsigned> factors;
	for(unsigned i = 0; i < maximum_length; i++) {
		factors.push_back(0);
	}

	for(unsigned i = 0; i < letters.size()-2 ; i++) {
		std::string first_trigram = "";
		first_trigram += letters[i];
		first_trigram += letters[i+1];
		first_trigram += letters[i+2];
		//std::cout << first_trigram << " , ";
		for(unsigned j = i+3; j < letters.size()-2; j++) {
			std::string next_trigram = "";
			next_trigram += "";
			next_trigram += letters[j];
			next_trigram += letters[j+1];
			next_trigram += letters[j+2];

			if (next_trigram == first_trigram) {
				unsigned distance;
				distance = j - i;

				addFactors(factors, distance);
			}
		}
	}


	unsigned max_value = 0;
	for(unsigned i = 0; i < factors.size(); i++) {
		//std::cout << "factor[i]: " << factors[i] << std::endl;
		if (factors[i] > max_value) {
			max_value = factors[i];
			length = i+2;
			//std::cout << max_value << " , " << length << std::endl;
		}
	}

	//std::cout << "key length: " << length << std::endl;

	//std::cout << "factors: "; printVector<unsigned>(factors," , ");
	this->factors = factors;

	return length;
}


char Vigenere::BreakCaesarCipher(std::vector<char>& vector) {
	char key;


	//std::cout << "vector size is " << vector.size() << std::endl;
	unsigned alphabet_size = alphabet.size();


	std::vector<double> statistic_vector;

	for(unsigned i = 0; i < alphabet_size; i++) {
		double value;

		value = (alphabet[i+'a'] )/100.0;

		statistic_vector.push_back(value);
	}

	//std::cout <<"Statistic vector: "; printVectorDouble(statistic_vector);

	std::vector< std::vector<double> > matrix;
	for(unsigned i = 0; i < alphabet_size; i++) {
		std::vector<double> new_vector;

		for(unsigned j = 0; j <alphabet_size; j++) {
			new_vector.push_back(0.0);
		}
		matrix.push_back(new_vector);
	}


	for(unsigned i = 0; i < alphabet_size; i++) {
		for(unsigned j = 0; j < alphabet_size; j++) {
			double value;
			unsigned k;
			k = (26-i + j)%26;
			value = statistic_vector[k];
			matrix[i][j] = value;
		}
	}

	//std::cout << "Matrix: "; printMatrixDouble(matrix);
	std::vector<char> letters = 
	{'a','b','c','d','e','f','g','h','i','j','k',
								'l','m','n','o','p','q','r','s','t','u','v',
								'w','x','y','z'};

	std::vector<double> values_vector;

	for(unsigned i = 0; i < letters.size(); i++) {

		char letter;
		double percentage = 0.0;
		double total = 0;

		letter = letters[i];

		total = std::count(vector.begin(), vector.end(), letter);
		percentage = total/vector.size();
		//printf("%c, %.3lf\n",letter, percentage);

		values_vector.push_back(percentage);
		
	}

	//std::cout << "values vector: "; printVectorDouble(values_vector);

	double max_value = 0;
	unsigned index = 0;
	for(unsigned i = 0; i < matrix.size(); i++) {
		double product;

		product = GetProduct(matrix[i], values_vector);

		if (product > max_value) {
			max_value = product;
			index = i;
		}
	}

	key = (index) +'a';
	//printf("key_int: %d, key_char: %c, index: %d\n", key, key, index);


	/*
	std::vector<double> v1 = {1, 2, 3};
	std::vector<double> v2 = {5, 3, 10};
	std::cout << "Product: "<< GetProduct(v1, v2) << std::endl;
	*/

	return key;
}

std::vector<unsigned> Vigenere::GetFactors() {
	return factors;
}