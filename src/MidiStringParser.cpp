//
// Created by philip on 26.02.23.
//

#include <map>
#include <algorithm>
#include "MidiStringParser.h"

// reference: https://www.zem-college.de/midi/mc_taben.htm
// Interpreter Features:
// Note parse (C D E ...)
// major Parse (#)
// pitch parse (-2 -> 8)
// value limit (max 127)
std::vector<int> MidiStringParser::generateMidiInts(std::string input) {
    std::vector<std::string> *stringBySpace = splitStringBySpace(input);
    auto* parsedNoteValues = new std::vector<int8_t>;

    for (auto &item: *stringBySpace) {
        // convert string to upper characters
        std::transform(item.begin(), item.end(), item.begin(),
                       [](unsigned char c) { return std::toupper(c); });

        uint8_t note = noteValues[item[0]];

        bool isMajor = item[1] == '#';

        if(item.length() == 1 || item.length() == 2){
            int8_t pitch = 2;
            uint8_t noteValue = pitch * 11 + note;
            if(isMajor){
                noteValue++;
            }


            parsedNoteValues->push_back(noteValue);
            continue;
        }


        if (isMajor) {
            item = item.erase(0, 2);
        } else {
            item = item.erase(0, 1);
        }

        int8_t pitch = std::stoi(item);
        pitch += 2; // the Midi values start at -2 pitch

        uint8_t noteValue = pitch * 11 + note;
        if(isMajor){
            noteValue++;
        }

        if(noteValue > 127){
            printf("invalid note Value %i", noteValue);
            continue;
        }

        parsedNoteValues->push_back(noteValue);
    }


    return std::vector<int>();
}


std::vector<std::string> *MidiStringParser::splitStringBySpace(const std::string &input) {
    auto *strings = new std::vector<std::string>;
    unsigned long lastPos = 0;
    auto spacePos = input.find(' ', lastPos);

    // move to first actual character, otherwise there will be empty strings in the vector
    if (spacePos == 0) {
        while (input[lastPos] == ' ') {
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
    if (lastPos != input.length()) {
        auto substring = input.substr(lastPos, input.length() - lastPos);
        strings->push_back(substring);
    }

    return strings;
}
