#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>

int main() {
    cv::VideoCapture camera(0);
    
    if (!camera.isOpened()) {
        std::cout << "无法打开摄像头！" << std::endl;
        return -1;
    }

    // 关键：明确设置MJPEG格式（和v4l2-ctl一样）
    int fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    camera.set(cv::CAP_PROP_FOURCC, fourcc);
    camera.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    camera.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    camera.set(cv::CAP_PROP_FPS, 30);
    camera.set(cv::CAP_PROP_BUFFERSIZE, 1);

    std::cout << "摄像头已打开，预热中..." << std::endl;
    
    // 预热摄像头
    cv::Mat frame;
    for (int i = 0; i < 50; i++) {
        camera.grab();
        usleep(50000);
    }
    
    std::cout << "开始实时显示，按 'q' 键退出..." << std::endl;
    
    // 实时显示
    int frameCount = 0;
    cv::Mat displayFrame;
    
    while (true) {
        if (!camera.read(frame)) {
            std::cout << "读取失败！" << std::endl;
            break;
        }
        
        if (frame.empty()) {
            std::cout << "帧为空！" << std::endl;
            break;
        }

        frameCount++;
        if (frameCount % 30 == 0) {
            std::cout << "已显示 " << frameCount << " 帧" << std::endl;
        }

        // 缩放到 1280x720 显示
        cv::resize(frame, displayFrame, cv::Size(1280, 720));

        // 显示帧
        cv::imshow("Camera", displayFrame);

        // 按 'q' 退出
        if (cv::waitKey(1) == 'q') {
            std::cout << "退出程序" << std::endl;
            break;
        }
    }
    
    camera.release();
    cv::destroyAllWindows();

    return 0;
}