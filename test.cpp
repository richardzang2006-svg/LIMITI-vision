#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 读取图片
    cv::Mat image = cv::imread("/root/LIMITI-vision/example.png");

    // 检查图片是否成功加载
    if (image.empty()) {
        std::cout << "无法加载图片！" << std::endl;
        return -1;
    }

    // 显示图片
    cv::imshow("Display Image", image);

    // 等待按键
    cv::waitKey(0);

    return 0;
}