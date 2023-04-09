#include<config.h>


using cv::Mat;
using std::cout;
using std::endl;



int main(int argc, char** argv) {
    options option;
    option.init();
    cout << "�Ƿ���ʾ����" << endl;
    cin >> option.is_show_windows;
    cout << "��ʼ��Ϸ��" << endl;

    std::thread main_Thread(&options::sendWrapper, &option);
    std::thread move_Thread(&mouse_control::receiveWrapper, &option.pid);
    std::thread auto_fire_Thread(&auto_fire::receive1Wrapper, &option.pid.Auto_fire);

    main_Thread.join();
    move_Thread.join();
    auto_fire_Thread.join();
    return 0;
}
