#include "pch.h"
#include "AdminEditFootballerPage.xaml.h"
#if __has_include("AdminEditFootballerPage.g.cpp")
#include "AdminEditFootballerPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t AdminEditFootballerPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AdminEditFootballerPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    
}



void winrt::FootballFantasy::implementation::AdminEditFootballerPage::ChangeTeam_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.AdminChangeTeamPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);

}


void winrt::FootballFantasy::implementation::AdminEditFootballerPage::RemoveFootballer_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.AdminRemoveFootballerPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);

}


void winrt::FootballFantasy::implementation::AdminEditFootballerPage::AddFootballer_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.AdminAddFootballer", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}
