#include "puzzle2.hpp"
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>

void Puzzle2::readFile() {
    ifstream file("../src/input.txt");
    string line;
    while (getline(file, line)) {
        // Output the text from the file
        grid.push_back(line);
    }
}

void Puzzle2::findAntennae() {
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[i].length(); j++) {
            if (grid[i][j] != '.') {
                antennae[grid[i][j]].push_back(make_pair(i,j));
            }
        }
    }
}

void Puzzle2::findAntinodes(vector<pair<int,int>> nodes) {
    for (int i=0; i<nodes.size(); i++) {
        int comparison = i+1;
        while (comparison < nodes.size()) {
            pair<int, int> distances = getDistance(nodes[i], nodes[comparison]);
            pair<int, int> smallestSubstep = findSmallestSubstepOnLine(distances);
            
            // cout << '[' << nodes[i].first << ',' << nodes[i].second << ']' 
            //      << '[' << nodes[comparison].first << ',' << nodes[comparison].second << ']' 
            //      << " DST: " << distances.first << ',' << distances.second << ' '
            //      << " Substep: " << smallestSubstep.first << ',' << smallestSubstep.second << endl;
            
            int x = nodes[i].first;
            int y = nodes[i].second;

            // Walk "backwards" from the first node in steps
            while (checkAntinodeIsInGrid(make_pair(x,y))) {
                bool add_to_list = true;
                for (pair<int, int> coords : antinodes) {
                    if (x == coords.first && y == coords.second) add_to_list = false;
                }
                if (add_to_list) antinodes.push_back(make_pair(x,y));
                x -= smallestSubstep.first;
                y -= smallestSubstep.second;
            }
            
            // Walk "forwards" from the first node in steps
            x = nodes[i].first + smallestSubstep.first;
            y = nodes[i].second + smallestSubstep.second;
            while (checkAntinodeIsInGrid(make_pair(x,y))) {
                bool add_to_list = true;
                for (pair<int, int> coords : antinodes) {
                    if (x == coords.first && y == coords.second) add_to_list = false;
                }
                if (add_to_list) antinodes.push_back(make_pair(x,y));
                x += smallestSubstep.first;
                y += smallestSubstep.second;
            }

            comparison++;
        }
    }
}

pair<int,int> Puzzle2::findSmallestSubstepOnLine(pair<int,int> step) {
    int greatest_common_divisor = __gcd(step.first, step.second);

    return make_pair(step.first/greatest_common_divisor, step.second/greatest_common_divisor);
}

pair<int,int> Puzzle2::getDistance(pair<int,int> node1, pair<int,int> node2) {
    int x_dist = node2.first - node1.first;
    int y_dist = node2.second - node1.second;

    return make_pair(x_dist, y_dist);
}

void Puzzle2::printAntennae() {
    for (const auto& [key, value] : antennae) {
        cout << key << ':';
        for (pair<int,int> pr : value) {
            cout << '[' << pr.first << ',' << pr.second << ']';
        }
        cout << endl;
    }
}

bool Puzzle2::checkAntinodeIsInGrid(pair<int,int> antinode) {
    if (antinode.first < 0 || antinode.first >= grid[0].length() || antinode.second < 0 || antinode.second >= grid.size()) {
        return false;
    } else {
        return true;
    }
}

int main() {
    Puzzle2 p1;
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