/**
 * @file Program2.cpp
 * 
 * This program demonstrates the basic functionality of OpenCV methods for image processing tasks.
 * The program applies the chroma key effect on a foreground image, replacing a selected color
 * with a background image. The user can interactively control the threshold using a trackbar.
 * 
 * Comments posted throughout, some general thoughts at the bottom.
 * 
 * @author Josiah Zacharias
 * Contact: josiahz@uw.edu
 * UW 587 with Clark Olsen
*/

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

// Function prototype
void applyChromaKey(const Mat& foreground, const Mat& background, Mat& output, int threshold);

/**
 * onTrackbar function is called whenever the trackbar value changes.
 * 
 * @param threshold The current threshold value for the chroma key effect.
 * @param data A void pointer to the data, which includes the foreground, background, and output images.
 * 
 * Preconditions:
 * - The data pointer must point to a valid tuple containing the Mat objects for foreground, background, and output images.
 * - The foreground, background, and output images should have the same dimensions, but not necessarily
 * - The threshold value should be in the range [0, 255].
 * 
 * Postconditions:
 * - The chroma key effect will be applied to the foreground image using the current threshold value, and the result will be stored in the output image.
 * - The "Overlay Image" window will be updated to display the new output image.
 */
void onTrackbar(int threshold, void* data) {
    auto context = static_cast<tuple<Mat, Mat, Mat>*>(data);
    applyChromaKey(get<0>(*context), get<1>(*context), get<2>(*context), threshold);
    imshow("Overlay Image", get<2>(*context));
}

/**
 * @brief Main function of the Program2.
 * 
 * Reads foreground and background images, applies the chroma key effect with an adjustable threshold value, and displays the result.
 * 
 * @param[in] argc The number of arguments passed to the program
 * @param[in] argv Array of arguments passed to the program
 * 
 * Preconditions:
 * - Foreground and background images should be in JPG format and placed in the same directory as the executable.
 * - Foreground and background images should have the same dimensions, but not necessarily
 * 
 * Postconditions:
 * - The program will display the foreground image with the chroma key effect applied.
 * - The user can interactively adjust the threshold value using the "Threshold" trackbar.
 * - When the user closes the window, the final output image will be saved as "overlay.jpg" in the same directory as the executable.
 * - The program will return 0 if it completes successfully, or -1 if there's an error reading the input images.
 */
int main(int argc, char* argv[]) {
    // read images
    Mat foreground = imread("foreground.jpg");
    Mat background = imread("background.jpg");
    Mat output;

    // Check if input images are read correctly
    if (foreground.empty() || background.empty()) {
        cerr << "Error: Unable to read input images." << endl;
        return -1;
    }

    int threshold = 24; // set initial threshold 

    // Bundle foreground, background, and output images in a tuple to pass to the trackbar callback
    namedWindow("Overlay Image", WINDOW_AUTOSIZE);
    tuple<Mat, Mat, Mat> context(foreground, background, output);
    createTrackbar("Threshold", "Overlay Image", &threshold, 255, onTrackbar, &context);

     // Apply the chroma key effect with the initial threshold value and show
    applyChromaKey(foreground, background, output, threshold);
    imshow("Overlay Image", output);

    // Wait for user interaction to close and save
    waitKey(0);
    imwrite("overlay.jpg", output);
    return 0;
}

/**
 * @brief Apply chroma key effect to blend foreground and background images.
 *
 * @param foreground The foreground image (Mat).
 * @param background The background image (Mat).
 * @param output The output image with the chroma key effect applied (Mat).
 * @param threshold The threshold to determine pixel replacement (int).
 * 
 * Preconditions:
 * - Foreground and background images are non-empty and have the same type.
 * - Threshold is a non-negative integer.
 * 
 * Postconditions:
 * - Output image is generated with the chroma key effect applied.
 */
void applyChromaKey(const Mat& foreground, const Mat& background, Mat& output, int threshold) {
    // Create a color histogram
    const int buckets = 4;
    int dims[] = {buckets, buckets, buckets};
    Mat hist(3, dims, CV_32S, Scalar::all(0));

    int bucketSize = 256 / buckets;

    // Iterate through foreground pixels and update the histogram
    for (int r = 0; r < foreground.rows; ++r) {
        for (int c = 0; c < foreground.cols; ++c) {
            Vec3b pixel = foreground.at<Vec3b>(r, c);
            int x = pixel[2] / bucketSize;
            int y = pixel[1] / bucketSize;
            int z = pixel[0] / bucketSize;
            hist.at<int>(x, y, z)++;
        }
    }

    // Find the most common color
    int maxVotes = 0;
    int maxIndex[3] = {0, 0, 0};

    // Iterate through the histogram to find the maximum votes
    for (int x = 0; x < buckets; ++x) {
        for (int y = 0; y < buckets; ++y) {
            for (int z = 0; z < buckets; ++z) {
                int votes = hist.at<int>(x, y, z);
                if (votes > maxVotes) {
                    maxVotes = votes;
                    maxIndex[0] = x;
                    maxIndex[1] = y;
                    maxIndex[2] = z;
                }
            }
        }
    }

    // Calculate the most common color's RGB values
    int cRed = maxIndex[0] * bucketSize + bucketSize / 2;
    int cGreen = maxIndex[1] * bucketSize + bucketSize / 2;
    int cBlue = maxIndex[2] * bucketSize + bucketSize / 2;
    Vec3b mostCommonColor(cBlue, cGreen, cRed);

    // Replace pixels close to the most common color
    output = foreground.clone();

    // Iterate through foreground pixels and replace with background pixels if needed
    for (int r = 0; r < foreground.rows; ++r) {
        for (int c = 0; c < foreground.cols; ++c) {
            Vec3b fgPixel = foreground.at<Vec3b>(r, c);
            // account for differently-sized background images
            Vec3b bgPixel = background.at<Vec3b>(r % background.rows, c % background.cols);

            if (norm(fgPixel - mostCommonColor) <= threshold) {
                output.at<Vec3b>(r, c) = bgPixel;
            }
        }
    }
}

/**
 * Some thoughts on the various odds and intricacies:
 * * The use of a color histogram with a limited number of buckets may not always represent the most common color perfectly. 
 * * The threshold value for the chroma key effect can be quite sensitive and depends on the color of the foreground image.
 * * If the background and foreground images are different sizes, it repeats the bckgrnd image to fit the output. 
 *   This may not always be the desired behavior, so additional functionality could be added to resize the background image to match the foreground.
 * * The chroma key effect in this project relies on a simple Euclidean distance between colors. More sophisticated methods or 
 *   additional user input could help improve the quality of the effect, such as adjusting the color space or adding noise reduction.
 *
 * Overall, this project demonstrates a simple and interactive way to experiment with the chroma key effect using OpenCV. 
 *   The use of trackbars and real-time feedback allows for quick adjustments and the possibility to explore different settings.
 */

