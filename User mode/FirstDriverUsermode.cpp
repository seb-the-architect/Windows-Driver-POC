#include <iostream>

#include "kernelinterface.h"

int main()
{
    KernelInterface kernelInterface = ("\\\\.\\ghLink");

    ULONG address = kernelInterface.GetClientAddress();

    if (address == -1)
    {
        std::cout << "failed :(" << std::endl;
    }

    std::cout << std::hex << address << std::endl;

    Sleep(10000);

    return 0;

}
