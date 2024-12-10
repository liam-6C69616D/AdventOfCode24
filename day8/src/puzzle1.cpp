#include "puzzle1.hpp"
#include <fstream>
#include <iostream>
#include <cmath>

void Puzzle1::readFile() {
    ifstream file("../src/input.txt");
    string line;
    while (getline(file, line)) {
        // Output the text from the file
        grid.push_back(line);
    }
}

void Puzzle1::findAntennae() {
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[i].length(); j++) {
            if (grid[i][j] != '.') {
                antennae[grid[i][j]].push_back(make_pair(i,j));
            }
        }
    }
}

void Puzzle1::findAntinodes(vector<pair<int,int>> nodes) {
    for (int i=0; i<nodes.size(); i++) {
        int comparison = i+1;
        while (comparison < nodes.size()) {
            pair<int, int> distances = getDistance(nodes[i], nodes[comparison]);
            pair<int, int> anti1 = make_pair(nodes[i].first - distances.first, nodes[i].second - distances.second);
            pair<int, int> anti2 = make_pair(nodes[comparison].first + distances.first, nodes[comparison].second + distances.second);
            // cout << '[' << nodes[i].first << ',' << nodes[i].second << ']' 
            //      << '[' << nodes[comparison].first << ',' << nodes[comparison].second << ']' 
            //      << " DST: " << distances.first << ',' << distances.second << ' '
            //      << '[' << anti1.first << ',' << anti1.second << ']'
            //      << '[' << anti2.first << ',' << anti2.second << ']' << endl;
            bool a1Add = true;
            bool a2Add = true;
            for (pair<int, int> coords : antinodes) {
                if (anti1.first == coords.first && anti1.second == coords.second) a1Add = false;
                if (anti2.first == coords.first && anti2.second == coords.second) a2Add = false;
            }

            if (a1Add) antinodes.push_back(anti1);
            if (a2Add) antinodes.push_back(anti2);

            comparison++;
        }
    }
}

pair<int,int> Puzzle1::getDistance(pair<int,int> node1, pair<int,int> node2) {
    int x_dist = node2.first - node1.first;
    int y_dist = node2.second - node1.second;

    return make_pair(x_dist, y_dist);
}

void Puzzle1::printAntennae() {
    for (const auto& [key, value] : antennae) {
        cout << key << ':';
        for (pair<int,int> pr : value) {
            cout << '[' << pr.first << ',' << pr.second << ']';
        }
        cout << endl;
    }
}

bool Puzzle1::checkAntinodeIsInGrid(pair<int,int> antinode) {
    if (antinode.first < 0 || antinode.first >= grid[0].length() || antinode.second < 0 || antinode.second >= grid.size()) {
        return false;
    } else {
        return true;
    }
}

int main() {
    Puzzle1 p1;
    p1.readFile();
    p1.findAntennae();
    for (const auto& [key, value] : p1.getAntennae()) {
        p1.findAntinodes(value);
    }
    int count = 0;
    for (pair<int,int> coord : p1.getAntinodes()) {
        if (p1.checkAntinodeIsInGrid(coord)) {
            count++;
        }
    }

    cout << count << endl;
}