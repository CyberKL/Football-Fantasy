#include "pch.h"
#include "AdminRemoveFootballTeamPage.xaml.h"
#if __has_include("AdminRemoveFootballTeamPage.g.cpp")
#include "AdminRemoveFootballTeamPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t AdminRemoveFootballTeamPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AdminRemoveFootballTeamPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void AdminRemoveFootballTeamPage::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}
