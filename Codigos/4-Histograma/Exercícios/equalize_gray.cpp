#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, imageCinza, imageCinzaEqualizada;
  int width, height;
  VideoCapture cap;
  Mat histCinza, histEqualizado; //Matrizes onde ficara guardado os histogramas das imagens
  int nbins = 64;
  float range[] = {0, 256};
  const float *histCinzaange = { range };
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

  //Define-se a largura e altura das imagens que serão usadas para desenhar os histogramas 
  int histw = nbins, histh = nbins/2;
  Mat histImgCinza(histh, histw, CV_8UC1, Scalar(0));
  Mat histImgCinzaEqualizado(histh, histw, CV_8UC1, Scalar(0));
  


  while(1){
    cap >> image;

    // Convertendo a imagem para tons de cinza
    cvtColor(image,imageCinza,CV_BGR2GRAY);

    // Equalizando imagem com tons de cinza
    equalizeHist(imageCinza, imageCinzaEqualizada);

    //Calculando os histogramas
    calcHist(&imageCinza, 1, 0, Mat(), histCinza, 1,
             &nbins, &histCinzaange,
             uniform, acummulate);
    calcHist(&imageCinzaEqualizada, 1, 0, Mat(), histEqualizado, 1,
             &nbins, &histCinzaange,
             uniform, acummulate);
    

    //Normalizando
    normalize(histCinza, histCinza, 0, histImgCinza.rows, NORM_MINMAX, -1, Mat());
    normalize(histEqualizado, histEqualizado, 0, histImgCinzaEqualizado.rows, NORM_MINMAX, -1, Mat());
    

    histImgCinza.setTo(Scalar(0));
    histImgCinzaEqualizado.setTo(Scalar(0));
   
  
    for(int i=0; i<nbins; i++){
      line(histImgCinza,
           Point(i, histh),
           Point(i, histh-cvRound(histCinza.at<float>(i))),
           Scalar(255, 255, 255), 1, 8, 0);
      line(histImgCinzaEqualizado,
           Point(i, histh),
           Point(i, histh-cvRound(histEqualizado.at<float>(i))),
           Scalar(255, 255, 255), 1, 8, 0);

    }
   
    histImgCinza.copyTo(imageCinza(Rect(0, 0, nbins, histh)));
    histImgCinzaEqualizado.copyTo(imageCinzaEqualizada(Rect(0, 0   ,nbins, histh)));
   
   
    imshow("Imagem em Cinza", imageCinza);
    imshow("Imagem em Cinza Equalizada", imageCinzaEqualizada);
    if(waitKey(30) >= 0) break;
    
  }
  
  return 0;
}
