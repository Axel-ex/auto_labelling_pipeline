#include "Pipeline.hpp"
#include "opencv2/core/utility.hpp"
#include <cstdlib>
#include <filesystem>
#include <format>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <ostream>

using namespace cv;

bool validateArgs(int argc, char** argv)
{
    if (argc != 3)
    {
        std::println(std::cerr, "./prog <path_to_folder> <treshold>");
        return false;
    }
    int treshold = std::atoi(argv[2]);
    if (treshold < 0 || treshold > 255) // NOLINT
        return false;

    return true;
}

int main(int argc, char** argv)
{

    if (!validateArgs(argc, argv))
        return EXIT_FAILURE;

    std::string path = argv[1];
    int v_treshold = std::atoi(argv[2]);

    Pipeline process_pipe(path, v_treshold);
    process_pipe.process();

    // std::string image_path = samples::findFile(path, false);
    // if (image_path.empty())
    // {
    //     std::println(std::cerr, "ERROR: reading image: {} not found",
    //                  image_path);
    //     return EXIT_FAILURE;
    // }
    //
    // auto processed = process_pipe.process(image_path, v_treshold);
    // if (processed.has_value())
    // {
    //     imshow("processed image", processed.value());
    //     waitKey();
    //
    //     std::filesystem::path file_path(image_path);
    //     auto file_name = file_path.stem().string();
    //
    //     file_name = std::format("./processed/{}.jpg", file_name);
    //     imwrite(file_name, processed.value());
    // }
    // else
    // {
    //     std::println(std::cerr, "ERROR: processing image");
    //     return EXIT_FAILURE;
    // }

    return EXIT_SUCCESS;
}

// int main()
// {
//     // Load the image
//     Mat src = imread("assets/road.jpeg");
//     if (src.empty())
//     {
//         cout << "Error loading image" << endl;
//         return -1;
//     }
//
//     // get the size of the picture
//     int x = src.cols;
//     int y = src.rows;
//     println(std::cout, "size: {} x {}", x, y);
//     // Create a vector of points for your ROI (triangle in this case)
//     vector<Point> points;
//     points.push_back(Point(x / 2, y / 2)); // Top point
//     points.push_back(Point(x, y));         // Right point
//     points.push_back(Point(0, y * 0.75));  // Left point
//
//     // Create a black mask the same size as input image
//     Mat mask = Mat::zeros(src.size(), CV_8UC1);
//
//     // Fill the triangle in white on the mask
//     fillConvexPoly(mask, points, Scalar(255));
//
//     // Create output image (all black)
//     Mat result = Mat::zeros(src.size(), src.type());
//
//     // Copy only the ROI from source to result
//     src.copyTo(result, mask);
//
//     // Show both original and result
//     imshow("Result", result);
//     waitKey(0);
//
//     return 0;
// }
