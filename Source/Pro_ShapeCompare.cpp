//////////////////////////////////////////////////////////////////////////
//
// 이 화일은 함수 등록시 자동으로 생성된 프로젝트입니다.
//
// 사용자가 임으로 만든 경우, Project의 Setting...의 설정이 필요하므로,
//
// 이는 도움말의 '함수 작성법'을 참조 바랍니다.
//
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "Pro_ShapeCompare.h"
#include <cv.h>
#include <opencv/highgui.h>
#include <KScOpenCvUtils.h>

// DLL을 만들기 위한 부분
BOOL WINAPI DllMain (HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH: break;
		case DLL_THREAD_ATTACH:  break;
		case DLL_THREAD_DETACH:  break;
		case DLL_PROCESS_DETACH: break;
	}

	return TRUE;
}

// 함수의 정의 부분
/*int CDECL Pro_ShapeCompare(KScScalarImage2dUint8* src,KScScalarImage2dUint8* ref,double* result)*/
int CDECL Pro_ShapeCompare(KScScalarImage2dUint8* src,KScScalarImage2dUint8* ref,int* result)
{
// 전처리 /////////////////////////////////////////////////////////////////////

    // 입력 버퍼 자료 형태 검사.

    // 출력 버퍼 자료 형태 검사.

    // 입력 버퍼 할당 여부 검사.

	// 출력 버퍼 할당 여부 검사.

// 실제 처리 부분 /////////////////////////////////////////////////////////////

	char text;
	int count = 20;
	int dec, sign;
	double m_result[3];
	CvFont font;
	IplImage *src_img, *ref_img;
	cv::Mat m1 = KScScalarImage2dUint8ToMat(src);
	src_img = new IplImage(m1);
	cv::Mat m2 = KScScalarImage2dUint8ToMat(ref);
	ref_img = new IplImage(m2);

	// (1)3 종류의 수법으로 형상을 비교
	m_result[0] = cvMatchShapes (src_img, ref_img, CV_CONTOURS_MATCH_I1, 0);
	m_result[1] = cvMatchShapes (src_img, ref_img, CV_CONTOURS_MATCH_I2, 0);
	m_result[2] = cvMatchShapes (src_img, ref_img, CV_CONTOURS_MATCH_I3, 0);
	
	*result = (int)(m_result[0] * 100000);

// 후처리 /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.




