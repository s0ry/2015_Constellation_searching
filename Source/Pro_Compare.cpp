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
#include "Pro_Compare.h"
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
int CDECL Pro_Compare(KScScalarImage2dUint8* src,KScScalarImage2dUint8* ref,KScScalarImage2dUint8* dst,int* min_x,int* min_y,int* max_x,int* max_y)
{
// 전처리 /////////////////////////////////////////////////////////////////////
	
    // 입력 버퍼의 자료 형태 검사.
    if (src->GetId() != KS_SCALAR_IMAGE_2D_UINT8)
	{
		::MessageBox(NULL, "Input buffer type not suitable.",
			"Pro_Compare", MB_OK);
        return FALSE;
	}
	if (ref->GetId() != KS_SCALAR_IMAGE_2D_UINT8)
	{
		::MessageBox(NULL, "Input buffer type not suitable.",
			"Pro_Compare", MB_OK);
        return FALSE;
	}

	// 출력 버퍼의 자료 형태 검사.
    if (dst->GetId() != KS_SCALAR_IMAGE_2D_UINT8)
	{
		::MessageBox(NULL, "Output buffer type not suitable.",
			"Pro_Compare", MB_OK);
        return FALSE;
	}

    // 입력 버퍼의 할당 여부 검사.
	int dx = src->GetMainXSize();
	int dy = src->GetMainYSize();
    if (!dx || !dy)
	{
		::MessageBox(NULL, "Input buffer not allocated.",
			"Pro_Compare", MB_OK);
        return FALSE;
	}
	int rdx = src->GetMainXSize();
	int rdy = src->GetMainYSize();
    if (!rdx || !rdy)
	{
		::MessageBox(NULL, "Input buffer not allocated.",
			"Pro_Compare", MB_OK);
        return FALSE;
	}

	// 출력 버퍼가 할당이 되지 않았거나 입력 버퍼와 크기가 다를 경우,
	// 출력 버퍼를 입력 버퍼와 동일한 크기로 재할당.
	if (dx != dst->GetXSize() ||
		dy != dst->GetYSize())
	{
		// ROI가 설정되어 있으면 Free()에서 ROI도 해제됨.
		dst->Free();
		// Alloc()의 반환값 : 성공적이면 0, 실패이면 0이 아닌 에러 코드.
		if (dst->Alloc(dx, dy))
		{
			::MessageBox(NULL, "Fail to allocate output buffer.",
				"Pro_Compare", MB_OK);
			return FALSE;
		}
	}
	// 출력 버퍼의 크기가 입력 버퍼의 것과 동일할 경우,
	else
	{
		// 입출력 버퍼가 다를 경우, 0으로 초기화.
		// 초기화를 하지 않거나 사용자가 원하는 값으로 초기화해도 무방.
		if (src != dst)
			dst->InitTo(0);
	}

// 실제 처리 부분 /////////////////////////////////////////////////////////////
	
	double min_val, max_val;
	CvPoint min_loc, max_loc;
	CvSize dst_size;
	IplImage *src_img, *tmp_img, *dst_img;
	cv::Mat m1 = KScScalarImage2dUint8ToMat(src);
	src_img = new IplImage(m1);
	cv::Mat m2 = KScScalarImage2dUint8ToMat(ref);
	tmp_img = new IplImage(m2);
	
	// (1)탐색 이미지 전체에 대해서, 템플릿의 매칭치(지정한 수법으로 의존)를 계산
	dst_size = cvSize (src_img->width - tmp_img->width + 1, src_img->height - tmp_img->height + 1);
	dst_img = cvCreateImage (dst_size, IPL_DEPTH_32F, 1);
	
	cvMatchTemplate (src_img, tmp_img, dst_img, CV_TM_CCOEFF_NORMED);
	cvMinMaxLoc (dst_img, &min_val, &max_val, &min_loc, &max_loc, NULL);
	
	// (2)템플릿에 대응하는 위치에 구형을 그리기
	
	cvRectangle (src_img, max_loc, cvPoint (max_loc.x + tmp_img->width, max_loc.y + tmp_img->height), CV_RGB(0, 0, 0), 3);
	cv::Mat ma(src_img);
	MatToKScScalarImage2dUint8(ma, dst);
	*min_x = max_loc.x;
	*min_y = max_loc.y;
	*max_x = max_loc.x + tmp_img->width;
	*max_y = max_loc.y + tmp_img->height;
	
// 후처리 /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.





