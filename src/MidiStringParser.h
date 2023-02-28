//
// Created by philip on 26.02.23.
//

#ifndef MIDI2BIT_MIDISTRINGPARSER_H
#define MIDI2BIT_MIDISTRINGPARSER_H


#include <vector>
#include <string>
#include <map>

#define SPLIT_DELIMITER ' '

#define DEFAULT_PITCH 0

class MidiStringParser {
public:
    std::vector<int8_t> *generateMidiInts(std::string input);

private:
    static std::vector<std::string> *splitStringBySpace(const std::string &input);

    std::map<char, int8_t> noteValues = {
            {'C', 0},
            {'D', 2},
            {'E', 4},
            {'F', 5},
            {'G', 7},
            {'A', 9},
            {'B', 11},
    };

    std::vector<int8_t> validMajorNotes = {
            0, 2, 5, 7, 9
    };

    bool noteIsMajor(int8_t note);

    int8_t calculateNoteValue(int8_t note, bool major, int8_t pitch);
};


#endif //MIDI2BIT_MIDISTRINGPARSER_H
