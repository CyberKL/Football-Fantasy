#include "pch.h"
#include "PlayerHomePage.xaml.h"
#if __has_include("PlayerHomePage.g.cpp")
#include "PlayerHomePage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t PlayerHomePage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void PlayerHomePage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}
