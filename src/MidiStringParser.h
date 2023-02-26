//
// Created by philip on 26.02.23.
//

#ifndef MIDI2BIT_MIDISTRINGPARSER_H
#define MIDI2BIT_MIDISTRINGPARSER_H


#include <vector>
#include <string>
#include <map>

class MidiStringParser {
public:
    std::vector<int> generateMidiInts(std::string input);

private:
    std::vector<std::string> *splitStringBySpace(const std::string &input);

    std::map<char, int> noteValues = {
            {'C', 0},
            {'D', 1},
            {'E', 2},
            {'F', 3},
            {'G', 4},
            {'A', 5},
            {'B', 6},
    };
};


#endif //MIDI2BIT_MIDISTRINGPARSER_H
