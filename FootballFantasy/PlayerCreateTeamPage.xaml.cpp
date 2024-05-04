#include "pch.h"
#include "PlayerCreateTeamPage.xaml.h"
#if __has_include("PlayerCreateTeamPage.g.cpp")
#include "PlayerCreateTeamPage.g.cpp"
#endif
#include "Presenter.h"
#include <string>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <unordered_set>

using namespace std;
using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t PlayerCreateTeamPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void PlayerCreateTeamPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}

unordered_set<int> tempTeam;

void winrt::FootballFantasy::implementation::PlayerCreateTeamPage::AddFootballer(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    Controls::Button button = sender.as<Controls::Button>();
    string position = to_string(button.Content().as<Controls::StackPanel>().Children().GetAt(0).as<Controls::TextBlock>().Text());
    vector<Footballer> footballers;
    if (position == "GK")
        // search gk
        footballers = Presenter::getInstance()->searchFootballersByPosition("Goalkeeper");
    else if (position == "DEF")
        // search def
        footballers = Presenter::getInstance()->searchFootballersByPosition("Defender");
    else if (position == "MID") 
        // search mid
        footballers = Presenter::getInstance()->searchFootballersByPosition("Midfielder");
    else if (position == "FWD")
        // search fwd
        footballers = Presenter::getInstance()->searchFootballersByPosition("Forward");

    Controls::ListView listView;
    for (Footballer footballer : footballers)
    {
        if (tempTeam.find(footballer.getId()) != tempTeam.end())
            continue;

        Controls::Grid g;
        g.ColumnDefinitions().Append(Controls::ColumnDefinition());
        g.ColumnDefinitions().Append(Controls::ColumnDefinition());
        hstring footballerName = to_hstring(footballer.getName());
        Controls::TextBlock name = Controls::TextBlock();
        name.Text(footballerName);
        Controls::FontIcon f;
        f.Glyph(L"\uE946");
        f.FontSize(25);
        f.PointerEntered(Input::PointerEventHandler([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args) {
            Controls::ToolTip flyout;
            Controls::Grid flyoutGrid;
            flyoutGrid.ColumnDefinitions().Append(Controls::ColumnDefinition());
            flyoutGrid.ColumnDefinitions().Append(Controls::ColumnDefinition());
            flyoutGrid.RowDefinitions().Append(Controls::RowDefinition());
            flyoutGrid.RowDefinitions().Append(Controls::RowDefinition());
            flyoutGrid.RowDefinitions().Append(Controls::RowDefinition());
            flyoutGrid.RowSpacing(20);
            flyoutGrid.ColumnSpacing(40);

            Controls::TextBlock name;
            name.Text(to_hstring(footballer.getName()));
            name.HorizontalAlignment(HorizontalAlignment::Center);
            flyoutGrid.SetColumnSpan(name, 2);
            flyoutGrid.Children().Append(name);

            Controls::StackPanel sTeam;
            Controls::TextBlock hTeam;
            hTeam.Text(L"Team");
            Controls::TextBlock team;
            team.Text(to_hstring(footballer.getTeam()->getName()));
            sTeam.Children().Append(hTeam);
            sTeam.Children().Append(team);
            flyoutGrid.SetRow(sTeam, 1);
            flyoutGrid.Children().Append(sTeam);

            Controls::StackPanel sLeague;
            Controls::TextBlock hLeague;
            hLeague.Text(L"League");
            //hLeague.FontWeight(Windows::UI::Text::FontWeights::Bold());
            Controls::TextBlock league;
            league.Text(to_hstring(footballer.getLeagueName()));
            sLeague.Children().Append(hLeague);
            sLeague.Children().Append(league);
            flyoutGrid.SetRow(sLeague, 1);
            flyoutGrid.SetColumn(sLeague, 1);
            flyoutGrid.Children().Append(sLeague);

            Controls::StackPanel sPoints;
            Controls::TextBlock hPoints;
            hPoints.Text(L"Points");
            //hPoints.FontWeight(Windows::UI::Text::FontWeights::Bold());
            Controls::TextBlock points;
            points.Text(to_hstring(footballer.getTotalPoints()));
            sPoints.Children().Append(hPoints);
            sPoints.Children().Append(points);
            flyoutGrid.SetRow(sPoints, 2);
            flyoutGrid.Children().Append(sPoints);

            Controls::StackPanel sPrice;
            Controls::TextBlock hPrice;
            hPrice.Text(L"Price");
            //hPrice.FontWeight(Windows::UI::Text::FontWeights::Bold());
            Controls::TextBlock price;
            price.Text(to_hstring(footballer.priceToString()));
            sPrice.Children().Append(hPrice);
            sPrice.Children().Append(price);
            flyoutGrid.SetRow(sPrice, 2);
            flyoutGrid.SetColumn(sPrice, 1);
            flyoutGrid.Children().Append(sPrice);

            flyout.Content(flyoutGrid);
            Controls::ToolTipService::SetToolTip(f, flyout);

            }));
        f.HorizontalAlignment(HorizontalAlignment::Right);
        g.Name(to_hstring(footballer.getId()));
        g.Children().Append(name);
        g.SetColumn(f, 1);
        g.Children().Append(f);
        listView.Items().Append(g);
    }
    
    auto dialogButtonClickHandler = [=](winrt::Windows::Foundation::IInspectable const& senderr, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
        {
            auto parentDialog = senderr.as<Controls::ContentDialog>();
            auto listView = parentDialog.Content().as<Controls::ListView>();
            auto selectedGrid = listView.SelectedItem().as<Controls::Grid>();
            int footballerId = stoi(to_string(selectedGrid.Name()));
            tempTeam.insert(footballerId);
            Footballer footballer = Presenter::getInstance()->getFootballer(footballerId);
            FootballerControl footballerControl;
            footballerControl.PlayerName(to_hstring(footballer.getName()));
            footballerControl.PlayerInfo(to_hstring(Presenter::getInstance()->getFootballerNextMatch(footballerId)));
            auto grid = sender.as<Controls::Button>().Parent().as<Controls::Grid>();
            int column = Controls::Grid::GetColumn(sender.as<Controls::Button>());
            uint32_t indexToRemove;
            grid.Children().IndexOf(sender.as<Controls::Button>(), indexToRemove);
            grid.Children().RemoveAt(indexToRemove);
            grid.SetColumn(footballerControl, column);
            grid.Children().Append(footballerControl);
            tempTeam.size() == 15 ? SubmitBtn().IsEnabled(true) : SubmitBtn().IsEnabled(false);
        };

    Controls::ContentDialog dialog;
    dialog.XamlRoot(this->XamlRoot());
    dialog.RequestedTheme(ElementTheme::Light);
    dialog.PrimaryButtonText(L"Add");
    dialog.PrimaryButtonClick(dialogButtonClickHandler);
    dialog.CloseButtonText(L"Cancel");
    dialog.Content(listView);
    dialog.ShowAsync();
}


void winrt::FootballFantasy::implementation::PlayerCreateTeamPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    //BudgetTextBlock().Text(to_hstring(Presenter::getInstance()->getLoggedInPlayerBudget()));
}


void winrt::FootballFantasy::implementation::PlayerCreateTeamPage::SubmitBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    Presenter::getInstance()->createPlayerTeam(tempTeam);
}
