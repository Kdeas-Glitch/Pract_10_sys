#include <windows.h>
#include <conio.h>
#include <math.h>
#include <iostream>


volatile UINT w = 0;
volatile UINT w1 = 0;
volatile UINT w2 = 0;
volatile UINT w3 = 0;
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

DWORD WINAPI Mass() {
    int a = 1;
    while (a!=-1) {
        for (int i = 0; i <= 100; i++)
        {
            a = std::pow(a, i) * pow(i, -a);

        }
        switch (a) {
        case 'Ъ':
            break;
        case 'Х':
            break;
        case 'Э':
            break;
        case 'Я':
            break;
        }
        w3++;
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
    HANDLE hThreadS=NULL;
    DWORD IDThreadS=NULL;
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
    /*hThreadS = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Mass, NULL, HANDLE_FLAG_INHERIT, &IDThreadS);
    if (hThreadS == NULL) {
        return GetLastError();
    }
    SetThreadPriority(hThreadS, THREAD_PRIORITY_TIME_CRITICAL);
    SuspendThread(hThreadS);*/
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
   /* std::cout << GetPriorityClass(ThThread) << std::endl;
    SetPriorityClass(ThThread, HIGH_PRIORITY_CLASS);
    std::cout << GetPriorityClass(ThThread) << std::endl;*/
    SetThreadPriority(hThread[0], THREAD_PRIORITY_HIGHEST);
    SetThreadPriority(hThread[1], THREAD_PRIORITY_BELOW_NORMAL);
    SetThreadPriority(hThread[2], THREAD_PRIORITY_IDLE);
    std::cout << GetPriorityClass(ThThread) << std::endl;
    std::cout << GetThreadPriority(hThread[0]) << std::endl;//2
    std::cout << GetThreadPriority(hThread[1]) << std::endl;//-1
    std::cout << GetThreadPriority(hThread[2]) << std::endl;//-15
    int a = 0;

    int u = 0;
    while (a!='5')
    {
        a = 0;
        std::cout << "Фибоначи:" <<w1<<" Приоритет:" << GetThreadPriority(hThread[0]) << std::endl;
        std::cout << "Факториал:" <<w<< " Приоритет:" << GetThreadPriority(hThread[1]) << std::endl;
        std::cout << "Инкрементал:" <<w2<< " Приоритет:" << GetThreadPriority(hThread[2]) << std::endl;
        if (hThreadS != NULL) {
            std::cout << "Выдавливатель:" << w3 << " Приоритет:" << GetThreadPriority(hThreadS) << std::endl;
            if (u < 10) {
                u++;
            }
            else {
                SetThreadPriority(hThreadS, THREAD_PRIORITY_NORMAL);

            }
        }
        std::cout << "1-изменить приоритет потока Фибоначи"  << std::endl;
        std::cout << "2-изменить приоритет потока Факториала"  << std::endl;
        std::cout << "3-изменить приоритет потока Инкрементал"  << std::endl;
        std::cout << "4-Запустить выдавливатель программ" << std::endl;
        std::cout << "5-Выйти" << std::endl;
        if (_kbhit()) {
            a = _getch();
        }
        switch (a) {
        case '1':
            if (GetThreadPriority(hThread[0]) == 2) {
                SetThreadPriority(hThread[0], THREAD_PRIORITY_ABOVE_NORMAL);
            }
            else {
                SetThreadPriority(hThread[0], THREAD_PRIORITY_HIGHEST);
            }
            break;
        case '2':
            if (GetThreadPriority(hThread[1]) == -1) {
                SetThreadPriority(hThread[1], THREAD_PRIORITY_NORMAL);
            }
            else {
                SetThreadPriority(hThread[1], THREAD_PRIORITY_BELOW_NORMAL);
            }
            break;
        case '3':
            if (GetThreadPriority(hThread[2]) == -15) {
                SetThreadPriority(hThread[2], THREAD_PRIORITY_LOWEST);
            }
            else {
                SetThreadPriority(hThread[2], THREAD_PRIORITY_IDLE);
            }
            break;
        case '4':
            hThreadS = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Mass, NULL, HANDLE_FLAG_INHERIT, &IDThreadS);
            if (hThreadS == NULL) {
                return GetLastError();
            }
            SetThreadPriority(hThreadS, THREAD_PRIORITY_TIME_CRITICAL);
            break;
        }
        Sleep(1000);
        
        system("cls");
    }
    CloseHandle(hThread[0]);
    CloseHandle(hThread[1]);
    CloseHandle(hThread[2]);
    CloseHandle(hThreadS);
}