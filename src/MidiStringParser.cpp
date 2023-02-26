//
// Created by philip on 26.02.23.
//

#include <map>
#include "MidiStringParser.h"

// reference: https://www.zem-college.de/midi/mc_taben.htm
// Interpreter Features:
// Note parse (C D E ...)
// sharp Parse (#)
// pitch parse (-2 -> 8)
// value limit (max 127)
std::vector<int> MidiStringParser::generateMidiInts(std::string input) {
    std::vector<std::string> *stringBySpace = splitStringBySpace(input);

    // TODO, handle lower/upper case
    for (const auto &item: *stringBySpace){
        int note = noteValues[item[0]];
        // TODO needs range check
        bool isSharp = item[1] == '#';
    }


    return std::vector<int>();
}



std::vector<std::string> * MidiStringParser::splitStringBySpace(const std::string& input) {
    auto *strings = new std::vector<std::string>;
    unsigned long lastPos = 0;
    auto spacePos = input.find(' ', lastPos);

    // move to first actual character, otherwise there will be empty strings in the vector
    if(spacePos == 0){
        while (input[lastPos] == ' '){
            lastPos++;
        }
        // rerun find to have a correct value in spacePos
        spacePos = input.find(' ', lastPos);
    }

    while (spacePos != std::string::npos) {
        auto substring = input.substr(lastPos, spacePos - lastPos);
        strings->push_back(substring);

        lastPos = spacePos + 1;
        spacePos = input.find(' ', lastPos);

    }

    // if we are not at the input end just take the rest of the input
    if(lastPos != input.length()){
        auto substring = input.substr(lastPos, input.length() - lastPos);
        strings->push_back(substring);
    }

    return strings;
}
