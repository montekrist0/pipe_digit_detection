#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudafilters.hpp>
#include <opencv2/cudabgsegm.hpp>
#include <opencv2/cudacodec.hpp>
#include <opencv2/cudaobjdetect.hpp>
#include <opencv2/cudaoptflow.hpp>
#include <opencv2/cudastereo.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudafeatures2d.hpp>

#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/imgproc.hpp>
#include <C:\Qt\MyProjects\img_proc\profile.h>
#include <fstream>
#include <iomanip>
#include <utility>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QResizeEvent>

using namespace cv;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateImage(cv::Mat& img);
    void updateSubImage(cv::Mat &img);
    void updateEdgesImage(cv::Mat &img);
protected:
    void resizeEvent(QResizeEvent* e);
private slots:
    void on_uploadOriginImgButton_clicked();

    void on_uploadGrayImgButton_clicked();

    void on_uploadBinaryImgButton_clicked();

    void on_thresholdSlider_valueChanged(int value);

    void on_morphFilterButton_clicked();

    void on_pushButton_clicked();

    void on_filenameBox_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

    void on_morphFilterButton_3_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_findEdges_clicked();

    void on_applyAllAndFindEdges_clicked();

private:
    cv::Mat original_image;
    cv::Mat imageBlurred;
    cv::Mat imageGray;
    cv::Mat imageGrayEqualized;
    cv::Mat imageBinary;
    cv::Mat imageBinaryMorph;
    QImage qImg;
    cuda::GpuMat imgGpu;
    cuda::GpuMat imgGpuBlurred;

    cuda::GpuMat imgGpuGray;
    cuda::GpuMat imgGpuGrayEqualized;
    cuda::GpuMat imgGpuBinary;
    cuda::GpuMat imgGpuBinaryMorph;

    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsScene* scene2;
    QGraphicsScene* edgesScene;
    QVector<string> fileNames{
        "resources/IMG_2906.JPG",
        "resources/IMG_2907.JPG",
        "resources/IMG_2908.JPG",
        "resources/IMG_2909.JPG",
        "resources/IMG_2910.JPG",
        "resources/IMG_2911.JPG",
        "resources/thread/IMG_2922_cropped.jpg",
        "resources/thread/IMG_2924_cropped.jpg",
        "resources/thread/IMG_2920_cropped.jpg",
        "resources/thread/thread_light.jpg",
        "resources/thread/thread_light_with_defect.jpg",
        "resources/thread/thread_light_with_defect2.jpg",
        "resources/thread/thread_light_with_defect3.jpg",
        "resources/thread/IMG_2994.JPG",
        "resources/thread/IMG_2995.JPG",
        "resources/thread/IMG_2996.JPG",
        "resources/thread/IMG_2997.JPG",
        "resources/thread/IMG_2998.JPG",
        "resources/thread/IMG_2999.JPG",
        "resources/thread/IMG_3001.JPG",
        "resources/thread/IMG_3002.JPG",
        "resources/thread/IMG_3003.JPG",
        "resources/thread/IMG_3004.JPG"
    };


    const string img_path = "resources/IMG_2906.JPG";
    const string img_path_thread = "resources/thread/IMG_2922_cropped.jpg";
    const string img_path_thread2 = "resources/thread/IMG_2924_cropped.jpg";
    const string img_path_thread3 = "resources/thread/IMG_2920_cropped.jpg";


};

#endif // MAINWINDOW_H
