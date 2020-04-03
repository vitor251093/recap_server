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

int main(int argc, char **argv)
{
    std::ifstream in("Darkspore.exe", std::ios::binary);
    std::ofstream out("Darkspore_nossl.exe", std::ios::binary);
    std::string wordToReplace(hexStringToString("80BF2C0100000075"));
    std::string wordToReplaceWith(hexStringToString("80BF2C0100000175"));

    if (!in) {
        std::cerr << "Could not open Darkspore.exe\n";
        system("pause");
        return 1;
    }

    if (!out) {
        std::cerr << "Could not write Darkspore_nossl.exe\n";
        system("pause");
        return 1;
    }

    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string str = buffer.str();

    size_t len = wordToReplace.length();
    while (true)
    {
        size_t pos = str.find(wordToReplace);
        if (pos == std::string::npos) break;
        str.replace(pos, len, wordToReplaceWith);    
    }

    out << str;
    std::cout << "Finished creating Darkspore_nossl.exe" << std::endl;
    system("pause");
}