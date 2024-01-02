#include <Windows.h>
#include "App.h"
int main(){
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    App app;
    app.Run();
    return 0;
}
