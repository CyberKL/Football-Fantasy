#include "pch.h"
#include "PlayerCreateTeamPage.xaml.h"
#if __has_include("PlayerCreateTeamPage.g.cpp")
#include "PlayerCreateTeamPage.g.cpp"
#endif
#include "Presenter.h"
#include <string>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <unordered_set>
#include <sstream>
#include <iomanip>
#include <winrt/Windows.UI.Text.h>
#include <winrt/Windows.UI.h>

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
int luckyFootballerId = -1;
int budget = 100000;

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
            hTeam.FontWeight(Windows::UI::Text::FontWeights::Bold());
            Controls::TextBlock team;
            team.Text(to_hstring(footballer.getTeam()->getName()));
            sTeam.Children().Append(hTeam);
            sTeam.Children().Append(team);
            flyoutGrid.SetRow(sTeam, 1);
            flyoutGrid.Children().Append(sTeam);

            Controls::StackPanel sLeague;
            Controls::TextBlock hLeague;
            hLeague.Text(L"League");
            hLeague.FontWeight(Windows::UI::Text::FontWeights::Bold());
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
            hPoints.FontWeight(Windows::UI::Text::FontWeights::Bold());
            Controls::TextBlock points;
            points.Text(to_hstring(footballer.getTotalPoints()));
            sPoints.Children().Append(hPoints);
            sPoints.Children().Append(points);
            flyoutGrid.SetRow(sPoints, 2);
            flyoutGrid.Children().Append(sPoints);

            Controls::StackPanel sPrice;
            Controls::TextBlock hPrice;
            hPrice.Text(L"Price");
            hPrice.FontWeight(Windows::UI::Text::FontWeights::Bold());
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
        if (footballer.getId() == luckyFootballerId) g.Background(Media::SolidColorBrush(Windows::UI::Colors::DarkBlue()));
        listView.Items().Append(g);
    }
    
    

    auto dialogButtonClickHandler = [=](winrt::Windows::Foundation::IInspectable const& dialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
        {
            auto parentDialog = dialog.as<Controls::ContentDialog>();
            auto listView = parentDialog.Content().as<Controls::ListView>();
            if (listView.SelectedItem() != nullptr)
            {
                auto selectedGrid = listView.SelectedItem().as<Controls::Grid>();
                int footballerId = stoi(to_string(selectedGrid.Name()));
                tempTeam.insert(footballerId);
                Footballer footballer = Presenter::getInstance()->getFootballer(footballerId);
                FootballerControl footballerControl;
                footballerControl.PlayerName(to_hstring(footballer.getName()));
                footballerControl.PlayerInfo(to_hstring(Presenter::getInstance()->getFootballerNextMatch(footballerId)));
                footballerControl.CaptaincyIcon(L"");
                footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
                    {
                        removeFootballer(sender, e);
                    });
                footballerControl.Name(to_hstring(footballer.getId()));
                auto grid = sender.as<Controls::Button>().Parent().as<Controls::Grid>();
                int column = Controls::Grid::GetColumn(sender.as<Controls::Button>());
                uint32_t indexToRemove;
                grid.Children().IndexOf(sender.as<Controls::Button>(), indexToRemove);
                grid.Children().RemoveAt(indexToRemove);
                grid.SetColumn(footballerControl, column);
                grid.Children().Append(footballerControl);
                if (footballerId != luckyFootballerId) budget -= footballer.getPrice();
                BudgetTextBlock().Text(to_hstring(Presenter::getInstance()->budgetToString(budget)));
                tempTeam.size() == 15 && budget > 0 ? SubmitBtn().IsEnabled(true) : SubmitBtn().IsEnabled(false);
            }
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
    for (auto item : Frame().Parent().as<Controls::NavigationView>().MenuItems())
        item.as<Controls::NavigationViewItem>().IsEnabled(false);
    Frame().Parent().as<Controls::NavigationView>().IsBackEnabled(false);
    Frame().Parent().as<Controls::NavigationView>().SettingsItem().as<Controls::NavigationViewItem>().IsEnabled(false);

    BudgetTextBlock().Text(to_hstring(Presenter::getInstance()->budgetToString(budget)));
}


void winrt::FootballFantasy::implementation::PlayerCreateTeamPage::SubmitBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    Presenter::getInstance()->createPlayerTeam(tempTeam, budget);
    for (auto item : Frame().Parent().as<Controls::NavigationView>().MenuItems())
        item.as<Controls::NavigationViewItem>().IsEnabled(true);
    Frame().Parent().as<Controls::NavigationView>().IsBackEnabled(true);
    Frame().Parent().as<Controls::NavigationView>().SettingsItem().as<Controls::NavigationViewItem>().IsEnabled(true);
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerTeamPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom};
    Frame().Navigate(page);
}


void winrt::FootballFantasy::implementation::PlayerCreateTeamPage::removeFootballer(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    auto button = sender.as<Controls::Button>();
    FootballerControl footballerControl = button.Parent().as<FootballerControl>();
    auto g = footballerControl.Parent().as<Controls::Grid>();
    Footballer footballer = Presenter::getInstance()->getFootballer(stoi(to_string(footballerControl.Name())));
    string position = footballer.getPosition();
    int column = Controls::Grid::GetColumn(footballerControl);
    uint32_t indexToRemove;
    g.Children().IndexOf(footballerControl, indexToRemove);
    g.Children().RemoveAt(indexToRemove);
    Controls::Button addBtn;
    addBtn.Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
        {
            AddFootballer(sender, e);
        });
    addBtn.Style(Application::Current().Resources().Lookup(winrt::box_value(L"AddFootballerBtnStyle")).as<Microsoft::UI::Xaml::Style>());
    Controls::StackPanel s;
    s.Spacing(5);
    Controls::TextBlock t;
    Controls::FontIcon f;
    f.Glyph(L"\uE8FA");
    if (position == "Goalkeeper")
        t.Text(L"GK");
    else if (position == "Defender")
        t.Text(L"DEF");
    else if (position == "Midfielder")
        t.Text(L"MID");
    else if (position == "Forward")
        t.Text(L"FWD");
    s.Children().Append(t);
    s.Children().Append(f);
    addBtn.Content(s);
    g.SetColumn(addBtn, column);
    g.Children().Append(addBtn);
    if (stoi(to_string(footballerControl.Name())) != luckyFootballerId) budget += footballer.getPrice();
    BudgetTextBlock().Text(to_hstring(Presenter::getInstance()->budgetToString(budget)));
    tempTeam.erase(footballer.getId());
    SubmitBtn().IsEnabled(false);
}


void winrt::FootballFantasy::implementation::PlayerCreateTeamPage::LuckyPickBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    pair<int, string> footballer;
    do
        footballer = Presenter::getInstance()->luckyWheelGenerator();
    while (tempTeam.find(footballer.first) != tempTeam.end());
    Controls::ContentDialog dialog;

    dialog.XamlRoot(this->XamlRoot());
    hstring mssg = L"Congratulations you have won " + to_hstring(footballer.second) + L" for free, please add him to your team";
    dialog.Content(winrt::box_value(mssg));
    dialog.PrimaryButtonText(L"Done");
    luckyFootballerId = footballer.first;
    dialog.ShowAsync();
    
}
