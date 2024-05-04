#include "pch.h"
#include "PlayerTeamPage.xaml.h"
#if __has_include("PlayerTeamPage.g.cpp")
#include "PlayerTeamPage.g.cpp"
#endif
#include "PlayerTeam.h"
#include "Presenter.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t PlayerTeamPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void PlayerTeamPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}


void winrt::FootballFantasy::implementation::PlayerTeamPage::PickTeamBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerTeamPickTeamPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom}; // Set Page
    Frame().Navigate(page);
}


void winrt::FootballFantasy::implementation::PlayerTeamPage::TransfersBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{

}


void winrt::FootballFantasy::implementation::PlayerTeamPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    PlayerTeam* playerTeam = Presenter::getInstance()->getPlayerTeam();
    if (playerTeam == nullptr)
    {
        // Prompt the user to create a team
        winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerCreateTeamPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
        Frame().Navigate(page);
    }
}