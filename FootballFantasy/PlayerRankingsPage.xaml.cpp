#include "pch.h"
#include "PlayerRankingsPage.xaml.h"
#if __has_include("PlayerRankingsPage.g.cpp")
#include "PlayerRankingsPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t PlayerRankingsPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void PlayerRankingsPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}
