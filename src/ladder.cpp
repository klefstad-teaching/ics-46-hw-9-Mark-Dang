#include "ladder.h"


void error(string word1, string word2, string msg) {
    std::cerr << msg << ": " << word1 << ", " << word2 << std::endl;
}


string to_lower(const string & s) {
    string result;
    for (auto letter: s) result.push_back(std::tolower(letter));
    return result;
}


int min(int a, int b, int c) {
    if (a <= b && a <= c) return a;
    if (b <= a && b <= c) return b;
    if (c <= a && c <= b) return c;
    else return a;
}

//if edit distance within is d return true
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    string s1 = to_lower(str1);
    string s2 = to_lower(str2);

    int s1_size = s1.size();
    int s2_size = s2.size();
    vector<vector<int>> dp(s1_size + 1, vector<int>(s2_size + 1));

    for (int i = 0; i <= s1_size; ++i) dp[i][0] = i;
    for (int j = 0; j <= s2_size; ++j) dp[0][j] = j;

    for (int i = 1; i <= s1_size; ++i) {
        for (int j = 1; j <= s2_size; ++j) {
            if (s1[i - 1] == s2[j- 1]) dp[i][j] = dp[i-1][j-1]; //no difference
            else dp[i][j] = min(dp[i-1][j-1]+ 1, dp[i-1][j] + 1, dp[i][j-1] + 1);
        }
    }
    
    int edit_distance = dp[s1_size][s2_size];
    return edit_distance <= d;
}


bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}



vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    set<string> visited;


    vector<string> first;
    first.push_back(begin_word);
    ladder_queue.push(first);

    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> cur_ladder = ladder_queue.front();
        string last_word = cur_ladder.back();
        ladder_queue.pop();
        
        for (string word: word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = cur_ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) return new_ladder;
                    else ladder_queue.push(new_ladder);
                }
            }

        }
    }
    vector<string> empty;
    return empty;
}



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
    if (ladder.size()==0) {
        std::cout << "No word ladder found." << std::endl;
        return;
    }
    std::cout << "Word ladder found: ";
    for (auto word : ladder)  std::cout << word << " ";
    std::cout << std::endl;
}


#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<string> word_list;
    load_words(word_list, "src/words.txt");
    //my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    //my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    //my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}

