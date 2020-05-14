#include "utilities.h"
#include "lodepng/lodepng.h"
#include <fstream>
#include <QDebug>
#include <complex>


uint8_t calculateMandelbrot(const unsigned int &iterations,
                            const unsigned int &zoom, const double &re,
                            const double &im, const double &xCoordinate,
                            const double &yCoordinate,
                            const unsigned int &imageSize,
                            const unsigned int maxIterations)
{
        // z = z^2 + c, determines if a single complex number (pixel) is in the
        // mandelbrot set.
        int currentIteration = 1;

        // Convert the current pixel to a complex number.
        // Re and Im are multiplied by 4 to scale the image properly. Offset -2
        // centers the image.
        std::complex<long double> z(0, 0);
        std::complex<long double> c(re*(4/zoom)/(double)imageSize +
                                    (xCoordinate - (2/zoom)),
                                    im*(4/zoom)/(double)imageSize +
                                    (-yCoordinate - (2/zoom)));

        // The complex number is not in the set if it escapes to infinity.
        while (abs(z) < 2 && currentIteration <= maxIterations) {

            z = pow(z,2) + c;
            currentIteration++;
        }

        // Returns a color value for a single pixel.
        if (currentIteration < maxIterations)
            return 255*currentIteration/maxIterations;
        else return 0;
}
