#include <cv.h> //영상처리 헤더
#include <stdio.h> 
#include <highgui.h> //카메라로 영상을 입력받거나 이지를 읽어들이고 화면에 보여주기위한 헤더
#include <string.h>

//중심좌표 : 300,250
int main()
{
	IplImage* image = 0; //IplImage구조체 선언,char형 imageData 를 가지고서 이미지에 직접적인 접근
	IplImage* R_channel = 0;
	IplImage* G_channel = 0;
	IplImage* B_channel = 0;
	IplImage* R_channel_out = 0;
	CvCapture* capture = cvCaptureFromCAM(0); //0 번째 연결된 카메라로부터 컨트롤를 얻어옴

	int width = 460;
	int height = 300;
	
	//cvNamedWindow( "jinwook test", 1); //"jinwook test"이름의카메라 윈도우 생성,0은 고정된 윈도우
	cvNamedWindow( "jinwook test", 0);
	cvResizeWindow( "jinwook test", width, height ); //윈도우 크기 조절
	
	//폰트 및 텍스트 초기화
	//void cvInitFont(CvFont* font, int font_face, double hscale, double vscale, double shear = 0, int thickness = 1, int line_type = 8);
	CvFont font;
	CvFont W_font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0, 2, CV_AA);
	cvInitFont(&W_font, CV_FONT_HERSHEY_SIMPLEX, 2.5, 2.5, 0, 5, CV_AA);


	//test value//
	float test_count[4];
	test_count[0] = 1.0;
	test_count[1] = 1.0;
	test_count[2] = 1.0;
	test_count[3] = 1.0;
	float temp = 1.0;
	char str_test_count[4][10];
	
	//int sonic_value[4];
	float limit_dis;
	limit_dis = 40.0;

	while(1) {
		//test value
		test_count[0] = test_count[0] + temp; 
		test_count[1] = test_count[1] + temp; 
		test_count[2] = test_count[2] + temp; 
		test_count[3] = test_count[3] + temp; 
		//형변환 float(2) -> string
		sprintf(str_test_count[0],"%.2f",test_count[0]);
		sprintf(str_test_count[1],"%.2f",test_count[1]);
		sprintf(str_test_count[2],"%.2f",test_count[2]);
		sprintf(str_test_count[3],"%.2f",test_count[3]);

		cvGrabFrame( capture ); //카메라로부터 한프레임을 잡음
		image = cvRetrieveFrame( capture ); // IplImage 형 구조를 리턴 받아 image 에 넣음		

		//도형그리기
		//cvRectangle(image,cvPoint(10,10),cvPoint(600,450),cvScalar(0,0,255,100),-1,8);


		if(test_count[0] < limit_dis || test_count[1] < limit_dis || test_count[2] < limit_dis || test_count[3] < limit_dis){
			//화면상에 글자 출력
			cvPutText(image, str_test_count[0], cvPoint(300, 20), &font, cvScalar(255, 255, 0));
			cvPutText(image, str_test_count[1], cvPoint(10, 250), &font, cvScalar(255, 255, 0));
			cvPutText(image, str_test_count[2], cvPoint(300, 470), &font, cvScalar(255, 255, 0));
			cvPutText(image, str_test_count[3], cvPoint(535, 250), &font, cvScalar(255, 255, 0));

			cvPutText(image, "WARNING!", cvPoint(150, 90), &W_font, cvScalar(0, 0, 0, 0));
			//RGB체널분리후 병합
			R_channel = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);			
			G_channel = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
			B_channel = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
			R_channel_out = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
			cvSplit(image, B_channel, G_channel, R_channel, 0);
			cvMerge(NULL, G_channel, NULL, NULL, R_channel_out);

			// "jinwook test" 윈도우에 image 를 보여줌
			cvShowImage( "jinwook test", R_channel_out );	
		}
		else{
			cvPutText(image, str_test_count[0], cvPoint(300, 20), &font, cvScalar(0, 0, 255));
			cvPutText(image, str_test_count[1], cvPoint(10, 250), &font, cvScalar(0, 0, 255));
			cvPutText(image, str_test_count[2], cvPoint(300, 470), &font, cvScalar(0, 0, 255));
			cvPutText(image, str_test_count[3], cvPoint(535, 250), &font, cvScalar(0, 0, 255));
			cvShowImage( "jinwook test", image);
		}

		if( cvWaitKey(10) >= 0 )
			break;

		
		//test's value loop
		if(test_count[0]  == 100)
			temp = -1*temp;
		else if(test_count[0] == 0)
			temp = -1*temp;

		}


	//capture 를 release 하여 카메라와의 연결을 종료하고 윈도우를 소멸시키면 프로그램은 종료
	cvReleaseImage( &R_channel );
	cvReleaseImage( &G_channel );
	cvReleaseImage( &B_channel );
	cvReleaseImage( &R_channel_out );
	cvReleaseCapture (&capture );
	cvDestroyWindow( "jinwook test" );

	return 0;
}


