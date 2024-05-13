#include "pch.h"
#include "AdminChangeTeamPage.xaml.h"
#if __has_include("AdminChangeTeamPage.g.cpp")
#include "AdminChangeTeamPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t AdminChangeTeamPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AdminChangeTeamPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void AdminChangeTeamPage::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}
