#include <opencv2/opencv.hpp>
#include <iostream>
#include <utility>
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
    init_pair(1, -1, COLOR_BLACK);
    init_pair(2, -1, COLOR_RED);
    init_pair(3, -1, COLOR_GREEN);
    init_pair(4, -1, COLOR_YELLOW);
    init_pair(5, -1, COLOR_BLUE);
    init_pair(6, -1, COLOR_MAGENTA);
    init_pair(7, -1, COLOR_CYAN);
    init_pair(8, -1, COLOR_WHITE);
}

std::pair<int, int> getscrsize()
{
    int y, x;
    getmaxyx(stdscr, y, x);
    return std::make_pair(y, x);
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cout << "Usage: " << av[0] << " <video_path>" << std::endl;
        return -1;
    }

    init_ncurses();
    std::pair<int, int> src_size = getscrsize();

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
                mvprintw(frame.rows / src_size.first * y,
                         frame.cols / src_size.second * x,
                         " ");
            }
        }

        refresh();
    }

    endwin();
}
