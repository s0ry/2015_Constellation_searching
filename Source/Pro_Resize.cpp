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
#include "Pro_Resize.h"
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
int CDECL Pro_Resize(KScScalarImage2dUint8* src,KScScalarImage2dUint8* dst)
{
// 전처리 /////////////////////////////////////////////////////////////////////

    // 입력 버퍼의 자료 형태 검사.
    if (src->GetId() != KS_SCALAR_IMAGE_2D_UINT8)
	{
		::MessageBox(NULL, "Input pSourceBuffer type not suitable.",
			"Pro_Resize", MB_OK);
        return FALSE;
	}

    // 출력 버퍼의 자료 형태 검사.
    if (dst->GetId() != KS_SCALAR_IMAGE_2D_UINT8)
	{
		::MessageBox(NULL, "Output pSourceBuffer type not suitable.",
			"Pro_Resize", MB_OK);
        return FALSE;
	}

    // 입력 버퍼의 할당 여부 검사.
	int dx = src->GetMainXSize();
	int dy = src->GetMainYSize();
    if (!dx || !dy)
	{
		::MessageBox(NULL, "Input pSourceBuffer not allocated.",
			"Pro_Resize", MB_OK);
        return FALSE;
	}

 	// 입력 버퍼를 기준으로 실제 처리 영역 설정.
	dx = src->GetXSize();
	dy = src->GetYSize();

	// ROI가 설정되어 있으면 Free()에서 ROI도 해제됨.
	dst->Free();
	if (dst->Alloc(dx, dy))
	{
		::MessageBox(NULL, "Fail to allocate output buffer.",
			"Pro_Resize", MB_OK);
		return FALSE;
	}

// 실제 처리 부분 /////////////////////////////////////////////////////////////

	// 버퍼를 1차원 배열로 접근.
	KSdUint8 **pSourceArray      = src->Get2dArray();
	KSdUint8 **pDestinationArray = dst->Get2dArray();

	int buf_size = dx * dy;
	int min_x = dx, min_y = dy, max_x, max_y;

	for (register int i=0,j ; i<dy ; i++){
		for (j=0 ; j<dx ; j++){
			pDestinationArray[i][j] = pSourceArray[i][j];
			if (pSourceArray[i][j] != 0 && min_x > j){
				min_x = j;
			}
			if (pSourceArray[i][j] != 0 && min_y > i){
				min_y = i;
			}
			if (pSourceArray[i][j] != 0){
				max_x = j;
				max_y = i;
			}
		}
	}
	
	IplImage *src_img, *dst_img;
	cv::Mat m1 = KScScalarImage2dUint8ToMat(src);
	src_img = new IplImage(m1);
	cv::Mat m2 = KScScalarImage2dUint8ToMat(dst);
	dst_img = new IplImage(m2);

	cvSetImageROI(src_img, cvRect(min_x, min_y, (max_x - min_x), (max_y - min_y))); 
	dst_img = (IplImage*)cvClone(src_img);

	cv::Mat ma(dst_img);
	MatToKScScalarImage2dUint8(ma, dst);
	
// 후처리 /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.




