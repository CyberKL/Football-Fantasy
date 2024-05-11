#include "pch.h"
#include "PlayerTransfersPage.xaml.h"
#if __has_include("PlayerTransfersPage.g.cpp")
#include "PlayerTransfersPage.g.cpp"
#endif
#include "Presenter.h"
#include <winrt/Windows.UI.Text.h>
#include <winrt/Windows.UI.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t PlayerTransfersPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void PlayerTransfersPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
    unordered_set<FootballerControl> tempTeam;
    int budget;
    stack<pair<int, int>> transfersStack;
    FootballerControl pressedFootballerControl = nullptr;
    void PlayerTransfersPage::CreateListView(Controls::ListView& listView, Footballer footballer)
    {
        Controls::Grid g;
        g.ColumnDefinitions().Append(Controls::ColumnDefinition());
        g.ColumnDefinitions().Append(Controls::ColumnDefinition());
        hstring footballerName = to_hstring(footballer.getName());
        Controls::TextBlock name = Controls::TextBlock();
        name.Text(footballerName);
        Controls::FontIcon f;
        f.Glyph(L"\uE946");
        f.FontSize(25);
        /*f.PointerEntered(Input::PointerEventHandler([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args) {
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

            }));*/
        f.HorizontalAlignment(HorizontalAlignment::Right);
        g.Name(to_hstring(footballer.getId()));
        g.Children().Append(name);
        g.SetColumn(f, 1);
        g.Children().Append(f);
        listView.Items().Append(g);
    };
    void PlayerTransfersPage::UndoTransfer()
    {
        int returningId = transfersStack.top().first;
        int outId = transfersStack.top().second;
        FootballerControl outFootballerControl;
        for (FootballerControl footballerControl : tempTeam)
            if (stoi(to_string(footballerControl.Name())) == outId)
            {
                outFootballerControl = footballerControl;
                break;
            }

        tempTeam.erase(outFootballerControl);
        
        Footballer footballer = Presenter::getInstance()->getFootballer(returningId);
        FootballerControl footballerControl;
        footballerControl.PlayerName(to_hstring(footballer.getName()));
        footballerControl.PlayerInfo(to_hstring(footballer.getPrice()));
        footballerControl.CaptaincyIcon(L"");
        footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
            {
                FootballerControl_Click(sender, e);
            });
        footballerControl.Name(to_hstring(footballer.getId()));
        tempTeam.insert(footballerControl);

        auto grid = outFootballerControl.Parent().as<Controls::Grid>();
        int column = Controls::Grid::GetColumn(outFootballerControl);
        uint32_t indexToRemove;
        grid.Children().IndexOf(outFootballerControl, indexToRemove);
        grid.Children().RemoveAt(indexToRemove);
        grid.SetColumn(footballerControl, column);
        grid.Children().Append(footballerControl);

        budget += stoi(to_string(outFootballerControl.PlayerInfo()));
        budget -= footballer.getPrice();
        BudgetTextBlock().Text(to_hstring(Presenter::getInstance()->budgetToString(budget)));
        budget > 0 ? ConfirmBtn().IsEnabled(true) : ConfirmBtn().IsEnabled(false);

        transfersStack.pop();
        if (transfersStack.empty())
        {
            winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerTransfersPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
            Frame().Navigate(page);
        }
            
    }
}


void winrt::FootballFantasy::implementation::PlayerTransfersPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    if (!tempTeam.empty()) tempTeam.clear();
    while (!transfersStack.empty()) transfersStack.pop();
    budget = Presenter::getInstance()->getLoggedInPlayerBudget();
    BudgetTextBlock().Text(to_hstring(Presenter::getInstance()->budgetToString(budget)));
    unordered_map<int, struct UiFootballer> footballers;
    footballers = Presenter::getInstance()->loadTeamTransfersPage();
    unordered_map<int, struct UiFootballer>::iterator it;

    int gkCount = 0;
    int defCount = 0;
    int midCount = 0;
    int fwdCount = 0;
    for (it = footballers.begin(); it != footballers.end(); it++)
    {
        UiFootballer footballer = it->second;
        FootballerControl footballerControl;
        footballerControl.PlayerName(to_hstring(footballer.name));
        footballerControl.PlayerInfo(to_hstring(footballer.info));
        footballerControl.CaptaincyIcon(L"");
        footballerControl.Name(to_hstring(footballer.id));
        tempTeam.insert(footballerControl);
        footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
            {
                FootballerControl_Click(sender, e);
            });
        if (footballer.position == "Goalkeeper")
        {
            Controls::Grid::SetColumn(footballerControl, gkCount);
            GkGrid().Children().Append(footballerControl);
            gkCount++;
        }
        else if (footballer.position == "Defender")
        {
            Controls::Grid::SetColumn(footballerControl, defCount);
            DefGrid().Children().Append(footballerControl);
            defCount++;
        }
        else if (footballer.position == "Midfielder")
        {
            Controls::Grid::SetColumn(footballerControl, midCount);
            MidGrid().Children().Append(footballerControl);
            midCount++;
        }
        else if (footballer.position == "Forward")
        {
            Controls::Grid::SetColumn(footballerControl, fwdCount);
            FwdGrid().Children().Append(footballerControl);
            fwdCount++;
        }
    }
}


