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

int main() {
    int duration = 2;
    std::ofstream audioFile;
    audioFile.open("waveform", std::ios::binary);
    SineOscillator SineOscillator(440, 0.5);

    float maxAmplitude = pow(2, BIT_DEPTH - 1) - 1;
    for (int i = 0; i < SAMPLE_RATE * duration; ++i) {
        //audioFile << SineOscillator.process() << std::endl;
        float sample = SineOscillator.process();
        int intSample = static_cast<int>(sample * maxAmplitude);
        audioFile.write(reinterpret_cast<char *>(&intSample), 2);
    }

    std::cout << "Float size: " << sizeof(float) << std::endl;
    std::cout << "Int size: " << sizeof(int) << std::endl;

    audioFile.close();
}
