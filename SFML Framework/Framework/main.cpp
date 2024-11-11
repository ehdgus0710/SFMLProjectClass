#include "stdafx.h"

int main()
{
    FRAMEWORK.Init(1920, 1080, "SFML Framework");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    
    // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    return 0;
}