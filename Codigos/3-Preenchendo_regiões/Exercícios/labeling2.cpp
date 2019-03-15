#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image;  //Matriz que guarda a imagem
  int width, height; //valores da largura e altura da imagem
  int bolhasComFuros = 0;   //numero de bolhas completas (bolhas com furos e borda completa)
  int bolhasImcompletas = 0; //numero de bolhas incompletas
  int bolhas = 0; //numero de bolhas com e sem buracos
  
  // Variável do tipo `CvPoint`, onde a mesma cria um ponto permite acesso às suas coordenadas `x` e `y`.
  CvPoint p; 

  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  if(!image.data)
  {
    cout << "A imagem não pode ser carregada" << endl;
    return(-1);
  }

  width=image.size().width;
  height=image.size().height;

  p.x=0;
  p.y=0;


  imshow("image", image);
  waitKey();

  //Eliminando as bolhas da borda da primeira coluna
  for(int i=0; i<height; i++)
  {
    for(int j=0; j<1; j++)
    {
      if(image.at<uchar>(i,j) == 255)
      {
        // achou um objeto
        bolhasImcompletas++;
        p.x=j;
        p.y=i;
        floodFill(image,p,0); //pinta de preto
      }
    }
  }

  //Eliminando as bolhas da borda da ultima coluna
  for(int i=0; i<height; i++)
  {
    for(int j=width; j >= width-1; j--)
    {
      if(image.at<uchar>(i,j) == 255)
      {
        // achou um objeto
        bolhasImcompletas++;
        p.x=j;
        p.y=i;
        floodFill(image,p,0); //pinta de preto
      }
    }
  }

  //Eliminando as bolhas da borda da primeira linha
  for(int i=0; i<1; i++)
  {
    for(int j=0; j<width; j++)
    {
      if(image.at<uchar>(i,j) == 255)
      {
        // achou um objeto
        bolhasImcompletas++;
        p.x=j;
        p.y=i;
        floodFill(image,p,0); //pinta de preto
      }
    }
  }

  //Eliminando as bolhas da borda da ultima linha
  for(int i=height; i>=height-1; i--)
  {
    for(int j=0; j<width; j++)
    {
      if(image.at<uchar>(i,j) == 255)
      {
        // achou um objeto
        bolhasImcompletas++;
        p.x=j;
        p.y=i;
        floodFill(image,p,0); //pinta de preto
      }
    }
  }


  imshow("image", image);
  waitKey();

  //pintando o fundo da imagem
  floodFill(image,p,100);

  imshow("image", image);
  waitKey();

 //pintando o fundo das bolhas com furos com a mesma cor do fundo da imagem
  for(int i=0; i<height; i++)
  {
    for(int j=0; j<width; j++)
    {
      if(image.at<uchar>(i,j) == 0)
      {
        // achou uma bolha
        bolhasComFuros++;
        p.x=j;
        p.y=i;
        floodFill(image,p,100);
      }
    }
  }

  imshow("image", image);
  waitKey();


  
  //pintando todas as bolhas
  for(int i=0; i<height; i++)
  {
    for(int j=0; j<width; j++)
    {
      if(image.at<uchar>(i,j) == 255)
      {
        // achou uma bolha
        bolhas++;
        p.x=j;
        p.y=i;
        floodFill(image,p,0);
      }
    }
  }

  imshow("image", image);
  imwrite("labeling.png", image);
  waitKey();

  cout << endl;
  cout << ">Numero de bolhas completas encontradas: " << bolhas - bolhasComFuros <<  endl;
  cout << ">Numero de bolhas com furos encontradas: " << bolhasComFuros <<  endl;
  cout << ">Numero de bolhas incompletas encontradas: " << bolhasImcompletas <<  endl; 
  cout << ">Total de bolhas: " << bolhasImcompletas + bolhasComFuros + (bolhas - bolhasComFuros) <<  endl; 
  return 0;
}
