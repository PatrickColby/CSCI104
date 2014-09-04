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
            int num_buckets;  //The first line of the text file that will be used to determine how many buckets there will be.
            int num_commands; //The second line in the text file will be used to determine how many commands there will be in the sequence.
            getline(ifile, line);
            stringstream ss;

            ss << line;
            ss >> num_buckets;
            ss >> num_commands;

            int **buckets = new int *[num_buckets]; //2D array for buckets
            int *bucket_sizes = new int[num_buckets];	//To store the size of each bucket.

            for (int i = 0; i < num_buckets; i++) {	//To initialize all of the buckets.
            	delete buckets[i];
            	buckets[i] = nullptr;
            }

            for(int i = 0; i < num_commands; i++) { //To iterate through each line individually.
            	getline(ifile, line); //We'll begin reading from the 2nd line of the text file.
            	string command; //Will be used to determine which command is on each line.
            	int target_bucket;	//The bucket we're curently working on.
            	int num_items;	//How many tihngs we will put PUTting in the bucket.

            	stringstream ssin(line);

            	if(ssin.good()) {
            		ssin >> command;
            	}

            	if(ssin.good()) {
            		ssin >> target_bucket;
            	}

            	if(ssin.good() && command == "PUT") {	//If we have info to read AND our command is PUT.

            		if(buckets[target_bucket - 1] == nullptr) { //check to see if bucket is full. If nullptr --> bucket is empty.
            			ssin >> num_items;
            			bucket_sizes[target_bucket - 1] = num_items;	//The number of buckets (e.g., 3) would be 1, 2, 3 (and not 0, 1, 2)
	            		buckets[target_bucket - 1] = new int[num_items]; //instantiate an array in this bucket's spot in the array of size num_items.

	            		for(int j = 0; j < num_items; j++) { //read in values here, put them into the bucket
	            			ssin >> buckets[target_bucket - 1][j];	//Store the number within the target bucket's array.
	            		}
	            	}
	            	else {
	            		cout << "Error - bucket " << target_bucket <<  " is not empty" << endl;
	            	}
            	}
            	else if(command == "OUTPUT") {
            		if(target_bucket > 0 && target_bucket <= num_buckets) {
            			if(buckets[target_bucket - 1] == nullptr) {	//Target bucket is empty.
            				cout << "empty" << endl;
            			}
            			else {	//Target bucket is not empty.
            				for(int j = 0; j < bucket_sizes[target_bucket - 1]; j++) {	//Going through each element in the target bucket.
            					cout << buckets[target_bucket - 1][j] << " ";
            				}
            				cout << endl;
            			}
            		}
            		else { //Target bucket doesn't exist.
            			cout << "Error - bucket " << target_bucket << " does not exist" << endl;
            		}
            	}

            	else if(command == "EMPTY") {
            		if(buckets[target_bucket - 1] != nullptr) { //Target bucket isn't empty.
            			delete buckets[target_bucket - 1];
            			buckets[target_bucket - 1] = nullptr;
            		}
            	}
            }
        }
    }
}