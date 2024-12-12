#include "puzzle1.hpp"
#include <fstream>
#include <iostream>

string readFile() {
    ifstream file("../src/input.txt");
    string line;
    getline(file, line);
    return line;
}

vector<string> parse(string contents) {
    int block_index = 0;
    bool file = true;
    vector<string> new_output;
    for (char ch : contents) {
        int number = ch - '0';
        if (file) {
            for (int i=0; i<number; i++) {
                new_output.push_back(to_string((block_index)));
            }
            file = false;
            block_index++;
        } else {
            for (int i=0; i<number; i++) {
                new_output.push_back(".");
            }
            file = true;
        }
    }

    return new_output;
}


vector<string> move_from_end(vector<string> contents) {
    int write_pos = 0;  // Position to write the next non-dot character
    for (int read_pos=contents.size()-1; read_pos >= 0; read_pos--) {
        if (contents[read_pos] != ".") {
            while (contents[write_pos] != ".") {
                write_pos++;
            }
            if (write_pos < read_pos) {
                contents[write_pos] = contents[read_pos];
                contents[read_pos] = ".";
            }
        }
    }
    return contents;
}

long long checksum(vector<string> line) {
    long long checksum = 0;
    for (int i=0; i<line.size(); i++) {
        if (line[i] != ".") {
            checksum += i * stoi(line[i]);
        }
    }

    return checksum;
}

int main() {
    string fileContents = readFile();
    vector<string> parsed = parse(fileContents);
    vector<string> moved = move_from_end(parsed);

    long long chsum = checksum(moved);
    cout << chsum << endl;
}