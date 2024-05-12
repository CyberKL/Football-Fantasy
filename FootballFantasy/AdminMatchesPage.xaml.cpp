#include "pch.h"
#include "AdminMatchesPage.xaml.h"
#if __has_include("AdminMatchesPage.g.cpp")
#include "AdminMatchesPage.g.cpp"
#endif
#include "Presenter.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t AdminMatchesPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AdminMatchesPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}


void winrt::FootballFantasy::implementation::AdminMatchesPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    MatchesGrid().Children().Clear();
    MatchesGrid().RowDefinitions().Clear();
    unordered_map<int, Match> matches = Presenter::getInstance()->getMatches()[Presenter::getInstance()->getCurrentGw()];
    unordered_map<int, Match>::iterator it;
    int count = 0;
    for (it = matches.begin(); it != matches.end(); it++)
    {
        MatchesGrid().RowDefinitions().Append(Controls::RowDefinition());
        Controls::TextBlock homeTeamTextBlock;
        Controls::TextBlock infoTextBlock;
        Controls::TextBlock awayTeamTextBlock;

        homeTeamTextBlock.Text(to_hstring(it->second.getHomeTeam()->getName()));
        it->second.getPlayed() ? infoTextBlock.Text(to_hstring(it->second.getScore())) : infoTextBlock.Text(L"VS");
        awayTeamTextBlock.Text(to_hstring(it->second.getAwayTeam()->getName()));

        Controls::Grid::SetColumn(infoTextBlock, 1);
        Controls::Grid::SetColumn(awayTeamTextBlock, 2);
        infoTextBlock.HorizontalAlignment(HorizontalAlignment::Center);
        awayTeamTextBlock.HorizontalAlignment(HorizontalAlignment::Right);

        Controls::Grid g;

        g.Children().Append(homeTeamTextBlock);
        g.Children().Append(infoTextBlock);
        g.Children().Append(awayTeamTextBlock);
        Controls::Button b;
        b.Content(g);
        b.Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
            {
                winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.AdminEditMatchesPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
                Frame().Navigate(page);
            });
        Controls::Grid::SetRow(b, count);

        MatchesGrid().Children().Append(b);
        
        count++;
    }
}
