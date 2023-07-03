#include <iostream>
#include "Class/HashMap/HashMap.h"

// Testing
int main() {
    string temp = "Data//Dict_Eng-Vie//HashMap.txt";
    BinarySearchTree hashMap(temp);
    hashMap.buildOriginal();

    Quiz testQuiz = hashMap.chooseRightWord();
    cout << "Question: " << testQuiz.question << endl;
    cout << "Choices:" << endl;
    for (int i = 0; i < 4; ++i) {
        cout << testQuiz.choices[i] << endl;
    }

    cout << "Answer: " << testQuiz.answer << endl;
	return 0;  
}
