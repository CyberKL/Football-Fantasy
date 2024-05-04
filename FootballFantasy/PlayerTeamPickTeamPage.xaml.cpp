#include "pch.h"
#include "PlayerTeamPickTeamPage.xaml.h"
#if __has_include("PlayerTeamPickTeamPage.g.cpp")
#include "PlayerTeamPickTeamPage.g.cpp"
#endif
#include "Presenter.h"
#include "PlayerTeam.h"

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
}


void winrt::FootballFantasy::implementation::PlayerTeamPickTeamPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    vector<struct UiFootballer> footballers = Presenter::getInstance()->loadPickTeamPage();
    int subsCount = 0;
    for (struct UiFootballer footballer : footballers)
    {
        FootballerControl footballerControl;
        footballerControl.PlayerName(to_hstring(footballer.name));
        footballerControl.PlayerInfo(to_hstring(footballer.info));
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
            footballerControl.HorizontalAlignment(HorizontalAlignment::Center);
            SubsGrid().Children().Append(footballerControl);
            SubsGrid().SetColumn(footballerControl, subsCount);
            subsCount++;
        }
    }
}
