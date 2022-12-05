#include "face.hpp"
#define FILEPATH "/mnt/remote/face/"

// code taken from https://docs.opencv.org/4.x/da/d60/tutorial_face_main.html

static vector<Mat> images;
static vector<int> labels;
static Ptr<EigenFaceRecognizer> model;
static CascadeClassifier detector;

static Mat norm_0_255(InputArray _src) {
    Mat src = _src.getMat();
    // Create and return normalized image:
    Mat dst;
    switch(src.channels()) {
    case 1:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
        break;
    default:
        src.copyTo(dst);
        break;
    }
    return dst;
}

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(Error::StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

void Face_initialize(bool pretraining)
{
    model = EigenFaceRecognizer::create();
    if(pretraining){
        string fn_csv = "training.csv";
        try {
            read_csv(fn_csv, images, labels);
        } catch (const cv::Exception& e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
        }
        printf("Read from csv\n");
        
        model->train(images, labels);
        model->save(FILEPATH "mymodel.yml");
        printf("Model trained\n");
    }else{
        model->read(FILEPATH "mymodel.yml");
        printf("Model fetched\n");
    }
    
    detector.load(FILEPATH "haarcascade_frontalface_default.xml"); // may need to change depending on filepath
    return;
}

int Face_predict(const char * inputimage)
{
    // Get input image and process it
    Mat testSample = imread(inputimage,1); // may need to edit depending on file path and name
    Mat grey;
    cvtColor(testSample,grey,COLOR_BGR2GRAY);
    vector<Rect> faces;
    detector.detectMultiScale(grey,faces);
    if(faces.size() == 0){
        printf("No face detected\n");
        return 0;
    }
    Rect roi; // region of interest
    roi.x = faces[0].x;
    roi.y = faces[0].y;
    roi.width = faces[0].width;
    roi.height = faces[0].height;
    Mat cropped = grey(roi);
    Mat resized;
    resize(cropped, resized,Size(92,112));
    printf("Loaded in test sample\n");
    
    int predictedLabel = -1;
    double confidence = 0.0;
    model->predict(resized, predictedLabel, confidence);

    string result_message = format("Predicted class = %d. Confidence = %f", predictedLabel,confidence);
    cout << result_message << endl;
    if(confidence <= 2000){ // may need to edit depending on number of samples used
        return 1;
    }else{
        return 0;
    }
}