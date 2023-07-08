#include"Quiz.h"
#include<iostream>

void quizChooseRightWord(BinarySearchTree wordMap) {
    std::cout << "Game: choose the right word which has the definition among 4 random word\n";

    Quiz curQuiz = wordMap.chooseRightWord();
    std::cout << "Question: " << curQuiz.question << '\n';
    std::cout << "Choices:\n";

    for (int i = 0; i < 4; ++i) {
        std::cout << i + 1 << " : " << curQuiz.choices[i] << '\n';
    }

    std::string choice;
    std::cout << "Your choice: ";
    getline(std::cin, choice);

    while (choice.size() > 1 || choice[0] > '4' || choice[0] < '1') {
        std::cout << "Invalid Input.Please try again: ";
        getline(std::cin, choice);
    }

    if (stoi(choice) - 1 == curQuiz.answer)std::cout << "Correct\n";
    else std::cout << "Incorrect\n";

    std::cout << "Answer is: " << curQuiz.answer << '\n';
}

void quizChooseRightDef(BinarySearchTree wordMap) {
    std::cout << "Game: choose the right definition of a random word among 4 words\n";

    Quiz curQuiz = wordMap.chooseRightDefinition();
    std::cout << "Question: " << curQuiz.question << '\n';
    std::cout << "Choices:\n";

    for (int i = 0; i < 4; ++i) {
        std::cout << i + 1 << " : " << curQuiz.choices[i] << '\n';
    }

    std::string choice;
    std::cout << "Your choice: ";
    getline(std::cin, choice);

    while (choice.size() > 1 || choice[0] > '4' || choice[0] < '1') {
        std::cout << "Invalid Input. Please try again: ";
        getline(std::cin, choice);
    }

    if (stoi(choice) - 1 == curQuiz.answer)std::cout << "Correct\n";
    else std::cout << "Incorrect\n";

    std::cout << "Answer is: " << curQuiz.answer << '\n';
}
