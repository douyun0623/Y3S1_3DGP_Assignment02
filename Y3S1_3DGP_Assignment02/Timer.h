#pragma once
#include "stdafx.h"

//------------------------------------------------------------------------------------
//-------------------------------------CGameTimer-------------------------------------
//------------------------------------------------------------------------------------
/* 컴퓨터가 성능 카운터(Performance Counter) 하드웨어를 가지고 있으면 
성능 카운터와 성능 주파수(Performance Frequency)를 사용하여 시간 단위를 설정한다. 
성능 주파수를 사용할 수 없으면 멀티미디어 타이머를 사용한다. 
이 경우 시간 단위는 0.001초(Millisecond)이다. 
성능 카운터에 대한 자세한 설명은 윈도우 API 도움말을 참조하라. */

const ULONG MAX_SAMPLE_COUNT = 50; // 50회의 프레임 처리시간을 누적하여 평균한다.


class CGameTimer
{
public:
	CGameTimer();
	~CGameTimer();

	void Start() { }
	void Stop() { }
	void Reset();

	// 타이머의 시간을 갱신
	void Tick(float fLockFPS = 0.0f); 

	// 프레임 레이트 반환
	unsigned long GetFrameRate(LPTSTR lpszString = nullptr, int nCharacters = 0);

	// 프레임의 평균 경과 시간 반환
	float GetTimeElapsed();

private:
	// 컴퓨터가 Performance Counter를 가지고 있는가
	bool m_bHardwareHasPerformanceCounter;

	// Scale Counter의 양
	float m_fTimeScale;

	// 마지막 프레임 이후 지나간 시간
	float m_fTimeElapsed;

	// 현재의 시간
	__int64 m_nCurrentTime;

	// 마지막 프레임의 시간
	__int64 m_nLastTime;

	// 컴퓨터의 Performance Frequency
	__int64 m_nPerformanceFrequency;

	// 프레임 시간을 누적하기 위한 배열
	float m_fFrameTime[MAX_SAMPLE_COUNT];

	// 누적된 프레임 횟수
	ULONG m_nSampleCount;

	// 현재의 프레임 레이트
	unsigned long m_nCurrentFrameRate;

	// 초당 프레임 수
	unsigned long m_nFramesPerSecond;

	// 프레임 레이트 계산 소요 시간
	float m_fFPSTimeElapsed;

	bool m_bStopped;
};

