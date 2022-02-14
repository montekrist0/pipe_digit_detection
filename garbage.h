//#pragma once
//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <opencv2/core/cuda.hpp>
//#include <opencv2/cudaimgproc.hpp>
//#include <opencv2/cudaarithm.hpp>
//#include <opencv2/cudafilters.hpp>
//#include <opencv2/cudabgsegm.hpp>
//#include <opencv2/cudacodec.hpp>
//#include <opencv2/cudaobjdetect.hpp>
//#include <opencv2/cudaoptflow.hpp>
//#include <opencv2/cudastereo.hpp>
//#include <opencv2/cudawarping.hpp>
//#include <opencv2/cudafeatures2d.hpp>

//#include <opencv2/videoio/videoio.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/video.hpp>
//#include <opencv2/imgproc.hpp>
//#include <profile.h>
//#include <fstream>
//#include <iomanip>
//#include <utility>
//using namespace std::chrono;


//using namespace std;
//using namespace cv;

//void findNonZeroPixels(Mat& I, vector<vector<uint16_t>> &V)
//{

//    // accept only char type matrices
//    CV_Assert(I.depth() == CV_8U);
//    int channels = I.channels();
//    size_t nRows = I.rows;
//    size_t nCols = I.cols * channels;
//    if (I.isContinuous())
//    {
//        nCols *= nRows;
//        nRows = 1;
//    }
//    size_t i,j;
//    uchar* p;
//    if (!I.isContinuous())
//    {
//        for( i = 0; i < nRows; ++i)
//        {
//            p = I.ptr<uchar>(i);
//            for ( j = 0; j < nCols; ++j)
//            {
//                if (p[j]) {

//                }
//            }
//        }
//    }

//    size_t cols = I.cols;
//    for (size_t i = 0; i<V.size(); i++) {
//        V[i].reserve(cols);
//    }
//    for( i = 0; i < nRows; ++i)
//    {
//        p = I.ptr<uchar>(i);
//        for ( j = 0; j < nCols; j++)
//        {
//            if (p[j]) {
//                V[j/cols].push_back(j%cols);
//            }
//        }
//    }
//}

//void show_wait_destroy(const char* winname, cv::Mat img) {
//    imshow(winname, img);
//    moveWindow(winname, 500, 0);
//    waitKey(0);
//    destroyWindow(winname);
//}

//int kernelSize = 30;
//int sigmaColor = 25;
//int sigmaSpatial = 30;
//int lowThresh = 150;
//cuda::GpuMat imgTransposedGPU;
//Mat imgResized;
//cuda::GpuMat imgGpuOrigin;
//VideoCapture cap;
//string imagePath = "iphone/IMG_2820_Moment.jpg";//IMG_2810.JPG";
////string imagePath = "1.jpg";//iphone/IMG_2820_Moment.jpg";//IMG_2810.JPG";
//string videoPath = "iphone/IMG_2820_Trim.mp4";//IMG_2820_Trim.mp4";
//string videoPath2 = "iphone/IMG_2855_Trim.mp4";//IMG_2820_Trim.mp4";
//string videoPath3 = "iphone/IMG_2857_Trim.mp4";//IMG_2820_Trim.mp4";
//string videoPath4 = "iphone/VID_20211119_112303.mp4";//IMG_2820_Trim.mp4";
//string videoPath5 = "iphone/VID_20211123_145908_1.mp4";

//Mat img, result, erodeImg, imgThreshold;
//cuda::GpuMat imgGpu, imgGpuEqualized, imgGpuGray, imgGpuThreshHold,
//erodeImgGpu, erodeEqualImgGpu2, ROIgpuMAT, transposedGPU, transposeOrigin, bilateralEqualizedThreshold;


