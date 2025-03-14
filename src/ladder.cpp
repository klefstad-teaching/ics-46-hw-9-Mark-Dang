#include "ladder.h"


void error(string word1, string word2, string msg) {
    std::cerr << msg << ": " << word1 << ", " << word2 << std::endl;
}


string to_lower(const string & s) {
    string result;
    for (auto letter: s) result.push_back(std::tolower(letter));
    return result;
}

//if edit distance within is d return true
//bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    //string s1 = to_lower(str1);
    //string s2 = to_lower(str2);
    
//}

//bool is_adjacent(const string& word1, const string& word2);

//vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list);

void load_words(set<string> & word_list, const string& file_name) {
    ifstream inFile(file_name);
    if (!inFile.is_open()) {
        error("", "", "File not open"); 
        return;
    }

    string word;
    while (inFile >> word) word_list.insert(word);
    inFile.close();
}
    

void print_word_ladder(const vector<string>& ladder) {
    for (auto word : ladder) {
        if (word == ladder[ladder.size() - 1]) std::cout << word;
        else std::cout << word << " -> ";
    }
}


#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}

