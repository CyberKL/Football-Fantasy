#include "pch.h"
#include "PlayerTeamPickTeamPage.xaml.h"
#if __has_include("PlayerTeamPickTeamPage.g.cpp")
#include "PlayerTeamPickTeamPage.g.cpp"
#endif
#include "Presenter.h"
#include "PlayerTeam.h"
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Text.h>
#include <winrt/Windows.UI.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t PlayerTeamPickTeamPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void PlayerTeamPickTeamPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    string captaincySelection;
    Controls::Grid PlayerTeamPickTeamPage::CreateGrid(Footballer footballer, char captaincy, bool isStarting)
    {
        Controls::Grid flyoutGrid;
        flyoutGrid.ColumnDefinitions().Append(Controls::ColumnDefinition());
        flyoutGrid.ColumnDefinitions().Append(Controls::ColumnDefinition());
        flyoutGrid.RowDefinitions().Append(Controls::RowDefinition());
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

        Controls::RadioButtons captainOptions;
        captainOptions.MaxColumns(2);
        captainOptions.SelectionChanged({ this, &PlayerTeamPickTeamPage::CaptaincySelectionChanged });
        flyoutGrid.SetColumnSpan(captainOptions, 2);
        flyoutGrid.SetRow(captainOptions, 3);
        flyoutGrid.Children().Append(captainOptions);
        Controls::RadioButton captain;
        Controls::RadioButton viceCaptain;
        captainOptions.Items().Append(captain);
        captainOptions.Items().Append(viceCaptain);
        captain.Content(winrt::box_value(L"Captain"));
        viceCaptain.Content(winrt::box_value(L"Vice Captain"));
        captain.RequestedTheme(ElementTheme::Light);
        viceCaptain.RequestedTheme(ElementTheme::Light);
        if (isStarting) 
        {
            if (captaincy == 'c')
                captain.IsChecked(true);
            else if (captaincy == 'v')
                viceCaptain.IsChecked(true);
        }
        else
        {
            captain.IsEnabled(false);
            viceCaptain.IsEnabled(false);
        }

        return flyoutGrid;
    }
}



void winrt::FootballFantasy::implementation::PlayerTeamPickTeamPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    unordered_map<int, struct UiFootballer> footballers;
    int captainId;
    int viceCaptainId;

    if (Presenter::getInstance()->getSquadEdited() || Presenter::getInstance()->getCaptaincyEdited())
    {
        Controls::Button CancelBtn;
        CancelBtn.Content(winrt::box_value(L"Cancel"));
        CancelBtn.HorizontalAlignment(HorizontalAlignment::Left);
        CancelBtn.Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
            {
                CancelChanges(sender, e);
            });
        FootballFieldGrid().Children().Append(CancelBtn);

        Controls::Button ConfirmBtn;
        ConfirmBtn.Content(winrt::box_value(L"Confirm"));
        ConfirmBtn.HorizontalAlignment(HorizontalAlignment::Right);
        ConfirmBtn.Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
            {
                ConfirmChanges(sender, e);
            });
        FootballFieldGrid().Children().Append(ConfirmBtn);

        for (auto item : Frame().Parent().as<Controls::NavigationView>().MenuItems())
            item.as<Controls::NavigationViewItem>().IsEnabled(false);
        Frame().Parent().as<Controls::NavigationView>().IsBackEnabled(false);
        Frame().Parent().as<Controls::NavigationView>().SettingsItem().as<Controls::NavigationViewItem>().IsEnabled(false);
    }

    if (Presenter::getInstance()->getSquadEdited())
        footballers = Presenter::getInstance()->loadTempSquad();
    else
        footballers = Presenter::getInstance()->loadPickTeamPage();

    if (Presenter::getInstance()->getCaptaincyEdited())
    {
        captainId = Presenter::getInstance()->getTempCaptainId();
        viceCaptainId = Presenter::getInstance()->getTempViceCaptainId();
    }
    else
        Presenter::getInstance()->getCaptainsIds(captainId, viceCaptainId);

    unordered_map<int, struct UiFootballer>::iterator it;
    int subsCount = 0;
    for (it = footballers.begin(); it != footballers.end(); it++)
    {
        UiFootballer footballer = it->second;
        FootballerControl footballerControl;
        footballerControl.PlayerName(to_hstring(footballer.name));
        footballerControl.PlayerInfo(to_hstring(footballer.info));
        footballerControl.Name(to_hstring(footballer.id));
        footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
            {
                FootballerControl_Click(sender, e);
            });
        if (footballer.isStarting)
        {
            if (footballer.id == captainId)
                footballerControl.CaptaincyIcon(L"\uE735");
            else if (footballer.id == viceCaptainId)
                footballerControl.CaptaincyIcon(L"\uE7C6");
            else
                footballerControl.CaptaincyIcon(L"");

            if (footballer.position == "Goalkeeper")
                GkPanel().Children().Append(footballerControl);
            else if (footballer.position == "Defender")
                DefPanel().Children().Append(footballerControl);
            else if (footballer.position == "Midfielder")
                MidPanel().Children().Append(footballerControl);
            else if (footballer.position == "Forward")
                FwdPanel().Children().Append(footballerControl);
        }
        else
        {
            footballerControl.CaptaincyIcon(L"");
            Controls::TextBlock pos;
            if (footballer.position == "Goalkeeper")
                pos.Text(L"GK");
            else if (footballer.position == "Defender")
                pos.Text(L"DEF");
            else if (footballer.position == "Midfielder")
                pos.Text(L"MID");
            else if (footballer.position == "Forward")
                pos.Text(L"FWD");
            SubsGrid().SetColumn(pos, subsCount);
            SubsGrid().Children().Append(pos);
            pos.HorizontalAlignment(HorizontalAlignment::Center);
            footballerControl.HorizontalAlignment(HorizontalAlignment::Center);
            SubsGrid().Children().Append(footballerControl);
            SubsGrid().SetColumn(footballerControl, subsCount);
            SubsGrid().SetRow(footballerControl, 1);
            subsCount++;
        }
    }
}


