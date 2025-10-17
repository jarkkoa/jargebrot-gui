#include "utilities.h"
#include "lodepng/lodepng.h"
#include <fstream>
#include <iostream>
#include <QDebug>


uint8_t Jarge::calculateMandelbrot(unsigned int iterations, double zoom,
                                   long double re, long double im,
                                   long double xCoordinate,
                                   long double yCoordinate,
                                   unsigned int imageSize)
{
        // z = z^2 + c, determines if a single complex number (pixel) is in the
        // mandelbrot set.
        unsigned int i;
        long double temp;
        Jarge::Complex z = {0,0};
        Jarge::Complex c;

        // Convert the current pixel to a complex number.
        // Re and Im are multiplied by 4 to scale the image properly. Offset -2
        // centers the image.
        c.re = re*(4/zoom)/(long double)imageSize + (xCoordinate - (2/zoom));
        c.im = im*(4/zoom)/(long double)imageSize + (-yCoordinate - (2/zoom));


        for(i = 0; i < iterations; i++)
        {

            // (a + bi)^2 = a^2 + 2abi - b^2
            temp = z.re*z.re - z.im*z.im + c.re;
            z.im = 2 * z.re * z.im + c.im;
            z.re = temp;

            // abs(z) > 2.0 == abs(z)^2 > 4.0
            if (z.re*z.re + z.im*z.im > 4.0L)
            {
                return (uint8_t)(i * 255.0L / iterations);
            }
        }

        return 0;
}



void Jarge::drawPPM(uint8_t *pixels, const std::string &fileName,
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



void Jarge::drawPNG(std::vector<uint8_t>& imageBuffer, const std::string &fileName,
             unsigned int &imageSize) {

    //Encode the image
    unsigned error = lodepng::encode(fileName, imageBuffer,
                                     imageSize, imageSize, LCT_GREY);

    //if there's an error, display it
    if(error) std::cout << "encoder error " << error
                        << ": "<< lodepng_error_text(error) << std::endl;
}
