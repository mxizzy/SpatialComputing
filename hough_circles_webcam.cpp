#include "opencv2/imgproc.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat frame;
    VideoCapture cap;
    cap.open(0);
    if (!cap.isOpened())
    {
        cerr << "Unable to open camera";
        return -1;
    };

    cap >> frame;
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    medianBlur(gray, gray, 5);
    vector<Vec3f> circles;
    HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1,
                 150,  // change this value to detect circles with different distances to each other
                 100, 30, 10, 100 // change the last two parameters
                 // (min_radius & max_radius) to detect larger circles
    );
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle( frame, center, 1, Scalar(0,100,100), 3, 8);
        // circle outline
        int radius = c[2];
        circle( frame, center, radius, Scalar(0,255,0), 3, 8);
    }
    imshow("detected circles", frame);
    waitKey();
    return EXIT_SUCCESS;
}
