#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, mask;
  int width, height;
  int bolhasComFuros = 0;   //numero de bolhas com furos
  int bolhasImcompletas = 0; //numero de bolhas incompletas
  int bolhas = 0; //numero de bolhas com e sem buracos

 
  
  // CvPoint p;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  if(!image.data)
  {
    cout << "nao abriu meme.jpg" << endl;
    return(-1);
  }

  width=image.size().width;
  height=image.size().height;

  // p.x=0;
  // p.y=0;

  

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
  floodFill(image,cv::Point(0,0),100);


/*
  imshow("image", image);
  waitKey();

  //pintando o fundo das bolhas com furos
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
*/

/*

  //pintando o das bordas com varios furos
  for(int i=0; i<height; i++)
  {
    for(int j=0; j<width; j++)
    {
      if(image.at<uchar>(i,j) == 255 && image.at<uchar>(i,j+1) == 0)
      {
        
        j += 1;
        image.at<uchar>(i,j) == 255; 
        j += 1;
        
        while(image.at<uchar>(i,j) == 0)
        {
          image.at<uchar>(i,j) == 255;
          j += 1;
        }
      }

      if(image.at<uchar>(i,j) == 0 && image.at<uchar>(i,j-1) == 255 && image.at<uchar>(i,j+1) == 255)
      {
          image.at<uchar>(i,j) == 255;
      } 

    }
  }

*/


/*
  imshow("image", image);
  waitKey();


  
  //pintando a borda de todas as bolhas
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
*/
  imshow("image", image);
  waitKey();


  cout << endl;
  cout << ">Numero de bolhas completas encontradas: " << bolhas - bolhasComFuros <<  endl;
  cout << ">Numero de bolhas com furos encontradas: " << bolhasComFuros <<  endl;
  cout << ">Numero de bolhas incompletas encontradas: " << bolhasImcompletas <<  endl; 
  cout << ">Total de bolhas: " << bolhasImcompletas + bolhasComFuros + (bolhas - bolhasComFuros) <<  endl; 


  return 0;
}
