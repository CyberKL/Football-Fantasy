#include "pch.h"
#include "AdminPanelPage.xaml.h"
#if __has_include("AdminPanelPage.g.cpp")
#include "AdminPanelPage.g.cpp"
#endif


using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t AdminPanelPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AdminPanelPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void AdminPanelPage::Navigate(hstring pageName)
    {
        winrt::Windows::UI::Xaml::Interop::TypeName page = { pageName, winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
        AdminFrame().Navigate(page);
    }




    void winrt::FootballFantasy::implementation::AdminPanelPage::NavView_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args)
    {
        if (args.SelectedItem())
        {
            winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem selectedItem = args.SelectedItem().as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>();
            if (selectedItem.IsSelected())
            {
                hstring tag = selectedItem.Tag().as<winrt::hstring>();
                if (tag == L"Matches")
                    Navigate(L"FootballFantasy.AdminMatchesPage");
                else if (tag == L"Footballers")
                    Navigate(L"FootballFantasy.AdminEditFootballerPage");
                else if (tag == L"FootballTeam")
                    Navigate(L"FootballFantasy.AdminEditFootballteamPage");

                else if (tag == L"Logout")
                {
                    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.SignUpPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
                    Frame().Navigate(page);
                }
            }
        }
    }
    
}



void winrt::FootballFantasy::implementation::AdminPanelPage::NavView_BackRequested(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewBackRequestedEventArgs const& args)
{
    if(AdminFrame().CanGoBack()) AdminFrame().GoBack();
}


void winrt::FootballFantasy::implementation::AdminPanelPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    //winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.AdminMatchesPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    //AdminFrame().Navigate(page);
}