//void processImage2() {
//    cv::Mat RoiMat;
//    cv::Mat imgEqualized;
//    cv::Mat imggraybilateral;
//    {
//        LOG_DURATION("all process");
//        {
//            LOG_DURATION(" preparing. read upload resize... download");
//            {
//                LOG_DURATION("read");
//                img = imread(imagePath, IMREAD_GRAYSCALE);
//            }
//            {
//                LOG_DURATION("uploading");
//                imgGpu.upload(img);
//            }
//            cuda::transpose(imgGpu, transposedGPU);
//            ROIgpuMAT = transposedGPU.rowRange(transposedGPU.rows/4, transposedGPU.rows-transposedGPU.rows/4);
//            cuda::resize(ROIgpuMAT, ROIgpuMAT, Size(), 0.5,0.5);
//            ROIgpuMAT.download(imgResized);
//        }
//        vector<int> meanValuesByCols(imgResized.cols);
//        int avg = 0;
//        int sum = 0;
//        int maxElem = 0;
//        int maxElemIndex = 0;
//        {
//            LOG_DURATION("calc mean values for all cols");
//            for (size_t i = 0; i<imgResized.cols; i++) {
//                int curColmean = mean(imgResized.col(i))[0];
//                sum+=curColmean;
//                meanValuesByCols[i] = curColmean;
//                if (curColmean > maxElem) {
//                    maxElem = curColmean;
//                    maxElemIndex = i;
//                }
//            }
//            avg = sum/imgResized.cols;

//        }


//        {
//            LOG_DURATION("cvtColor bilateral thresh");
////            cuda::cvtColor(/*ROIgpuMAT*/, imgGpuGray, COLOR_BGR2GRAY);

//            cuda::bilateralFilter(ROIgpuMAT,ROIgpuMAT, 15, 25, 30,1);
//            ROIgpuMAT.download(imggraybilateral);
//            cuda::threshold(ROIgpuMAT, imgGpuThreshHold, 90, 240, THRESH_BINARY);
//            cuda::equalizeHist(ROIgpuMAT, ROIgpuMAT);
//            cuda::threshold(ROIgpuMAT, bilateralEqualizedThreshold, 90, 240, THRESH_BINARY);

//            ROIgpuMAT.download(imgEqualized);
//        }

//        imgGpuThreshHold.download(imgThreshold);
//        {
//            LOG_DURATION("morph Filter");
//            cv::Mat kernelGPU1 = Mat::ones(100,1, CV_8UC1);
//            cv::Mat kernelGPU2 = Mat::ones(1,3, CV_8UC1);

//            Ptr<cuda::Filter> morphFilter1 = cuda::createMorphologyFilter(MORPH_OPEN, CV_8UC1, kernelGPU1, Point(-1,-1), 1);
//            Ptr<cuda::Filter> morphFilter2 = cuda::createMorphologyFilter(MORPH_OPEN, CV_8UC1, kernelGPU2, Point(-1,-1), 1);

//            morphFilter1->apply(imgGpuThreshHold, erodeImgGpu);
//            morphFilter1->apply(bilateralEqualizedThreshold, erodeEqualImgGpu2);

////            morphFilter2->apply(erodeImgGpu,erodeImgGpu);

//            erodeImgGpu.download(erodeImg);
//        }

//        vector <vector<Point>> contours; //вектор объектов, найденных на принятом изобрабражении imgDil
//        vector<Vec4i>hierarchy;          // иерархия непонятно что за параметр, нужно узнавать. читать документацию
//        findContours(erodeImg, contours, hierarchy, RETR_LIST , CHAIN_APPROX_SIMPLE );
//        for (size_t i = 0; i<contours.size(); i++) {
//            int area = contourArea(contours[i]);    //находим площадь очередного контура
//            if (area > 100) drawContours(imgResized, contours, i,Scalar(100,40,50), 2);
//        }
//    }
//    cv::Mat imgEqualThreshEroded;
//    erodeEqualImgGpu2.download(imgEqualThreshEroded);
//    imshow("imgEqualThreshEroded", imgEqualThreshEroded);

//    imshow("imgThreshold", imgThreshold);
//    imshow("image", imgResized);
//    imshow("erodeImg", erodeImg);
//    imshow("equalized image", imgEqualized);
//    imshow("imggraybilateral",imggraybilateral);

//    waitKey(0);
//    int a = 0;
//}


//void GPUVideoCaptureWithMyAlg(){

//    cap.open(videoPath);
//    int sum = 0;
//    int col = 0;
//    int avg = 0;
//    while(cap.read(img)){

