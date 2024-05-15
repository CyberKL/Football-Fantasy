#include "pch.h"
#include "PlayerHomePage.xaml.h"
#if __has_include("PlayerHomePage.g.cpp")
#include "PlayerHomePage.g.cpp"
#endif
#include "Presenter.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t PlayerHomePage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void PlayerHomePage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}


void winrt::FootballFantasy::implementation::PlayerHomePage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    if (Presenter::getInstance()->getSeasonStarted())
    {
        MainPanel().Visibility(Visibility::Visible);
        int numOfGw = Presenter::getInstance()->getMatches().size();
        for (int i = 0; i < numOfGw; i++)
        {
            GwBox().Items().Append(winrt::box_value(to_hstring(i + 1)));
        }
        for (auto&& item : GwBox().Items())
        {
            if (item && item.as<hstring>() == to_hstring(Presenter::getInstance()->getCurrentGw()))
            {
                GwBox().SelectedItem(item);
                break;
            }
        }
    }
    else
    {
        Controls::TextBlock textBlock;
        textBlock.Text(L"Season has not started yet, please check back soon!");
        textBlock.HorizontalAlignment(HorizontalAlignment::Center);
        textBlock.VerticalAlignment(VerticalAlignment::Center);
        textBlock.FontSize(56);
        textBlock.TextAlignment(TextAlignment::Center);
        this->Content(textBlock);
    }
}


void winrt::FootballFantasy::implementation::PlayerHomePage::PreviousBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    int selectedIndex = GwBox().SelectedIndex();
    if (selectedIndex > 0)
    {
        GwBox().SelectedIndex(selectedIndex - 1);
    }
}


void winrt::FootballFantasy::implementation::PlayerHomePage::NextBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    int selectedIndex = GwBox().SelectedIndex();
    if (selectedIndex < GwBox().Items().Size() - 1)
    {
        GwBox().SelectedIndex(selectedIndex + 1);
    }
}


void winrt::FootballFantasy::implementation::PlayerHomePage::GwBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
{
    MatchesGrid().Children().Clear();
    MatchesGrid().RowDefinitions().Clear();
    int gw = stoi(to_string(sender.as<winrt::Microsoft::UI::Xaml::Controls::ComboBox>().SelectedItem().as<winrt::hstring>()));
    unordered_map<int, Match*> matches = Presenter::getInstance()->getMatches()[gw];

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
                int gameweek = stoi(to_string(GwBox().SelectedItem().as<winrt::hstring>()));
                Match* match = Presenter::getInstance()->getMatches()[gameweek][stoi(to_string(sender.as<Controls::Button>().Name()))];
                Presenter::getInstance()->setPressedMatch(match);
                winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerViewMatchPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
                Frame().Navigate(page);
            });
        infoTextBlock.FontSize(16);
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
        count++;
    }

}
