#include <iostream>
#include <string>
#include <cctype>

void help() {
	std::cout << "Usage: ./vigenere [OPTION] <text> <key>\n"
		<< "Options:\n"
		<< "	-e, --encrypt	Encrypt the provided text with the key.\n"
		<< "	-d, --decrypt	Decrypt the provided text with the key.\n"
		<< "	-h, --help	Display this help message.\n";
}

std::string encrypt(const std::string& text, const std::string& key){
	std::string cipher;
	int keyIndex = 0;

	for (char c:text){
		if(std::isalpha(c)){
			bool isLower = std::islower(c);
			char base = isLower ? 'a':'A';

			char encryptedChar = (c - base + (std::tolower(key[keyIndex % key.length()]) - 'a')) % 26 + base;
			cipher += encryptedChar;

			keyIndex++;
		}else{
			cipher += c;
		}
	}
	return cipher;
}

std::string decrypt(const std::string& text, const std::string& key){
	std::string plainText;
	int keyIndex = 0;

	for(char c:text){
		if(std::isalpha(c)){
			bool isLower = std::islower(c);
			char base = isLower ? 'a' : 'A';

			char decryptedChar = (c - base - (std::tolower(key[keyIndex % key.length()]) - 'a') + 26) % 26 + base;
			plainText += decryptedChar;

			keyIndex++;
		}else{
			plainText += c;
		}
	}
	return plainText;
}

int main(int argc, char* argv[])
{
	if(argc < 2){
		std::cerr << "Usage: ./encrypt [OPTION] <text> <key>\n"
			<< "Error: No arguments provided. Use -h or --help for help\n";
		return 1;
	}
	std::string flag = argv[1];
	if (flag == "--help" || flag == "-h"){
		help();
		return 0;
	}
	if(argc != 4){
		std::cerr << "Usage: ./encrypt [OPTION] <text> <key>\n"
			<< "Error: Incorrect number of arguments. Use -h or --help for help\n";
		return 1;

	}
	std::string text = argv[2];
	std::string key = argv[3];
	for (char c : key){
		if(!std::isalpha(c)){
			std::cerr << "Error: Key must contain only alphabetic characters.\n";
			return 1;
		}
	}
	if (flag == "-e" || flag == "--encrypt"){
		std::cout << "Encrypted text: " << encrypt(text, key) << '\n';
	}else if(flag == "-d" || flag == "--decrypt"){
		std::cout << "Decrypted text: " << decrypt(text, key) << '\n';
	}	
	return 0;
}
