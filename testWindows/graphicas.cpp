#include "stdafx.h"
#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>

void drawWindow(HWND hWnd)
{
	ID2D1Factory *pD2DFactory = nullptr;
	D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&pD2DFactory
	);

	ID2D1HwndRenderTarget *pRT = nullptr;
	RECT rc;
	GetClientRect(hWnd, &rc);
	HRESULT hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hWnd,
			D2D1::SizeU(
				rc.right - rc.left,
				rc.bottom - rc.top)
		),
		&pRT
	);

	ID2D1SolidColorBrush *pBlackBrush = nullptr;
	if (SUCCEEDED(hr))
	{
		pRT->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),
			&pBlackBrush
		);
	}

	IDWriteFactory *pWriteFactory = nullptr;
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(pWriteFactory),
		reinterpret_cast<IUnknown **>(&pWriteFactory)
	);

	IDWriteTextFormat *pTextFormat = nullptr;
	pWriteFactory->CreateTextFormat(
		L"Arial Block",
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		44,
		L"",
		&pTextFormat
	);

	pRT->BeginDraw();
	pRT->DrawRectangle(
		D2D1::RectF(
			100.0f,
			100.0f,
			200.0f,
			200.0f
		),
		pBlackBrush
	);

	const wchar_t *str = L"hello world";
	pRT->DrawTextW(
		str,
		wcslen(str),
		pTextFormat,
		D2D1::RectF(
			50.0f,
			50.0f,
			500.0f,
			100.0f
		),
		pBlackBrush
	);

	pRT->EndDraw();
}