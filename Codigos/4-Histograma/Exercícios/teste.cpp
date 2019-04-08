#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, imageEqualizada;
  int width, height;
  VideoCapture cap;
  vector<Mat> planes, planesEqualizado;
  Mat histR, histG, histB, histREqualizado, histGEqualizado, histBEqualizado;
  int nbins = 64;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

  cap.open(0);

  if(!cap.isOpened()){
    cout << "cameras indisponiveis";
    return -1;
  }

  width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  cout << "largura = " << width << endl;
  cout << "altura  = " << height << endl;

  int histw = nbins, histh = nbins/2;
  Mat histImgR(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgG(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgB(histh, histw, CV_8UC3, Scalar(0,0,0));  

  Mat histImgREqualizado(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgGEqualizado(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgBEqualizado(histh, histw, CV_8UC3, Scalar(0,0,0));

  while(1){
    cap >> image;
    split (image, planes);

    equalizeHist(planes[0], planesEqualizado[0]);
    equalizeHist(planes[1], planesEqualizado[1]);
    equalizeHist(planes[2], planesEqualizado[2]);    
     

    calcHist(&planesEqualizado[0], 1, 0, Mat(), histREqualizado, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&planesEqualizado[1], 1, 0, Mat(), histGEqualizado, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&planesEqualizado[2], 1, 0, Mat(), histBEqualizado, 1,
             &nbins, &histrange,
             uniform, acummulate);

    calcHist(&planes[0], 1, 0, Mat(), histR, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&planes[1], 1, 0, Mat(), histG, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&planes[2], 1, 0, Mat(), histB, 1,
             &nbins, &histrange,
             uniform, acummulate);

    normalize(histR, histR, 0, histImgREqualizado.rows, NORM_MINMAX, -1, Mat());
    normalize(histG, histG, 0, histImgGEqualizado.rows, NORM_MINMAX, -1, Mat());
    normalize(histB, histB, 0, histImgBEqualizado.rows, NORM_MINMAX, -1, Mat());

    normalize(histR, histR, 0, histImgR.rows, NORM_MINMAX, -1, Mat());
    normalize(histG, histG, 0, histImgG.rows, NORM_MINMAX, -1, Mat());
    normalize(histB, histB, 0, histImgB.rows, NORM_MINMAX, -1, Mat());
    
    histImgR.setTo(Scalar(0));
    histImgG.setTo(Scalar(0));
    histImgB.setTo(Scalar(0));    

    histImgREqualizado.setTo(Scalar(0));
    histImgGEqualizado.setTo(Scalar(0));
    histImgBEqualizado.setTo(Scalar(0));

    for(int i=0; i<nbins; i++){
      line(histImgR,
           Point(i, histh),
           Point(i, histh-cvRound(histR.at<float>(i))),
           Scalar(0, 0, 255), 1, 8, 0);
      line(histImgG,
           Point(i, histh),
           Point(i, histh-cvRound(histG.at<float>(i))),
           Scalar(0, 255, 0), 1, 8, 0);
      line(histImgB,
           Point(i, histh),
           Point(i, histh-cvRound(histB.at<float>(i))),
           Scalar(255, 0, 0), 1, 8, 0);


      line(histImgREqualizado,
           Point(i, histh),
           Point(i, histh-cvRound(histR.at<float>(i))),
           Scalar(0, 0, 255), 1, 8, 0);
      line(histImgGEqualizado,
           Point(i, histh),
           Point(i, histh-cvRound(histG.at<float>(i))),
           Scalar(0, 255, 0), 1, 8, 0);
      line(histImgBEqualizado,
           Point(i, histh),
           Point(i, histh-cvRound(histB.at<float>(i))),
           Scalar(255, 0, 0), 1, 8, 0);
    }

    histImgR.copyTo(image(Rect(0, 0       ,nbins, histh)));
    histImgG.copyTo(image(Rect(0, histh   ,nbins, histh)));
    histImgB.copyTo(image(Rect(0, 2*histh ,nbins, histh)));

    histImgREqualizado.copyTo(imageEqualizada(Rect(0, 0       ,nbins, histh)));
    histImgGEqualizado.copyTo(imageEqualizada(Rect(0, histh   ,nbins, histh)));
    histImgBEqualizado.copyTo(imageEqualizada(Rect(0, 2*histh ,nbins, histh)));
    imshow("image", image);
    imshow("image Equalizada", imageEqualizada);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}