#include <iostream>
#include <cmath>
#include <fstream>

const int SAMPLE_RATE = 44100;
const float PI = 3.14159;
const int BIT_DEPTH = 16;

class SineOscillator {
    float frequency;
    float amplitude;
    float angle = 0.0f;
    float offset;

public:
    SineOscillator(float theFrequency, float theAmplitude): frequency(theFrequency), amplitude(theAmplitude) {
        offset = PI * frequency / SAMPLE_RATE;
    }
    float process() {
        float sample = amplitude * sin(angle);
        angle += offset;
        return sample;
    }
};

void write(std::ofstream& file, int value, int size) {
    file.write(reinterpret_cast<const char *>(&value), size);
}

int main() {
    int duration = 2;
    std::ofstream audioFile;
    audioFile.open("waveform.wav", std::ios::binary);
    SineOscillator SineOscillator(440, 0.5);

    // header
    audioFile << "RIFF";
    audioFile << "----"; // placeholder
    audioFile << "WAVE";

    // format
    audioFile << "fmt ";
    write(audioFile, 16, 4);
    write(audioFile, 1, 4); // PCM uncompressed
    write(audioFile, 1, 2); // number of channels
    write(audioFile, SAMPLE_RATE, 4); // sample rate
    write(audioFile, SAMPLE_RATE * BIT_DEPTH / 8, 4); // bit rate
    write(audioFile, BIT_DEPTH / 8, 2); // block align
    write(audioFile, BIT_DEPTH, 2); // significant bits per sample

    // Data
    audioFile << "data";
    audioFile << "----"; // placeholder


    float maxAmplitude = pow(2, BIT_DEPTH - 1) - 1;
    for (int i = 0; i < SAMPLE_RATE * duration; ++i) {
        //audioFile << SineOscillator.process() << std::endl;
        float sample = SineOscillator.process();
        int intSample = static_cast<int>(sample * maxAmplitude);
        write(audioFile, intSample, 2);
    }

    std::cout << "Float size: " << sizeof(float) << std::endl;
    std::cout << "Int size: " << sizeof(int) << std::endl;

    audioFile.close();
}
