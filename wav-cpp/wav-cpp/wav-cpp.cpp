#include <iostream>
#include <cmath>

const int SAMPLE_RATE = 44100;
const float PI = 3.14159;

class SineOscillator {
    float frequency;
    float amplitude;
    float angle = 0.0f;

public:
    SineOscillator(float theFrequency, float theAmplitude): frequency(theFrequency), amplitude(theAmplitude) {}
    float process() {
        float sample = amplitude * sin(angle);
        angle += 2 * PI * frequency / SAMPLE_RATE;
        return sample;
    }
};

int main()
{
    std::cout << "Hello World!\n";
}
