/*--------------------------------------------------------------------------------
*This code is creatd to play AVI and FLV
---------------------------------------------------------------------------------*/
#include <stdio.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

#define FILE_PATH "./res/video/flowers.avi"
#pragma comment( lib, "winmm" )


int main(int argc, char** argv) {
	/*--------------------------------------------------------------------------------
	*codes reserved for calling file from console
	---------------------------------------------------------------------------------*/
	/*wchar_t wtext[20];
	mbstowcs(wtext, argv[1], strlen(argv[1]) + 1);
	LPWSTR filename = wtext;*/
	/*--------------------------------------------------------------------------------
	*codes reserved for calling file from console
	---------------------------------------------------------------------------------*/
	cvNamedWindow("PlayVideo", CV_WINDOW_AUTOSIZE);
	CvCapture* capture = cvCreateFileCapture(FILE_PATH);
	if(!capture)
	{
	std::cout <<"Video Not captured\n";
	return -1;
	}

	/*--------------------------------------------------------------------------------
	*play Video
	---------------------------------------------------------------------------------*/

	IplImage* frame = NULL;
	while (1) {
		frame = cvQueryFrame(capture);
		//end of video
		if (!frame)
			break;
		cvShowImage("PlayVideo", frame);
		//press q to leave (ascii code 113)
		char q = cvWaitKey(33);
		if (q == 113) break;
	}

	/*--------------------------------------------------------------------------------
	*Close
	---------------------------------------------------------------------------------*/
	cvReleaseCapture(&capture);
	cvDestroyWindow("PlayVideo");
	return 0;
}


