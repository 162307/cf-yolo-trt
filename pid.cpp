#include<pid.h>

void pid_move::move()
{
    while (1)
    {
        std::unique_lock<std::mutex> lock(data_mutex_);
        data_cond_.wait(lock, [this] { return data_ready_; });
        //std::cout << Type << " " << target_position << " " << Kp << " " << std::endl;
        while (abs(position - target_position) > 0.3)
        {
            // �������
            error = target_position - position;

            // ���������
            integral += error;

            // ����΢����
            derivative = error - last_error;

            // ������һ�ε����
            last_error = error;

            // ���������
            double control = Kp * error + Ki * integral + Kd * derivative;

            // ��������������Ϊ�ƶ��ľ���
            double move_distance = control;

            if (Type == 1)
            {
                mouse_event(MOUSEEVENTF_MOVE, move_distance, 0, 0, 0);
            }
            else
            {
                mouse_event(MOUSEEVENTF_MOVE, 0, move_distance, 0, 0);
            }

            // ����λ��
            position += move_distance;
        }
        //std::cout << 1 << std::endl;
        refresh();
        data_ready_ = false;
    }
}

void pid_move::refresh()
{
    position = 0.0;
    integral = 0.0;
    last_error = 0.0;
}

void pid_move::init(double kp, double ki, double kd, int type)
{
    Kp = kp;
    Ki = ki;
    Kd = kd;
    Type = type;
}