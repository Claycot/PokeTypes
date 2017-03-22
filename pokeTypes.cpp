// pokemonTypes.cpp : Defines the entry point for the console application.
// Code by Claycot

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
int matchType(string inputType, string libTypes[19]);
string argvToStr(char *argv[], unsigned int argNum);
float damageMult(int atkDefTypes[], int effec[18][18]);

int main(int argc, char *argv[])
{
	string types[19] = {"normal", "fire", "water", "electric", "grass", "ice", 
		"fighting", "poison", "ground", "flying", "psychic", "bug", "rock", 
		"ghost", "dragon", "dark", "steel", "fairy"};
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
	int inputTypes[3] = { -1, -1 , -1 };

	if (argc < 3 || argc > 4) {
		if (argc == 1) {
			cout << "Please run this program from the command line.\n"
				<< "Run the program with the following command for help.\n"
				<< "\"help\"";
			cin.ignore();
		}
		else if (argvToStr(argv, 1) == "help") {
			cout << "Please follow one of the formats below...\n"
				<< "<attacking type> <defending type>\n"
				<< "<attacking type> <defending type 1> <defending type 2>\n"
				<< "(Run with command \"types\" for a list of types)\n";
		}
		else if (argvToStr(argv, 1) == "types") {
			for (int i = 0; i < 17; i++) {
				cout << types[i] << ", ";
			}
			cout << types[17] << endl;
		}
		else {
			cout << "Usage error. Run with command \"help\" for guidance." << endl;
		}
	}

	if (argc >= 3 || argc <= 4) {
		switch (argc) {
		case 3:
			for (int argNum = 1; argNum <= 2; argNum++) {
				inputTypes[argNum - 1] = matchType(argvToStr(argv, argNum), types);
				if (inputTypes[argNum - 1] == -1) {
					return -1;
				}
			}
			inputTypes[2] = -1;
			cout << "Attacker: " << types[inputTypes[0]] << "\n"
				<< "Defender: " << types[inputTypes[1]] << "\n"
				<< "Multiplier: "
				<< damageMult(inputTypes, effectivity)
				<< "x\n";
				break;
		case 4:
			for (int argNum = 1; argNum <= 3; argNum++) {
				inputTypes[argNum - 1] = matchType(argvToStr(argv, argNum), types);
				if (inputTypes[argNum - 1] == -1) {
					return -1;
				}
			}
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

int matchType(string inputType, string libTypes[19]) {
	for (int ind = 0; ind < 19; ind++) {
		if (inputType == libTypes[ind]) {
			return ind;
		}
	}

	cout << "Error: type " << inputType << " not found.\n"
		<< "Run the program with argument \"types\" to view.\n";
	return -1;
}

string argvToStr(char *argv[], unsigned int argNum) {
	string outputStr = argv[argNum];

	for (unsigned int let = 0; let <= outputStr.length(); let++) {
		outputStr[let] = tolower(outputStr[let]);
	}

	return outputStr;
}

float damageMult(int atkDefTypes[], int effec[18][18]) {
	float mult1 = 2;
	float mult2 = 2;
	cout << setprecision(2);

	mult1 = effec[atkDefTypes[0]][atkDefTypes[1]];
	//cout << "Mult 1 = " << mult1 << endl;
	if (atkDefTypes[2] == -1) {
		return mult1 / 2;
	}
	else {
		mult2 = effec[atkDefTypes[0]][atkDefTypes[2]];
		//cout << "Mult 2 = " << mult2 << endl;
		return mult1 * mult2 / 4;
	}
}
