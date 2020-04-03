// References:
// https://stackoverflow.com/a/21182038
// https://stackoverflow.com/a/3790661
//
// Build in macOS/Linux:
// gcc -o patch_darkspore_exe patch_darkspore_exe.cpp -lstdc++
// 
// Build in Windows (needs Visual Studio's Developer Command Prompt):
// cl patch_darkspore_exe.cpp

#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>

std::string hexStringToString(std::string hex) {
    size_t len = hex.length();
    std::string newString;
    for(size_t i=0; i<len; i+=2)
    {
        std::string byte = hex.substr(i,2);
        char chr = (char) (int)strtol(byte.c_str(), 0, 16);
        newString.push_back(chr);
    }
    return newString;
}

void replaceAllOccurencesInString(std::string* str, std::string wordToReplace, std::string wordToReplaceWith) {
    size_t len = wordToReplace.length();
    while (true)
    {
        size_t pos = str->find(wordToReplace);
        if (pos == std::string::npos) break;
        str->replace(pos, len, wordToReplaceWith);    
    }
}

void replaceHostWithLocalhostInString(std::string* str, std::string host) {
    int zeroCount = host.length() - 9;
    std::string localhost = "127.0.0.";
    for (int i = 0; i < zeroCount; i++) localhost += "0";
    localhost += "1";
    replaceAllOccurencesInString(str, host, localhost);
}

int main(int argc, char **argv)
{
    std::ifstream in("Darkspore.exe", std::ios::binary);
    std::ofstream out("Darkspore_local.exe", std::ios::binary);
    
    if (!in) {
        std::cerr << "Could not open Darkspore.exe\n";
        system("pause");
        return 1;
    }

    if (!out) {
        std::cerr << "Could not write Darkspore_local.exe\n";
        system("pause");
        return 1;
    }

    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string str = buffer.str();

    replaceAllOccurencesInString(&str, hexStringToString("80BF2C0100000075"), 
                                       hexStringToString("80BF2C0100000175"));

    replaceHostWithLocalhostInString(&str, "config.darkspore.com");
    replaceHostWithLocalhostInString(&str, "gosredirector.ea.com");
    replaceHostWithLocalhostInString(&str, "gosredirector.scert.ea.com");
    replaceHostWithLocalhostInString(&str, "gosredirector.stest.ea.com");
    replaceHostWithLocalhostInString(&str, "gosredirector.online.ea.com");
    replaceHostWithLocalhostInString(&str, "api.darkspore.com");
                                      
    out << str;
    std::cout << "Finished creating Darkspore_local.exe" << std::endl;
    system("pause");
}