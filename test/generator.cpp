/***
    Copyright (C) <2017>  <Razvan STANCIOIU>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <fstream>
#include <iostream>
#define NR 100000
#define NS 1000000
#define MR 10
#define MS 15

using namespace std;

// Generates a random database with N tuples and M attributes
// the elements of the database are integers
void generate(const char* str, unsigned int N, unsigned int M) {
    ofstream output;
    output.open(str);
    for (unsigned int i = 0; i < N; ++i) {
        for (unsigned int j = 0; j < M; ++j) {
            output << rand() % N << " ";
        }
        output << endl;
    }
    output.close();
    output.clear();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    generate("r-large.txt", NR, MR);
    generate("s-large.txt", NS, MS);
    return 0;
}