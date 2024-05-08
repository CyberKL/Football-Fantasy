#include "pch.h"
#include "PlayerRankingsPage.xaml.h"
#if __has_include("PlayerRankingsPage.g.cpp")
#include "PlayerRankingsPage.g.cpp"
#endif
#include "Presenter.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t PlayerRankingsPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void PlayerRankingsPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}


void winrt::FootballFantasy::implementation::PlayerRankingsPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    // Displaying current gw rankings
    map<int, vector<string>> gwRankings = Presenter::getInstance()->getCurrentGwRankings();
    map<int, vector<string>>::iterator it;
    int pos = 1;
    for (it = gwRankings.begin(); it != gwRankings.end(); it++)
        for (int i = 0; i < it->second.size(); i++)
        {
            GwRankingsGrid().RowDefinitions().Append(Controls::RowDefinition());

            Controls::TextBlock posTextBlock;
            Controls::TextBlock usernameTextBlock;
            Controls::TextBlock pointsTextBlock;

            posTextBlock.Text(to_hstring(pos));
            usernameTextBlock.Text(to_hstring(it->second[i]));
            pointsTextBlock.Text(to_hstring(it->first));

            Controls::Grid::SetRow(posTextBlock, pos - 1);
            Controls::Grid::SetRow(usernameTextBlock, pos - 1);
            Controls::Grid::SetRow(pointsTextBlock, pos - 1);
            Controls::Grid::SetColumn(usernameTextBlock, 1);
            Controls::Grid::SetColumn(pointsTextBlock, 2);

            GwRankingsGrid().Children().Append(posTextBlock);
            GwRankingsGrid().Children().Append(usernameTextBlock);
            GwRankingsGrid().Children().Append(pointsTextBlock);

            pos++;
        }

    // Displaying Total Rankings
    map<int, vector<string>> totalRankings = Presenter::getInstance()->getTotalRankings();
    pos = 1;
    for (it = totalRankings.begin(); it != totalRankings.end(); it++)
        for (int i = 0; i < it->second.size(); i++)
        {
            TotalRankingsGrid().RowDefinitions().Append(Controls::RowDefinition());

            Controls::TextBlock posTextBlock;
            Controls::TextBlock usernameTextBlock;
            Controls::TextBlock pointsTextBlock;

            posTextBlock.Text(to_hstring(pos));
            usernameTextBlock.Text(to_hstring(it->second[i]));
            pointsTextBlock.Text(to_hstring(it->first));

            Controls::Grid::SetRow(posTextBlock, pos - 1);
            Controls::Grid::SetRow(usernameTextBlock, pos - 1);
            Controls::Grid::SetRow(pointsTextBlock, pos - 1);
            Controls::Grid::SetColumn(usernameTextBlock, 1);
            Controls::Grid::SetColumn(pointsTextBlock, 2);

            TotalRankingsGrid().Children().Append(posTextBlock);
            TotalRankingsGrid().Children().Append(usernameTextBlock);
            TotalRankingsGrid().Children().Append(pointsTextBlock);

            pos++;
        }
}
