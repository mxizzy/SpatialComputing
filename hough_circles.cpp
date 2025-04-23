#include "opencv2/imgproc.hpp"
#include <opencv2/highgui.hpp>
using namespace cv;

int main(int argc, char** argv)
{

    Mat image;
    image = imread("Media.jpg", IMREAD_COLOR);
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    medianBlur(gray, gray, 5);
    vector<Vec3f> circles;
    HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1,
                 150,  // change this value to detect circles with different distances to each other
                 100, 30, 1, 300 // change the last two parameters
                 // (min_radius & max_radius) to detect larger circles
    );
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle( image, center, 1, Scalar(0,100,100), 3, 8);
        // circle outline
        int radius = c[2];
        circle( image, center, radius, Scalar(255,0,255), 3, 8);
    }
    imshow("detected circles", image);
    waitKey();
    return EXIT_SUCCESS;
}
