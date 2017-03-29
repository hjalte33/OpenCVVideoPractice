// OpenCVVideoPractice.cpp : Defines the entry point for the console application.
//

// VideoProcessing.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <cstdio>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv[])
{
	VideoCapture video = VideoCapture("KU_1.avi");
	if (!video.isOpened())
	{
		std::cout << "!!! Failed to open file: " << argv[1] << std::endl;
		return -1;
	}
	Mat frame;
	Mat prevFrame;
	Mat diff;
	Mat binary;

	video >> prevFrame;
	cvtColor(prevFrame, prevFrame, CV_RGB2GRAY, 1);
	
	while (true) {
		if (!video.read(frame)) {
			break;
		}

		cvtColor(frame, frame, CV_RGB2GRAY, 1);
		absdiff(frame, prevFrame, diff);
		threshold(diff, binary, 40, 255, THRESH_BINARY);

		imshow("Frame", frame);
		imshow("Threshold", binary);

		int offset = 1;
		video.set(CV_CAP_PROP_POS_FRAMES, video.get(CV_CAP_PROP_POS_FRAMES) - offset);

		video >> prevFrame;
		cvtColor(prevFrame, prevFrame, CV_RGB2GRAY, 1);
		video.set(CV_CAP_PROP_POS_FRAMES, video.get(CV_CAP_PROP_POS_FRAMES) + offset -1);
		
		char key = cvWaitKey(10);
		if (key == 27) // ESC
			break;
	}

}