void winrt::FootballFantasy::implementation::PlayerTeamPickTeamPage::dialogButtonClickHandler(winrt::Windows::Foundation::IInspectable const& dialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{
    int captainId;
    int viceCaptainId;

    int pressedFootballerId = stoi(to_string(dialog.as<Controls::ContentDialog>().Name()));

    if (Presenter::getInstance()->getCaptaincyEdited())
    {
        captainId = Presenter::getInstance()->getTempCaptainId();
        viceCaptainId = Presenter::getInstance()->getTempViceCaptainId();
    }
    else
        Presenter::getInstance()->getCaptainsIds(captainId, viceCaptainId);

    if (captaincySelection == "Captain")
    {
        if (pressedFootballerId != captainId)
        {
            if (pressedFootballerId == viceCaptainId)
            {
                Presenter::getInstance()->setTempCaptainId(pressedFootballerId);
                Presenter::getInstance()->setTempViceCaptainId(captainId);
            }
            else
            {
                Presenter::getInstance()->setTempCaptainId(pressedFootballerId);
                Presenter::getInstance()->setTempViceCaptainId(viceCaptainId);
            }
            captaincySelection = "";
            Presenter::getInstance()->setCaptaincyEdited(true);
            winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerTeamPickTeamPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
            Frame().Navigate(page);
        }
    }
    else if (captaincySelection == "Vice Captain")
    {
        if (pressedFootballerId != viceCaptainId)
        {
            if (pressedFootballerId == captainId)
            {
                Presenter::getInstance()->setTempCaptainId(viceCaptainId);
                Presenter::getInstance()->setTempViceCaptainId(pressedFootballerId);
            }
            else
            {
                Presenter::getInstance()->setTempCaptainId(captainId);
                Presenter::getInstance()->setTempViceCaptainId(pressedFootballerId);
            }
            captaincySelection = "";
            Presenter::getInstance()->setCaptaincyEdited(true);
            winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerTeamPickTeamPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
            Frame().Navigate(page);
        }
    }

    dialog.as<Controls::ContentDialog>().Hide();
    int footballerId = stoi(to_string(dialog.as<Controls::ContentDialog>().Name()));
    Presenter::getInstance()->setPressedFootballerControlId(footballerId);
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.SubstitutePlayerPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom}; // Set Page
    Frame().Navigate(page);
}


