#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

/*
	Simple utility for reading bytes from files straight into a source
	file in C++.
*/

int main(int argc, char* argv[])
{
	if (argc >= 4) {
		char* arg1 = argv[1];

		//read bytes
		std::ifstream inStream(arg1, std::ios::binary);

        std::vector<char> bytes;
        {
            std::ostringstream ss;
            ss << inStream.rdbuf();

            std::string s = ss.str();
            bytes = std::vector<char>(s.begin(), s.end());

        }
        
		inStream.close();

		//write to file

		std::string variableName;
		
		if (argc == 3) {
			std::cout << "Enter a name for the variable: ";
			std::cin >> variableName;
		}
		else {
			variableName = argv[3];
		}

        std::string headerPath = std::string(argv[2]) + ".hpp";

		std::ofstream outHeaderStream(headerPath);

		outHeaderStream << "#pragma once" << std::endl;
		outHeaderStream << "extern unsigned char " << variableName << " [" << bytes.size() << "];" << std::endl;
		outHeaderStream << "const unsigned int " << variableName << "Length = " << bytes.size() << ";"<< std::endl;;
		outHeaderStream.close();

		std::ofstream outSourceStream(std::string(argv[2]) + ".cpp");

        std::string headerName = headerPath.substr(headerPath.find_last_of('/') + 1);

		outSourceStream << "#include \"" << headerName << "\"" << std::endl;

		outSourceStream << "unsigned char " << variableName << "[" << "] = {";
    
        size_t count = bytes.size();
        for (char b : bytes) {
			outSourceStream << "0x" << std::hex << (((unsigned int)b) & 0xFF);
            count--;
            if(count > 0) {
                outSourceStream << ",";
            } 
        }

		outSourceStream << "};" << std::endl;
		
		std::cout << "Resource packed!" << std::endl;

	}
	else {
		std::cout << "please enter input file name, an output filename and a variable name" << std::endl;
		return 1;
	}

	return 0;
}