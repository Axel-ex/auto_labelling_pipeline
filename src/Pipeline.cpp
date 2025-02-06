#include "Pipeline.hpp"
#include <opencv2/opencv.hpp>
#include <print>

using namespace cv;
using namespace std::chrono;

Pipeline::Pipeline(const std::string& path, uint8_t treshold)
    : asset_path_(path), v_treshold_(treshold)
{
}

void Pipeline::process()
{
    auto begin = steady_clock::now();

    for (const auto& dir_entry :
         std::filesystem::directory_iterator(asset_path_))
    {
        if (std::filesystem::is_directory(dir_entry))
            continue;

        Mat img = imread(dir_entry.path(), IMREAD_COLOR_BGR);
        convertToHSL(img);
        applyThreshold(img);
        applyROI(img);
        writeResult(dir_entry.path().stem().string(), img);

        processed++;
    }
    auto elapsed =
        duration_cast<milliseconds>(steady_clock::now() - begin).count();
    std::println(std::cout, "Processed {} pictures in {}ms", processed,
                 elapsed);
}

void Pipeline::applyPerspectiveTransform(Mat& img)
{
    std::array<Point, 4> src_vertices;
    std::array<Point, 4> dst_vertices;
    // int x = img.cols;
    // int y = img.rows;

    src_vertices.at(0) = Point(10, 30); // NOLINT
    (void)img;
    // define a rectangle and a trapezoid for the transformation
}

/**
 * @brief extract Value channel.
 *
 * convert to HSL (hue saturation value) and extract the value channel
 *
 * @param img
 */
void Pipeline::convertToHSL(Mat& img)
{
    std::vector<Mat> channels(3);

    cvtColor(img, img, COLOR_BGR2HSV);
    split(img, channels);
    img = channels.at(2);
}

/**
 * @brief Apply a treshold to the Value channel.
 *
 * This operation transforms all pixels above the treshold to the max value
 * (255), and all pixel below are blacked (0)
 *
 * @param img
 * @param v_treshold
 */
void Pipeline::applyThreshold(Mat& img)
{
    Mat dst;
    threshold(img, img, v_treshold_, std::numeric_limits<uint8_t>::max(),
              THRESH_BINARY);
}

void Pipeline::applyROI(Mat& img)
{
    // Apply a rectangular picture croping in the middle of the pictur
    int x = img.cols;
    int y = img.rows;

    auto roi = Rect(0, y / 2, x, y / 2);
    img = img(roi);
}

void Pipeline::writeResult(const std::string& filename, Mat& img)
{
    imwrite(std::format("processed/{}_processed.jpg", filename), img);
}
