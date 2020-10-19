// UDPClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#pragma comment(lib,"ws2_32.lib")

#include <iostream>

#include <winsock2.h>
#include <WS2tcpip.h>

int main()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    int num;
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        return 1;
    }

    /* Confirm that the WinSock DLL supports 2.2.*/
    /* Note that if the DLL supports versions greater    */
    /* than 2.2 in addition to 2.2, it will still return */
    /* 2.2 in wVersion since that is the version we      */
    /* requested.                                        */

    if (LOBYTE(wsaData.wVersion) != 2 ||
        HIBYTE(wsaData.wVersion) != 2) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        WSACleanup();
        return 1;
    }

    // 创建套接字
    SOCKET sockclient = socket(AF_INET,SOCK_DGRAM,0);

    num = WSAGetLastError();

    //发送数据

    SOCKADDR_IN addrSrv;
    inet_pton(AF_INET,"127.0.0.1",&addrSrv.sin_addr);
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htonl(6000);

    sendto(sockclient,"This is UDP Client!",strlen("This is UDP Client!")*1,0, (SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
    num = WSAGetLastError();
    // 关闭套接字
    closesocket(sockclient);
    WSACleanup();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
