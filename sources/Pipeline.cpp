#include "Pipeline.hpp"
#include <opencv2/opencv.hpp>
#include <print>

using namespace cv;

std::optional<Mat> Pipeline::process(const std::string& path, int v_treshold)
{
    Mat img = imread(path, IMREAD_COLOR_BGR);

    if (img.empty())
        return std::nullopt;

    convertToHSL(img);
    applyThreshold(img, v_treshold);
    applyROI(img);
    // applyPerspectiveTransform(img);
    return std::make_optional<Mat>(img);
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
void Pipeline::applyThreshold(Mat& img, int v_treshold)
{
    Mat dst;
    threshold(img, img, v_treshold, std::numeric_limits<uint8_t>::max(),
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
