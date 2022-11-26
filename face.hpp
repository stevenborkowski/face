#ifndef FACE_HPP
#define FACE_HPP

#include <opencv2/core.hpp>
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace cv::face;
using namespace std;

static Mat norm_0_255(InputArray _src);
static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator);
void Face_initialize(bool pretraining);
int Face_predict(const char * inputimage);

#endif