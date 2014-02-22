#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "answer05.h"



Image *Image_load(const char *filename)
{
  ImageHeader header;
  size_t read;
  Image * tmp_im = NULL, * im = NULL;
  
  //open the file
  FILE * fp = fopen(filename,"rb");
  int err = fp == NULL;

  //error
  if (err) fprintf(stderr,"unable to open file %s\n",filename);
  
  if(!err) {
    read = fread(&header, sizeof(ImageHeader),1,fp);
    err = read != 1 ||
      header.magic_number != ECE264_IMAGE_MAGIC_NUMBER ||
      header.width == 0 ||
      header.height == 0 ||
      header.comment_len == 0;
      if (err) fprintf(stderr,"corrupt header\n");
  }
 

  //allocate memory
  if(!err){
    tmp_im = malloc(sizeof(Image));    
    err = tmp_im == NULL;
    if(err) fprintf(stderr,"unable to allocate memory\n");
  }
  

  if (!err){
    tmp_im->width = header.width;
    tmp_im->height = header.height;
    tmp_im->comment = malloc(sizeof(char) * header.comment_len);
    tmp_im->data = malloc(sizeof(uint8_t)*header.width*header.height);
    err = tmp_im->comment ==NULL ||
      tmp_im->data == NULL;///////////////////
    if(err) fprintf(stderr,"failed to allocate memory to pixels and comments\n");
   }
  
  // read the comment
  if(!err){
    read = fread(tmp_im->comment,sizeof(char),header.comment_len,fp);
    err = ((read != header.comment_len) || tmp_im->comment[header.comment_len - 1] !='\0');
    if(err) fprintf(stderr, "unable to read the comment\n");
  }

  // read the pixels
  if(!err){
    read = fread(tmp_im->data,sizeof(uint8_t),header.width * header.height,fp);
    err = read != header.width * header.height;
    if(err) fprintf(stderr, "unable to read the pixels\n");
  }

  // makesure we reached the end of the file
  if(!err) {
    fgetc(fp);
    err = !feof(fp);
    if(err) fprintf(stderr,"unable to reach the end of the file\n");
  }

  if(!err){
    im = tmp_im;
    tmp_im = NULL;
    return im;
  }
  
  //makesure to close the file
  if (fp != NULL) fclose(fp);


  Image_free(tmp_im);
   
  return NULL;
}




int Image_save(const char * filename, Image * image)
#define TRUE 1
#define FAIL 0
  {
    ImageHeader save;
    size_t write;
    
    // op file
    FILE * fp = NULL;
    fp = fopen(filename,"wb");
    int err = fp == NULL;
    
    // check if you can open it correctly
    if(err)    {
      fprintf(stderr, "unable to open file %s\n",filename);
      return FAIL;
    }

    //save the image
    ImageHeader imsave;
    save.magic_number = ECE264_IMAGE_MAGIC_NUMBER;
    save.width = image-> width;
    save.height = image-> height;
    save.comment_len = strlen(image->comment)+1;
        
    write = fwrite(&save, sizeof(ImageHeader),1,fp);
    write = fwrite(image->comment,sizeof(char),save.comment_len,fp);
    write = fwrite(image->data,sizeof(uint8_t),save.width * save.height,fp);
    if (fp != NULL)     fclose(fp);
      
    return TRUE;
 
}

void Image_free(Image * image)

{
  if(image != NULL)
  {
    free(image->comment);
    free(image->data);
    free(image);
  }
}  


void linearNormalization(int width, int height, uint8_t * intensity)
{
    int data = width * height;
    int i;
    int max = 0;
    int min = intensity[0];
    for(i = 0; i < data; i++)
    {
      if(intensity[i]> max)
      {
	max = intensity[i];
      }
      if(intensity[i]< min)
      {
	min = intensity[i];
      }
    }
    for(i = 0; i < data; i++)
    {
      intensity[i] = (intensity[i] - min) * 255.0 / (max - min);
    }
}
