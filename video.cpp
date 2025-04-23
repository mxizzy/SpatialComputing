#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;
int main(int, char**)
{
    Mat colorframe;
    Mat frame;
    Mat back;
    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    // open the default camera using default API
    // cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 0;             // 0 = open default camera
    // open selected camera using selected API
    cap.open(deviceID);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    BackgroundSubtractorMOG2 bg;
    vector<vector<Point> > contours;

    vector<Vec3f> circles;
    HoughCircles(frame, circles, CV_HOUGH_GRADIENT, 1,
                 0,  // change this value to detect circles with different distances to each other
                 100, 30, 1, 30 // change the last two parameters
                 // (min_radius & max_radius) to detect larger circles
    );
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
    << "Press any key to terminate" << endl;
    for (;;)
    {
        for( size_t i = 0; i < circles.size(); i++ )
        {
            Vec3i c = circles[i];
            Point center = Point(c[0], c[1]);
            // circle center
            circle( frame, center, 1, Scalar(0,100,100), 3);
            // circle outline
            int radius = c[2];
            circle( frame, center, radius, Scalar(255,0,255), 3);}
        // wait for a new frame from camera and store it into 'frame'
        bg.getBackgroundImage(back);
        cap.read(colorframe);
        cvtColor(colorframe, frame, CV_BGR2GRAY);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", frame);
        if (waitKey(5) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