//        auto start = getTickCount();
//        cuda::GpuMat imgTransposedGPU;
//        Mat imgResized, imgResizedTransposed;
//        {
//            LOG_DURATION("upload resize cvtColor transpose");
//            imgGpu.upload(img);
//            cuda::resize(imgGpu, imgGpu, Size(), 0.5,0.5);
//            imgGpu.copyTo(ROIgpuMAT);
//            cuda::cvtColor(imgGpu, imgGpuGray, COLOR_BGR2GRAY);
//            cuda::transpose(imgGpuGray, imgTransposedGPU);
//            {
//                LOG_DURATION("CPU transpose");
//                imgGpu.download(imgResized);
//                cv::transpose(imgResized,imgResized);
//            }
//        }
//        {
//            LOG_DURATION("bilateral");
//            cuda::bilateralFilter(imgTransposedGPU,imgTransposedGPU, 15, 25, 30,1);
//        }
//        {
//            LOG_DURATION("threshold");
//            cuda::threshold(imgTransposedGPU, imgGpuThreshHold, 90, 200, THRESH_BINARY);
//        }
//        {
//            LOG_DURATION("eroded filter");
//            cv::Mat kernelGPU = Mat::ones(50,1, CV_8UC1);
//            cv::Mat kernelGPU2 = Mat::ones(1,10, CV_8UC1);
//            Ptr<cuda::Filter> morphFilter = cuda::createMorphologyFilter(MORPH_OPEN, CV_8UC1, kernelGPU, Point(-1,-1), 2);
//            Ptr<cuda::Filter> morphFilter2 = cuda::createMorphologyFilter(MORPH_OPEN, CV_8UC1, kernelGPU2, Point(-1,-1), 2);

//            morphFilter->apply(imgGpuThreshHold, erodeImgGpu);
//            morphFilter2->apply(erodeImgGpu, erodeImgGpu);
//            imgGpuThreshHold.download(result);
//        }
//        Mat erodeImg;
//        erodeImgGpu.download(erodeImg);
//        {
////            auto m = erodeImg.rowRange(0,100);
//            LOG_DURATION("assigning to 0");
//            for (auto x = erodeImg.ptr(); x != erodeImg.ptr(120); x++) {
//                *x = 0;
//            }
//            for (auto x = erodeImg.ptr(erodeImg.rows-120); x != erodeImg.dataend; x++) {
//                *x = 0;
//            }
//        }

//        {
//            LOG_DURATION("findContours");
//            vector <vector<Point>> contours; //вектор объектов, найденных на принятом изобрабражении imgDil
//            vector<Vec4i>hierarchy;          // иерархия непонятно что за параметр, нужно узнавать. читать документацию
//            findContours(erodeImg, contours, hierarchy, RETR_LIST , CHAIN_APPROX_SIMPLE );
//            for (size_t i = 0; i<contours.size(); i++) {

//                int area = contourArea(contours[i]);    //находим площадь очередного контура
//                if (area > 5000) {
//                    Rect boundRect = boundingRect(contours[i]);
//                    if (boundRect.width < 200 && boundRect.x != 0 && boundRect.br().x!=imgResized.cols) {
//                        rectangle(imgResized,boundRect.tl(), boundRect.br(), Scalar(0,0,255), 2); // прорисовываем прямоугольник вокруг найденных объектов
//                        putText(imgResized, "Weld", {boundRect.x, (boundRect.y)+boundRect.height/2}, FONT_HERSHEY_DUPLEX, 1, Scalar(10,100,255),2);
//                    }
//                }
//            }
//        }

//        auto end = getTickCount();
//        auto totalTime = (end - start) / getTickFrequency();
//        auto fps = 1 / totalTime;
//        cout <<  "totalTime - " << totalTime << "\n";
//        putText(imgResized, "FPS: " + to_string(int(fps)), Point(50, 50), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 255, 0), 2, false);
//        imshow("Image", imgResized);
//        imshow("erodeImg", erodeImg);
//        imshow("bilateral + threshold + laplacian filtered image", result);
//        if(waitKey(1) == 'q'){
//            break;
//        }


//    }
//    cap.release();
//    destroyAllWindows();
//}

//void GPUVideoCaptureWithMyAlg2(){

