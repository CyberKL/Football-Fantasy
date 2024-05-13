#include "pch.h"
#include "AdminEditMatchesPage.xaml.h"
#if __has_include("AdminEditMatchesPage.g.cpp")
#include "AdminEditMatchesPage.g.cpp"
#endif
#include "Presenter.h"
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.h>

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

    struct FootballerStats
    {
        int goals;
        int assists;
        int penaltiesMissed;
        int yellowCards;
        bool redCards;
        int ownGoals;
        int penaltiesSaved;
        int shotsSaved;
        int timePlayed = 0;
        int goalsConceded = 0;
        bool cleanSheet = false;
    };
    unordered_map<int, FootballerStats> homeStats;
    unordered_map<int, FootballerStats> awayStats;
    unordered_map<int, Footballer> homeTeam;
    unordered_map<int, Footballer> awayTeam;
    int pressedFootballerId;
    vector<pair<pair<int, int>, int>> homeSubtitutions;
    vector<pair<pair<int, int>, int>> awaySubtitutions;
    int homeScore;
    int awayScore;

    Controls::Button clickedBtn = nullptr;

    void AdminEditMatchesPage::CreateListView(Controls::ListView& listView, Footballer footballer)
    {
        Controls::Grid g;
        g.ColumnDefinitions().Append(Controls::ColumnDefinition());
        g.ColumnDefinitions().Append(Controls::ColumnDefinition());
        hstring footballerName = to_hstring(footballer.getName());
        Controls::TextBlock name = Controls::TextBlock();
        name.Text(footballerName);
        g.Name(to_hstring(footballer.getId()));
        g.Children().Append(name);
        listView.Items().Append(g);
    };
}


void winrt::FootballFantasy::implementation::AdminEditMatchesPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    if (!homeTeam.empty()) homeTeam.clear();
    if (!awayTeam.empty()) awayTeam.clear();
    clickedBtn = nullptr;

    Match match = Presenter::getInstance()->getPressedMatch();

    HomeTeamBlock().Text(to_hstring(match.getHomeTeam()->getName()));
    AwayTeamBlock().Text(to_hstring(match.getAwayTeam()->getName()));

    for (int i = 1; i < 12; i++)
    {
        Controls::Button addBtn;
        addBtn.HorizontalAlignment(HorizontalAlignment::Stretch);
        addBtn.Background(Media::SolidColorBrush(Windows::UI::Colors::Transparent()));
        addBtn.Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
            {
                AddFootballer(sender, e);
            });
        Controls::Grid::SetRow(addBtn, i);
        Controls::StackPanel panel;
        panel.Orientation(Controls::Orientation::Horizontal);
        panel.Spacing(20);
        Controls::TextBlock textBlock;
        textBlock.Text(L"Add");
        Controls::FontIcon icon;
        icon.Glyph(L"\uE710");
        icon.Foreground(Media::SolidColorBrush(Windows::UI::Colors::Black()));
        icon.HorizontalAlignment(HorizontalAlignment::Right);
        panel.Children().Append(textBlock);
        panel.Children().Append(icon);
        addBtn.Content(panel);
        HomeTeamStartingGrid().Children().Append(addBtn);
    }

    for (int i = 1; i < 8; i++)
    {
        Controls::Button addBtn;
        addBtn.HorizontalAlignment(HorizontalAlignment::Stretch);
        addBtn.Background(Media::SolidColorBrush(Windows::UI::Colors::Transparent()));
        addBtn.Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
            {
                AddFootballer(sender, e);
            });
        Controls::Grid::SetRow(addBtn, i);
        Controls::StackPanel panel;
        panel.Orientation(Controls::Orientation::Horizontal);
        panel.Spacing(20);
        Controls::TextBlock textBlock;
        textBlock.Text(L"Add");
        Controls::FontIcon icon;
        icon.Glyph(L"\uE710");
        icon.Foreground(Media::SolidColorBrush(Windows::UI::Colors::Black()));
        icon.HorizontalAlignment(HorizontalAlignment::Right);
        panel.Children().Append(textBlock);
        panel.Children().Append(icon);
        addBtn.Content(panel);
        HomeTeamSubsGrid().Children().Append(addBtn);
    }

    for (int i = 1; i < 12; i++)
    {
        Controls::Button addBtn;
        addBtn.HorizontalAlignment(HorizontalAlignment::Stretch);
        addBtn.Background(Media::SolidColorBrush(Windows::UI::Colors::Transparent()));
        addBtn.Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
            {
                AddFootballer(sender, e);
            });
        Controls::Grid::SetRow(addBtn, i);
        Controls::StackPanel panel;
        panel.Orientation(Controls::Orientation::Horizontal);
        panel.Spacing(20);
        Controls::TextBlock textBlock;
        textBlock.Text(L"Add");
        Controls::FontIcon icon;
        icon.Glyph(L"\uE710");
        icon.Foreground(Media::SolidColorBrush(Windows::UI::Colors::Black()));
        icon.HorizontalAlignment(HorizontalAlignment::Right);
        panel.Children().Append(textBlock);
        panel.Children().Append(icon);
        addBtn.Content(panel);
        AwayTeamStartingGrid().Children().Append(addBtn);
    }

    for (int i = 1; i < 8; i++)
    {
        Controls::Button addBtn;
        addBtn.HorizontalAlignment(HorizontalAlignment::Stretch);
        addBtn.Background(Media::SolidColorBrush(Windows::UI::Colors::Transparent()));
        addBtn.Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
            {
                AddFootballer(sender, e);
            });
        Controls::Grid::SetRow(addBtn, i);
        Controls::StackPanel panel;
        panel.Orientation(Controls::Orientation::Horizontal);
        panel.Spacing(20);
        Controls::TextBlock textBlock;
        textBlock.Text(L"Add");
        Controls::FontIcon icon;
        icon.Glyph(L"\uE710");
        icon.Foreground(Media::SolidColorBrush(Windows::UI::Colors::Black()));
        icon.HorizontalAlignment(HorizontalAlignment::Right);
        panel.Children().Append(textBlock);
        panel.Children().Append(icon);
        addBtn.Content(panel);
        AwayTeamSubsGrid().Children().Append(addBtn);
    }


}