void winrt::FootballFantasy::implementation::PlayerTransfersPage::FootballerControl_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    pressedFootballerControl = sender.as<Controls::Button>().Parent().as<FootballerControl>();
    string position = to_string(pressedFootballerControl.Parent().as<Controls::Grid>().Name());

    vector<Footballer> footballers;
    if (position == "GkGrid")
        // search gk
        footballers = Presenter::getInstance()->searchFootballersByPosition("Goalkeeper");
    else if (position == "DefGrid")
        // search def
        footballers = Presenter::getInstance()->searchFootballersByPosition("Defender");
    else if (position == "MidGrid")
        // search mid
        footballers = Presenter::getInstance()->searchFootballersByPosition("Midfielder");
    else if (position == "FwdGrid")
        // search fwd
        footballers = Presenter::getInstance()->searchFootballersByPosition("Forward");

    Controls::ListView listView;
    for (Footballer footballer : footballers)
    {
        bool found = false;
        for (FootballerControl footballerControl : tempTeam)
            if (stoi(to_string(footballerControl.Name())) == footballer.getId())
            {
                found = true;
                break;
            }
        if(!found) CreateListView(listView, footballer);
    }

    Controls::ContentDialog dialog;
    dialog.XamlRoot(this->XamlRoot());
    dialog.RequestedTheme(ElementTheme::Light);
    dialog.PrimaryButtonText(L"Add");
    dialog.PrimaryButtonClick([=](winrt::Windows::Foundation::IInspectable const& senderDialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
        {
            dialogButtonClickHandler(senderDialog, args);
        });
    dialog.CloseButtonText(L"Cancel");
    dialog.Content(listView);
    dialog.ShowAsync();
}


void winrt::FootballFantasy::implementation::PlayerTransfersPage::dialogButtonClickHandler(winrt::Windows::Foundation::IInspectable const& dialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{
    auto parentDialog = dialog.as<Controls::ContentDialog>();
    auto listView = parentDialog.Content().as<Controls::ListView>();
    if (listView.SelectedItem() != nullptr)
    {
        auto selectedGrid = listView.SelectedItem().as<Controls::Grid>();
        int footballerId = stoi(to_string(selectedGrid.Name()));
        tempTeam.erase(pressedFootballerControl);
        Footballer footballer = Presenter::getInstance()->getFootballer(footballerId);
        FootballerControl footballerControl;
        footballerControl.PlayerName(to_hstring(footballer.getName()));
        footballerControl.PlayerInfo(to_hstring(footballer.getPrice()));
        footballerControl.CaptaincyIcon(L"");
        footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
            {
                FootballerControl_Click(sender, e);
            });
        footballerControl.Name(to_hstring(footballer.getId()));
        tempTeam.insert(footballerControl);
        auto grid = pressedFootballerControl.Parent().as<Controls::Grid>();
        int column = Controls::Grid::GetColumn(pressedFootballerControl);
        uint32_t indexToRemove;
        grid.Children().IndexOf(pressedFootballerControl, indexToRemove);
        grid.Children().RemoveAt(indexToRemove);
        grid.SetColumn(footballerControl, column);
        grid.Children().Append(footballerControl);

        budget += stoi(to_string(pressedFootballerControl.PlayerInfo()));
        budget -= footballer.getPrice();
        BudgetTextBlock().Text(to_hstring(Presenter::getInstance()->budgetToString(budget)));
        budget > 0 ? ConfirmBtn().IsEnabled(true) : ConfirmBtn().IsEnabled(false);

        transfersStack.push(make_pair(stoi(to_string(pressedFootballerControl.Name())), footballer.getId()));
        UndoBtn().IsEnabled(true);

        OptionsPanel().Visibility(Visibility::Visible);
        for (auto item : Frame().Parent().as<Controls::NavigationView>().MenuItems())
            item.as<Controls::NavigationViewItem>().IsEnabled(false);
        Frame().Parent().as<Controls::NavigationView>().IsBackEnabled(false);
        Frame().Parent().as<Controls::NavigationView>().SettingsItem().as<Controls::NavigationViewItem>().IsEnabled(false);
    }
}


void winrt::FootballFantasy::implementation::PlayerTransfersPage::ConfirmBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    for (auto item : Frame().Parent().as<Controls::NavigationView>().MenuItems())
        item.as<Controls::NavigationViewItem>().IsEnabled(true);
    Frame().Parent().as<Controls::NavigationView>().IsBackEnabled(true);
    Frame().Parent().as<Controls::NavigationView>().SettingsItem().as<Controls::NavigationViewItem>().IsEnabled(true);
    Presenter::getInstance()->confirmTransfersPage(transfersStack);
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerTransfersPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}


void winrt::FootballFantasy::implementation::PlayerTransfersPage::ResetBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    for (auto item : Frame().Parent().as<Controls::NavigationView>().MenuItems())
        item.as<Controls::NavigationViewItem>().IsEnabled(true);
    Frame().Parent().as<Controls::NavigationView>().IsBackEnabled(true);
    Frame().Parent().as<Controls::NavigationView>().SettingsItem().as<Controls::NavigationViewItem>().IsEnabled(true);
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerTransfersPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}


void winrt::FootballFantasy::implementation::PlayerTransfersPage::UndoBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    UndoTransfer();
}
