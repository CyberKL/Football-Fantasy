#include "pch.h"
#include "PlayerPage.xaml.h"
#if __has_include("PlayerPage.g.cpp")
#include "PlayerPage.g.cpp"
#endif

#include <winrt/Microsoft.UI.Xaml.Controls.h>

#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>

#include <winrt/Microsoft.UI.Xaml.Navigation.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t PlayerPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void PlayerPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void PlayerPage::Navigate(hstring pageName)
    {
        winrt::Windows::UI::Xaml::Interop::TypeName page = { pageName, winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
        PlayerFrame().Navigate(page);
    }
}


void winrt::FootballFantasy::implementation::PlayerPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    Navigate(L"FootballFantasy.PlayerHomePage"); // PlayerHomePage
}


void winrt::FootballFantasy::implementation::PlayerPage::NavView_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args)
{
    if (args.SelectedItem())
    {
        winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem selectedItem = args.SelectedItem().as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>();
        if (selectedItem.IsSelected())
        {
            hstring tag = selectedItem.Tag().as<winrt::hstring>();
            if (tag == L"HomePage")
                Navigate(L"FootballFantasy.PlayerHomePage");
            else if (tag == L"TeamPage")
                Navigate(L"FootballFantasy.PlayerTeamPage");
            else if (tag == L"RankingsPage")
                Navigate(L"FootballFantasy.PlayerRankingsPage");
            else if (tag == L"MorePage")
                Navigate(L"FootballFantasy.PlayerMorePage");
            else if (tag == L"Settings")
                Navigate(L"FootballFantasy.PlayerSettingsPage");
        }
    }
}

void winrt::FootballFantasy::implementation::PlayerPage::NavView_BackRequested(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewBackRequestedEventArgs const& args)
{
    if(PlayerFrame().CanGoBack())
        PlayerFrame().GoBack();
}