void winrt::FootballFantasy::implementation::AdminEditMatchesPage::AddFootballer(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    string team = to_string(sender.as <Controls::Button>().Parent().as<Controls::Grid>().Name());
    clickedBtn = sender.as<Controls::Button>();

    Controls::ContentDialog dialog;
    dialog.XamlRoot(this->XamlRoot());
    Controls::ListView listView;
    listView.SelectionChanged([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
        {
            if(sender.as<Controls::ListView>().SelectedItem() != nullptr) dialog.IsPrimaryButtonEnabled(true);
        });

    if (team.substr(0, 8) == "HomeTeam")
    {
        FootballTeam footballTeam = *Presenter::getInstance()->getPressedMatch().getHomeTeam();
        vector<Footballer*> footballers = footballTeam.getFootballers();
        int row = Controls::Grid::GetRow(sender.as <Controls::Button>());
        if (row == 1)
        {
            for (Footballer* footballer : footballers)
            {
                if (footballer->getPosition() == "Goalkeeper" && homeTeam.find(footballer->getId()) == homeTeam.end())
                    CreateListView(listView, *footballer);
            }
        }
        else 
        {
            for (Footballer* footballer : footballers)
            {
                if (homeTeam.find(footballer->getId()) == homeTeam.end() && footballer->getPosition() != "Goalkeeper")
                    CreateListView(listView, *footballer);
            }
        }
    }
    else if (team.substr(0, 8) == "AwayTeam")
    {
        FootballTeam footballTeam = *Presenter::getInstance()->getPressedMatch().getAwayTeam();
        vector<Footballer*> footballers = footballTeam.getFootballers();
        int row = Controls::Grid::GetRow(sender.as <Controls::Button>());
        if (row == 1)
        {
            for (Footballer* footballer : footballers)
            {
                if (footballer->getPosition() == "Goalkeeper" && awayTeam.find(footballer->getId()) == awayTeam.end())
                    CreateListView(listView, *footballer);
            }
        }
        else
        {
            for (Footballer* footballer : footballers)
            {
                if (awayTeam.find(footballer->getId()) == awayTeam.end() && footballer->getPosition() != "Goalkeeper")
                    CreateListView(listView, *footballer);
            }
        }
    }
    
    dialog.Content(listView);
    dialog.PrimaryButtonText(L"Add");
    dialog.IsPrimaryButtonEnabled(listView.SelectedItem() != nullptr);
    dialog.PrimaryButtonClick([=](winrt::Windows::Foundation::IInspectable const& dialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
        {
            AddFootballerToUI(dialog, args);
        });
    dialog.CloseButtonText(L"Cancel");
    dialog.ShowAsync();
}


void winrt::FootballFantasy::implementation::AdminEditMatchesPage::AddFootballerToUI(winrt::Windows::Foundation::IInspectable const& dialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{
    int footballerId = stoi(to_string(dialog.as<Controls::ContentDialog>().Content().as<Controls::ListView>().SelectedItem().as<Controls::Grid>().Name()));
    Footballer footballer = Presenter::getInstance()->getFootballer(footballerId);

    string team = to_string(clickedBtn.Parent().as<Controls::Grid>().Name());
    if (team.substr(0, 8) == "HomeTeam")
        homeTeam.insert(make_pair(footballerId, footballer));
    else if (team.substr(0, 8) == "AwayTeam")
        awayTeam.insert(make_pair(footballerId, footballer));

    Controls::Button footballerBtn;
    footballerBtn.HorizontalAlignment(HorizontalAlignment::Stretch);
    footballerBtn.Background(Media::SolidColorBrush(Windows::UI::Colors::Transparent()));
    footballerBtn.Foreground(Media::SolidColorBrush(Windows::UI::Colors::Black()));
    footballerBtn.Content(winrt::box_value(to_hstring((footballer.getName()))));
    footballerBtn.Name(to_hstring(footballerId));
    footballerBtn.Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
        {
            FootballerOptions(sender, e);
        });

    int row = Controls::Grid::GetRow(clickedBtn);
    Controls::Grid::SetRow(footballerBtn, row);
    Controls::Grid parentGrid = clickedBtn.Parent().as<Controls::Grid>();
    uint32_t index;
    parentGrid.Children().IndexOf(clickedBtn, index);
    parentGrid.Children().RemoveAt(index);
    parentGrid.Children().Append(footballerBtn);
    if (to_string(parentGrid.Name()).find("Subs")) footballerBtn.IsEnabled(false);

    if (homeTeam.size() == 18) HomeTeamSubBtn().IsEnabled(true);
    if (awayTeam.size() == 18) AwayTeamSubBtn().IsEnabled(true);
    if (homeTeam.size() == 18 && awayTeam.size() == 18) ConfirmBtn().IsEnabled(true);
}


void winrt::FootballFantasy::implementation::AdminEditMatchesPage::FootballerOptions(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    Controls::ContentDialog dialog;
    dialog.XamlRoot(this->XamlRoot());

    Controls::StackPanel panel;

    Controls::NumberBox goalsBox;
    goalsBox.SpinButtonPlacementMode(Controls::NumberBoxSpinButtonPlacementMode::Inline);
    goalsBox.SmallChange(1);
    goalsBox.Value(0);
    goalsBox.Minimum(0);
    goalsBox.Header(winrt::box_value(L"Goals"));

    Controls::NumberBox assistBox;
    assistBox.SpinButtonPlacementMode(Controls::NumberBoxSpinButtonPlacementMode::Inline);
    assistBox.SmallChange(1);
    assistBox.Value(0);
    assistBox.Minimum(0);
    assistBox.Header(winrt::box_value(L"Assists"));

    Controls::NumberBox penaltyMiss;
    penaltyMiss.SpinButtonPlacementMode(Controls::NumberBoxSpinButtonPlacementMode::Inline);
    penaltyMiss.SmallChange(1);
    penaltyMiss.Value(0);
    penaltyMiss.Minimum(0);
    penaltyMiss.Header(winrt::box_value(L"Penalty misses"));

    Controls::CheckBox redCardBox;
    redCardBox.Content(winrt::box_value(L"Red card"));

    Controls::NumberBox yellowCardBox;
    yellowCardBox.SpinButtonPlacementMode(Controls::NumberBoxSpinButtonPlacementMode::Inline);
    yellowCardBox.SmallChange(1);
    yellowCardBox.Value(0);
    yellowCardBox.Maximum(2);
    yellowCardBox.Minimum(0);
    yellowCardBox.ValueChanged([=](winrt::Microsoft::UI::Xaml::Controls::NumberBox const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args)
        {
            if (sender.Value() == 2)
            {
                redCardBox.IsChecked(true);
                redCardBox.IsEnabled(false);
            }
            else
            {
                redCardBox.IsChecked(false);
                redCardBox.IsEnabled(true);
            }
        });
    yellowCardBox.Header(winrt::box_value(L"Yellow cards"));

    

    Controls::NumberBox ownGoalsBox;
    ownGoalsBox.SpinButtonPlacementMode(Controls::NumberBoxSpinButtonPlacementMode::Inline);
    ownGoalsBox.SmallChange(1);
    ownGoalsBox.Value(0);
    ownGoalsBox.Minimum(0);
    ownGoalsBox.Header(winrt::box_value(L"Own goals"));


    panel.Children().Append(goalsBox);
    panel.Children().Append(assistBox);
    panel.Children().Append(penaltyMiss);
    panel.Children().Append(yellowCardBox);
    panel.Children().Append(redCardBox);
    panel.Children().Append(ownGoalsBox);

    string position = Presenter::getInstance()->getFootballer(stoi(to_string(sender.as<Controls::Button>().Name()))).getPosition();
    if (position == "Goalkeeper")
    {
        Controls::NumberBox shotsSavedBox;
        shotsSavedBox.SpinButtonPlacementMode(Controls::NumberBoxSpinButtonPlacementMode::Inline);
        shotsSavedBox.SmallChange(1);
        shotsSavedBox.Value(0);
        shotsSavedBox.Minimum(0);
        shotsSavedBox.Header(winrt::box_value(L"Shots saved"));

        Controls::NumberBox penaltiesSavedBox;
        penaltiesSavedBox.SpinButtonPlacementMode(Controls::NumberBoxSpinButtonPlacementMode::Inline);
        penaltiesSavedBox.SmallChange(1);
        penaltiesSavedBox.Value(0);
        penaltiesSavedBox.Minimum(0);
        penaltiesSavedBox.Header(winrt::box_value(L"Penalties saved"));

        panel.Children().Append(shotsSavedBox);
        panel.Children().Append(penaltiesSavedBox);
    }

    dialog.Content(panel);
    dialog.CloseButtonText(L"Cancel");
    dialog.PrimaryButtonText(L"Done");
    dialog.PrimaryButtonClick([=](winrt::Windows::Foundation::IInspectable const& dialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
        {
            Confirm_Stats(dialog, args);
        });
    string team = to_string(sender.as<Controls::Button>().Parent().as<Controls::Grid>().Name()).substr(0, 8);
    dialog.Name(to_hstring(team));
    pressedFootballerId = stoi(to_string(sender.as<Controls::Button>().Name()));
    dialog.ShowAsync();
}


void winrt::FootballFantasy::implementation::AdminEditMatchesPage::SubstituteFootballer(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    Controls::ContentDialog dialog;
    dialog.XamlRoot(this->XamlRoot());

    Controls::ListView startingList;
    Controls::ListView subsList;
    Controls::Grid::SetColumn(subsList, 1);
    unordered_map<int, Footballer>::iterator it;
    string team = to_string(sender.as<Controls::Button>().Parent().as<Controls::Grid>().Name());

    if (team.substr(0, 8) == "HomeTeam")
    {
        it = homeTeam.begin();
        dialog.Name(L"HomeTeam");
    }
    else if (team.substr(0, 8) == "AwayTeam")
    {
        it = awayTeam.begin();
        dialog.Name(L"AwayTeam");
    }
    for (int i = 0; i < 11; i++)
    {
        CreateListView(startingList, it->second);
        it++;
    }
    for (int i = 0; i < 7; i++)
    {
        CreateListView(subsList, it->second);
        it++;
    }

    Controls::Grid grid;
    grid.ColumnDefinitions().Append(Controls::ColumnDefinition());
    grid.ColumnDefinitions().Append(Controls::ColumnDefinition());
    grid.RowDefinitions().Append(Controls::RowDefinition());
    grid.RowDefinitions().Append(Controls::RowDefinition());
    grid.Children().Append(startingList);
    grid.Children().Append(subsList);
    startingList.HorizontalAlignment(HorizontalAlignment::Stretch);
    subsList.HorizontalAlignment(HorizontalAlignment::Stretch);

    Controls::NumberBox subTimeBox;
    subTimeBox.SpinButtonPlacementMode(Controls::NumberBoxSpinButtonPlacementMode::Inline);
    subTimeBox.SmallChange(1);
    subTimeBox.Value(0);
    subTimeBox.Maximum(90);
    subTimeBox.Minimum(0);
    subTimeBox.Header(winrt::box_value(L"Substitution time"));
    Controls::Grid::SetRow(subTimeBox, 1);
    Controls::Grid::SetColumnSpan(subTimeBox, 2);
    grid.Children().Append(subTimeBox);

    grid.ColumnSpacing(50);
    grid.RowSpacing(20);
    dialog.PrimaryButtonText(L"Done");
    dialog.PrimaryButtonClick([=](winrt::Windows::Foundation::IInspectable const& dialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
        {
            SubstituteFootballer_Dialog_Click(dialog, args);
        });
    dialog.CloseButtonText(L"Cancel");
    dialog.Content(grid);
    dialog.ShowAsync();
}


void winrt::FootballFantasy::implementation::AdminEditMatchesPage::SubstituteFootballer_Dialog_Click(winrt::Windows::Foundation::IInspectable const& dialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{
    int startingPlayerId = stoi(to_string(dialog.as<Controls::ContentDialog>().Content().as<Controls::Grid>().Children().GetAt(0).as<Controls::ListView>().SelectedItem().as<Controls::Grid>().Name()));
    int subPlayerId = stoi(to_string(dialog.as<Controls::ContentDialog>().Content().as<Controls::Grid>().Children().GetAt(1).as<Controls::ListView>().SelectedItem().as<Controls::Grid>().Name()));
    int time = dialog.as<Controls::ContentDialog>().Content().as<Controls::Grid>().Children().GetAt(2).as<Controls::NumberBox>().Value();

    if (to_string(dialog.as<Controls::ContentDialog>().Name()) == "HomeTeam")
    {
        homeSubtitutions.push_back(make_pair(make_pair(startingPlayerId, subPlayerId), time));
        Controls::StackPanel panel;
        panel.Orientation(Controls::Orientation::Horizontal);
        panel.Spacing(20);
        Controls::TextBlock startingBlock;
        Controls::TextBlock subBlock;
        startingBlock.Text(to_hstring(homeTeam[startingPlayerId].getName()));
        subBlock.HorizontalAlignment(HorizontalAlignment::Right);
        subBlock.Text(to_hstring(homeTeam[subPlayerId].getName()));
        Controls::FontIcon icon;
        icon.Glyph(L"\uE8EE");
        icon.Foreground(Media::SolidColorBrush(Windows::UI::Colors::Black()));
        icon.HorizontalAlignment(HorizontalAlignment::Center);
        panel.Children().Append(startingBlock);
        panel.Children().Append(icon);
        panel.Children().Append(subBlock);
        Controls::Grid::SetRow(panel, homeSubtitutions.size());
        HomeSubstitutionsGrid().Children().Append(panel);
        for (auto btn : HomeTeamSubsGrid().Children()) 
            if (stoi(to_string(btn.as<Controls::Button>().Name())) == subPlayerId)
            {
                btn.as<Controls::Button>().IsEnabled(true);
                break;
            }
    }
    else if (to_string(dialog.as<Controls::ContentDialog>().Name()) == "AwayTeam")
    {
        awaySubtitutions.push_back(make_pair(make_pair(startingPlayerId, subPlayerId), time));
        Controls::StackPanel panel;
        panel.Orientation(Controls::Orientation::Horizontal);
        panel.Spacing(20);
        Controls::TextBlock startingBlock;
        Controls::TextBlock subBlock;
        startingBlock.Text(to_hstring(homeTeam[startingPlayerId].getName()));
        subBlock.HorizontalAlignment(HorizontalAlignment::Right);
        subBlock.Text(to_hstring(homeTeam[subPlayerId].getName()));
        Controls::FontIcon icon;
        icon.Glyph(L"\uE8EE");
        icon.Foreground(Media::SolidColorBrush(Windows::UI::Colors::Black()));
        icon.HorizontalAlignment(HorizontalAlignment::Center);
        panel.Children().Append(startingBlock);
        panel.Children().Append(icon);
        panel.Children().Append(subBlock);
        Controls::Grid::SetRow(panel, awaySubtitutions.size());
        AwaySubstitutionsGrid().Children().Append(panel);
        for (auto btn : AwayTeamSubsGrid().Children())
            if (stoi(to_string(btn.as<Controls::Button>().Name())) == subPlayerId)
            {
                btn.as<Controls::Button>().IsEnabled(true);
                break;
            }
    }

    if (homeSubtitutions.size() == 5) HomeTeamSubBtn().IsEnabled(false);
    if (awaySubtitutions.size() == 5) AwayTeamSubBtn().IsEnabled(false);
}


void winrt::FootballFantasy::implementation::AdminEditMatchesPage::Confirm_Stats(winrt::Windows::Foundation::IInspectable const& dialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{
    Controls::StackPanel optionsPanel = dialog.as<Controls::ContentDialog>().Content().as<Controls::StackPanel>();
    FootballerStats footballer;

    footballer.goals = optionsPanel.Children().GetAt(0).as<Controls::NumberBox>().Value();
    footballer.assists = optionsPanel.Children().GetAt(1).as<Controls::NumberBox>().Value();
    footballer.penaltiesMissed = optionsPanel.Children().GetAt(2).as<Controls::NumberBox>().Value();
    footballer.yellowCards = optionsPanel.Children().GetAt(3).as<Controls::NumberBox>().Value();
    footballer.redCards = optionsPanel.Children().GetAt(4).as<Controls::CheckBox>().IsChecked().Value();
    footballer.ownGoals = optionsPanel.Children().GetAt(5).as<Controls::NumberBox>().Value();

    footballer.penaltiesSaved = 0;
    footballer.shotsSaved = 0;

    if (optionsPanel.Children().Size() > 5)
    {
        footballer.shotsSaved = optionsPanel.Children().GetAt(6).as<Controls::NumberBox>().Value();
        footballer.penaltiesSaved = optionsPanel.Children().GetAt(7).as<Controls::NumberBox>().Value();
    }

    string team = to_string(dialog.as<Controls::ContentDialog>().Name());
    if (team == "HomeTeam")
    {
        if (homeStats.find(pressedFootballerId) != homeStats.end())
        {
            homeScore -= homeStats[pressedFootballerId].goals;
            homeStats.erase(pressedFootballerId);
        }
        homeScore += footballer.goals;
        homeStats.insert(make_pair(pressedFootballerId, footballer));
    }
    else if (team == "AwayTeam")
    {
        if (awayStats.find(pressedFootballerId) != awayStats.end())
        {
            awayScore -= homeStats[pressedFootballerId].goals;
            awayStats.erase(pressedFootballerId);
        }
        awayScore += footballer.goals;
        awayStats.insert(make_pair(pressedFootballerId, footballer));
    }
}


void winrt::FootballFantasy::implementation::AdminEditMatchesPage::ConfirmBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    unordered_map<int, FootballerStats>::iterator it;
    Footballer footballer;
    vector<Footballer*> scorers;
    for (it = homeStats.begin(); it != homeStats.end(); it++)
    {
        footballer = Presenter::getInstance()->getFootballer(it->first);
        string position = footballer.getPosition();
        if (awayScore == 0 && position != "Forward")
            it->second.cleanSheet = true;
        else if (awayScore != 0 && position != "Forward" && position != "Midfielder")
            it->second.goalsConceded = awayScore;

        bool starting = false;
        for (auto button : HomeTeamStartingGrid().Children())
            if (stoi(to_string(button.as<Controls::Button>().Name())) == it->first) starting = true;

        bool subbed;
        int subTime;
        for (int i = 0; i < 5; i++)
            if (homeSubtitutions[i].first.first == it->first || homeSubtitutions[i].first.first == it->first)
            {
                subbed = true;
                subTime = homeSubtitutions[i].second;
                break;
            }

        if (starting && subbed)
            it->second.timePlayed = subTime;
        else if (starting && !subbed)
            it->second.timePlayed = 90;
        else if (!starting && subbed)
            it->second.timePlayed = 90 - subTime;


        if (it->second.goals > 0)
            scorers.push_back(&Presenter::getInstance()->getFootballer(it->first));

    }

    for (it = awayStats.begin(); it != awayStats.end(); it++)
    {
        footballer = Presenter::getInstance()->getFootballer(it->first);
        string position = footballer.getPosition();
        if (homeScore == 0 && position != "Forward")
            it->second.cleanSheet = true;
        else if (homeScore != 0 && position != "Forward" && position != "Midfielder")
            it->second.goalsConceded = homeScore;

        bool starting = false;
        for (auto button : AwayTeamStartingGrid().Children())
            if (stoi(to_string(button.as<Controls::Button>().Name())) == it->first) starting = true;

        bool subbed;
        int subTime;
        for (int i = 0; i < 5; i++)
            if (awaySubtitutions[i].first.first == it->first || awaySubtitutions[i].first.first == it->first)
            {
                subbed = true;
                subTime = awaySubtitutions[i].second;
                break;
            }

        if (starting && subbed)
            it->second.timePlayed = subTime;
        else if (starting && !subbed)
            it->second.timePlayed = 90;
        else if (!starting && subbed)
            it->second.timePlayed = 90 - subTime;


        if (it->second.goals > 0)
            scorers.push_back(&Presenter::getInstance()->getFootballer(it->first));
    }

    Presenter::getInstance()->getPressedMatch().setPlayed(true);
    string score = homeScore + ":" + awayScore;
    Presenter::getInstance()->getPressedMatch().setScore(score);
    Presenter::getInstance()->getPressedMatch().setScorers(scorers);

    for (it = homeStats.begin(); it != homeStats.end(); it++)
        Presenter::getInstance()->updateFootballerPoints(it->first, it->second.goals, it->second.assists, it->second.penaltiesMissed, it->second.yellowCards, it->second.redCards, it->second.ownGoals, it->second.penaltiesSaved, it->second.shotsSaved, it->second.timePlayed, it->second.goalsConceded, it->second.cleanSheet);
    for (it = awayStats.begin(); it != awayStats.end(); it++)
        Presenter::getInstance()->updateFootballerPoints(it->first, it->second.goals, it->second.assists, it->second.penaltiesMissed, it->second.yellowCards, it->second.redCards, it->second.ownGoals, it->second.penaltiesSaved, it->second.shotsSaved, it->second.timePlayed, it->second.goalsConceded, it->second.cleanSheet);
}
