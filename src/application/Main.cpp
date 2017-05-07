#include "Chat.h"

int main(int argc, char* argv[])
{
    Application* application = new Chat();
    application->Run();

    delete application;

    return 0;
}
