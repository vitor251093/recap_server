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
    for (size_t i=0; i<len; i+=2)
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
    bool showDisplay = true;
    std::string in_path  = "Darkspore.exe";
    std::string out_path = "Darkspore_local.exe";
    
    std::string last_arg = "";
    std::string arg = "";
    int argIndex = 0;
    for (argIndex = 1; argIndex < argc; argIndex++) {
        arg = argv[argIndex];
        if (last_arg == "") {
            if (arg == "--no-display" || arg == "-nd") {
                showDisplay = false;
                continue;
            }
            if (arg == "-in") {
                last_arg = arg;
                continue;
            }
            if (arg == "-out") {
                last_arg = arg;
                continue;
            }
            continue;
        }
        else if (last_arg == "-in") {
            in_path = arg;
            last_arg = "";
            continue;
        }
        else if (last_arg == "-out") {
            out_path = arg;
            last_arg = "";
            continue;
        }
        else {
            last_arg = "";
        }
    }
    
    std::ifstream in(in_path, std::ios::binary);
    std::ofstream out(out_path, std::ios::binary);
    
    if (!in) {
        if (showDisplay) {
            std::cerr << "Could not open " << in_path << "\n";
            system("pause");
        }
        return 1;
    }

    if (!out) {
        if (showDisplay) {
            std::cerr << "Could not write " << out_path << "\n";
            system("pause");
        }
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
    
    if (showDisplay) {
        std::cout << "Finished creating " << out_path << std::endl;
        system("pause");
    }
    return 0;
}
