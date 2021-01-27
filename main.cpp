#include <set>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>
#include <list>
using namespace std;

int main(int argc, char* argv[]) {
    /* For Part 7, I adapted my code to create script to the Harry Potter movies.
     * I had the program re-read the file, keeping colons and apostrophes. Every time the code sees a colon, it adds a
     * new line. This is to put it in script format. A big part of getting this to work was formatting the input text
     * file. For this, I found the scripts to the first 3 moves publicly available online. I removed all of the stagecraft
     * element (i.e [Harry pulls out his wand]) and removed all the weird whitespacing and capitalization. After that,
     * the script is simply read into the program. As a huge harry potter fan, I think some of it's output is very funny.
     * Here is some sample text:
     *
     * Neville: Oh
     * Hooch: Mr Longbottom to the dormitories Oh and there's something wrong with the monster into the Girl's Bathroom
     * Harry: Hermione move
     * Hermione: Help Help
     * Ron: Hey pea brain
     * Hermione: Ahhh Help
     * Harry: Ron was here But Dobby had to tell you Harry It's a world that's entirely our own Let them swim in the wizarding
     * world hearing voices isn't a witch in the deepest most desperate desires of our bylaws Severus having written more than
     * werewolves in those trees lad You can be found even in the moonlight are we
     * Lupin: Harry this is it I got the
     */
    string filename;
    if (argc == 2) {
        filename = argv[1];
    }
    else {
        cout << "Invalid arguments" << endl;
        exit(3);
    }

    int M=2; // Word association coefficient
    cout << "Target file: " << filename << endl;

    vector<string> tokens;
    set <string> unique;

    string next_line;  // Each data line
    ifstream in(filename);

    if(!in.is_open()) {
        cout << "Could not open file, " << filename << endl;
        exit(3);
    }

    while (getline(in, next_line)) { //populating the vector and set
        istringstream iss(next_line);
        string token;
        while (iss >> token) {
            string nopunct = "";
            for (int i = 0; i < token.size(); i++) {
                if (isalpha(token.at(i))) { //remove punctuation
                    nopunct += token.at(i);
                }
            }
            tokens.push_back(nopunct); //insert each word into vector
            unique.insert(nopunct); //insert each word into set
        }
    }
    in.close();
    cout << "Number of words: " << tokens.size() <<endl;
    cout << "Number of unique words: " << unique.size() <<endl;

    //PART 1
    cout << endl << "Part 1: Wrote to file " << filename << "_set.txt" << endl;
    ofstream setWrite(filename + "_set.txt");
    for (auto i = unique.begin(); i != unique.end(); i++) {
        setWrite << *i << endl;
    }

    //PART 2
    cout << endl << "Part 2: Wrote to file " << filename << "_vector.txt" << endl;
    ofstream vectorWrite(filename + "_vector.txt");
    for (auto i = tokens.begin(); i != tokens.end(); i++) {
        vectorWrite << *i << endl;
    }

    //PART 3
    cout << endl << "Part 3: Wrote to file " << filename << "_map.txt" << endl;
    map<string, string> wordMap;
    string previousWord = "";

    for (auto i = tokens.begin(); i != tokens.end(); i++) { //populating map
        wordMap[previousWord] = *i;
        previousWord = *i;
    }

    ofstream mapWrite(filename + "_1_1.txt");
    for (auto i = wordMap.begin(); i != wordMap.end(); i++) {
        mapWrite << i->first << ", " << i->second << endl;
    }

    //PART 4
    cout << endl << "Part 4: One-to-one map output:" << endl;
    string state = "";
    for (int i = 0; i < 100; i++) {
        cout << wordMap[state] << " ";
        state = wordMap[state];
    }
    cout << endl;

    //PART 5
    cout << endl << "Part 5: " << endl;
    map<string, vector<string>> wordMap2;
    previousWord = "";
    for (auto i = tokens.begin(); i != tokens.end(); i++) {
        wordMap2[previousWord].push_back(*i);
        previousWord = *i;
    }
    auto elementSixItr = wordMap2.begin();
    advance(elementSixItr,5);
    cout << "6th entry: " << elementSixItr->first << endl << "Values: ";
    for (int i = 0; i < elementSixItr->second.size(); i++) {
        cout << elementSixItr->second.at(i) << ", ";
    }

		cout << endl << "Sample output:" << endl;
    state = "";
    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
        int ind = rand() % wordMap2[state].size();
        cout << wordMap2[state][ind] << " ";
        state = wordMap2[state][ind];
    }
    cout << endl;

    //PART 6
    cout << endl << "Part 6: ";
    map<list<string>, vector<string>> wordMap3;
    list<string> listState;
    tokens.clear();
    unique.clear();

    in.open(filename);
    while (getline(in, next_line)) {
        istringstream iss(next_line);
        string token;
        while (iss >> token) {
            string nopunct = "";
            for (int i = 0; i < token.size(); i++) { // Remove punctuation except apostrophes and colons which I need for my improved algorithm
                if (isalpha(token.at(i)) || token.at(i) == '\''|| token.at(i) == ':') {
                    nopunct += token.at(i);
                }
            }
            tokens.push_back(nopunct); //insert each word into vector
            unique.insert(nopunct); //insert each word into set
        }
    }

    for (int i = 0; i < M; i++) { //setting the list elements to default
        listState.push_back("");
    }

    for (auto i = tokens.begin(); i != tokens.end(); i++) { //populating the map
        wordMap3[listState].push_back(*i);
        listState.push_back(*i);
        listState.pop_front();
    }

    listState.clear();
    for (int i = 0; i < M; i++) { //resetting the state-list to default
        listState.push_back("");
    }

    for (int i = 0; i < 100; i++) { //printing the map
        int ind = rand() % wordMap3[listState].size();

        //making separate lines for each character in the script
        if (wordMap3[listState][ind].size() != 0) {
            if (wordMap3[listState][ind].at(wordMap3[listState][ind].size() - 1) == ':') {
                cout << endl;
            }
        }
        cout << wordMap3[listState][ind]<<" ";
        listState.push_back(wordMap3[listState][ind]);
        listState.pop_front();
    }
    cout << endl << endl << "Part 7: " << endl << "Look at top of code for discription"<< endl;

    return 0;
}