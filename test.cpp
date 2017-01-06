#include <iostream>
#include <stack>
#include <algorithm>
#include <conio.h>
#include "Jeu/Grille.h"
#include "Jeu/Sequence.h"
#include <time.h>

using namespace std;
int main() {
    vector<int> vec;
    for (int i = 1; i < 8; ++i) {
        vec.push_back(i);
    }
    vec.erase(std::remove(vec.begin(), vec.end(), 8), vec.end());
    for (int i = 0; i < vec.size(); ++i) {
        cout<<" "<<vec.at(i);
    }
//    getch();
    return 0;
}
