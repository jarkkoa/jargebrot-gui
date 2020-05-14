#include <cstdint>
#include <string>
#include <vector>

#ifndef CALCULATIONS_H
#define CALCULATIONS_H

/**
 * @brief calculateMandelbrot Determines if a single pixel is in the Mandelbrot
 * set.
 * @param iterations
 * @param zoom
 * @param x
 * @param y
 * @return Color value of a single pixel
 */
uint8_t calculateMandelbrot(const unsigned int &iterations,
                            const unsigned int &zoom, const double &re,
                            const double &im, const double &xCoordinate,
                            const double &yCoordinate,
                            const unsigned int &imageSize,
                            const unsigned int maxIterations);

/**
 * @brief writePNG Saves the image buffer into a PNG file by using LodePNG.
 * @param pixels Image buffer
 * @param fileName
 * @param imageSize
 */
void drawPNG(std::vector<uint8_t> pixels, const std::string& fileName,
              unsigned int& imageSize);

#endif // CALCULATIONS_H
