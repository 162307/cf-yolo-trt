/*��ͨ�����зֱ���
ǡ���҂��ۺ�һ��
����ֱ��ʞ�1920
Ȼ���Ǵ����Α�*/
#pragma once
#include<windows.h>
#include<math.h>
float pi = 3.1416;
float fov_x(float delta_x) {
	float FOV = 106.260205;
	int width = 1920;
	int pixel_x = 4800;   //���������Ҳ�����
	float per_pixel_rad = pixel_x / (2 * pi);
	float delta_abs_x = abs((int)delta_x);
	float sup_distance = (width / 2) / tan((FOV * pi / 180) / 2);
	float target_angle_rad = atan(delta_abs_x / sup_distance);
	float target_move = target_angle_rad * per_pixel_rad;
	float flag = delta_x;
	if (flag < 0) {
		return (-1) * target_move;
	}
	else {
		return target_move;
	}
}
//��׌Y�S���c�㷨
//�H�y�m����������Α�
//������    ����ֵ = fov_x(X�����Ƅ�ֵ);





