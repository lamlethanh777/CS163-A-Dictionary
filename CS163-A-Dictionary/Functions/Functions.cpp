#include "Functions.h"

#include <iostream>
#include <exception>

void clearScreen() {
	std::cout << "\033[2J\033[1;1H";
}

void displayCurrentDataset(const std::string& currentDatasetName) {
    std::cout << "***** Current dataset: " << currentDatasetName << " dictionary *****\n\n";
}

void displayAllDatasets() {
	std::cout << "Please choose your dataset below:\n"
	          << "1. English - English dictionary\n"
	          << "2. English - Vienamese dictionary\n"
	          << "3. Vienamese - English dictionary\n"
	          << "4. Slang dictionary\n"
	          << "5. Emoji dictionary\n";
}

void displayMenu() {
    std::cout << "What do you want to do?\n"
              << "1. Change your current dataset\n"
              << "2. Search for a keyword\n"
              << "3. Search for a definition\n"
              << "4. View your searching history\n"
              << "5. Add new word/definition to dictionary\n"
              << "6. Edit the definition of existing word\n"
              << "7. Remove a word from the dictionary\n"
              << "8. Reset the current dictionary's dataset\n"
              << "9. View a random word with definition\n"
              << "10. View words in your favorite list\n"
              << "11. Remove/add word from your favorite list\n"
              << "12. Game: choose the right definition of a word among 4 definitions\n"
              << "13. Game: choose the right word which has a definition stated among 4 words\n"
              << "0. Leave the dictionary :`(\n";
}

bool inputAndValidateUserChoice(int& commandNumber) {
    std::string buffer;
    std::cout << "Your choice: ";
    getline(std::cin, buffer);

    if (buffer.size() > 2) {
        return false;
    }

    for (unsigned int i = 0; i < buffer.size(); ++i) {
        if (buffer[i] < '0' || buffer[i] > '9') {
            return false;
        }
    }

    try {
        commandNumber = std::stoi(buffer);
    } catch (...) {
        return false; // Invalid number conversion
    }

    return true;
}

void chooseDataset(int& currentDatasetNumber, std::string& currentDatasetName) {
	do {
		displayAllDatasets();

        if (!inputAndValidateUserChoice(currentDatasetNumber)) {
            clearScreen();
            std::cout << "Invalid option! Please try again!\n\n";
            currentDatasetNumber = 0;
            continue;
        }

		switch (currentDatasetNumber) {
            case 1: {
                currentDatasetName = "Eng-Eng";
                break;
            }

            case 2: {
                currentDatasetName = "Eng-Vie";
                break;
            }

            case 3: {
                currentDatasetName = "Vie-Eng";
                break;
            }

            case 4: {
                currentDatasetName = "Slang";
                break;
            }

            case 5: {
                currentDatasetName = "Emoji";
                break;
            }

            default: {
                clearScreen();
                std::cout << "Invalid option! Please try again!\n\n";
                currentDatasetNumber = 0;
                break;
            }
		}
	} while (currentDatasetNumber == 0); 
	// currentDatasetNumber == 0 : no dataset chosen (1-5)
}

void chooseFeature(int& commandNumber, int& currentDatasetNumber, std::string& currentDatasetName, Dictionary& currentDictionary) {
    if (!inputAndValidateUserChoice(commandNumber)) {
        clearScreen();
        displayCurrentDataset(currentDatasetName);
        std::cout << "Invalid option! Please try again!\n\n";
        commandNumber = 0;
        return;
    }

    clearScreen();
    displayCurrentDataset(currentDatasetName);

	switch (commandNumber)
	{
        case 0: {
            // throw "leave" -> loop = false (see "catch" below)
            throw std::invalid_argument("leave");
        }
        
        case 1: {
            // handled outside (the outer while loop)
            break;
        }

        case 2: {
            std::cout << "2. Search for a keyword\n";
            searchWord(*(currentDictionary.wordsList), *(currentDictionary.definitionsList), currentDictionary.searchHistory);
            break;
        }

        case 3: {
            std::cout << "3. Search for a definition\n";
            searchForDefinition(*(currentDictionary.definitionsList));
            break;
        }

        case 4: {
            std::cout << "4. View your searching history\n";
            viewSearchHistory(currentDictionary.searchHistory);
            break;
        }

        case 5: {
            std::cout << "5. Add new word/definition to dictionary\n";
            addNewWord(*(currentDictionary.wordsList), *(currentDictionary.definitionsList));
            break;
        }

        case 6: {
            std::cout << "6. Edit the definition of existing word\n";
            // 6. Edit the definition of existing word
            break;
        }
		
	    case 7: {
            std::cout << "7. Remove a word from the dictionary\n";
            // 7. Remove a word from the dictionary
            break;
        }
		
        case 8: {
            std::cout << "8. Reset the current dictionary's dataset\n";
            currentDictionary.resetToOriginal();
            std::cout << "Dictionary reset to original state successfully!\n";
            break;
        }

        case 9: {
            std::cout << "9. View a random word with definition\n";
            viewRandomWord(*(currentDictionary.definitionsList));
            break;
        }

        case 10: {
            std::cout << "10. View your favorite list\n";
            viewFavoriteList(currentDictionary.favoriteList);
            break;
        }

        case 11: {
            std::cout << "11. Remove/add word from your favorite list\n";
            add_removeFariteWord(*(currentDictionary.wordsList), currentDictionary.favoriteList);
            break;
        }

        case 12: {
            std::cout << "12. Game: choose the right definition of a word among 4 definitions\n";
            quizChooseRightDef(*(currentDictionary.definitionsList));
            break;
        }

        case 13: {
            std::cout << "13. Game: choose the right word which has a definition stated among 4 words\n";
            quizChooseRightWord(*(currentDictionary.definitionsList));
            break;
        }

        default: {
            std::cout << "Invalid option! Please try again!\n\n";
            break;
        }
	}
    std::cout << '\n';
}

void menu() {
    Dictionary* currentDictionary = nullptr;
	int currentDatasetNumber = 0, commandNumber = 0;
    bool loop = true;
    std::string currentDatasetName;

    // currentDatasetNumber == 0 -> havent chose the dataset         (1-5)
    // currentDatasetName -> access data file                        (Eng-Eng, Eng-Vie, Vie-Eng, Slang, Emoji)
    // main loop of the program, loop == false -> leave
	do {
        try {
            // choose/change dataset
            chooseDataset(currentDatasetNumber, currentDatasetName);
            if (!currentDictionary) {
                currentDictionary = new Dictionary(currentDatasetName);
            }
            else {
                currentDictionary->changeDataset(currentDatasetName);
            }

            clearScreen();

            commandNumber = 0;
            // choices which do not change the dataset
            while (commandNumber != 1) {
                displayCurrentDataset(currentDatasetName);
                displayMenu();
                chooseFeature(commandNumber, currentDatasetNumber, currentDatasetName, *currentDictionary);
            }

            clearScreen();
        }
        catch (std::exception& error) {
            std::string prompt = error.what();

            if (prompt.compare("leave") == 0) {
                loop = false;
            }
            else {
                std::cout << prompt << '\n';
            }
        }
	} while (loop);
    
    clearScreen();
    delete currentDictionary;
    std::cout << "\nThanks for using our app! Leaving...\n";
}
