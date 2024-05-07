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

    Controls::Grid PlayerTeamPickTeamPage::CreateGrid(Footballer footballer, char captaincy)
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
        if (captaincy == 'c')
            captain.IsChecked(true);
        else if (captaincy == 'v')
            viceCaptain.IsChecked(true);

        return flyoutGrid;
    }
}



void winrt::FootballFantasy::implementation::PlayerTeamPickTeamPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    unordered_map<int, struct UiFootballer> footballers = Presenter::getInstance()->loadPickTeamPage();
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
    char captaincy;
    if (playerTeam.getCaptain()->getId() == footballer.getId())
        captaincy = 'c';
    else if (playerTeam.getViceCaptain()->getId() == footballer.getId())
        captaincy = 'v';
    else
        captaincy = 'n';
    Controls::ContentDialog dialog;
    Controls::Grid contentGrid = CreateGrid(footballer, captaincy);

    dialog.XamlRoot(this->XamlRoot());
    dialog.Content(contentGrid);
    dialog.Name(to_hstring(footballerId));
    dialog.PrimaryButtonText(L"Substitute");
    dialog.PrimaryButtonClick([=](winrt::Windows::Foundation::IInspectable const& senderDialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
        {
            dialogButtonClickHandler(senderDialog, args);
        });
    dialog.CloseButtonText(L"Cancel");
    dialog.ShowAsync();
}
