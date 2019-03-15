#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char** argv){
  Mat image;
  int auxiliar;
  int largura, altura;

  image= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "A imagem não pode ser carregada" << endl;

  largura =  image.size().width;
  altura  =  image.size().height;

  namedWindow("janela",WINDOW_AUTOSIZE);

  imshow("janela", image);  
  waitKey();

  // Trocando os quadrantes
  for(int i=0;i<altura;i++)
  {
    for(int j=0;j<(largura/2);j++)
    { 
        // Trocando os quadrantes 1 e 4
        auxiliar = image.at<uchar>(i,j); //Guardano o pixel atual para fazer a troca
        if (i < altura/2)
        {
          image.at<uchar>(i,j) = image.at<uchar>(i + altura/2 , j + largura/2);
          image.at<uchar>(i + altura/2 , j + largura/2) = auxiliar;
        }    

        // Trocando os quadrantes 2 e 3
        else
        {
          image.at<uchar>(i,j) = image.at<uchar>(i - altura/2 , j + largura/2);
          image.at<uchar>(i - altura/2 , j + largura/2) = auxiliar;
        }

    }
  }
  
  imshow("janela", image);  
  imwrite("Troca Regiões.png", image);
  waitKey();
  return 0;
}
