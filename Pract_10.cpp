#include <windows.h>
#include <conio.h>
#include <iostream>


volatile UINT w = 0;
volatile UINT w1 = 0;
volatile UINT w2 = 0;
DWORD WINAPI Factorial() {
    while (true) {
        int a = 1;
        for (int i = 1; i <= w; i++) {
            a = a * i;
        }

        w++;
    }
    return 0;
}
DWORD WINAPI Fibonachi() {
    while (true) {
        int a = 0;
        int b = 1;
        int c=0;
        for (int i = 2; i <= w1; i++)
        {
            c = a + b;
            a = b;
            b = c;
        }
        w1++;
    }
    return 0;
}
DWORD WINAPI Incremetnal () {
    int a = 0;
    while (true) {
        a++;
        w2++;
    }
    return 0;
}
int main()
{
    setlocale(0,"rus");
    STARTUPINFO si;
    HANDLE hThread[3];
    DWORD IDThread[3];
    hThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Fibonachi, NULL, HANDLE_FLAG_INHERIT, &IDThread[0]);
    if (hThread == NULL) {
        return GetLastError();
    }
    hThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Factorial, NULL, HANDLE_FLAG_INHERIT, &IDThread[1]);
    if (hThread == NULL) {
        return GetLastError();
    }
    hThread[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Incremetnal, NULL, HANDLE_FLAG_INHERIT, &IDThread[2]);
    if (hThread == NULL) {
        return GetLastError();
    }
    //SetPriorityClass(GetCurrentProcess(),5);
    
    HANDLE ThThread = GetCurrentProcess();
    /*
    if (!DuplicateHandle(
            GetCurrentProcess(),
            NULL,
            GetCurrentProcess(),
            &ThThread, 
            NULL, 
            TRUE, 
            NULL)) {
        return GetLastError();
    }*/
    std::cout << GetPriorityClass(ThThread) << std::endl;
    SetPriorityClass(ThThread, HIGH_PRIORITY_CLASS);
    std::cout << GetPriorityClass(ThThread) << std::endl;
    SetThreadPriority(hThread[1], THREAD_PRIORITY_BELOW_NORMAL);
    SetThreadPriority(hThread[2], THREAD_PRIORITY_IDLE);
    SetThreadPriority(hThread[0], THREAD_PRIORITY_HIGHEST);
    std::cout << GetPriorityClass(ThThread) << std::endl;
    std::cout << GetThreadPriority(hThread[0])+15 << std::endl;
    std::cout << GetThreadPriority(hThread[1])+15 << std::endl;
    std::cout << GetThreadPriority(hThread[2])+15 << std::endl;
    std::cin.get();
    while (true)
    {
        if (_kbhit) {

        }
        std::cout << "Фибоначи:" <<w1<< std::endl;
        std::cout << "Факториал:" <<w<< std::endl;
        std::cout << "Инкрементал:" <<w2<< std::endl;
        std::cout << "1-изменить приоритет потока Фибоначи"  << std::endl;
        std::cout << "2-изменить приоритет потока Факториала"  << std::endl;
        std::cout << "3-изменить приоритет потока Инкрементал"  << std::endl;
        Sleep(10000);
        system("cls");
    }
}