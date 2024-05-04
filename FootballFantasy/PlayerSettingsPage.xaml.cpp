#include "pch.h"
#include "PlayerSettingsPage.xaml.h"
#if __has_include("PlayerSettingsPage.g.cpp")
#include "PlayerSettingsPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t PlayerSettingsPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void PlayerSettingsPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}
