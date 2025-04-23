// C++ program for the above approach
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// Driver code
int main(int argc, char** argv)
{
    // Read the image file as
    // imread("default.jpg");
    VideoCapture cap("/dev/video0");

    // Error Handling
    if (!cap.isOpened()) {
        cout << "video "
        << "Not Found" << endl;

        // wait for any key press
        cin.get();
        return -1;
    }

    while(1){
    Mat frame;
    cap >> frame;

    if (frame.empty())
        break;
    // Show Image inside a window with
    // the name provided
    imshow("Window Name", frame);
    // Wait for any keystroke
    waitKey(0);
    return 0;
    };
}
