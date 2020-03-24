// Convert YUV image to JPEG image

#include <iostream>
#include <string>
#include <unistd.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

int showUsage(void);
FILE* openImageFile(const char*);
/**
 * Get basename but without extension
 */
std::string getBasename(const std::string&);
long int getBlockSize(FILE*);

int main(int argc, char *argv[])
{
    int opt;
    unsigned int img_height, img_width;

    while ( (opt = getopt(argc, argv, "w:h:")) != -1)
    {
        switch (opt)
        {
            case 'w':
                img_width = atoi(optarg);
                break;
            case 'h':
                img_height = atoi(optarg);
                break;
            default:
                showUsage();
                exit(EXIT_FAILURE);
        }
    }
    if (optind >= argc)
    {
        showUsage();
        exit(EXIT_FAILURE);
    }

    for (int i = optind; i < argc; i++)
    {
        FILE *fp = openImageFile(argv[i]);
        std::string filename = getBasename(argv[i]);

        long int yuv_size = getBlockSize(fp);
        if (yuv_size == 0)
        {
            std::cout << "Error: YUV image has 0 block size" << std::endl;
            exit(EXIT_FAILURE);
        }

        char *rawYUV = (char *)malloc(sizeof(char) * yuv_size);
        std::size_t ret_size = fread(rawYUV, sizeof(char), yuv_size, fp);

        if(ret_size == yuv_size)
        {
            std::cout << "Processing YUV image " << filename << std::endl;;
        }
        else
        {
            std::cout << "Error: YUV image read error" << std::endl;
            exit(EXIT_FAILURE);
        }

        // TODO get rid of the dependency to opencv for conversion
        cv::Mat yuv_mat(cv::Size(img_width, img_height * 3 / 2), CV_8UC1, rawYUV);
        cv::Mat srcImg;
        srcImg.create(cv::Size(img_width, img_height), CV_8UC3);
        cv::cvtColor(yuv_mat, srcImg, CV_YUV420sp2BGR);

        if (srcImg.data == NULL)
        {
            std::cout << "Error: Can't convert YUV420sp to BGR" << std::endl;
            exit(EXIT_FAILURE);
        }
        cv::imwrite(filename+".jpg", srcImg);

        // Don't forget to clear environment
        free(rawYUV);
        fclose(fp);
    }

    std::cout << "All files done. Images saved." << std::endl;

    return EXIT_SUCCESS;
}

int showUsage(void)
{
    std::cout << "Error: Wrong number of arguments.\n";
    std::cout << "Usage:\n";
    std::cout << "\tprogram -w imgWidth -h imgHight list_yuv_images\n";
    std::cout << std::endl;

    return EXIT_FAILURE;
}

FILE* openImageFile(const char* fileName)
{
    FILE* fp;
    if ((fp = fopen(fileName, "r")) == NULL)
    {
        perror("fopen");
        return NULL;
    }
    return fp;
}

std::string getBasename(const std::string& path)
{
    std::string pathName = path;
    std::string::size_type slashPos = pathName.find_last_of('/');
    std::string::size_type dotPos = pathName.find_last_of('.');
    pathName = pathName.substr(slashPos + 1, dotPos - slashPos - 1);
    return pathName;
}

long int getBlockSize(FILE* yuvfp)
{
    long int blockSize;

    if(fseek(yuvfp, 0, SEEK_END) != 0)
    {
        return 0L;
    }
    if((blockSize = ftell(yuvfp)) == -1L)
    {
        return 0L;
    }
    fseek(yuvfp, 0, SEEK_SET);

    return blockSize;
}
