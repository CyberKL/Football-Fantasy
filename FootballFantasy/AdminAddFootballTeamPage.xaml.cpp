#include "pch.h"
#include "AdminAddFootballTeamPage.xaml.h"
#if __has_include("AdminAddFootballTeamPage.g.cpp")
#include "AdminAddFootballTeamPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t AdminAddFootballTeamPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AdminAddFootballTeamPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

}


void winrt::FootballFantasy::implementation::AdminAddFootballTeamPage::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.AdminPanelPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}
