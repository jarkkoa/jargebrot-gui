#include "utilities.h"
#include "lodepng/lodepng.h"
#include <fstream>
#include <iostream>
#include <QDebug>
#include <complex>


uint8_t calculateMandelbrot(const unsigned int &iterations,
                            const double &zoom, const double &re,
                            const double &im, const double &xCoordinate,
                            const double &yCoordinate,
                            const unsigned int &imageSize)
{
        // z = z^2 + c, determines if a single complex number (pixel) is in the
        // mandelbrot set.
        unsigned int currentIteration = 1;

        // Convert the current pixel to a complex number.
        // Re and Im are multiplied by 4 to scale the image properly. Offset -2
        // centers the image.
        std::complex<long double> z(0, 0);
        std::complex<long double> c(re*(4/zoom)/(long double)imageSize +
                                    (xCoordinate - (2/zoom)),
                                    im*(4/zoom)/(long double)imageSize +
                                    (-yCoordinate - (2/zoom)));

        // The complex number is not in the set if it escapes to infinity.
        while (abs(z) < 2 && currentIteration <= iterations) {

            z = pow(z,2) + c;
            currentIteration++;
        }

        // Returns a color value for a single pixel.
        if (currentIteration < iterations)
            return 255*currentIteration/iterations;
        else return 0;
}



void drawPPM(uint8_t *pixels, const std::string &fileName,
             unsigned int &imageSize)
{
    // Draws a PPM image using color data from iterate()
    std::ofstream imageFile(fileName, std::ios::trunc);
    std::string line;
    std::string pixel_value;

    if (imageFile) {

        imageFile << "P3\n" << imageSize << " " << imageSize << "\n" << "255\n";

        for (unsigned int i = 0; i < imageSize*imageSize; ++i, ++pixels) {
            pixel_value = std::to_string(*pixels);
            line = pixel_value + " " + pixel_value + " " + pixel_value + "\n";
            imageFile << line;
        }

        imageFile.close();

    } else
        qDebug() << "Could not create image file. Check file permissions.";
}
