#pragma once
#include <string>
#include <vector>
#include <map>
#include <utility>

using namespace std;

class Puzzle1 {
    private:
        vector<string> grid;
        map<char, vector<pair<int,int>>> antennae;
        vector<pair<int,int>> antinodes;
    
    public:
        void readFile();
        void findAntennae();
        void printAntennae();
        void findAntinodes(vector<pair<int,int>> nodes);
        pair<int,int> getDistance(pair<int,int> node1, pair<int,int> node2);
        bool checkAntinodeIsInGrid(pair<int,int> antinode);
        
        map<char, vector<pair<int,int>>> getAntennae() {
            return antennae;
        }

        vector<pair<int,int>> getAntinodes() {
            return antinodes;
        }
};