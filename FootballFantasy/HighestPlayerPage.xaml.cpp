#include "pch.h"
#include "HighestPlayerPage.xaml.h"
#if __has_include("HighestPlayerPage.g.cpp")
#include "HighestPlayerPage.g.cpp"
#endif
#include "Presenter.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t HighestPlayerPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void HighestPlayerPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}


void winrt::FootballFantasy::implementation::HighestPlayerPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    unordered_map<int, struct UiFootballer> footballers;
    int captainId;
    int viceCaptainId;
    footballers = Presenter::getInstance()->loadHighestPlayerPage();
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
