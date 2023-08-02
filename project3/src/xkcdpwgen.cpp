#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <algorithm> // for std::shuffle
#include <random>    // for std::default_random_engine

void printUsage(const std::string& programName);
int getRandomNumber(int min, int max);
std::string generatePassword(const std::vector<std::string>& wordList, int numWords, int capitalizeWords, int numNumbers, int numSymbols);

int main(int argc, char* argv[])
{
    srand(time(nullptr));

    // Load the wordlist from the file "words.txt"
    std::vector<std::string> wordList;
    std::ifstream wordFile("words.txt");
    if (wordFile.is_open())
    {
        std::string word;
        while (getline(wordFile, word))
        {
            wordList.push_back(word);
        }
        wordFile.close();
    }
    else
    {
        std::cout << "Error: Unable to open wordlist file 'words.txt'\n";
        return 1;
    }

    int numWords = 4;
    int capitalizeWords = 0;
    int numNumbers = 0;
    int numSymbols = 0;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help")
        {
            printUsage(argv[0]);
            return 0;
        } 
        else if (arg == "-w" || arg == "--words")
        {
            if (i + 1 < argc)
            {
                numWords = std::stoi(argv[i + 1]);
                ++i;
            }
        }
        else if (arg == "-c" || arg == "--caps")
        {
            if (i + 1 < argc)
            {
                capitalizeWords = std::stoi(argv[i + 1]);
                ++i;
            }
        }
        else if (arg == "-n" || arg == "--numbers")
        {
            if (i + 1 < argc)
            {
                numNumbers = std::stoi(argv[i + 1]);
                ++i;
            }
        }
        else if (arg == "-s" || arg == "--symbols")
        {
            if (i + 1 < argc)
            {
                numSymbols = std::stoi(argv[i + 1]);
                ++i;
            }
        }
        else
        {
            std::cout << "Unknown option: " << arg << std::endl;
            return 1;
        }
    }

    std::string password = generatePassword(wordList, numWords, capitalizeWords, numNumbers, numSymbols);
    std::cout << password << std::endl;

    return 0;
}

int getRandomNumber(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

std::string generatePassword(const std::vector<std::string>& wordList, int numWords, int capitalizeWords, int numNumbers, int numSymbols)
{
    std::string password;

    // Capitalize random words
    std::vector<bool> capitalizeFlags(numWords, false);
    int wordsToCapitalize = std::min(capitalizeWords, numWords);
    for (int i = 0; i < wordsToCapitalize; ++i)
    {
        int randomIndex = getRandomNumber(0, numWords - 1);
        while (capitalizeFlags[randomIndex])
        {
            randomIndex = getRandomNumber(0, numWords - 1);
        }
        capitalizeFlags[randomIndex] = true;
    }

    // Add words
    for (int i = 0; i < numWords; ++i)
    {
        std::string word = wordList[getRandomNumber(0, wordList.size() - 1)];
        if (capitalizeFlags[i])
        {
            word[0] = toupper(word[0]);
        }
        password += word;
    }

    // Add numbers
    for (int i = 0; i < numNumbers; ++i)
    {
        char digit = '0' + getRandomNumber(0, 9);
        int insertPosition = getRandomNumber(0, password.length());
        password.insert(insertPosition, 1, digit);
    }

    // Add symbols
    std::string symbols = "~!@#$%^&*.:;";
    for (int i = 0; i < numSymbols; ++i)
    {
        char symbol = symbols[getRandomNumber(0, symbols.length() - 1)];
        int insertPosition = getRandomNumber(0, password.length());
        password.insert(insertPosition, 1, symbol);
    }

    return password;
}

void printUsage(const std::string& programName)
{
    std::cout << "Usage: " << programName << " [-h] [-w WORDS] [-c CAPS] [-n NUMBERS] [-s SYMBOLS]\n\n"
              << "Generate a secure, memorable password using the XKCD method\n\n"
              << "optional arguments:\n"
              << "  -h, --help            show this help message and exit\n"
              << "  -w WORDS, --words WORDS\n"
              << "                        include WORDS words in the password (default=4)\n"
              << "  -c CAPS, --caps CAPS  capitalize the first letter of CAPS random words\n"
              << "                        (default=0)\n"
              << "  -n NUMBERS, --numbers NUMBERS\n"
              << "                        insert NUMBERS random numbers in the password\n"
              << "                        (default=0)\n"
              << "  -s SYMBOLS, --symbols SYMBOLS\n"
              << "                        insert SYMBOLS random symbols in the password\n"
              << "                        (default=0)\n";
}