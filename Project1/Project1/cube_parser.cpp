/*
#include <windows.h> // use proper includes for your system
#include <iostream>
#include <vector>
#include <string>
#ifndef _parser // must be unique name in the project
#define _parser
std::vector<std::string> rubix_parser(std::string inputs)
{	// declare num for use later
	int num;
	// declare rotations to contain additions later
	std::vector<std::string> rotations;
	// declare current as a temporary string variable
	std::string current;
	//for loop. start at zero count up by threes to jump "c# " characters
	for (size_t current_index = 0; current_index<inputs.size(); current_index = current_index + 3) {
		//covert the char value from the string to an integer by subtracting ASCI 0
		num = inputs[current_index + 1] - '0';
		//take a 1 character substring of the current char so that we maintain string type
		current = inputs.substr(current_index, 1);
		//algorithm specifies number of rotations
		// for each rotation add it to the end of the vector
		for (int y = 0; y<num; y++)
			rotations.push_back(current);
	}
	return rotations;
}
#endif
/*
int main(int argc, char** argv)
{
std::string example;
example="a2 b3 c4 d5 e6";
std::cout<<example << "\n";
std::vector<std::string> temp;
temp=rubix_parser(example);
for(std::vector<std::string>::size_type i = 0; i != temp.size(); i++) {
std::cout << temp[i]<<"\n";
}
return 0;
}
*/