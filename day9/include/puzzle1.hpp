#pragma once
#include <string>
#include <vector>

using namespace std;

string readFile();
vector<string> parse(string contents);
string move_from_end(string contents);
long long checksum(string line);
