#include <iostream>
#include <unordered_map>
#include <string>

#include "Funcoes.h"


int menu() {
	int option = -1;

	while (option < 1 || option > 4 ) {
		std::cout << "============ Menu ============ " << std::endl;
		std::cout << "Choose one of the options bellow:\n";
		std::cout << "1 - Encrypt\n";
		std::cout << "2 - Decrypt\n";
		std::cout << "3 - Break Vigenere\n";
		std::cout << "4 - Exit\n";

		std::cout << "Option: ";
		scanf("%d", &option);

		if (option < 1 || option > 4 ) {
			printf("Error! Invalid option.\n");
		}
	}
	return option;
}

void Run(Vigenere* vigenere) {
	bool exit = false;

	while(!exit) {
			int option;
			option = menu();
			std::string key;

			if (option == 1) {
					std::cout << "Type the key: ";
					std::cin >> key;
					vigenere->SetKey(key);
					vigenere->Encrypt();
			} else if (option == 2) {
					std::cout << "Type the key: ";
					std::cin >> key;
					vigenere->SetKey(key);
					vigenere->Decrypt();
			} else if (option == 3) {
				bool success = false;
				key = vigenere->FindKey(0);

				while(!success) {
					vigenere->SetKey(key);
					vigenere->Decrypt();
					std::string answer;

					std::cout << "Key is : " << vigenere->vigenere_key << std::endl;
					std::cout << "Was decrypting successful?" << std::endl;
					std::cout << "Answer(y/n): ";
					std::cin >> answer;

					if (answer == "y") {
						success = true;

					} else {
						std::vector<unsigned> factors;
						unsigned key_length;

						factors = vigenere->GetFactors();

						std::cout << "Choose one of key sizes bellow:" << std::endl;

						for(unsigned i = 0; i < factors.size(); i++) {
							std::cout << i+2 << " : " << factors[i] << std::endl;
						}
						std::cout << std::endl;

						std::cout << "Enter the key size: ";
						std::cin >> key_length;

						key = vigenere->FindKey(key_length);

					}
				}
				std::cout << std::endl;

			} else if (option == 4) {
				exit = true;
			}

			std::cout << std::endl;
	}

}

void Load(int argc,char** argv,std::string& plainPath,
		  std::string& hiddenPath,  std::string& language) {

	if (argc >= 4) {
		plainPath = argv[1];
		hiddenPath = argv[2];
		language = argv[3];
	} else {
		printf("Error! Incorrect number of argumens!\n");
	}
}