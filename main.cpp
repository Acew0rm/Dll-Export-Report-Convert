#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
int main() {
	//dll redirection file name
	std::string redirection = "";
	//report begins with junk lines
	int reportjunk = 11;
	//counter for lines for reportjunk
	int linecounter = 0;
	//flag for finding call length
	int endflag = 0;
	//junk before call/function
	int junklinedata = 31;
	//length of call/function
	int calllength = 0;
	//line buffer for parse
	std::string currentparsedline = "";
	//line buffer
	std::string currentline = "";
	//file name 
	std::string filetoparse = "";
	//file name output
	std::string fileout = "";
	//list for file in memory
	std::vector<std::string> filelines;
	//reading file
	std::cout << "Enter filename of html to parse with extension-";
	std::cin >> filetoparse;
	std::cout << "Enter filename for txt output without extension-";
	std::cin >> fileout;
	std::cout << "Enter filename for the dll to redirect to without extension-";
	std::cin >> redirection;
	//file declarations
	std::ifstream myfile(filetoparse);
	std::ofstream myfile1(fileout+".txt");
	if (myfile.is_open()) {
		while (std::getline(myfile, currentline)){
			if (linecounter > reportjunk) {
				 filelines.push_back(currentline);
			}
			linecounter++;
		}
		myfile.close();
	}
	else {
		std::cout << "Failed to open";
	}
	//getting rid of last 3 junk lines
	for (int junk = 0; junk < 3; junk++) {
		filelines.pop_back();
	}
	//getting function names and replacing list with them
	for (int read = 0; read < filelines.size(); read++) {	
		currentparsedline=filelines[read];
		while (endflag == 0) {
			calllength++;
			if (currentparsedline[junklinedata+calllength]=='<') {
				endflag = 1;
			}	
		}
		filelines[read]=filelines[read].substr(junklinedata,calllength);
		calllength = 0;
		endflag = 0;
	}
	//output to file formatted
	if (myfile1.is_open()) {
		for (int read1 = 0; read1 < filelines.size(); read1++) {
			myfile1 << "#pragma comment(linker,\"/export:" << filelines[read1] << "=" << redirection << "." << filelines[read1] << ",@" << read1 + 1 << "\")" << "\n";
		}
		myfile1.close();
	}
	else {
		std::cout << "Failed to open";
	}
	std::cout << "Done\n";
	return 0;
}