//    cap.open(videoPath5);
//    int numOfFrames = 0;
//    while(cap.read(img)){
//        numOfFrames++;
//        auto start = getTickCount();
//        cuda::GpuMat imgTransposedGPU;
//        //загружаем в память видеокарты очередной кадр
//        {
//            LOG_DURATION("upload resize cvtColor transpose");
//            imgGpu.upload(img);
//            //изменяем его размер
//            cuda::resize(imgGpu, imgGpu, Size(), 0.7,0.7);

//            //переводим из 3х канального BGR изображения в одноканальное (8 битовое) серое изображение
//            cuda::cvtColor(imgGpu, imgGpuGray, COLOR_BGR2GRAY);
//            //просто переворачиваем очередной кадр
////            cuda::transpose(imgGpuGray, imgTransposedGPU);
//        }
//        int cols = imgGpu.cols;
//        int rows = imgGpu.rows;
//        Mat imgResized;
//        imgGpu.download(imgResized);//360х640

//        {
//            LOG_DURATION("bilateral");
//            cuda::bilateralFilter(imgGpuGray,imgGpuGray, 15, 25, 30,1);
//        }
//        {
//            LOG_DURATION("threshold");

//            cuda::threshold(imgGpuGray, imgGpuThreshHold, 230, 240, THRESH_BINARY);

//        }
//        {
//            LOG_DURATION("eroded filter");
//            cv::Mat kernelGPU = Mat::ones(100,1, CV_8UC1);
//            cv::Mat kernelGPU2 = Mat::ones(1,5, CV_8UC1);
//            Ptr<cuda::Filter> morphFilter = cuda::createMorphologyFilter(MORPH_OPEN, CV_8UC1, kernelGPU, Point(-1,-1), 2);
//            Ptr<cuda::Filter> morphFilter2 = cuda::createMorphologyFilter(MORPH_OPEN, CV_8UC1, kernelGPU2, Point(-1,-1), 2);

//            morphFilter->apply(imgGpuThreshHold, erodeImgGpu);
//            morphFilter2->apply(erodeImgGpu, erodeImgGpu);
//            imgGpuThreshHold.download(result);
//        }



//        auto end = getTickCount();
//        auto totalTime = (end - start) / getTickFrequency();
//        auto fps = 1 / totalTime;
//        cout <<  "totalTime - " << totalTime << "\n";
//        putText(imgResized, "FPS: " + to_string(int(fps)), Point(50, 50), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 255, 0), 2, false);
//        Mat erodeImg;
//        erodeImgGpu.download(erodeImg);

//        {
//            LOG_DURATION("findContours");
//            vector <vector<Point>> contours; //вектор объектов, найденных на принятом изобрабражении imgDil
//            vector<Vec4i>hierarchy;          // иерархия непонятно что за параметр, нужно узнавать. читать документацию
//            findContours(erodeImg, contours, hierarchy, RETR_LIST , CHAIN_APPROX_SIMPLE );
//            for (size_t i = 0; i<contours.size(); i++) {

//                int area = contourArea(contours[i]);    //находим площадь очередного контура
//                if (area > 5000) {
//                    Rect boundRect = boundingRect(contours[i]);
//                    if (boundRect.width < 200 && boundRect.x != 0 && boundRect.br().x!=imgResized.cols) {
//                        rectangle(imgResized,boundRect.tl(), boundRect.br(), Scalar(0,0,255), 2); // прорисовываем прямоугольник вокруг найденных объектов
//                        putText(imgResized, "Weld", {boundRect.x, (boundRect.y)+boundRect.height/2}, FONT_HERSHEY_DUPLEX, 1, Scalar(10,100,255),2);
//                    }
//                }
//            }
//        }
//        imshow("bilateral + threshold + laplacian filtered image", result);
//        imshow("erodeImg", erodeImg);
//        imshow("Image", imgResized);
//        if(waitKey(20) == 'q'){
//            break;
//        }

//    }
//    cap.release();
//    destroyAllWindows();
//}

