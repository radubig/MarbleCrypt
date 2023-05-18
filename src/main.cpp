#include "GameApp.h"
#include "Exceptions.h"
#include <iostream>

#ifdef __linux__
#include <X11/Xlib.h>
#endif

int main()
{
#ifdef __linux__
    XInitThreads();
#endif

    try
    {
        GameApp app;
        app.SetResolution(1340, 820);
        app.SetFramerateLimit(144);
        app.InitWindow();
        app.Run();
    }
    catch(const ResourceLoadException& err)
    {
        std::cerr << "[Resource Load Exception]: " << err.what() << "\n";
    }
    catch(const InvalidDataException& err)
    {
        std::cerr << "[Invalid Data Exception]: " << err.what() << "\n";
    }
    catch(const std::runtime_error& err)
    {
        std::cerr << "[Runtime Error Exception]: " << err.what() << "\n";
    }
    catch(...)
    {
        std::cerr << "An unknown exception has occured!\n";
    }
    return 0;
}
