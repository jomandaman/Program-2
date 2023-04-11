/**
 * @file Program2.cpp
 * 
 * This program demonstrates basic functionality of OpenCV methods for image processing tasks.
 * The program allows the user to apply edge detection (Canny) and image enhancement (embossing) on an image
 * using trackbars to control the parameters interactively.
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

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    // Step 1: Read two images
    Mat foreground = imread("foreground.jpg");
    Mat background = imread("background.jpg");

    if (foreground.empty() || background.empty()) {
        cerr << "Error: Unable to read input images." << endl;
        return -1;
    }

    // Step 2: Create a color histogram
    const int buckets = 4;
    int dims[] = {buckets, buckets, buckets};
    Mat hist(3, dims, CV_32S, Scalar::all(0));

    int bucketSize = 256 / buckets;

    for (int r = 0; r < foreground.rows; ++r) {
        for (int c = 0; c < foreground.cols; ++c) {
            Vec3b pixel = foreground.at<Vec3b>(r, c);
            int x = pixel[2] / bucketSize;
            int y = pixel[1] / bucketSize;
            int z = pixel[0] / bucketSize;

            hist.at<int>(x, y, z)++;
        }
    }

    // Step 3: Find the most common color
    int maxVotes = 0;
    int maxIndex[3] = {0, 0, 0};

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

    int cRed = maxIndex[0] * bucketSize + bucketSize / 2;
    int cGreen = maxIndex[1] * bucketSize + bucketSize / 2;
    int cBlue = maxIndex[2] * bucketSize + bucketSize / 2;
    Vec3b mostCommonColor(cBlue, cGreen, cRed); // determine the chroma key

    // Step 4: Replace pixels close to the most common color
    int threshold = bucketSize / 2;

    for (int r = 0; r < foreground.rows; ++r) {
        for (int c = 0; c < foreground.cols; ++c) {
            Vec3b fgPixel = foreground.at<Vec3b>(r, c);
            Vec3b bgPixel = background.at<Vec3b>(r % background.rows, c % background.cols);

            if (norm(fgPixel - mostCommonColor) <= threshold) {
                foreground.at<Vec3b>(r, c) = bgPixel;
            }
        }
    }

    // Step 5: Display and save the resulting image
    imshow("Overlay Image", foreground);
    imwrite("overlay.jpg", foreground);
    waitKey(0);

    return 0;
}

