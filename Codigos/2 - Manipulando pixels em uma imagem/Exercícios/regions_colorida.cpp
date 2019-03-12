#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void mostraImagem(string janela, Mat image){
    imshow("janela", image);  
    waitKey();
}

int main(int, char**){
  Mat image;
  //Vec3b val;
  CvPoint P1, P2;
  int largura, altura;

  image= imread("meme.jpg",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "nao abriu meme.jpg" << endl;

 // image= imread("meme.jpg",CV_LOAD_IMAGE_COLOR);

  largura =  image.size().width;
  altura  =  image.size().height;

  cout << largura << " " << altura << endl;

  namedWindow("janela",WINDOW_AUTOSIZE);

  cout << "-Informe o valor x de P1: " ;
  cin >> P1.x;
  if (P1.x < 0 || P1.x > altura)
  {
    cout << "Valor invalido para altura da imagem!" << endl;
    return(-1);
  }

  cout << "-Informe o valor y de P1: " ;
  cin >> P1.y;
  if (P1.x < 0 || P1.x > largura)
  {
    cout << "Valor invalido para largura da imagem!" << endl;
    return(-1);
  }
  
  cout << "-Informe o valor x de P2: " ;
  cin >> P2.x;
  if (P2.x < 0 || P2.x > altura)
  {
    cout << "Valor invalido para altura da imagem!" << endl;
    return(-1);
  }

  cout << "-Informe o valor y de P2: " ;
  cin >> P2.y;
   if (P2.x < 0 || P2.x > largura)
  {
    cout << "Valor invalido para largura da imagem!" << endl;
    return(-1);
  }

/*
  for(int i=P1.x; i<P2.x; i++){
    for(int j=P1.y; j<P2.y; j++){
      image.at<uchar>(i,j) = 255 - image.at<uchar>(i,j) ;
    }
  }
*/

  mostraImagem("janela", image);
/*
  image= imread("meme.jpg",CV_LOAD_IMAGE_COLOR);

  val[0] = 0;   //B
  val[1] = 0;   //G
  val[2] = 255; //R
  
  for(int i=200;i<210;i++){
    for(int j=10;j<200;j++){
      image.at<Vec3b>(i,j)=val;
    }
  }
*/
  mostraImagem("janela", image);
  return 0;
}
