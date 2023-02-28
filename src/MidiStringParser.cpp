//
// Created by philip on 26.02.23.
//

#include <map>
#include <algorithm>
#include "MidiStringParser.h"

// reference: https://www.zem-college.de/midi/mc_taben.htm
std::vector<int8_t> *MidiStringParser::generateMidiInts(std::string input) {
    std::vector<std::string> *stringBySpace = splitStringBySpace(input);
    auto *parsedNoteValues = new std::vector<int8_t>;

    for (auto &item: *stringBySpace) {
        // convert string to upper characters
        std::transform(item.begin(), item.end(), item.begin(),
                       [](unsigned char c) { return std::toupper(c); });

        int8_t note = noteValues[item[0]];

        bool isMajor = item[1] == '#';

        if (item.length() == 1 || item.length() == 2) {

            int8_t noteValue = calculateNoteValue(note, isMajor, 0);
            parsedNoteValues->push_back(noteValue);
            continue;
        }

        if (isMajor) {
            item = item.erase(0, 2);
        } else {
            item = item.erase(0, 1);
        }

        int8_t pitch = std::stoi(item);

        int8_t noteValue = calculateNoteValue(note, isMajor, pitch);


        parsedNoteValues->push_back(noteValue);
    }


    return parsedNoteValues;
}


int8_t MidiStringParser::calculateNoteValue(int8_t note, bool major, int8_t pitch) {
    if (pitch > 8 || pitch < -2) {
        printf("pitch out of range: %i\n", pitch);
        return -1;
    }
    pitch += 2; // the Midi values start at -2 pitch

    int8_t noteValue = pitch * 12 + note;
    if (major && !noteIsMajor(note)) {
        printf("invalid major note");
        return -1;
    }

    if (major) {
        noteValue++;
    }

    if (noteValue > 127 || noteValue  < 0) {
        printf("note value out of range: %i\n", noteValue);
        return -1;
    }

    return noteValue;
}

std::vector<std::string> *MidiStringParser::splitStringBySpace(const std::string &input) {
    auto *strings = new std::vector<std::string>;
    unsigned long lastPos = 0;
    auto spacePos = input.find(SPLIT_DELIMITER, lastPos);

    // move to first actual character, otherwise there will be empty strings in the vector
    if (spacePos == 0) {
        while (input[lastPos] == SPLIT_DELIMITER) {
            lastPos++;
        }
        // rerun find to have a correct value in spacePos
        spacePos = input.find(SPLIT_DELIMITER, lastPos);
    }

    while (spacePos != std::string::npos) {
        auto substring = input.substr(lastPos, spacePos - lastPos);
        strings->push_back(substring);

        lastPos = spacePos + 1;
        spacePos = input.find(SPLIT_DELIMITER, lastPos);

    }

    // if we are not at the input end just take the rest of the input
    if (lastPos != input.length()) {
        auto substring = input.substr(lastPos, input.length() - lastPos);
        strings->push_back(substring);
    }

    return strings;
}

bool MidiStringParser::noteIsMajor(int8_t note) {
    return std::find(validMajorNotes.begin(), validMajorNotes.end(), note) != validMajorNotes.end();
}
