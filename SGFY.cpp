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

using namespace std;

struct store {
    int intBank[128][128];
    int index, vindex;
    bool printAsChar;
    bool notFlaged;
    string storedLoop;

    store() {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                intBank[j][i] = 0;
            }
        }
        index = 0;
        vindex = 0;
        printAsChar = true;
    }

    void getCommand(istream & inputStream);
    void getCommand(char c);
};

void store::getCommand(istream & inputStream) {

    char c = inputStream.get();

    switch (c) {
        case '+':
            intBank[vindex][index]++;
            break;
        case '-':
            intBank[vindex][index]--;
            break;
        case '>':
            if (index == 127) {
                index = 0;
            } else {
                index++;
            }
            break;
        case '<':
            if (index == 0) {
                index = 127;
            } else {
                index--;
            }
            break;
        case '^':
            if (vindex == 127) {
                vindex = 0;
            } else {
                vindex++;
            }
            break;
        case '\\':
            if (vindex == 0) {
                vindex = 127;
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
            if (vindex < 127) {
                intBank[vindex][index] = intBank[vindex + 1][index];
            } else {
                intBank[vindex][index] = intBank[0][index];
            }
            break;
        case '}':
            if (index > 0) {
                intBank[vindex][index] = intBank[vindex][index - 1];
            } else {
                intBank[vindex][index] = intBank[vindex][127];
            }
            break;
        case '[':
            if (intBank[vindex][index] != 0) {
                while (inputStream.peek() != ']') {
                    storedLoop += inputStream.get();
                }
            } else {
                while (inputStream.get() != ']') {

                }
            }
            break;
        case ']':
            while (intBank[vindex][index] != 0) {
                for (char c : storedLoop) {
                    this->getCommand(c);
                }
            }
            storedLoop = "";
            break;

    }
}

void store::getCommand(char c) {

    switch (c) {
        case '+':
            intBank[vindex][index]++;
            break;
        case '-':
            intBank[vindex][index]--;
            break;
        case '>':
            if (index == 127) {
                index = 0;
            } else {
                index++;
            }
            break;
        case '<':
            if (index == 0) {
                index = 127;
            } else {
                index--;
            }
            break;
        case '^':
            if (vindex == 127) {
                vindex = 0;
            } else {
                vindex++;
            }
            break;
        case '\\':
            if (vindex == 0) {
                vindex = 127;
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
            if (vindex < 127) {
                intBank[vindex][index] = intBank[vindex + 1][index];
            } else {
                intBank[vindex][index] = intBank[0][index];
            }
            break;
        case '}':
            if (index > 0) {
                intBank[vindex][index] = intBank[vindex][index - 1];
            } else {
                intBank[vindex][index] = intBank[vindex][127];
            }
            break;

    }
}

/*
 * 
 */
int main(int argc, char** argv) {


    srand(time(NULL));

    store s;
    string choice;

    while (true) {
        cout << "SGFY interpreter v0.1.1\n\n------------------------------------------\n"
                << "Enter filename (cin if live interpret): ";
        cin >> choice;
        cin.clear();

        s.notFlaged = true;

        if (choice == "cin") {
            while (s.notFlaged) {
                s.getCommand(cin);
            }
        } else {
            ifstream stream(choice);
            while (!stream.eof()) {
                s.getCommand(stream);
            }
        }

        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    }

    //    if (argc <= 1) {
    //        while (true) {
    //            s.getCommand(cin.get());
    //        }
    //    } else{
    //        //Get args
    //    }


    return 0;
}

