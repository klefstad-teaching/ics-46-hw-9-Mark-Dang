#include "ladder.h"
#include <cassert>

void test_edit_distance_within() {
    cout << "Test edit_distance_within" << std::endl;
    assert(edit_distance_within("abc", "BC", 1)==true);
    assert(edit_distance_within("abc", "BC", 2)==true);
    assert(edit_distance_within("abc", "B", 1)==false);
    assert(edit_distance_within("abc", "CBC", 1)==true);
    assert(edit_distance_within("bail", "Beet", 2)==false);    
    cout << "Test edit_distance good" << std::endl;
}



int main() {
    verify_word_ladder();
    return 0;
}