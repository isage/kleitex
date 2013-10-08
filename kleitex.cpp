#include <cstdio>
#include <iostream>
#include <string>
#include <squish.h>
#include "squishpng.h"

typedef struct kleitex_header {
  char sig[8];
  unsigned short width;
  unsigned short height;
  unsigned short unk1;
  unsigned short unk2;
  unsigned short unk3;
} kleitex_header_t;

int main(int argc, char **argv)
{

  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " <filename.tex>" << std::endl;
    return -1;
  }

  FILE* fp;
  kleitex_header_t head;
  unsigned int len;
  DxtData dxt;
  Image* im=new Image();

  fp=fopen(argv[1],"rb");
  if (!fp)
  {
    std::cout << "Cannot open " << argv[1] << std::endl;
    return -1;
  }
  fseek(fp,0,SEEK_END);
  len=ftell(fp);
  fseek(fp,0,SEEK_SET);

  len=len-sizeof(kleitex_header);
  fread(&head,sizeof(head),1,fp);

  std::cout << "SIG: " << head.sig << std::endl;
  std::cout << "WIDTH: " << head.width << std::endl;
  std::cout << "HEIGHT: " << head.height << std::endl;

  //load dxt data
  dxt.data.Reset(len);
  fread(dxt.data.Get(),len,1,fp);
  dxt.width=head.width;
  dxt.height=head.height;
  dxt.format=squish::kDxt5;
  dxt.isColour=true;
  dxt.isAlpha=true;

  //decompress
  im->Decompress(dxt);

  //save to png
  std::string filename=std::string(argv[1]);
  filename.replace(filename.end()-4,filename.end(),".png");
  im->SavePng(filename);
  std::cout << "Wrote " << filename << std::endl;
  return 0;
}
