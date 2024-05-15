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
    bool seasonStarted = Presenter::getInstance()->getSeasonStarted();
    if (seasonStarted)
    {
        MainPanel().Visibility(Visibility::Visible);
        MatchesGrid().Children().Clear();
        MatchesGrid().RowDefinitions().Clear();
        unordered_map<int, Match*> matches = Presenter::getInstance()->getMatches()[Presenter::getInstance()->getCurrentGw()];
        hstring gameweek = to_hstring(Presenter::getInstance()->getCurrentGw());
        hstring gameweekText = L"Gameweek " + gameweek;
        GameweekBlock().Text(gameweekText);

        bool gwFinished = true;
        unordered_map<int, Match*>::iterator it;
        int count = 0;
        for (it = matches.begin(); it != matches.end(); it++)
        {
            MatchesGrid().RowDefinitions().Append(Controls::RowDefinition());
            Controls::TextBlock homeTeamTextBlock;
            Controls::Button infoTextBlock;
            Controls::TextBlock awayTeamTextBlock;

            homeTeamTextBlock.Text(to_hstring(it->second->getHomeTeam()->getName()));
            it->second->getPlayed() ? infoTextBlock.Content(winrt::box_value(to_hstring(it->second->getScore()))) : infoTextBlock.Content(winrt::box_value(L"VS"));
            infoTextBlock.Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
                {
                    int gameweek = stoi(to_string(GameweekBlock().Text()).substr(9));
                    Match* pressedMatch = Presenter::getInstance()->getMatches()[gameweek][stoi(to_string(sender.as<Controls::Button>().Name()))];
                    Presenter::getInstance()->setPressedMatch(pressedMatch);
                    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.AdminEditMatchesPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
                    Frame().Navigate(page);
                });
            infoTextBlock.FontSize(16);
            infoTextBlock.Name(to_hstring(it->second->getId()));
            awayTeamTextBlock.Text(to_hstring(it->second->getAwayTeam()->getName()));

            homeTeamTextBlock.VerticalAlignment(VerticalAlignment::Center);
            awayTeamTextBlock.VerticalAlignment(VerticalAlignment::Center);

            Controls::Grid::SetRow(homeTeamTextBlock, count);
            Controls::Grid::SetRow(infoTextBlock, count);
            Controls::Grid::SetRow(awayTeamTextBlock, count);
            Controls::Grid::SetColumn(infoTextBlock, 1);
            Controls::Grid::SetColumn(awayTeamTextBlock, 2);
            infoTextBlock.HorizontalAlignment(HorizontalAlignment::Center);
            awayTeamTextBlock.HorizontalAlignment(HorizontalAlignment::Right);

            MatchesGrid().Children().Append(homeTeamTextBlock);
            MatchesGrid().Children().Append(infoTextBlock);
            MatchesGrid().Children().Append(awayTeamTextBlock);
            if (!it->second->getPlayed()) gwFinished = false;
            count++;
        }
        FinishBtn().IsEnabled(gwFinished);
    }
    else
    {
        Controls::Button btn;
        btn.Content(winrt::box_value(L"Start Season"));
        btn.Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
            {
                Presenter::getInstance()->setSeasonStarted(true);
                Presenter::getInstance()->makeMatchesList();
                for (auto item : Frame().Parent().as<Controls::NavigationView>().MenuItems())
                {
                    if (item.as<Controls::NavigationViewItem>().Tag().as<winrt::hstring>() == L"Edit")
                    {
                        for (auto subItem : item.as<Controls::NavigationViewItem>().MenuItems())
                        {
                            if (subItem.as<Controls::NavigationViewItem>().Tag().as<winrt::hstring>() == L"FootballTeam") subItem.as<Controls::NavigationViewItem>().IsEnabled(false);
                        }
                    }
                }
                winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.AdminMatchesPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
                Frame().Navigate(page);
            });
        btn.HorizontalAlignment(HorizontalAlignment::Center);
        this->Content(btn);
    }
}


void winrt::FootballFantasy::implementation::AdminMatchesPage::FinishBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    Presenter::getInstance()->progressGameweek();
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.AdminMatchesPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}
