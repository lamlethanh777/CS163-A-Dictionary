#include"Quiz.h"
#include<iostream>

void quizChooseRightWord(BinarySearchTree& wordMap) {
    Quiz curQuiz = wordMap.chooseRightWord();
    std::cout << "\nWhich word has the definition below:\n" << curQuiz.question << "\n\n";

    for (char i = 0; i < 4; ++i) {
        std::cout << (char) (i + 'A') << ". " << curQuiz.choices[i] << '\n';
    }

    std::string choice;
    std::cout << "\nYour choice is: ";
    getline(std::cin, choice);

    while (choice.size() > 1 || choice[0] > 'D' || choice[0] < 'A') {
        std::cout << "Invalid Input. Please try again: ";
        getline(std::cin, choice);
    }

    if (choice[0] - 'A' == curQuiz.answer) {
        std::cout << "Congratulation! You chose the correct answer!\n";
    }
    else {
        std::cout << "Incorrect! The correct answer is " << (char) (curQuiz.answer + 'A') << ". " << curQuiz.choices[curQuiz.answer] << '\n';
    }
}

void quizChooseRightDef(BinarySearchTree& wordMap) {
    Quiz curQuiz = wordMap.chooseRightDefinition();
    std::cout << "\nWhich one is the defintion of this word: " << curQuiz.question << "\n\n";

    for (char i = 0; i < 4; ++i) {
        std::cout << (char) (i + 'A') << ". " << curQuiz.choices[i] << '\n';
    }

    std::string choice;
    std::cout << "\nYour choice is: ";
    getline(std::cin, choice);

    while (choice.size() > 1 || choice[0] > 'D' || choice[0] < 'A') {
        std::cout << "Invalid Input. Please try again: ";
        getline(std::cin, choice);
    }

    if (choice[0] - 'A' == curQuiz.answer) {
        std::cout << "Congratulation! You chose the correct answer!\n";
    }
    else {
        std::cout << "Incorrect! The correct answer is " << (char) (curQuiz.answer + 'A') << ". " << curQuiz.choices[curQuiz.answer] << '\n';
    }
}
