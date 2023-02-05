#include<pid.h>
int pid_control::fire(float* Boxes, int* ClassIndexs, int* BboxNum, int isHead)
{
	int min_value = 9999;
	cv::Rect aim;
	if (*BboxNum > 100)
	{
		cout << "too much aim" << endl;
		return 0;
	}
	for (int i = 0; i < BboxNum[0]; i++)
	{
		if (ClassIndexs[i] == 1)
			continue;

		cv::Rect rect(Boxes[i * 4], Boxes[i * 4 + 1], Boxes[i * 4 + 2], Boxes[i * 4 + 3]);
		if (sqrt(pow((rect.x - 208), 2) + pow((rect.y - 208), 2)) < min_value)
		{
			min_value = sqrt(pow((rect.x - 208), 2) + pow((rect.y - 208), 2));
			aim = rect;
		}
	}
	if (aim.x == 0 && aim.y == 0)
	{
		cout << "no aim" << endl;
		return 0;
	}
	float pos_x = ((aim.x + aim.width / 2.0f - 208) / 416);
	float pos_y = ((aim.y + aim.height / 2.0f - 208) / 416);
	float w = aim.width / 416.0f;
	float h = aim.height / 416.0f;
    
    float offset_x = pos_x * 416;
    float offset_y = pos_y * 416;
    // x����pid����
    float pid_x_p = kx_p * offset_x;
    pid_x_I = pid_x_I + offset_x * kx_i;
    float pid_x_d = (last_offset_x - offset_x) * kx_d;
    if (pid_x_I > max_i) {
        pid_x_I = max_i;
    }
    else if (pid_x_I < -max_i) {
        pid_x_I = -max_i;
    }
    //y����pid����
    float pid_y_p = ky_p * offset_y;
    pid_y_I = pid_y_I + offset_x * kx_i;
    float pid_y_d = (last_offset_x - offset_x) * kx_d;
    if (pid_y_I > max_i) {
        pid_y_I = max_i;
    }
    else if (pid_y_I < -max_i) {
        pid_y_I = -max_i;
    }

    int rel_x = int(pid_x_p + pid_x_I + pid_x_d);
    int rel_y = int(pid_y_p + pid_y_I + pid_y_d);
    //cout << rel_x << " " << rel_y << endl;
    // ͷ����׼
    if (isHead == 1) {
        // ��һ֡�ƶ�    ��֡����
        if (first_move) {
            offset_x = pos_x * 416;
            pid_x_p = 0.83 * offset_x;
            rel_x = int(pid_x_p);
            offset_y = ((pos_y - w * 0.55) * 416);
            int pidy_p = int(0.98 * offset_y);
            rel_y = int(pidy_p);
            pid_x_I = 0;
            pid_y_I = 0;
        }
        if (abs(rel_y) < 250 && abs(rel_x) < 250 && abs(rel_y) > 0 && abs(rel_x) > 0)
        {
            mouse_event(MOUSEEVENTF_MOVE, rel_x, rel_y, 0, 0);
        }
    }
    // ������׼
    else if (isHead == 0) {
        // ��һ֡�ƶ�    ��֡����
        if (first_move) {
            offset_x = pos_x * 416;
            pid_x_p = 0.83 * offset_x;
            rel_x = int(pid_x_p);
            offset_y = ((pos_y - w * 0.3) * 416);
            int pidy_p = int(0.98 * offset_y);
            rel_y = int(pidy_p);
            pid_y_I = 0;
        }
        if (abs(rel_y) < 250 && abs(rel_x) < 250 && abs(rel_y) > 0 && abs(rel_x) > 0)
        {
            cout << 1 << endl;
            mouse_event(MOUSEEVENTF_MOVE, rel_x, rel_y, 0, 0);
        }
    }
    last_offset_x = offset_x;
    first_move = 0;
}
void pid_control::rec()
{
    last_offset_x = 0;  // ��һ�ν�ͼʱ�Ĺ۲���� 
    last_offset_y = 0;
    pid_x_I = 0;        // x����I���ۼ�ֵ
    pid_y_I = 0;        // y����I���ۼ�ֵ
    kx_p = 0.2;    // X������P�Ĳ���
    kx_i = 0.01;        // X������I�Ĳ���
    kx_d = 0.1;        //X�����ϵ�D����
    ky_p = 0.2;      // Y������P�Ĳ���
    ky_i = 0.01;      // Y������I�Ĳ���
    ky_d = 0.1;       // Y������D�Ĳ���
    first_move = 1;     // �Ƿ�Ϊ��һ���ƶ�
}