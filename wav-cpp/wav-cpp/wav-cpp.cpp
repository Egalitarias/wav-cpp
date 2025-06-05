#include <iostream>
#include <cmath>
#include <fstream>

const int SAMPLE_RATE = 44100;
const float PI = 3.14159;

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
    audioFile.open("waveform");
    SineOscillator SineOscillator(440, 0.5);

    for (int i = 0; i < SAMPLE_RATE * duration; ++i) {
        audioFile << SineOscillator.process() << std::endl;
    }

    audioFile.close();
}
