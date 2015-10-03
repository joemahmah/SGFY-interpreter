/*
 * File:   Sfuck.cpp
 * Author: Michael Hrcek <hrcekmj@clarkson.edu>
 *
 * Created on September 14, 2015, 6:25 PM
 */

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <vector>
#include <string>

using namespace std;

struct store {
    vector< vector<int>  > intBank;
    int index, vindex;
    int sizeX, sizeY;
    int loopCounter;
    bool printAsChar;
    bool notFlaged;
    bool verbose;
    vector<string> storedLoop;

    store() : store(1024, 1024) {}

    store(int sizeX, int sizeY, bool verbose = false) {

	storedLoop.resize(10);
	intBank.resize(sizeY);

        for (int i = 0; i < sizeY; i++) {
	    vector<int> row;
		row.resize(sizeX);
            for (int j = 0; j < sizeX; j++) {
                row[j] = 0;
            }
	    intBank[i] = row;
        }
	this->sizeX = sizeX;
	this->sizeY = sizeY;
        index = 0;
        vindex = 0;
	loopCounter = 0;
        printAsChar = true;
	this->verbose = verbose;
    }

    void getCommand(istream & inputStream);
    void getCommand(char c, bool isLoop=false);
};

void store::getCommand(istream & inputStream) {

    char c = inputStream.get();
    getCommand(c);

}

void store::getCommand(char c, bool isLoop) {

if(loopCounter == 0 || isLoop){

    switch (c) {
        case '+':
            intBank[vindex][index]++;
            break;
        case '-':
            intBank[vindex][index]--;
            break;
        case '>':
            if (index == sizeX-1) {
                index = 0;
            } else {
                index++;
            }
            break;
        case '<':
            if (index == 0) {
                index = sizeX-1;
            } else {
                index--;
            }
            break;
        case '^':
            if (vindex == sizeY-1) {
                vindex = 0;
            } else {
                vindex++;
            }
            break;
        case '\\':
            if (vindex == 0) {
                vindex = sizeY-1;
            } else {
                vindex--;
            }
            break;
        case '#':
            index = vindex = 0;
            break;
        case ',':
            intBank[vindex][index] = (int) cin.get();
            break;
        case '.':
            if (printAsChar) {
                cout << (char) intBank[vindex][index];
            } else {
                cout << intBank[vindex][index];
            }
            break;
        case '=':
            if (intBank[vindex][index] == (int) 'x') {
                intBank[vindex][index] = 1;
            } else {
                intBank[vindex][index] = 0;
            }
            break;
        case '&':
            if (intBank[vindex][index] == (int) 'x') {
                intBank[vindex][index] = intBank[vindex][index]/2*'x'*'x'+'c';
            } else {
                intBank[vindex][index] = intBank[vindex][index]/2*'x'+'c';
            }
            break;
        case '?':
            intBank[vindex][index] = rand();
            break;
        case '@':
            printAsChar = !printAsChar;
            break;
        case '~':
            notFlaged = false;
            break;
        case '|':
            if (vindex < sizeY-1) {
                intBank[vindex][index] = intBank[vindex + 1][index];
            } else {
                intBank[vindex][index] = intBank[0][index];
            }
            break;
        case '}':
            if (index > 0) {
                intBank[vindex][index] = intBank[vindex][index - 1];
            } else {
                intBank[vindex][index] = intBank[vindex][sizeX-1];
            }
            break;
        case '[':
	    loopCounter++;
            break;
        case ']':
            while (intBank[vindex][index] != 0 && loopCounter > 0) {
                for (char c : storedLoop[loopCounter-1]) {
                    getCommand(c,true);
                }
            }
            storedLoop[loopCounter-1] = "";
	    loopCounter--;
            break;

    }
} else if (loopCounter > 0){

    if(verbose){
	cout << "Current Loop: " << loopCounter << endl;
    }

    if(c == '[' || c == ']'){
    	switch(c){
	    case '[':
	        loopCounter++;
       	        break;
            case ']':
                while (intBank[vindex][index] != 0 && loopCounter > 0) {
		    for (char c : storedLoop[loopCounter-1]) {
                        getCommand(c,true);
                    }
                }
                storedLoop[loopCounter-1] = "";
	        loopCounter--;
                break;
    	}
    } else{
	storedLoop[loopCounter-1] += c;
    }
} else{
    loopCounter = 0;
}
}

/*
 * 
 */
