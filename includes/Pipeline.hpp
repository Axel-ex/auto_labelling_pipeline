#pragma once

#include <filesystem>
#include <opencv2/core/mat.hpp>
#include <optional>

class Pipeline
{
    public:
        Pipeline(const std::string& path);
        ~Pipeline() = default;

        std::optional<cv::Mat> process(const std::string& path, int v_treshold);

    private:
        // PREPROCESSING
        void applyPerspectiveTransform(cv::Mat& img); // bird eye view
        void convertToHSL(cv::Mat& img);
        //  convert to greyScale / HSV
        //  applyThreshold
        void applyThreshold(cv::Mat& img, int v_treshold);
        void applyROI(cv::Mat& img);

        std::filesystem::path asset_path;

        // DETECTING
        //  Hough transform
        //  filter
        //  fit polynomial to lanes
};
