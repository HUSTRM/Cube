//
// Created by top on 19-1-2.
//

#include "CubeDetector.hpp"

CubeDetector::CubeDetector() {};

CubeDetector::~CubeDetector() {}

vector<Rect> CubeDetector::getROI(Mat &src, int s_max, int s_min) {
    std::cout << "getting ROI..." << std::endl;
    Mat musk, gray, blurred, canny, dilated;
    src.copyTo(musk);
    cvtColor(src, gray, CV_RGB2GRAY);
    GaussianBlur(gray, blurred, Size(15,15), 0);
    Canny(blurred, canny, 20, 40);
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(canny, dilated, element, Point(-1,-1), 2);
    vector<vector<Point>>contours;
    vector<Vec4i>hierarchy;
    findContours(dilated, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
    vector<Rect> rect;
    for(int i=0; i<contours.size(); i++){
        Rect rect_tmp = boundingRect(contours[i]);
        double s = rect_tmp.area();
        cout<<"Square area :"<<s<<"  hierarchy:"<<hierarchy[i][2]<<endl;
        rectangle(musk, rect_tmp.tl(), rect_tmp.br(), Scalar(0, 255, 0));
        if(hierarchy[i][2] == -1 && s>s_min && s<s_max){
            rect.push_back(rect_tmp);
        }
        imshow("musk", musk);
        waitKey(0);
    }
    sort(rect.begin(), rect.end(), comp);
    return rect;
}

int CubeDetector::Sum(Mat &src) {
    int counter = 0;
    //迭代器访问像素点
    Mat_<uchar>::iterator it = src.begin<uchar>();
    Mat_<uchar>::iterator itend = src.end<uchar>();
    for (; it != itend; ++it)
    {
        if ((*it)>0)
            counter += 1;
    }
    return counter;
}

string CubeDetector::this_face_color(FACE face, int isRotate) {
    //face.src = src;
    cout<<"Detecting this face color..."<<endl;
    char color_this_face[9];
    vector<Rect> ROI_rect = getROI(face.src, face.s_max, face.s_min);
    if(ROI_rect.size() != 9){
        cout<<"False to get the right number of the blocks."<<endl;
        cout<<"Please fix your auguments."<<endl;
        return "return false";
    }
    Mat imgHSV;
    vector<Mat> hsvSplit;
    cvtColor(face.src, imgHSV, COLOR_BGR2HSV);
    split(imgHSV, hsvSplit);
    equalizeHist(hsvSplit[2], hsvSplit[2]);
    merge(hsvSplit, imgHSV);
    inRange(imgHSV, Scalar(white.H_Low, white.S_Low, white.V_Low),
            Scalar(white.H_High, white.S_High, white.V_High), W_Thresholded);
    inRange(imgHSV, Scalar(red.H_Low, red.S_Low, red.V_Low),
            Scalar(red.H_High, red.S_High, red.V_High), R_Thresholded);
    inRange(imgHSV, Scalar(green.H_Low, green.S_Low, green.V_Low),
            Scalar(green.H_High, green.S_High, green.V_High), G_Thresholded);
    inRange(imgHSV, Scalar(blue.H_Low, blue.S_Low, blue.V_Low),
            Scalar(blue.H_High, blue.S_High, blue.V_High), B_Thresholded);
    inRange(imgHSV, Scalar(orange.H_Low, orange.S_Low, orange.V_Low),
            Scalar(orange.H_High, orange.S_High, orange.V_High), O_Thresholded);
    inRange(imgHSV, Scalar(yellow.H_Low, yellow.S_Low, yellow.V_Low),
            Scalar(yellow.H_High, yellow.S_High, yellow.V_High), Y_Thresholded);
    blue.color_thresh = B_Thresholded;
    white.color_thresh = W_Thresholded;
    green.color_thresh = G_Thresholded;
    orange.color_thresh = O_Thresholded;
    red.color_thresh = R_Thresholded;
    yellow.color_thresh = Y_Thresholded;
    colorV.push_back(blue);
    colorV.push_back(white);
    colorV.push_back(red);
    colorV.push_back(green);
    colorV.push_back(orange);
    colorV.push_back(yellow);
    namedWindow("[1]Cube", WINDOW_NORMAL);
    imshow("[1]Cube", face.src);
    namedWindow("[2]W_Thresholded", WINDOW_NORMAL);
    imshow("[2]W_Thresholded", W_Thresholded);
    namedWindow("[3]R_Thresholded", WINDOW_NORMAL);
    imshow("[3]R_Thresholded", R_Thresholded);
    namedWindow("[4]G_Thresholded", WINDOW_NORMAL);
    imshow("[4]G_Thresholded", G_Thresholded);
    namedWindow("[5]B_Thresholded", WINDOW_NORMAL);
    imshow("[5]B_Thresholded", B_Thresholded);
    namedWindow("[6]O_Thresholded", WINDOW_NORMAL);
    imshow("[6]O_Thresholded", O_Thresholded);
    namedWindow("[7]Y_Thresholded", WINDOW_NORMAL);
    imshow("[7]Y_Thresholded", Y_Thresholded);
    waitKey(0);
    for(auto item = colorV.begin(); item != colorV.end(); ++item){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                COLOR it = *item;
                Mat roi = it.color_thresh(ROI_rect[3*i+j]);
                int isColor = Sum(roi);
                cout<<"isColor:"<< isColor<<endl;
                if (isColor > 40) {
                    rectangle(face.src, ROI_rect[3 * i + j], Scalar(0, 255, 0));
                    putText(face.src, it.colorNameString, ROI_rect[3*i+j].tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0,255,0), 1);
                    color_this_face[3 * i + j] = it.colorCode;
                    imshow("color of each blocks", face.src);
                    waitKey(0);
                }
            }
        }
    }
    string str = color_this_face;
    string substring = str.substr(0,9);
    if(isRotate == 0) {return substring;}
    else {return Reverse(substring);}
}

void CubeDetector::separate(string fileName) {
    cout<<"Separating.."<<endl;
    Mat src = imread(fileName);
    Mat src_scaled ;
    resize(src, src_scaled, Size(800,452));
    Point2f OriPoint_l[3] = {left.lt, left.lb, left.rb};
    Point2f OriPoint_r[3] = {right.lt, right.lb, right.rb};
    Point2f OriPoint_t[3] = {up.lt, up.lb, up.rb};
    Point2f AffinePoint[3] = {Point(30, 30), Point(30, 230), Point(230,230)};
    Mat AffineMatrix_l = getAffineTransform(OriPoint_l, AffinePoint);
    Mat AffineMatrix_r = getAffineTransform(OriPoint_r, AffinePoint);
    Mat AffineMatrix_t = getAffineTransform(OriPoint_t, AffinePoint);
    warpAffine(src_scaled, left.src, AffineMatrix_l, Size(260, 260));
    warpAffine(src_scaled, right.src, AffineMatrix_r, Size(260, 260));
    warpAffine(src_scaled, up.src, AffineMatrix_t, Size(260, 260));
    imshow("Separate to face left", left.src);
    waitKey(0);
    imshow("Separate to face right", right.src);
    waitKey(0);
    imshow("Separate to face top", up.src);
    waitKey(0);
}



