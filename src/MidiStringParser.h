//
// Created by philip on 26.02.23.
//

#ifndef MIDI2BIT_MIDISTRINGPARSER_H
#define MIDI2BIT_MIDISTRINGPARSER_H


#include <vector>
#include <string>

class MidiStringParser {
public:
    std::vector<int> generateMidiInts(std::string input);
private:
    std::vector<std::string> * splitStringBySpace(const std::string& input);
};


#endif //MIDI2BIT_MIDISTRINGPARSER_H
