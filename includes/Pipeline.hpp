#pragma once

#include <filesystem>
#include <opencv2/core/mat.hpp>

class Pipeline
{
    public:
        Pipeline(const std::string& path, uint8_t treshold);
        ~Pipeline() = default;

        void process();

    private:
        // PREPROCESSING
        void applyPerspectiveTransform(cv::Mat& img); // bird eye view
        void convertToHSL(cv::Mat& img);
        void applyThreshold(cv::Mat& img);
        void applyROI(cv::Mat& img);
        void writeResult(const std::string& filename, cv::Mat& img);

        std::filesystem::path asset_path_;
        uint8_t v_treshold_;
        int processed{0};

        // DETECTING
        //  Hough transform
        //  filter
        //  fit polynomial to lanes
};
