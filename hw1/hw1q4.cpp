#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>


using namespace std;

int main(int argc, const char * argv[]) {
    if (argc != 2) {  //To make sure that we can properly run the program.
        cout << "usage: " << argv[0] << " <filename>\n";
    }
    else {
        ifstream ifile (argv[1]); //ifile is our object that we will be using to open the file. argv[0] is where the file name should be located.
        if(!ifile.is_open()) {  //the file will not open
            cout << "The file could not be opened. Please review the text file and try again." << endl;
            return 0;   //The program terminates.
        } 
        else {  //The file successfully opened
            string line;
            int num_lines;  //The first line of the text file that will be used to determine how many lines there are.
            getline(ifile, line);
            stringstream ss;

            ss << line;
            // ss << line.trim();   //Do we need to take trailing whitespace into consideration??
            ss >> num_lines;

            int num_words[num_lines]; //To dynamically allocate memory for the # of words per line.

            for (int i = 0; i < num_lines; i++) {   //To iterate through each line individually.
                getline(ifile, line); //We are starting at the 2nd line of the file and reading from there.
                string temp;
                int line_num_words = 0; //The # of words in each line.
                stringstream ssin(line);
                while(ssin.good()) {   //While there are still words in the line to read.
                    ssin >> temp;
                    //cout << temp << endl;
                    if(temp != "") {  //Compares temp and "" to see whether or not they are equal.
                        line_num_words++;
                    }
                    temp = "";  //Used to determine whether or not temp has been reset.
                }
                num_words[i] = line_num_words;  //Adding the number of words on the line to the array, how many words each respective line contains.
            }

            for(int i = num_lines - 1; i >= 0; i--) {
                cout << num_words[i] << endl;
            }
        }
    }
}