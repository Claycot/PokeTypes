//Code by claycot

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

//Prototype functions
int matchType(string inputType, string libTypes[18]);
string argvToStr(char *argv[], unsigned int argNum);
string strToLwr(string inputString);
float damageMult(int atkDefTypes[], int effec[18][18]);
void showHelp();
void showTypes(string types[18]);

int main(int argc, char *argv[])
{
	//Define all of the pokemon types
	string types[18] = {"normal", "fire", "water", "electric", "grass", "ice", 
		"fighting", "poison", "ground", "flying", "psychic", "bug", "rock", 
		"ghost", "dragon", "dark", "steel", "fairy"};
	
	//Grid of effectiveness. Actual effectiveness is half of these values
	//Order for columns is same as order for rows
	int effectivity[18][18] = {
		/*norm*/ {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 2, 2, 1, 2},
		/*fire*/ {2, 1, 1, 2, 4, 4, 2, 2, 2, 2, 2, 4, 1, 2, 1, 2, 4, 2},
		/*watr*/ {2, 4, 1, 2, 1, 2, 2, 2, 4, 2, 2, 2, 4, 2, 1, 2, 2, 2},
		/*elec*/ {2, 2, 4, 1, 1, 2, 2, 2, 0, 4, 2, 2, 2, 2, 1, 2, 2, 2},
		/*gras*/ {2, 1, 4, 2, 1, 2, 2, 1, 4, 1, 2, 1, 4, 2, 1, 2, 1, 2},
		/*ice */ {2, 1, 1, 2, 4, 1, 2, 2, 4, 4, 2, 2, 2, 2, 4, 2, 1, 2},
		/*fght*/ {4, 2, 2, 2, 2, 4, 2, 1, 2, 1, 1, 1, 4, 0, 2, 4, 4, 1},
		/*psn */ {2, 2, 2, 2, 4, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 0, 4},
		/*grnd*/ {2, 4, 2, 4, 1, 2, 2, 4, 2, 0, 2, 1, 4, 2, 2, 2, 4, 2},
		/*fly */ {2, 2, 2, 1, 4, 2, 4, 2, 2, 2, 2, 4, 1, 2, 2, 2, 1, 2},
		/*psy */ {2, 2, 2, 2, 2, 2, 4, 4, 2, 2, 1, 2, 2, 2, 2, 0, 1, 2},
		/*bug */ {2, 1, 2, 2, 4, 2, 1, 1, 2, 1, 4, 2, 2, 1, 2, 4, 1, 1},
		/*rock*/ {2, 4, 2, 2, 2, 4, 1, 2, 1, 4, 2, 4, 2, 2, 2, 2, 1, 2},
		/*ghst*/ {0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 1, 2, 2},
		/*drag*/ {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 1, 0},
		/*dark*/ {2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 4, 2, 2, 4, 2, 1, 2, 1},
		/*stel*/ {2, 1, 1, 1, 2, 4, 2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 1, 4},
		/*fair*/ {2, 1, 2, 2, 2, 2, 4, 1, 2, 2, 2, 2, 2, 2, 4, 4, 1, 2}
	};

	//Initialize the type matches as -1 (error/not found)
	int inputTypes[3] = { -1, -1 , -1 };

	//Check arguments, use this if not wanting direct input
	if (argc < 3 || argc > 4) {

		//If started without arguments, enter into CLI version
		if (argc == 1) {

			//Welcome message and show help
			cout << "Welcome to the Pokemon effectiveness calculator!\n";
			showHelp();
			cout << "Enter the letter Q at any time to quit.\n";

			//Initialize user inputs
			string userInput = "";
			string buffer[3] = { "", "", "" };

			//Get user input until user wants to quit
			do {
				
				//Prompt user and receive input
				userInput = "";
				cout << "\nEnter the Pokemon types: ";
				getline(cin, userInput);

				//If user requests types, display them
				if (userInput.substr(0, 5) == "types" || userInput.substr(0, 5) == "TYPES") {
					showTypes(types);
				}

				//Process user input
				else {
					stringstream input(userInput);

					//For the first three arguments in the string stream,
					//Process and match the types
					for (int i = 0; i < 3; i++) {
						buffer[i] = "";
						input >> buffer[i];

						//Convert the input type to lower for matching
						buffer[i] = strToLwr(buffer[i]);

						if (buffer[i] != "") {
							inputTypes[i] = matchType(buffer[i], types);
						}
						else {
							inputTypes[i] = -1;
						}
					}

					//Output effectiveness if not an error
					if (inputTypes[0] != -1 && inputTypes[1] != -1) {
						cout << "Attacker: " << types[inputTypes[0]] << "\n"
							<< "Defender: " << types[inputTypes[1]];

						//If a third type was entered, output that too
						if (inputTypes[2] != -1) {
							cout << " & " << types[inputTypes[2]];
						}
						cout << "\n"
							<< "Multiplier: "
							<< damageMult(inputTypes, effectivity)
							<< "x\n";
					}
				}
			} while (buffer[0] != "q" && buffer[0] != "Q");
		}

		//Process user help request
		else if (argvToStr(argv, 1) == "help") {
			showHelp();
		}

		//Process user types request
		else if (argvToStr(argv, 1) == "types") {
			showTypes(types);
		}

		//Catch-all for bad inputs
		else {
			cout << "Usage error. Run with command \"help\" for guidance." << endl;
		}
	}

	//Process direct input
	if (argc >= 3 || argc <= 4) {
		
		//Switch for number of arguments
		switch (argc) {
		
		//If 3 arguments, process the 1-attack, 1-defense calculation
		case 3:
			
			//Match each argument to a type
			for (int argNum = 1; argNum <= 2; argNum++) {
				inputTypes[argNum - 1] = matchType(argvToStr(argv, argNum), types);
				if (inputTypes[argNum - 1] == -1) {
					return -1;
				}
			}
			inputTypes[2] = -1;

			//Output the result
			cout << "Attacker: " << types[inputTypes[0]] << "\n"
				<< "Defender: " << types[inputTypes[1]] << "\n"
				<< "Multiplier: "
				<< damageMult(inputTypes, effectivity)
				<< "x\n";
				break;

		//If 4 arguments, process the 1-attack, 2-defense calculation
		case 4:

			//Match each argument to a type
			for (int argNum = 1; argNum <= 3; argNum++) {
				inputTypes[argNum - 1] = matchType(argvToStr(argv, argNum), types);
				if (inputTypes[argNum - 1] == -1) {
					return -1;
				}
			}

			//Output the result
			cout << "Attacker: " << types[inputTypes[0]] << "\n"
				<< "Defender: " << types[inputTypes[1]] << " & " 
				<< types[inputTypes[2]] << "\n"
				<< "Multiplier: "
				<< damageMult(inputTypes, effectivity)
				<< "x\n";
			break;
		}
	}
    return 0;
}


