#include "pch.h"
#include "AdminEditMatchesPage.xaml.h"
#if __has_include("AdminEditMatchesPage.g.cpp")
#include "AdminEditMatchesPage.g.cpp"
#endif
#include "Presenter.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t AdminEditMatchesPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AdminEditMatchesPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

}


void winrt::FootballFantasy::implementation::AdminEditMatchesPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    /*Match match = Presenter::getInstance()->getPressedMatch();

    HomeTeamBlock().Text(to_hstring(match.getHomeTeam()->getName()));
    AwayTeamBlock().Text(to_hstring(match.getAwayTeam()->getName()));*/


}
