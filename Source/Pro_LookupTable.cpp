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
#include "Pro_LookupTable.h"

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
int CDECL Pro_LookupTable(KScScalarImage2dUint8* src,KScScalarImage2dUint8* dst)
{
// 전처리 /////////////////////////////////////////////////////////////////////

    // 입력 버퍼의 자료 형태 검사.
    if (src->GetId() != KS_SCALAR_IMAGE_2D_UINT8)
	{
		::MessageBox(NULL, "Input buffer type not suitable.",
			"Pro_LookupTable", MB_OK);
        return FALSE;
	}

	// 출력 버퍼의 자료 형태 검사.
    if (dst->GetId() != KS_SCALAR_IMAGE_2D_UINT8)
	{
		::MessageBox(NULL, "Output buffer type not suitable.",
			"Pro_LookupTable", MB_OK);
        return FALSE;
	}

    // 입력 버퍼의 할당 여부 검사.
	int dx = src->GetMainXSize();
	int dy = src->GetMainYSize();
    if (!dx || !dy)
	{
		::MessageBox(NULL, "Input buffer not allocated.",
			"Pro_LookupTable", MB_OK);
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
				"Pro_LookupTable", MB_OK);
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

	// 버퍼를 2차원으로 접근하기 위한 처리
    KSdUint8 *pSourceArray      = src->GetBuffer();
    KSdUint8 *pDestinationArray = dst->GetBuffer();

	int bufSize = dx * dy;

	// 히스토그램 값과 look up table의 값을 저장할 버퍼
	unsigned char lut[256];

	// 히스토그램 버퍼의 초기화
	for (register int i = 0 ; i < 256 ; i++){
		if (i < 50)
			lut[i] = 255;
		else
			lut[i] = 0;
	}

	// 변경된 Lookup table을 통하여 입력영상을 변경시켜 출력
	for (int i = 0 ; i < bufSize ; i++)
		pDestinationArray[i] = lut[pSourceArray[i]];

// 후처리 /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.



