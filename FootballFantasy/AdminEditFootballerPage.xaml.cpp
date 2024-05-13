#include "pch.h"
#include "AdminEditFootballerPage.xaml.h"
#if __has_include("AdminEditFootballerPage.g.cpp")
#include "AdminEditFootballerPage.g.cpp"
#endif
#include "Presenter.h"


using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t AdminEditFootballerPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AdminEditFootballerPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void AdminEditFootballerPage::CreateListView(Controls::ListView& listView, Footballer footballer)
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
    
}



void winrt::FootballFantasy::implementation::AdminEditFootballerPage::ChangeTeam_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.AdminChangeTeamPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);

}


void winrt::FootballFantasy::implementation::AdminEditFootballerPage::RemoveFootballer_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    unordered_map<int, Footballer*> footballers;

    footballers = Presenter::getInstance()->getFootballersList();

    Controls::ListView listView;

    for (auto it = footballers.begin(); it != footballers.end(); ++it) {
        CreateListView(listView, *it->second);
    }


    Controls::ContentDialog dialog;
    dialog.XamlRoot(this->XamlRoot());
    dialog.RequestedTheme(ElementTheme::Light);
    dialog.PrimaryButtonText(L"Remove");
    dialog.PrimaryButtonClick([=](winrt::Windows::Foundation::IInspectable const& senderDialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
        {
            int footballerId = stoi(to_string(senderDialog.as<Controls::ContentDialog>().Content().as<Controls::ListView>().SelectedItem().as < Controls::Grid>().Name()));
            Presenter::getInstance()->removeFootballer(footballerId);
        });
    dialog.CloseButtonText(L"Cancel");
    dialog.Content(listView);
    dialog.ShowAsync();

}


void winrt::FootballFantasy::implementation::AdminEditFootballerPage::AddFootballer_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{

    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.AdminAddFootballer", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}


