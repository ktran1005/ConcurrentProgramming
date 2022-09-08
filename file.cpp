#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
				fstream myFile;
				/*myFile.open("hello.txt", ios::out);  // write mode
				if (myFile.is_open()) {
								myFile << "Hello\n";
								myFile << "This is second line\n";
								myFile.close();
				}*/

				myFile.open("hello.txt", ios::in); // read
				if (myFile.is_open()) {
								string line;
								while(getline(myFile,line)) {
												cout << line << endl;
								}
								myFile.close();
				}
				return 0;

}

