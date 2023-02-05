#define NOMINMAX
#include<iostream>
#include<windows.h>
#include<opencv2/opencv.hpp>
#include<math.h>

using cv::Mat;
using std::cout;
using std::endl;
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
class pid_control
{
private:
	float last_offset_x = 0;  // ��һ�ν�ͼʱ�Ĺ۲���� 
	float last_offset_y = 0;
	float pid_x_I = 0;        // x����I���ۼ�ֵ
	float pid_y_I = 0;        // y����I���ۼ�ֵ
	float kx_p = 0.2;    // X������P�Ĳ���
	float kx_i = 0.01;        // X������I�Ĳ���
	float kx_d = 0.1;        //X�����ϵ�D����
	float ky_p = 0.2;      // Y������P�Ĳ���
	float ky_i = 0.01;      // Y������I�Ĳ���
	float ky_d = 0.1;       // Y������D�Ĳ���
	int first_move = 1;     // �Ƿ�Ϊ��һ���ƶ�
	int max_i = 50;
public:
	int fire(float* Boxes, int* ClassIndexs, int* BboxNum, int isHead);
	void rec();
};