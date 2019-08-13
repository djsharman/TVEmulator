#include <stdio.h>
#include <vector>

using namespace std;

class tvParams {
    public: 
        static unsigned char getGamma(size_t postition);
        static unsigned int getGammaSize();
        static unsigned char getColor(size_t postition);
        static unsigned int getColorSize();
        static vector <unsigned char> gamma8;
        static vector <unsigned char> colors;

};