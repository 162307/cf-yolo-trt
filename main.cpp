#include<config.h>


using cv::Mat;
using std::cout;
using std::endl;



int main(int argc, char** argv) {
    options option;
    //getchar();
    option.init();
    cout << "�Ƿ���ʾ����" << endl;
    cin >> option.is_show_windows;
    cout << "��ʼ��Ϸ��" << endl;

    std::thread main_Thread(&options::sendWrapper, &option);
    std::thread move_Thread(&pid_move::receiveWrapper2, &option.mouse.pid);
    std::thread smooth_Thread(&pid_move::receiveWrapper3, &option.mouse.pid);

    main_Thread.join();
    move_Thread.join();
    smooth_Thread.join();
    return 0;
}
