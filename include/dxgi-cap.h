#define NOMINMAX
#include<iostream>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <dxgi1_3.h>
#include <dxgi1_5.h>
#include <opencv2/highgui/highgui_c.h>
#include<opencv2/opencv.hpp>
#pragma comment(lib, "d3d11.lib") 
#pragma comment(lib, "dxgi.lib")

#define show_windows 1
#define do_not_show_windows 0

using namespace cv;
using namespace std;

class dxgi_cap
{
private:
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	IDXGIOutputDuplication* desktopDupl = nullptr;
	UINT output = 0;
	DXGI_OUTDUPL_FRAME_INFO frameInfo;
	// �������ͼ��
	ID3D11Texture2D* acquiredDesktopImage = nullptr;
	bool timeOut;
	HRESULT ret;
	HRESULT initDXGIResources(ID3D11Device** device, ID3D11DeviceContext** deviceContext);
	void clearDXGIResources(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	HRESULT initDuplication(ID3D11Device* device, IDXGIOutputDuplication** dupl, UINT output);
	void clearDuplication(IDXGIOutputDuplication* dupl);
	HRESULT getFrame(IDXGIOutputDuplication* dupl, DXGI_OUTDUPL_FRAME_INFO* frameInfo, ID3D11Texture2D** texture2D, bool* timeOut);
	HRESULT doneWithFrame(IDXGIOutputDuplication* dupl);
	void saveDesktopImage(ID3D11Texture2D* data, ID3D11Device* device, ID3D11DeviceContext* deviceContext, cv::Mat* img);
public:
	void init();
	void release();
	cv::Mat get_img(int is_show);
};