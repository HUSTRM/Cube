//
// Created by top on 19-1-15.
//

#ifndef RUBIKS3_SOLVE_CUBEDETECTOR_HPP
#define RUBIKS3_SOLVE_CUBEDETECTOR_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <functional>
#include <vector>

using namespace std;
using namespace cv;

struct FACE{
    char faceCode; //每个面的代号，'L','U','R','D','F','B'
    string faceName; //每个面的名字， 'left','up','right','down',front','back'
    int s_max; //每个色块的最大面积
    int s_min; //每个色块的最小面积
    Mat src; //经过一整图片的拆分后得到的每一个图的数据
    Point2f lt; //左上角的顶点
    Point2f lb; //左下角的顶点
    Point2f rt; //右上角的顶点
    Point2f rb; //右下角的顶点
};

struct COLOR{
    char colorCode; //每个颜色的代号，'B','W','R','Y','G','O'
    string colorNameString; //每个颜色的名字，'blue','white','red','yellow','green','orange'
    const int H_Low; //H参数的最小值
    const int H_High; //H参数的最大值
    const int S_Low; //S参数的最小值
    const int S_High; //S参数的最大值
    const int V_Low; //V参数的最小值
    const int V_High; //V参数的最大值
    Mat color_thresh; //HSV颜色阈值化后的图像
};

class CubeDetector {
public:
    CubeDetector();
    ~CubeDetector();

    string this_face_color(FACE face, int isRotate = 0);
    void separate(string fileName);

    /***
     * 需要调整的参数
     * left,right,up指的是一个摄像头能拍到的三个面（摄像头在魔方的一个上顶角处）
     * 根据结构体的定义方式，调整各参数
     */
    Mat face_l;
    Mat face_r;
    Mat face_t;
    Mat face_f;
    Mat face_d;
    Mat face_b;

    FACE left = {'L', "Left", 4350, 1900, face_l, Point(229, 176), Point(241, 324),
                 Point(377, 247), Point(365, 398)};
    FACE right = {'R', "Right", 4350, 1400, face_r, Point(377, 247), Point(369, 405),
                  Point(493, 175), Point(476, 315)};
    FACE up = {'U', "Up", 3550, 1400, face_t, Point(355, 117), Point(230, 167),
               Point(490, 147), Point(376, 238)};
    FACE front = {'F', "Front", 3550, 1400, face_f, Point(355, 117), Point(230, 167),
               Point(490, 147), Point(376, 238)};
    FACE down = {'D', "Down", 3550, 1400, face_d, Point(355, 117), Point(230, 167),
               Point(490, 147), Point(376, 238)};
    FACE back = {'B', "Back", 3550, 1400, face_b, Point(355, 117), Point(230, 167),
               Point(490, 147), Point(376, 238)};

    FACE getface(string faceCode){
        if(faceCode == "U") return this->up;
        else if(faceCode == "F") return this->front;
        else if(faceCode == "L") return this->left;
        else if(faceCode == "R") return this->right;
        else if(faceCode == "B") return this->back;
        else if(faceCode == "D") return this->down;
    }

private:
    int Sum(Mat& src);
    vector<Rect> getROI(Mat &src, int s_max, int s_min);

    Mat W_Thresholded;
    Mat R_Thresholded;
    Mat G_Thresholded;
    Mat B_Thresholded;
    Mat O_Thresholded;
    Mat Y_Thresholded;

    vector<COLOR> colorV;

    static bool comp(const Rect &a, const Rect &b) {
        if(fabs(a.y-b.y)>40){
            if(a.y > b.y) return false;
            else return true;
        }else{
            if(a.x > b.x) return false;
            else return true;
        }
    }

    /*
     * 需要调整的参数：每一个颜色的HSV的范围
     */

    COLOR blue = {'B', "Blue", 101, 150, 128, 255, 128, 255, B_Thresholded};
    COLOR white = {'W', "White", 10, 43, 0, 50, 50, 255, W_Thresholded};//白色参数还得调整，根据亮度而定
    COLOR red = {'R', "Red", 0, 9, 128, 255, 128, 255, R_Thresholded};
    COLOR green = {'G', "Green", 46, 100, 128, 255, 128, 255, G_Thresholded};
    COLOR orange = {'O', "Orange", 10, 15, 128, 255, 128, 255, O_Thresholded};
    COLOR yellow = {'Y', "Yellow", 16, 45, 128, 255, 128, 255, Y_Thresholded};

    string Reverse(string str){
        int si=str.size();
        char str_r[9];
        for(int i=8;i>=0;i--)
        {
            str_r[8-i] = str[i];
        }
        return string(str_r).substr(0,9);
    }
};

#endif //RUBIKS3_SOLVE_CUBEDETECTOR_HPP