int main(int argc, char** argv) {

    int x = 1024, y = 1024;
    bool verbose = false;
    string fileLocation = "";

    for(int i=1; i<argc; i++){
	if(string(argv[i]) == "-h" || string(argv[i]) == "--help"){
	    //List params
	    return 0;
	}
	if(string(argv[i]) == "-S" && i + 2 < argc){
	    x = stoi(argv[i+1]);
	    y = stoi(argv[i+2]);
	    i+=2;
	}
	if(string(argv[i]) == "-V"){
	    verbose = true;
	}
	if(string(argv[i]) == "--file" && i + 1 < argc){
	    fileLocation = argv[i+1];
	    i+=1;
	}
    }


    srand(time(NULL));

    store s(x,y,verbose);

    if(verbose){
	cout << "X:" << s.sizeX << "\nY:" << s.sizeY << endl;
    }

    if(!verbose){
    cout <<
"             .        .--.                                                         \n"<<
"           .'|        |__|                                                         \n"<<
"          <  |        .--.     .|                                                  \n"<<
"           | |        |  |   .' |_                                                 \n"<<
"       _   | | .'''-. |  | .'     |                                                \n"<<
"     .' |  | |/.'''. \\|  |'--.  .-'                                                \n"<<
"    .   | /|  /    | ||  |   |  |                                                  \n"<<
"  .'.'| |//| |     | ||__|   |  |                                                  \n"<<
".'.'.-'  / | |     | |       |  '.'                                                \n"<<
".'   \\_.'  | '.    | '.      |   /                                                 \n"<<
"           '---'   '---'     `'-'                                                  \n"<<
"            .-'''-.                                                                \n"<<
"           '   _    \\                                                              \n"<<
"         /   /` '.   \\                                                             \n"<<
"  .--./).   |     \\  '                                                             \n"<<
" /.''\\ |   '      |  '  .|                                                        \n"<<
"| |  | |\\    \\     / / .' |_                                                       \n"<<
" \\`-' /  `.   ` ..' /.'     |                                                      \n"<<
" /(\"'`      '-...-'`'--.  .-'                                                      \n"<<
" \\ '---.               |  |                                                        \n"<<
"  /'\"\"'.\\              |  |                                                        \n"<<
" ||     ||             |  '.'                                                      \n"<<
" \\'. __//              |   /                                                       \n"<<
"  `'---'               `'-'                                                        \n"<<
"                        _..._                                                      \n"<<
"                     .-'_..._''.                              _______              \n"<<
"                   .' .'      '.\\    .           __.....__    \\  ___ `'.           \n"<<
"     _.._         / .'             .'|       .-''         '.   ' |--.\\  \\          \n"<<
"   .' .._|       . '             .'  |      /     .-''\"'-.  `. | |    \\  '         \n"<<
"   | '           | |            <    |     /     /________\\   \\| |     |  '        \n"<<
" __| |__  _    _ | |             |   | ____|                  || |     |  |        \n"<<
"|__   __|| '  / |. '             |   | \\ .'\\    .-------------'| |     ' .',.--.   \n"<<
"   | |  .' | .' | \\ '.          .|   |/  .  \\    '-.____...---.| |___.' /'//    \\  \n"<<
"   | |  /  | /  |  '. `._____.-'/|    /\\  \\  `.             .'/_______.'/ \\     | \n"<<
"   | | |   `'.  |    `-.______ / |   |  \\  \\   `''-...... -'  \\_______|/   `'-) /  \n"<<
"   | | '   .'|  '/            `  '    \\  \\  \\                                /.'   \n"<<
"   |_|  `-'  `--'   .-'''-.     '--===-'  '---'                                    \n"<<
"                   '   _    \\   .'/   \\                                            \n"<<
"                 /   /` '.   \\ / /     \\                                           \n"<<
" .-.          .-.   |     \\  ' | |     |                                           \n"<<
"  \\ \\        / /|   '      |  '| |     |                                           \n"<<
"   \\ \\      / / \\    \\     / / |/`.   .'                                           \n"<<
"    \\ \\    / /   `.   ` ..' /   `.|   |                                            \n"<<
"     \\ \\  / /       '-...-'`     ||___|                                            \n"<<
"      \\ `  /                     |/___/                                            \n"<<
"       \\  /                      .'.--.                                            \n"<<
"       / /                      | |    |                                           \n"<<
"   |`-' /                       \\_\\    /                                           \n"<<
"    '..'                         `''--'                                            \n\n";
    }

    s.notFlaged = true;

    if(verbose){
	cout << "Reading from file " << fileLocation << endl;
    }

    if (fileLocation == "") {
        while (s.notFlaged) {
            s.getCommand(cin);
        }
    } else {
        ifstream stream(fileLocation);
        while (!stream.eof()) {
            s.getCommand(stream);
        }
    }

    return 0;
}

