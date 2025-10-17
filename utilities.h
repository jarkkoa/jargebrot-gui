#include <cstdint>
#include <string>
#include <vector>

#ifndef CALCULATIONS_H
#define CALCULATIONS_H


namespace Jarge
{
    struct Complex
    {
        long double re;
        long double im;
    };

    /**
     * @brief calculateMandelbrot Determines if a single pixel is in the Mandelbrot
     * set.
     * @param iterations
     * @param zoom
     * @param x
     * @param y
     * @return Color value of a single pixel
     */
    uint8_t calculateMandelbrot(unsigned int iterations, double zoom,
                                long double re, long double im,
                                long double xCoordinate,
                                long double yCoordinate,
                                unsigned int imageSize);

    /**
     * @brief writePNG Saves the image buffer into a PNG file by using LodePNG.
     * @param pixels Image buffer
     * @param fileName
     * @param imageSize
     */
    void drawPNG(std::vector<uint8_t>& imageBuffer, const std::string &fileName,
                 unsigned int &imageSize);

    void drawPPM(uint8_t *pixels, const std::string& fileName,
                 unsigned int& imageSize);
}



#endif // CALCULATIONS_H