//void GPUVideoCaptureWithMyAlg3(){
//    cv::Mat equalizedImg;
//    cap.open(videoPath3);
//    int numOfFrames = 0;
//    while(cap.read(img)){
//        numOfFrames++;
//        auto start = getTickCount();
//        cuda::GpuMat imgTransposedGPU;
//        //загружаем в память видеокарты очередной кадр
//        {
//            LOG_DURATION("upload resize cvtColor transpose");
//            imgGpu.upload(img);
//            //изменяем его размер
//            cuda::resize(imgGpu, imgGpu, Size(), 0.5,0.5);

//            //переводим из 3х канального BGR изображения в одноканальное (8 битовое) серое изображение
//            cuda::cvtColor(imgGpu, imgGpuGray, COLOR_BGR2GRAY);
//            cuda::bilateralFilter(imgGpuGray,imgGpuGray, 5, 15, 15);
//            cuda::equalizeHist(imgGpuGray, imgGpuEqualized);
//            //просто переворачиваем очередной кадр
////            cuda::transpose(imgGpuGray, imgTransposedGPU);
//        }
//        Mat imgResized;
//        imgGpu.download(imgResized);//360х640
//        imgGpuEqualized.download(equalizedImg);
////        {
////            LOG_DURATION("bilateral");
////
////        }
////        {
////            LOG_DURATION("threshold");
////            cuda::threshold(imgGpuGray, imgGpuThreshHold, 170, 240, THRESH_BINARY);
////        }
////        {
////            LOG_DURATION("eroded filter");
////            cv::Mat kernelGPU = Mat::ones(150,1, CV_8UC1);
////            cv::Mat kernelGPU2 = Mat::ones(1,5, CV_8UC1);
////            Ptr<cuda::Filter> morphFilter = cuda::createMorphologyFilter(MORPH_OPEN, CV_8UC1, kernelGPU, Point(-1,-1), 2);
////            Ptr<cuda::Filter> morphFilter2 = cuda::createMorphologyFilter(MORPH_OPEN, CV_8UC1, kernelGPU2, Point(-1,-1), 2);

////            morphFilter->apply(imgGpuThreshHold, erodeImgGpu);
////            morphFilter2->apply(erodeImgGpu, erodeImgGpu);
////            imgGpuThreshHold.download(result);
////        }
////        auto end = getTickCount();
////        auto totalTime = (end - start) / getTickFrequency();
////        auto fps = 1 / totalTime;
////        cout <<  "totalTime - " << totalTime << "\n";
////        putText(imgResized, "FPS: " + to_string(int(fps)), Point(50, 50), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 255, 0), 2, false);
////        Mat erodeImg;
////        erodeImgGpu.download(erodeImg);
////        {
////            LOG_DURATION("findContours");
////            vector <vector<Point>> contours; //вектор объектов, найденных на принятом изобрабражении imgDil
////            vector<Vec4i>hierarchy;          // иерархия непонятно что за параметр, нужно узнавать. читать документацию
////            findContours(erodeImg, contours, hierarchy, RETR_LIST , CHAIN_APPROX_SIMPLE );
////            for (size_t i = 0; i<contours.size(); i++) {

////                int area = contourArea(contours[i]);    //находим площадь очередного контура
////                if (area > 5000) {
////                    Rect boundRect = boundingRect(contours[i]);
////                    if (boundRect.width < 200 && boundRect.x != 0 && boundRect.br().x!=imgResized.cols) {
////                        rectangle(imgResized,boundRect.tl(), boundRect.br(), Scalar(0,0,255), 2); // прорисовываем прямоугольник вокруг найденных объектов
////                        putText(imgResized, "Weld", {boundRect.x, (boundRect.y)+boundRect.height/2}, FONT_HERSHEY_DUPLEX, 1, Scalar(10,100,255),2);
////                    }
////                }
////            }
////        }
////        imshow("bilateral + threshold + laplacian filtered image", result);
////        imshow("erodeImg", erodeImg);
//        imshow("Image", imgResized);
//        imshow("Image equalized", equalizedImg);
//        if(waitKey(1) == 'q'){
//            break;
//        }

//    }
//    cap.release();
//    destroyAllWindows();
//}

//int main()
//{
////    processImage2();
//        GPUVideoCaptureWithMyAlg();

//    return 0;
//}
