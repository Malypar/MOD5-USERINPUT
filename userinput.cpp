#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <mutex>
#include <thread>

std::mutex file_mutex;

void appendToFile(const std::string& filename, const std::string& input) {
    std::lock_guard<std::mutex> lock(file_mutex);
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << input << std::endl;
        file.close();
    } else {
        std::cerr << "Unable To Open File For Appending." << std::endl;
    }
}

void reverseFile(const std::string& inputFile, const std::string& outputFile) {
    std::lock_guard<std::mutex> lock(file_mutex);
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

    if (inFile.is_open() && outFile.is_open()) {
        std::string totalContent((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        std::reverse(totalContent.begin(), totalContent.end());
        outFile << totalContent;
        inFile.close();
        outFile.close();
    } else {
        std::cerr << "There Was An Error Opening The Files." << std::endl;
    }
}

int main() {
    std::string userInput;
    std::cout << "Enter Text To Append To File: \n";
    std::getline(std::cin, userInput);

    const std::string origianlFile = "CSC450_CT5_mod5.txt";
    const std::string reversedFile = "CSC450-mod5-reverse.txt";

    std::thread t1(appendToFile, origianlFile, userInput);
    std::thread t2(reverseFile, origianlFile, reversedFile);

    t1.join();
    t2.join();

    std::cout << "The Data Has Been Appended To The New File." << std::endl;
    
    return 0;
}