void winrt::FootballFantasy::implementation::PlayerTeamPickTeamPage::FootballerControl_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    auto button = sender.as<Controls::Button>();
    FootballerControl footballerControl = button.Parent().as<FootballerControl>();
    int footballerId = stoi(to_string(footballerControl.Name()));
    Footballer footballer = Presenter::getInstance()->getFootballer(footballerId);
    PlayerTeam playerTeam = *Presenter::getInstance()->getPlayerTeam();
    bool isStarting = playerTeam.getSquad()[footballer.getId()].second;

    int captainId;
    int viceCaptainId;
    if (Presenter::getInstance()->getCaptaincyEdited())
    {
        captainId = Presenter::getInstance()->getTempCaptainId();
        viceCaptainId = Presenter::getInstance()->getTempViceCaptainId();
    }
    else
        Presenter::getInstance()->getCaptainsIds(captainId, viceCaptainId);

    char captaincy;
    if (captainId == footballer.getId())
        captaincy = 'c';
    else if (viceCaptainId == footballer.getId())
        captaincy = 'v';
    else
        captaincy = NULL;

    Controls::ContentDialog dialog;
    Controls::Grid contentGrid = CreateGrid(footballer, captaincy, isStarting);

    dialog.XamlRoot(this->XamlRoot());
    dialog.Content(contentGrid);
    dialog.Name(to_hstring(footballerId));
    dialog.PrimaryButtonText(L"Substitute");
    dialog.PrimaryButtonClick([=](winrt::Windows::Foundation::IInspectable const& senderDialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
        {
            dialogButtonClickHandler(senderDialog, args);
        });
    dialog.CloseButtonText(L"Back");
    dialog.CloseButtonClick([=](winrt::Windows::Foundation::IInspectable const& senderDialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
        {
            dialogCloseButtonClickHandler(senderDialog, args);
        });
    dialog.ShowAsync();
}


void winrt::FootballFantasy::implementation::PlayerTeamPickTeamPage::CancelChanges(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    Presenter::getInstance()->setSquadEdited(false);
    Presenter::getInstance()->setCaptaincyEdited(false);
    for (auto item : Frame().Parent().as<Controls::NavigationView>().MenuItems())
        item.as<Controls::NavigationViewItem>().IsEnabled(true);
    Frame().Parent().as<Controls::NavigationView>().IsBackEnabled(true);
    Frame().Parent().as<Controls::NavigationView>().SettingsItem().as<Controls::NavigationViewItem>().IsEnabled(true);

    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerTeamPickTeamPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}

void winrt::FootballFantasy::implementation::PlayerTeamPickTeamPage::ConfirmChanges(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    for (auto item : Frame().Parent().as<Controls::NavigationView>().MenuItems())
        item.as<Controls::NavigationViewItem>().IsEnabled(true);
    Frame().Parent().as<Controls::NavigationView>().IsBackEnabled(true);
    Frame().Parent().as<Controls::NavigationView>().SettingsItem().as<Controls::NavigationViewItem>().IsEnabled(true);

    Presenter::getInstance()->confirmChangesInPickTeam();
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerTeamPickTeamPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}

void winrt::FootballFantasy::implementation::PlayerTeamPickTeamPage::dialogCloseButtonClickHandler(winrt::Windows::Foundation::IInspectable const& dialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
{
    int captainId;
    int viceCaptainId;

    int pressedFootballerId = stoi(to_string(dialog.as<Controls::ContentDialog>().Name()));

    if (Presenter::getInstance()->getCaptaincyEdited())
    {
        captainId = Presenter::getInstance()->getTempCaptainId();
        viceCaptainId = Presenter::getInstance()->getTempViceCaptainId();
    }
    else
        Presenter::getInstance()->getCaptainsIds(captainId, viceCaptainId);

    if (captaincySelection == "Captain")
    {
        if (pressedFootballerId != captainId)
        {
            if (pressedFootballerId == viceCaptainId)
            {
                Presenter::getInstance()->setTempCaptainId(pressedFootballerId);
                Presenter::getInstance()->setTempViceCaptainId(captainId);
            }
            else
            {
                Presenter::getInstance()->setTempCaptainId(pressedFootballerId);
                Presenter::getInstance()->setTempViceCaptainId(viceCaptainId);
            }
            captaincySelection = "";
            Presenter::getInstance()->setCaptaincyEdited(true);
            winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerTeamPickTeamPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
            Frame().Navigate(page);
        }
    }
    else if (captaincySelection == "Vice Captain")
    {
        if (pressedFootballerId != viceCaptainId)
        {
            if (pressedFootballerId == captainId)
            {
                Presenter::getInstance()->setTempCaptainId(viceCaptainId);
                Presenter::getInstance()->setTempViceCaptainId(pressedFootballerId);
            }
            else
            {
                Presenter::getInstance()->setTempCaptainId(captainId);
                Presenter::getInstance()->setTempViceCaptainId(pressedFootballerId);
            }
            captaincySelection = "";
            Presenter::getInstance()->setCaptaincyEdited(true);
            winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerTeamPickTeamPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
            Frame().Navigate(page);
        }
    }
}

void winrt::FootballFantasy::implementation::PlayerTeamPickTeamPage::CaptaincySelectionChanged(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
{
    captaincySelection = to_string(sender.as<Controls::RadioButtons>().SelectedItem().as<Controls::RadioButton>().Content().as<winrt::hstring>());
}