//Match the user input to a valid pokemon type
int matchType(string inputType, string libTypes[18]) {
	
	//Loop through all types searching for a match
	for (int ind = 0; ind < 18; ind++) {
		if (inputType == libTypes[ind]) {
			return ind;
		}
	}

	//Output error message if not found
	cout << "Error: type " << inputType << " not found.\n"
		<< "Run the program with argument \"types\" to view.\n";
	return -1;
}

//Convert an argument to a lowercase string
string argvToStr(char *argv[], unsigned int argNum) {
	string outputStr = argv[argNum];

	//For each character in the argument, add to string
	for (unsigned int let = 0; let <= outputStr.length(); let++) {
		outputStr[let] = tolower(outputStr[let]);
	}

	return outputStr;
}

//Convert a string to a lowercase string
string strToLwr(string inputString) {
	string outputStr = inputString;

	//For each character in the argument, add to string
	for (unsigned int let = 0; let <= inputString.length(); let++) {
		inputString[let] = tolower(inputString[let]);
	}

	return inputString;
}

//Calculate the damage multiplier
float damageMult(int atkDefTypes[], int effec[18][18]) {
	
	//Initialize the two multipliers
	float mult1 = 2;
	float mult2 = 2;
	cout << setprecision(2);

	//Calculate the first multiplier
	mult1 = effec[atkDefTypes[0]][atkDefTypes[1]];

	//If no second defending type, return the primary result
	if (atkDefTypes[2] == -1 || atkDefTypes[1] == atkDefTypes[2]) {
		return mult1 / 2;
	}

	//If a second defending type, calculate for that scenario
	else {
		mult2 = effec[atkDefTypes[0]][atkDefTypes[2]];

		//Return the result
		return mult1 * mult2 / 4;
	}
}

//Draw the help menu
void showHelp() {
	cout << "Please follow one of the formats below...\n"
		<< "<attacking type> <defending type>\n"
		<< "<attacking type> <defending type 1> <defending type 2>\n"
		<< "(Run with command \"types\" for a list of types)\n";
}

//Draw each of the pokemon types
void showTypes(string types[18]) {
	for (int i = 0; i < 17; i++) {
		cout << types[i] << ", ";
	}
	cout << types[17] << endl;
}
