#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene2 = new QGraphicsScene(this);
    edgesScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->edgesView->setScene(edgesScene);
    ui->edgesView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->subView->setScene(scene2);
    //    ui->subView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    original_image = cv::imread(fileNames[ui->filenameBox->currentIndex()]);
    imgGpu.upload(original_image);
    cuda::cvtColor(imgGpu, imgGpuGray, cv::COLOR_BGR2GRAY);
    imgGpuGray.download(imageGray);
    ui->filenameBox->setMaxCount(fileNames.size());
    ui->filenameBox->setMaxVisibleItems(fileNames.size());
    ui->threshValue->setText(QString::number(ui->thresholdSlider->value()));
    //    updateSubImage(original_image);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateImage(cv::Mat &img)
{
    for (auto x: scene->items()) {
        scene->removeItem(x);
    }

    if (img.channels() == 3){
        qImg = QImage(img.data, img.cols, img.rows, img.step, QImage::Format_BGR888);
    }
    else if (img.channels() == 1){
        qImg = QImage(img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
    }
    auto pixImg = QPixmap::fromImage(qImg);

    auto item = new QGraphicsPixmapItem(pixImg);
    scene->addItem(item);
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::updateSubImage(cv::Mat &img)
{
    for (auto x: scene2->items()) {
        scene2->removeItem(x);
    }

    if (img.channels() == 3){
        qImg = QImage(img.data, img.cols, img.rows, img.step, QImage::Format_BGR888);
    }
    else if (img.channels() == 1){
        qImg = QImage(img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
    }
    auto pixImg = QPixmap::fromImage(qImg);

    auto item = new QGraphicsPixmapItem(pixImg);
    scene2->addItem(item);
    ui->subView->fitInView(scene2->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::updateEdgesImage(cv::Mat &img)
{
    for (auto x: edgesScene->items()) {
        edgesScene->removeItem(x);
    }

    if (img.channels() == 3){
        qImg = QImage(img.data, img.cols, img.rows, img.step, QImage::Format_BGR888);
    }
    else if (img.channels() == 1){
        qImg = QImage(img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
    }
    auto pixImg = QPixmap::fromImage(qImg);

    auto item = new QGraphicsPixmapItem(pixImg);
    edgesScene->addItem(item);
    ui->edgesView->fitInView(edgesScene->sceneRect(), Qt::KeepAspectRatio);

}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    qDebug() << "window size " << e->size();
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    ui->edgesView->fitInView(edgesScene->sceneRect(), Qt::KeepAspectRatio);
}


void MainWindow::on_uploadOriginImgButton_clicked()
{
    if (original_image.empty()) {
        qDebug() << "cant read an image";
        return;
    }
    original_image = cv::imread(fileNames[ui->filenameBox->currentIndex()]);
    imgGpu.upload(original_image);
    cuda::cvtColor(imgGpu, imgGpuGray, cv::COLOR_BGR2GRAY);
    imgGpuGray.download(imageGray);
    imgGpuBinaryMorph.data = NULL;
    updateImage(original_image);
}



void MainWindow::on_uploadGrayImgButton_clicked()
{
    cuda::cvtColor(imgGpu, imgGpuGray, cv::COLOR_BGR2GRAY);
    imgGpuGray.download(imageGray);
    qDebug()<< "imgGpuGray cols: " << imgGpuGray.cols << ", imgGpuGray rows: " << imgGpuGray.rows;
    updateImage(imageGray);

}

void MainWindow::on_uploadBinaryImgButton_clicked()
{
    cuda::cvtColor(imgGpu, imgGpuGray, cv::COLOR_BGR2GRAY);
    imgGpuGray.download(imageGray);
    int low_threshold = ui->thresholdSlider->value();
    cuda::threshold(imgGpuGray, imgGpuBinary, low_threshold, 255, THRESH_BINARY);
    imgGpuBinary.download(imageBinary);
    updateImage(imageBinary);
}


void MainWindow::on_thresholdSlider_valueChanged(int value)
{
    on_uploadBinaryImgButton_clicked();
    ui->threshValue->setText(QString::number(value));
}

void MainWindow::on_morphFilterButton_clicked()
{
    int rows = ui->rowSpinBox->value();
    int cols = ui->colSpinBox->value();
    int morphOperation = ui->morphFilterType->currentIndex();
    cv::Mat kernelGPU1 = Mat::ones(rows,cols, CV_8UC1);
    //    cv::Mat kernelGPU2 = Mat::ones(1,21, CV_8UC1);
    Ptr<cuda::Filter> morphFilter1 = cuda::createMorphologyFilter(morphOperation, CV_8UC1, kernelGPU1, Point(-1,-1), 1);
    //    Ptr<cuda::Filter> morphFilter2 = cuda::createMorphologyFilter(MORPH_DILATE, CV_8UC1, kernelGPU2, Point(-1,-1), 2);
    //    Ptr<cuda::Filter> morphFilter3 = cuda::createMorphologyFilter(MORPH_ERODE, CV_8UC1, kernelGPU2, Point(-1,-1), 1);
    auto x = imgGpuBinaryMorph.data;
    if (!imgGpuBinaryMorph.data) {
        morphFilter1->apply(imgGpuBinary, imgGpuBinaryMorph);
    }
    else {
        morphFilter1->apply(imgGpuBinaryMorph, imgGpuBinaryMorph);
    }
    //    morphFilter2->apply(imgGpu, imgGpu);
    imgGpuBinaryMorph.download(imageBinaryMorph);
    updateImage(imageBinaryMorph);
}

void MainWindow::on_pushButton_clicked()
{
    cuda::bilateralFilter(imgGpu,imgGpuBlurred, 15, 25, 30,1);
    imgGpuBlurred.download(original_image);
    updateImage(original_image);
}

void MainWindow::on_filenameBox_currentIndexChanged(int index)
{
    original_image = cv::imread(fileNames[index]);
    imgGpu.upload(original_image);
    cuda::cvtColor(imgGpu, imgGpuGray, cv::COLOR_BGR2GRAY);
    imgGpuGray.download(imageGray);
    updateSubImage(original_image);
}

void MainWindow::on_pushButton_2_clicked()
{
    imgGpuBinaryMorph.data = NULL;
    imageBinaryMorph.data = NULL;
    updateImage(imageBinary);
}

void MainWindow::on_morphFilterButton_3_clicked()
{
    int rows = ui->rowSpinBox_3->value();
    int cols = ui->colSpinBox_3->value();
    int morphOperation = ui->morphFilterType_3->currentIndex();
    cv::Mat kernelGPU1 = Mat::ones(rows,cols, CV_8UC1);
    //    cv::Mat kernelGPU2 = Mat::ones(1,21, CV_8UC1);
    Ptr<cuda::Filter> morphFilter1 = cuda::createMorphologyFilter(morphOperation, CV_8UC1, kernelGPU1, Point(-1,-1), 1);
    //    Ptr<cuda::Filter> morphFilter2 = cuda::createMorphologyFilter(MORPH_DILATE, CV_8UC1, kernelGPU2, Point(-1,-1), 2);
    //    Ptr<cuda::Filter> morphFilter3 = cuda::createMorphologyFilter(MORPH_ERODE, CV_8UC1, kernelGPU2, Point(-1,-1), 1);
    auto x = imgGpuBinaryMorph.data;
    if (!imgGpuBinaryMorph.data) {
        morphFilter1->apply(imgGpuBinary, imgGpuBinaryMorph);
    }
    else {
        morphFilter1->apply(imgGpuBinaryMorph, imgGpuBinaryMorph);
    }
    //    morphFilter2->apply(imgGpu, imgGpu);
    imgGpuBinaryMorph.download(imageBinaryMorph);
    updateImage(imageBinaryMorph);
}

void MainWindow::on_pushButton_3_clicked()
{
    if (imageBinaryMorph.data) {
        updateImage(imageBinaryMorph);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    if (imgGpuGray.size() != imgGpu.size()) {
        cuda::cvtColor(imgGpu, imgGpuGray, cv::COLOR_BGR2GRAY);
        imgGpuGray.download(imageGray);
    }
    cuda::equalizeHist(imgGpuGray, imgGpuGray);
    imgGpuGray.download(imageGray);
    updateImage(imageGray);
}

void MainWindow::on_pushButton_5_clicked()
{
    cv::Size kernel_size(ui->gausKernelSize->value(), ui->gausKernelSize->value());
    //    cv::Mat kernelGPU1 = Mat::ones(kernel_size,kernel_size, CV_8UC1);
    auto origin_type = imgGpu.type();
    Ptr<cuda::Filter> gaussFilter = cuda::createGaussianFilter(origin_type, origin_type, kernel_size, 1);//, kernelGPU1, Point(-1,-1), 1);
    gaussFilter->apply(imgGpu, imgGpu);
    imgGpu.download(original_image);
    updateImage(original_image);
}

//bool operator<(Rect &lhs, Rect &rhs) {
//    return lhs.height < rhs.height;
//}

//int findMedianHeight(vector<Rect> &v) {
//    size_t n = v.size() / 2;
//    nth_element(v.begin(), v.begin()+n, v.end());
//    return v[n].height;
//}

void MainWindow::on_findEdges_clicked()
{
    cv::Mat original_image_with_contours;
    original_image.copyTo(original_image_with_contours);
    vector<Rect> boundingRects;
    vector <vector<Point>> contours; //вектор объектов, найденных на принятом изобрабражении imgDil
    vector<Vec4i>hierarchy;          // иерархия непонятно что за параметр, нужно узнавать. читать документацию
    findContours(imageBinaryMorph, contours, hierarchy, RETR_EXTERNAL , CHAIN_APPROX_SIMPLE );
    for (size_t i = 0; i<contours.size(); i++) {

        int area = contourArea(contours[i]);    //находим площадь очередного контура
        if (area > 5000) {
            Rect boundRect = boundingRect(contours[i]);
            auto ratio = (float)boundRect.height/boundRect.width;
            if (boundRect.width > 300 && boundRect.height > 600 /*&& (ratio > 1.5 && ratio < 3)*/) {
                rectangle(original_image_with_contours,boundRect.tl(), boundRect.br(), Scalar(0,0,255), 10); // прорисовываем прямоугольник вокруг найденных объектов
                putText(original_image_with_contours, "digit", {boundRect.x, (boundRect.y)}, FONT_HERSHEY_DUPLEX, 3, Scalar(10,100,255),2);
                boundingRects.push_back(boundRect);
            }
        }
    }


    int a = 0;
    updateEdgesImage(original_image_with_contours);
}

void MainWindow::on_applyAllAndFindEdges_clicked()
{
    //загружаем оригинальное изображение
    original_image = cv::imread(fileNames[ui->filenameBox->currentIndex()]);
    imgGpu.upload(original_image);

    //применяем размытие 4-5 раз
    cv::Size kernel_size(ui->gausKernelSize->value(), ui->gausKernelSize->value());
    //    cv::Mat kernelGPU1 = Mat::ones(kernel_size,kernel_size, CV_8UC1);
    auto origin_type = imgGpu.type();
    Ptr<cuda::Filter> gaussFilter = cuda::createGaussianFilter(origin_type, origin_type, kernel_size, 1);//, kernelGPU1, Point(-1,-1), 1);
    for (int i = 0; i<5; i++) gaussFilter->apply(imgGpu, imgGpu);

    //преобразовываем в серый
    cuda::cvtColor(imgGpu, imgGpuGray, cv::COLOR_BGR2GRAY);
    //    imgGpuGray.download(imageGray);

    //преобразовываем в бинарное
    cuda::threshold(imgGpuGray, imgGpuBinary, 173, 255, THRESH_BINARY);
    //применяем морфологические фильтры
    cv::Mat kernelGPU1 = Mat::ones(17,17, CV_8UC1);
    cv::Mat kernelGPU2 = Mat::ones(1,7, CV_8UC1);
    Ptr<cuda::Filter> morphFilter1 = cuda::createMorphologyFilter(MORPH_DILATE, CV_8UC1, kernelGPU1, Point(-1,-1), 2);
    Ptr<cuda::Filter> morphFilter2 = cuda::createMorphologyFilter(MORPH_ERODE, CV_8UC1, kernelGPU1, Point(-1,-1), 2);
    Ptr<cuda::Filter> morphFilter3 = cuda::createMorphologyFilter(MORPH_ERODE, CV_8UC1, kernelGPU2, Point(-1,-1), 2);
    morphFilter1->apply(imgGpuBinary, imgGpuBinaryMorph);
    morphFilter2->apply(imgGpuBinaryMorph, imgGpuBinaryMorph);
    morphFilter3->apply(imgGpuBinaryMorph, imgGpuBinaryMorph);


    imgGpuBinaryMorph.download(imageBinaryMorph);
    on_findEdges_clicked();


}
