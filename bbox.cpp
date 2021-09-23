#include <stdio.h>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, char *argv[])
{
    if (argc < 6)
    {
        printf("Usage: %s img tl_x tl_y width height\n", argv[0]);
    }

    cv::Mat img;
    std::string imgfile = std::string(argv[1]);
    std::string &outfile = imgfile; // overwrite
    cv::Point tl(atoi(argv[2]), atoi(argv[3]));
    cv::Point br(atoi(argv[2]) + atoi(argv[4]), atoi(argv[3]) + atoi(argv[5]));
    cv::Scalar red(0, 0, 255);
    int thickness = 2;

    img = cv::imread(imgfile);
    cv::rectangle(img, tl, br, red, thickness);
    cv::imwrite(outfile, img);

    return 0;
}
