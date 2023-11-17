#include <opencv2/opencv.hpp>
#include <iostream>
#include <utility>
#include <ncurses.h>
#include "RGB.h"
#include <chrono>
#include <thread>

void init_ncurses()
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_RED);
    init_pair(3, COLOR_WHITE, COLOR_GREEN);
    init_pair(4, COLOR_WHITE, COLOR_YELLOW);
    init_pair(5, COLOR_WHITE, COLOR_BLUE);
    init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(7, COLOR_WHITE, COLOR_CYAN);
    init_pair(8, COLOR_WHITE, COLOR_WHITE);
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

    cv::VideoCapture cap(av[1]);
    if (!cap.isOpened()) {
        std::cout << "Cannot open video file: " << av[1] << std::endl;
        return -1;
    }

    init_ncurses();

    double fps = cap.get(cv::CAP_PROP_FPS);
    int delay = static_cast<int>(1000 / fps);

    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty())
            break;
        
        std::pair<int, int> src_size = getscrsize();

        double scale = std::min(static_cast<double>(src_size.second) / frame.cols,
                                static_cast<double>(src_size.first) / frame.rows);

        for (int y = 0; y < src_size.first; ++y) {
            for (int x = 0; x < src_size.second; ++x) {
                int img_y = static_cast<int>(y / scale);
                int img_x = static_cast<int>(x / scale);

                if (img_y >= frame.rows || img_x >= frame.cols)
                    continue;

                cv::Vec3b color = frame.at<cv::Vec3b>(cv::Point(img_x, img_y));
                int ncursesColorIndex = getClosestNcursesColorIndex({color[2], color[1], color[0]});
                attron(COLOR_PAIR(ncursesColorIndex));
                mvprintw(y, x, " ");
                attroff(COLOR_PAIR(ncursesColorIndex));
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));

        refresh();
    }

    endwin();
}
