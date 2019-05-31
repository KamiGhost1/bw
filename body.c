#include "head.h"


int testParam(int C, char **V){
    if (C==1){
        printf("lumaY by GHost\nenjoy!\n");
        exit(0);
    }
    if(C==3){
        if (!strcmp(V[1],"-y")){
            return 0;
        }
    }
    if(C==2){
        if(!strcmp(V[1],"-h")){
            printf("\thelp menu!\n\nuse command '-y':\nprog.exe -y image.bmp\n");
            exit(0);
        }
    }
    printf("incorrect parameters!\nuse -h to more information!\n");
    exit(1);
}


void IRead(FILE *input, COLOR **image, int height,int width){
    int i,j;
    for (i=0;i<height;i++)
        for(j=0;j<width;j++)
            fread(&image[i][j], sizeof(COLOR),1,input);
}


void IWrite(FILE *output, COLOR **image,int height,int width){
    int i,j;
    for (i=0;i<height;i++)
        for(j=0;j<width;j++)
            fwrite(&image[i][j],sizeof(COLOR),1,output);
}


COLOR **createColor(int height,int width){
    int i;
    COLOR **RGB;
    RGB=(COLOR**)malloc(sizeof(COLOR*)*height);
    for(i=0;i<height;i++)
        RGB[i]=(COLOR*)malloc(sizeof(COLOR)*width);
    return RGB;
}


FILE *IOpen(char *name){
    FILE *f;
    f = fopen(name, "rb+");
    if (!f){
        printf("file '%s' not found!\n",name);
        exit(2);
    }
    return f;
}


BMPFILEHEADER readFH(FILE *input){
    BMPFILEHEADER fh;
    fread(&fh,sizeof(BMPFILEHEADER),1,input);
    if(fh.bfType!=bmp){
        printf("file is not BMP!\n");
        exit(3);
    }
    return fh;
}


BMPINFOHEADER readIH(FILE *input){
    BMPINFOHEADER ih;
    fread(&ih, sizeof(BMPINFOHEADER),1,input);
    return ih;
}


void chgLuma(COLOR **image, int height, int width){
    int i,j;
	float Y;
    for(i=0;i<height;i++)
        for(j=0;j<width;j++){
            Y = (cR*image[i][j].R + cG*image[i][j].G + cB*image[i][j].B);
            Y += changeKoef;;
            image[i][j].R = Y;
            image[i][j].B = Y;
            image[i][j].G = Y;
            #ifdef debugL
            printf("%.3f\n",Y[i][j]);
            #endif
        }
    #ifdef debug
    printf("chg Luma ok\n");
    #endif
}
