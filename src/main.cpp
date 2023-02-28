#include <vector> 
#include <iostream>
#include <MidiStringParser.h>

typedef unsigned char byte;

class MIDIVec: public std::vector<byte>{
public:
    template<class... Args>
    void addBytes(Args... data){
        for(const auto d : {data...}){
            push_back(d);
        }
    }
};

class MIDIData: public MIDIVec{
    private:
    uint64_t tempo;
    uint64_t delay = 0;

    public:

    MIDIData():tempo(1000000){
        // Add Track end
        addBytes(0x00);
        addBytes(0xFF);

        // ADD misc settings
        addBytes(0x58, 0x04, 0x04, 0x02, 0x18, 0x08, 0x00, 0xFF);

        // Add Tempo
        addBytes(0x51);
        addBytes(0x03);
        addBytes(tempo >> 16);
        addBytes(tempo >>  8);
        addBytes(tempo >>  0);
        addBytes(0x00);
    }

    void writeDelay()
    {
        uint64_t splitBytes;
        uint64_t firstByte;

        if(delay > 127){

            if(delay < 16384){
                firstByte = delay/128;
                splitBytes = firstByte + 128;
            }
            else{
                std::cout << "ERROR: delay can not be greater than 16383" << std::endl;
            }
            addBytes(splitBytes);
            splitBytes = delay - (128*firstByte);
            addBytes(splitBytes);
        }
        else{
            splitBytes = delay;
            addBytes(splitBytes);
        }
        delay = 0;
    }

    void addDelay(uint64_t delayAmount){
        delay += delayAmount;
    }
    
    void pressKey(bool keyPressed, int note, int pressure = 127, int channel = 0)
    {
        writeDelay();
        int64_t event = 0x80;
        if(keyPressed){
            event = 0x90;
        }

        if(0 <= channel <= 16){
            addBytes(event|channel);
        }else{
            std::cerr << "WARNING: The channel has to be between 0 and 16!" << std::endl;
            addBytes(0x80|0);
        }
        if(0 <= note <= 127){
            addBytes(note);
        }else{
            std::cerr << "ERROR: Given note does not exist";
        }
        if(0 < pressure <= 127){
            addBytes(pressure);
        }else{
            std::cerr << "WARNING: The Volume/Velocity can not bee higher then 127!\br"
                      << "Furthermore 0 equals to NoteOff!" << std::endl;
            addBytes(127);
        }
    }

    void changeSynth(int device){
        addBytes(0xC0);
        addBytes(device);
    }

};

class MIDIFile: public MIDIVec{
private:
    MIDIData* data;
public:

    MIDIFile(MIDIData* midiData): data(midiData)
    {
    }

    void packFile(){
        addBytes(
            0x4D, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06,
            0x00, 0x01, 0x00, 0x01, 0x03, 0xE8, 0x4D, 0x54,
            0x72, 0x6B
        );

        // Add File End
        data->addBytes(0x00, 0xFF, 0x2F, 0x00);

        // Add Data Size
        uint64_t dataSize = data->size();
        addBytes(dataSize >> 24,
                 dataSize >> 16,
                 dataSize >>  8,
                 dataSize >>  0);

        // Add Data to the File
        insert(end(), data->begin(), data->end());
    }

};

int main()
{
    MidiStringParser parser;
    const std::vector<int8_t> *noteVector;
    std::string input;
    std::cout << "Type in your song" << std::endl;
    std::getline(std::cin,  input);
    noteVector = parser.generateMidiInts(input);
    MIDIData* midiData = new MIDIData();
    MIDIFile midiFile(midiData);

    midiData->changeSynth(1);
    const int pressure = 111;
    const int release = 32;

    // A2 . B2

    for (int i = 0; i < noteVector->size(); i++){
        if(noteVector->at(i) != -1){
            midiData->pressKey(true, noteVector->at(i), pressure);
            midiData->addDelay(500);

            int j = 0;
            while(noteVector->size() > i+j+1 && noteVector->at(i + j + 1) == -2)
            {
                midiData->addDelay(500);
                j++;
            }
            midiData->pressKey(false, noteVector->at(i), release);
            i = i + j;
        }
        else{
            std::cerr << "ERROR: Wrong Inputs" << std::endl;
        }
    }

    midiFile.packFile();

    char const* songName = "myMidiSound.mid";
    FILE* fs = std::fopen(songName, "wb");
    if(fs == nullptr){
        printf("could not open file");
        exit(1);
    }
    std::fwrite(&midiFile.at(0), 1, midiFile.size(), fs);
    std::fclose(fs);

    return 0;
}