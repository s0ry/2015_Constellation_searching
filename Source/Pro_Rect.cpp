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
#include "Pro_Rect.h"
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
int CDECL Pro_Rect(int* min_x,int* min_y,int* max_x,int* max_y,KScRgbImage2d* src,KScRgbImage2d* dst)
{
// 전처리 /////////////////////////////////////////////////////////////////////

    // 입력 버퍼 자료 형태 검사.
	if(src->GetId() != KS_RGB_IMAGE_2D)
	{
		::MessageBox(NULL, "Input buffer type not suitable.", "Pro_Rect", MB_OK);
		return FALSE;
	}
	
	// 출력 버퍼 자료 형태 검사.
	if(dst->GetId() != KS_RGB_IMAGE_2D)
	{
		::MessageBox(NULL, "Output buffer type not suitable.", "Pro_Rect", MB_OK);
		return FALSE;
	}

	// 입력 버퍼 할당 여부 검사.
	int dx = src->GetMainXSize();
	int dy = src->GetMainYSize();

	// 출력 버퍼 할당 여부 검사.
	if(dx != dst->GetMainXSize() || dy != dst->GetMainYSize())
	{
		dst->Free();
		dst->Alloc(dx, dy);
	}
	dst->InitTo(0);

// 실제 처리 부분 /////////////////////////////////////////////////////////////

	KSdUint8 **pSrouceArray_R = src->GetRed2dArray();
	KSdUint8 **pSrouceArray_G = src->GetGreen2dArray();
	KSdUint8 **pSrouceArray_B = src->GetBlue2dArray();
	KSdUint8 **pDestinationArray_R = dst->GetRed2dArray();
	KSdUint8 **pDestinationArray_G = dst->GetGreen2dArray();
	KSdUint8 **pDestinationArray_B = dst->GetBlue2dArray();
	
	for (register int i=0,j ; i<dy ; i++){
		for (j=0 ; j<dx ; j++){
			pDestinationArray_R[i][j] = pSrouceArray_R[i][j];
			pDestinationArray_G[i][j] = pSrouceArray_G[i][j];
			pDestinationArray_B[i][j] = pSrouceArray_B[i][j];
		}
	}
	
	CvPoint pt1, pt2;
	pt1.x = *min_x;
	pt1.y = *min_y;
	pt2.x = *max_x;
	pt2.y = *max_y;

	cv::Mat m1 = KScRgbImage2dToMat(dst);
	cv::rectangle (m1, pt1, pt2, CV_RGB(255, 0, 0), 3);
	MatToKScRgbImage2d(m1,dst);

// 후처리 /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.


