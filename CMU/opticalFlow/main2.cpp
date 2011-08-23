

#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include "cv.h"
#include "highgui.h"
#include "fhead.h"

#define WIN_SIZE 200

int main( int argc, char** argv )
{
    if (argc<1){
        printf("Need a folder\n");
        return 0;
    }
    const int tmpLength=300;
    char tmp[tmpLength];
    vector< vector<CvPoint> > gazePoints;
    vector<CvPoint2D32f> flows;
    sprintf(tmp,"%s/tmp.txt",argv[1]);
    
    ifstream ifs(tmp);
    if ( !ifs ) {     
        printf("No tmp.txt\n");
        exit(0);
    } else {
		int nbPoints=0; 
        while( ifs.good() ) { 
            ifs.getline(tmp,tmpLength);
            //if(!strcmp(tmp,"")) break;
            int x,y;
			vector<CvPoint> v;
            if(2==sscanf(tmp,"%i %i",&x,&y)){
				nbPoints++;
				v.push_back(cvPoint((int)x,(int)y));
			}
            gazePoints.push_back(v);
        }
        ifs.close();
		printf("%i points retrieved\n",nbPoints);
    }
    
    cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE); 
    IplImage *im1, *im2, *DxVMap, *DyVMap, *eigImage, *tmpImage;
    sprintf(tmp,"%s/capture_img_out_%08i.jpg",argv[1],0);
    im1=cvLoadImage(tmp,CV_LOAD_IMAGE_GRAYSCALE);
    //DxVMap=cvCreateImage(cvSize(WIN_SIZE,WIN_SIZE), IPL_DEPTH_32F, 1);
    //DyVMap=cvCreateImage(cvSize(WIN_SIZE,WIN_SIZE), IPL_DEPTH_32F, 1);
    //DxVMap=cvCreateImage(cvSize((WIN_SIZE-17)/2,(WIN_SIZE-17)/2), IPL_DEPTH_32F, 1);
    //DyVMap=cvCreateImage(cvSize((WIN_SIZE-17)/2,(WIN_SIZE-17)/2), IPL_DEPTH_32F, 1);

    eigImage=cvCreateImage(cvSize(WIN_SIZE,WIN_SIZE), IPL_DEPTH_32F, 1);
    tmpImage=cvCreateImage(cvSize(WIN_SIZE,WIN_SIZE), IPL_DEPTH_32F, 1);
    for(int i=1;i<gazePoints.size()-1;i++){
        sprintf(tmp,"%s/capture_img_out_%08i.jpg",argv[1],i);
        im2=cvLoadImage(tmp,CV_LOAD_IMAGE_GRAYSCALE);
        if(!im1 || !im2){
            printf("Could not load image file: %s\n",tmp);
            exit(0);
        }
		for(int j=0;j<gazePoints[i].size();j++){
			int x=gazePoints[i][j].x , y=gazePoints[i][j].y;
		    CvRect rect=cvRect (max(min(x-WIN_SIZE/2,im1->width-WIN_SIZE),0), max(min(y-WIN_SIZE/2,im1->height-WIN_SIZE),0), WIN_SIZE, WIN_SIZE);
        	cvSetImageROI(im1, rect);
		    cvSetImageROI(im2, rect);
		    
		    //cvCalcOpticalFlowHS( im1, im2, 1, DxVMap, DyVMap, 0.002, cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03));
		    //cvCalcOpticalFlowLK( im1, im2, cvSize(11,11), DxVMap, DyVMap);
		    //cvCalcOpticalFlowBM(im1, im2, cvSize(17,17), cvSize(2,2), cvSize(40,40), 0, DxVMap, DyVMap);
		    //float dx=cvSum(DxVMap).val[0]/cvCountNonZero(DxVMap);
		    //float dy=cvSum(DyVMap).val[0]/cvCountNonZero(DyVMap);
		    int cornerCount=1000;
		    CvPoint2D32f *prevFeatures, *currFeatures;
		    prevFeatures=(CvPoint2D32f*)malloc(cornerCount*sizeof(CvPoint2D32f));
		    cvGoodFeaturesToTrack(im1, eigImage, tmpImage, prevFeatures, &cornerCount, 0.01, 10);
		    //printf("%i points found\n",cornerCount);
		    currFeatures=(CvPoint2D32f*)malloc(cornerCount*sizeof(CvPoint2D32f));
		    char* status=(char*)malloc(cornerCount*sizeof(char));
		    float* track_error=(float*)malloc(cornerCount*sizeof(float));
		    cvCalcOpticalFlowPyrLK(im1, im2, NULL, NULL, prevFeatures, currFeatures, cornerCount, cvSize(15,15), 3, status, track_error, cvTermCriteria( CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, .3 ), 0);
		    cvResetImageROI(im1);
			cvResetImageROI(im2);
		    float dx=0, dy=0;
		    int n=0;
			for(int k=0;k<cornerCount;k++){
				if(status[k]){
					n++;
					dx+=currFeatures[k].x-prevFeatures[k].x;
	        		dy+=currFeatures[k].y-prevFeatures[k].y;
				}
			}
			if(n!=0){
				dx/=n;
				dy/=n;
			};
		    //printf("%i points matched \n",n);
		    free(prevFeatures);
		    free(currFeatures);
		    free(status);
		    free(track_error);
		    
			int x2=(int)(x+dx), y2=(int)(y+dy);
			if(x2>=0 && y2>=0 && x2<im1->width && y2<im1->height)
				gazePoints[i+1].push_back(cvPoint(x2,y2));
		    //printf("%f %f\n",dx,dy);
        }
		IplImage *result=cvCreateImage(cvGetSize(im1),IPL_DEPTH_8U,3);
		cvConvertImage(im1,result);
		for(int k=0;k<gazePoints[i].size();k++){
			cvCircle( result, gazePoints[i][k], 10, CV_RGB ( 0,255,0),-1);
		}
		printf("%i points tracked\n",gazePoints[i].size());
		cvShowImage("mainWin", result );
		cvWaitKey(0);
		cvReleaseImage(&result);

        
        cvReleaseImage(&im1);
        im1=im2;

        if(i%100==0)
            printf("%i images processed\n",i);        
    }

    sprintf(tmp,"%s/tmp.txt",argv[1]);

    ofstream ofs(tmp, ios_base::out | ios_base::trunc);
    if ( !ofs ) {     
        printf("Unable to write\n");
        exit(0);
    } else {    
        for( int i=0;i<gazePoints.size();i++ ) { 
			for( int j=0;j<gazePoints[i].size();j++ ) { 
			
		        ofs << gazePoints[i][j].x << " " << gazePoints[i][j].y << " ";
		    }
            ofs << endl;
        }
        ofs.close();
    }
    
    return 0;
}
