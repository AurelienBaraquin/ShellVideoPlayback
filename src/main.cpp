#include <opencv2/opencv.hpp>
#include <iostream>
#include <ncurses.h>

void init_ncurses()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    start_color();
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cout << "Usage: " << av[0] << " <video_path>" << std::endl;
        return -1;
    }

    // init_ncurses();

    cv::VideoCapture cap(av[1]);
    if (!cap.isOpened()) {
        std::cout << "Cannot open video file: " << av[1] << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty())
            break;

        // Go through each pixel of the frame
        for (int y = 0; y < frame.rows; y++) {
            for (int x = 0; x < frame.cols; x++) {
                cv::Vec3b color = frame.at<cv::Vec3b>(cv::Point(x, y));
                // color[0], color[1], color[2] are B, G, R respectively
            }
        }
    }

}
