
#include <iostream>
#include <windows.h>
#define baseAddress 0x006a9ec0
int mddain()
{
    unsigned int baseValue = 0;
    unsigned int fstValue = 0;
    unsigned int secValue = 0;
    unsigned int fstOffest = 0x768;
    unsigned int secOffset = 0x5560;
    HWND gameWindow = FindWindow("MainWindow",NULL);
    if(gameWindow == NULL)
    {
        std::cout<<"Get window failed"<<std::endl<<GetLastError();
        return -1;
    }
    DWORD processId;
    GetWindowThreadProcessId(gameWindow,&processId);
    if(processId == 0)
    {
        std::cout<<"Get process's id failed"<<std::endl<<GetLastError();
        return -1;
    }
    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS,false,processId);
    if(process == NULL)
    {
        std::cout<<"Open process failed"<<std::endl<<GetLastError();
        return -1;
    }
    if(NULL == ReadProcessMemory(process,(LPCVOID)baseAddress,&baseValue,sizeof(DWORD),0))
    {
        std::cout<<"Read prc memory failed"<<std::endl<<GetLastError();
        return -1;
    }
    if(NULL == ReadProcessMemory(process,(LPCVOID)(baseValue + fstOffest),&fstValue,sizeof(DWORD),0))
    {
        std::cout<<"Read prc memory (first offset)"<<std::endl<<GetLastError();
        return -1;
    }
    if(NULL == ReadProcessMemory(process,(LPVOID)(fstValue + secOffset),&secOffset,sizeof(DWORD),0))
    {
        std::cout<<"Read prc memory (second offset)"<<std::endl<<GetLastError();
        return -1;
    }
    std::cout<<secValue;

    return 0;
}
