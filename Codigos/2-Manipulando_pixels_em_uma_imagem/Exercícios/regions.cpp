#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void mostraImagem(string janela, Mat image){
    imshow("janela", image);  
    waitKey();
}

int main(int, char** argv){
  Mat image;
  CvPoint P1, P2;
  int largura, altura;

  image= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "A imagem não pode ser carregada" << endl;


  largura =  image.size().width;
  altura  =  image.size().height;
 
  mostraImagem("janela", image);

  cout << "-Informe o valor x de P1: ";
  cin >> P1.x;
  if (P1.x < 0 || P1.x > altura)
  {
    cout << "Valor invalido para altura da imagem!" << endl;
    return(-1);
  }

  cout << "-Informe o valor y de P1: ";
  cin >> P1.y;
  if (P1.x < 0 || P1.x > largura)
  {
    cout << "Valor invalido para largura da imagem!" << endl;
    return(-1);
  }
  
  cout << "-Informe o valor x de P2: ";
  cin >> P2.x;
  if (P2.x < 0 || P2.x > altura)
  {
    cout << "Valor invalido para altura da imagem!" << endl;
    return(-1);
  }

  cout << "-Informe o valor y de P2: ";
  cin >> P2.y;
   if (P2.x < 0 || P2.x > largura)
  {
    cout << "Valor invalido para largura da imagem!" << endl;
    return(-1);
  }

  namedWindow("janela",WINDOW_AUTOSIZE);

  for(int i=P1.x; i<P2.x; i++){
    for(int j=P1.y; j<P2.y; j++){
      image.at<uchar>(i,j) = 255 - image.at<uchar>(i,j);
    }
  }

  imwrite("Regiões.png", image);
  mostraImagem("janela", image);
  return 0;
}
