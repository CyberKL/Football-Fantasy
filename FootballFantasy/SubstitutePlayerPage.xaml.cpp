#include "pch.h"
#include "SubstitutePlayerPage.xaml.h"
#if __has_include("SubstitutePlayerPage.g.cpp")
#include "SubstitutePlayerPage.g.cpp"
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
    int32_t SubstitutePlayerPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void SubstitutePlayerPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
    unordered_map<int, FootballerControl> footballerControls;
}


void winrt::FootballFantasy::implementation::SubstitutePlayerPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    int pressedFootballerControlId = Presenter::getInstance()->getPressedFootballerControlId();
    unordered_map<int, struct UiFootballer> footballers = Presenter::getInstance()->loadPickTeamPage();
    unordered_map<int, struct UiFootballer>::iterator it;
    UiFootballer pressedFootballer = footballers[pressedFootballerControlId];
    int subsCount = 0;

    PlayerTeam playerTeam = *Presenter::getInstance()->getPlayerTeam();

    unordered_map<int, pair<Footballer*, bool>>::iterator squadIt;
    unordered_map<int, pair<Footballer*, bool>> squad = playerTeam.getSquad();
    int defCount = 0;
    int midCount = 0;
    int fwdCount = 0;
    for (squadIt = squad.begin(); squadIt != squad.end(); squadIt++)
    {
        if (squadIt->second.first->getPosition() == "Defender")
            defCount++;
        else if (squadIt->second.first->getPosition() == "Midfielder")
            midCount++;
        else if (squadIt->second.first->getPosition() == "Forward")
            fwdCount++;
    }

    if (pressedFootballer.isStarting) // pressed footballer in the starting lineup
    {
        for (it = footballers.begin(); it != footballers.end(); it++)
        {
            UiFootballer footballer = it->second;
            FootballerControl footballerControl;
            footballerControl.PlayerName(to_hstring(footballer.name));
            footballerControl.PlayerInfo(to_hstring(footballer.info));
            footballerControl.Name(to_hstring(footballer.id));
            if (footballer.id != pressedFootballer.id) {
                if (footballer.isStarting)
                {
                    footballerControl.Content().as<Controls::Button>().IsEnabled(false); // Disable all other starting players
                    // adding the control to the ui
                    if (footballer.position == "Goalkeeper")
                        GkPanel().Children().Append(footballerControl);
                    else if (footballer.position == "Defender")
                        DefPanel().Children().Append(footballerControl);
                    else if (footballer.position == "Midfielder")
                        MidPanel().Children().Append(footballerControl);
                    else if (footballer.position == "Forward")
                        FwdPanel().Children().Append(footballerControl);
                }
                else // Dealing with the bench
                {
                    if (pressedFootballer.position == "Goalkeeper")
                    {
                        if (footballer.position == "Goalkeeper")
                        {
                            footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
                            footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
                            footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
                                {
                                    SwapFootballer(sender, e);
                                });
                        }
                        else
                            footballerControl.Content().as<Controls::Button>().IsEnabled(false);
                    }
                    else if (pressedFootballer.position == "Defender")
                    {
                        if (defCount == 3) // Sub with defenders only
                        {
                            if (footballer.position == "Defender")
                            {
                                footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
                                footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
                                footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
                                    {
                                        SwapFootballer(sender, e);
                                    });
                            }
                            else
                                footballerControl.Content().as<Controls::Button>().IsEnabled(false);
                        }
                        else
                        {
                            if (footballer.position != "Goalkeeper") // sub with all except goalkeeper
                            {
                                footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
                                footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
                                footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
                                    {
                                        SwapFootballer(sender, e);
                                    });
                            }
                            else
                                footballerControl.Content().as<Controls::Button>().IsEnabled(false);
                        }
                    }
                    else if (pressedFootballer.position == "Midfielder")
                    {
                        if (footballer.position != "Goalkeeper")
                        {
                            footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
                            footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
                            footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
                                {
                                    SwapFootballer(sender, e);
                                });
                        }
                        else
                            footballerControl.Content().as<Controls::Button>().IsEnabled(false);
                    }
                    else if (pressedFootballer.position == "Forward")
                    {
                        if (defCount == 3) // Sub with forwards only
                        {
                            if (footballer.position == "Forward")
                            {
                                footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
                                footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
                                footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
                                    {
                                        SwapFootballer(sender, e);
                                    });
                            }
                            else
                                footballerControl.Content().as<Controls::Button>().IsEnabled(false);
                        }
                        else // sub with all except goalkeeper
                        {
                            if (footballer.position != "Goalkeeper")
                            {
                                footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
                                footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
                                footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
                                    {
                                        SwapFootballer(sender, e);
                                    });
                            }
                            else
                                footballerControl.Content().as<Controls::Button>().IsEnabled(false);
                        }
                    }

                    // adding the control to the ui
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
            else
            {
                footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
                footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Red()));
                footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
                    {
                        CancelChanges(sender, e);
                    });
                if (footballer.position == "Goalkeeper")
                    GkPanel().Children().Append(footballerControl);
                else if (footballer.position == "Defender")
                    DefPanel().Children().Append(footballerControl);
                else if (footballer.position == "Midfielder")
                    MidPanel().Children().Append(footballerControl);
                else if (footballer.position == "Forward")
                    FwdPanel().Children().Append(footballerControl);
            }
            footballerControls[footballer.id] = footballerControl;
        }
    }
    else // pressed footballer is benched
    {
        for (it = footballers.begin(); it != footballers.end(); it++)
        {
            UiFootballer footballer = it->second;
            FootballerControl footballerControl;
            footballerControl.PlayerName(to_hstring(footballer.name));
            footballerControl.PlayerInfo(to_hstring(footballer.info));
            footballerControl.Name(to_hstring(footballer.id));
            if (footballer.id != pressedFootballer.id)
            {
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

                    if (pressedFootballer.position == "Goalkeeper") 
                    {
                        if (footballer.position == "Goalkeeper")
                        {
                            footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
                            footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Red()));
                            footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
                                {
                                    SwapFootballer(sender, e);
                                });
                        }
                        else
                            footballerControl.Content().as<Controls::Button>().IsEnabled(false);
                    }
                    else if (pressedFootballer.position == "Defender")
                    {
                        if (footballer.position != "Goalkeeper") 
                        {
                            if (defCount > 3)
                            {
                                footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
                                footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Red()));
                                footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
                                    {
                                        SwapFootballer(sender, e);
                                    });
                            }
                            else
                                footballerControl.Content().as<Controls::Button>().IsEnabled(false);
                        }
                        else
                            footballerControl.Content().as<Controls::Button>().IsEnabled(false);
                        
                    }
                    else if (pressedFootballer.position == "Midfielder")
                    {
                        if (footballer.position != "Goalkeeper")
                        {
                            if (midCount > 2)
                            {
                                footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
                                footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Red()));
                                footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
                                    {
                                        SwapFootballer(sender, e);
                                    });
                            }
                            else
                                footballerControl.Content().as<Controls::Button>().IsEnabled(false);
                        }
                        else
                            footballerControl.Content().as<Controls::Button>().IsEnabled(false);
                    }
                    else if (pressedFootballer.position == "Forward")
                    {
                        if (footballer.position != "Goalkeeper")
                        {
                            if (fwdCount > 1)
                            {
                                footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
                                footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Red()));
                                footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
                                    {
                                        SwapFootballer(sender, e);
                                    });
                            }
                            else
                                footballerControl.Content().as<Controls::Button>().IsEnabled(false);
                        }
                        else
                            footballerControl.Content().as<Controls::Button>().IsEnabled(false);
                    }
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

                    if (pressedFootballer.position == "Goalkeeper") 
                        footballerControl.Content().as<Controls::Button>().IsEnabled(false);
                    else
                    {
                        if (footballer.position != "Goalkeeper")
                        {
                            footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
                            footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
                            footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
                                {
                                    SwapFootballer(sender, e);
                                });
                        }
                        else
                            footballerControl.Content().as<Controls::Button>().IsEnabled(false);
                    }
                }
            }
            else 
            {
                footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
                footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
                footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
                    {
                        CancelChanges(sender, e);
                    });

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
            footballerControls[footballer.id] = footballerControl;
        }
    }

}

void winrt::FootballFantasy::implementation::SubstitutePlayerPage::SwapFootballer(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    FootballerControl pressedPlayer = footballerControls[Presenter::getInstance()->getPressedFootballerControlId()];
    FootballerControl substitutePlayer = sender.as<Controls::Button>().Parent().as<FootballerControl>();

    auto pressedPlayerParent = pressedPlayer.Parent();
    auto substitutePlayerParent = substitutePlayer.Parent();
    if (pressedPlayerParent.try_as<Controls::StackPanel>()) // pressed player was starting, so substitute player is on the bench
    {
        string pressedPlayerPosition = to_string(pressedPlayerParent.as<Controls::StackPanel>().Name());
        int column = Controls::Grid::GetColumn(substitutePlayer);
        string substitutePlayerPosition = to_string(substitutePlayerParent.as<Controls::Grid>().Children().GetAt(column * 2).as<Controls::TextBlock>().Text());
        if (pressedPlayerPosition == "GkPanel")
            SubsGrid().Children().GetAt(column * 2).as<Controls::TextBlock>().Text(L"GK");
        else if (pressedPlayerPosition == "DefPanel")
            SubsGrid().Children().GetAt(column * 2).as<Controls::TextBlock>().Text(L"DEF");
        else if (pressedPlayerPosition == "MidPanel")
            SubsGrid().Children().GetAt(column * 2).as<Controls::TextBlock>().Text(L"MID");
        else if (pressedPlayerPosition == "FwdPanel")
            SubsGrid().Children().GetAt(column * 2).as<Controls::TextBlock>().Text(L"FWD");
        uint32_t panelIndex;

        pressedPlayerParent.as<Controls::StackPanel>().Children().IndexOf(pressedPlayer, panelIndex);
        pressedPlayerParent.as<Controls::StackPanel>().Children().RemoveAt(panelIndex);

        substitutePlayerParent.as<Controls::Grid>().Children().RemoveAt(column * 2 + 1);
        if (substitutePlayerPosition == "GK")
            GkPanel().Children().Append(substitutePlayer);
        else if (substitutePlayerPosition == "DEF")
            DefPanel().Children().Append(substitutePlayer);
        else if (substitutePlayerPosition == "MID")
            MidPanel().Children().Append(substitutePlayer);
        else if (substitutePlayerPosition == "FWD")
            FwdPanel().Children().Append(substitutePlayer);

        substitutePlayerParent.as<Controls::Grid>().Children().InsertAt(column * 2 + 1, pressedPlayer);
        substitutePlayerParent.as<Controls::Grid>().SetColumn(pressedPlayer, column);
        substitutePlayerParent.as<Controls::Grid>().SetRow(pressedPlayer, 1);
        pressedPlayer.HorizontalAlignment(HorizontalAlignment::Center);
    }
    else // pressed player out was benched 
    {
        if (substitutePlayerParent.try_as<Controls::StackPanel>()) // substitute player was starting
        {
            int column = Controls::Grid::GetColumn(pressedPlayer);
            string pressedPlayerPosition = to_string(pressedPlayerParent.as<Controls::Grid>().Children().GetAt(column * 2).as<Controls::TextBlock>().Text());
            string substitutePlayerPosition = to_string(substitutePlayerParent.as<Controls::StackPanel>().Name());
            if (substitutePlayerPosition == "GkPanel")
                SubsGrid().Children().GetAt(column * 2).as<Controls::TextBlock>().Text(L"GK");
            else if (substitutePlayerPosition == "DefPanel")
                SubsGrid().Children().GetAt(column * 2).as<Controls::TextBlock>().Text(L"DEF");
            else if (substitutePlayerPosition == "MidPanel")
                SubsGrid().Children().GetAt(column * 2).as<Controls::TextBlock>().Text(L"MID");
            else if (substitutePlayerPosition == "FwdPanel")
                SubsGrid().Children().GetAt(column * 2).as<Controls::TextBlock>().Text(L"FWD");

            uint32_t panelIndex;
            substitutePlayerParent.as<Controls::StackPanel>().Children().IndexOf(substitutePlayer, panelIndex);
            substitutePlayerParent.as<Controls::StackPanel>().Children().RemoveAt(panelIndex);

            pressedPlayerParent.as<Controls::Grid>().Children().RemoveAt(column * 2 + 1);
            if (pressedPlayerPosition == "GK")
                GkPanel().Children().Append(pressedPlayer);
            else if (pressedPlayerPosition == "DEF")
                DefPanel().Children().Append(pressedPlayer);
            else if (pressedPlayerPosition == "MID")
                MidPanel().Children().Append(pressedPlayer);
            else if (pressedPlayerPosition == "FWD")
                FwdPanel().Children().Append(pressedPlayer);

            pressedPlayerParent.as<Controls::Grid>().Children().InsertAt(column * 2 + 1, substitutePlayer);
            pressedPlayerParent.as<Controls::Grid>().SetColumn(substitutePlayer, column);
            pressedPlayerParent.as<Controls::Grid>().SetRow(substitutePlayer, 1);
            substitutePlayer.HorizontalAlignment(HorizontalAlignment::Center);
        }
        else // substitute player was benched (both were on the bench)
        {
            int pressedPlayerColumn = Controls::Grid::GetColumn(pressedPlayer);
            int substitutePlayerColumn = Controls::Grid::GetColumn(substitutePlayer);

            hstring pressedPlayerPosition = SubsGrid().Children().GetAt(pressedPlayerColumn * 2).as<Controls::TextBlock>().Text();
            hstring substitutePlayerPosition = SubsGrid().Children().GetAt(substitutePlayerColumn * 2).as<Controls::TextBlock>().Text();
            SubsGrid().Children().GetAt(pressedPlayerColumn * 2).as<Controls::TextBlock>().Text(substitutePlayerPosition);
            SubsGrid().Children().GetAt(substitutePlayerColumn * 2).as<Controls::TextBlock>().Text(pressedPlayerPosition);

            uint32_t indexToRemove;
            SubsGrid().Children().IndexOf(pressedPlayer, indexToRemove);
            SubsGrid().Children().RemoveAt(indexToRemove);
            SubsGrid().Children().IndexOf(substitutePlayer, indexToRemove);
            SubsGrid().Children().RemoveAt(indexToRemove);

            SubsGrid().Children().Append(substitutePlayer);
            SubsGrid().SetRow(substitutePlayer, 1);
            SubsGrid().SetColumn(substitutePlayer, pressedPlayerColumn);
            substitutePlayer.HorizontalAlignment(HorizontalAlignment::Center);
            
            SubsGrid().Children().Append(pressedPlayer);
            SubsGrid().SetRow(pressedPlayer, 1);
            SubsGrid().SetColumn(pressedPlayer, substitutePlayerColumn);
            pressedPlayer.HorizontalAlignment(HorizontalAlignment::Center);
        }
    }

}

void winrt::FootballFantasy::implementation::SubstitutePlayerPage::CancelChanges(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    Frame().GoBack();
}

//void winrt::FootballFantasy::implementation::PlayerTeamPickTeamPage::dialogButtonClickHandler(winrt::Windows::Foundation::IInspectable const& dialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args)
//{
//    auto senderDialog = dialog.as<Controls::ContentDialog>();
//    int footballerId = stoi(to_string(senderDialog.Name()));
//    Footballer footballer = Presenter::getInstance()->getFootballer(footballerId);
//    senderDialog.Hide();
//    PlayerTeam playerTeam = *Presenter::getInstance()->getPlayerTeam();
//
//    unordered_map<int, pair<Footballer*, bool>>::iterator it;
//    unordered_map<int, pair<Footballer*, bool>> squad = playerTeam.getSquad();
//    int defCount = 0;
//    int midCount = 0;
//    int fwdCount = 0;
//    for (it = squad.begin(); it != squad.end(); it++)
//    {
//        if (it->second.first->getPosition() == "Defender")
//            defCount++;
//        else if (it->second.first->getPosition() == "Midfielder")
//            midCount++;
//        else if (it->second.first->getPosition() == "Forward")
//            fwdCount++;
//    }
//
//    if (playerTeam.getSquad()[footballerId].second) // Footballer in the starting lineup
//    {
//        //// Disable all starting players except the pressed player
//        //for (auto element : GkPanel().Children())
//        //{
//        //    FootballerControl footballerControl = element.as<FootballerControl>();
//        //    if (footballerControl.Name() != senderDialog.Name()) // not the pressed footballer, disable
//        //        element.as<FootballerControl>().Content().as<Controls::Button>().IsEnabled(false);
//        //    else // change pressed footballer to red
//        //    {
//        //        element.as<FootballerControl>().Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
//        //        element.as<FootballerControl>().Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Red()));
//        //    }
//        //}
//        //for (auto element : DefPanel().Children())
//        //{
//        //    FootballerControl footballerControl = element.as<FootballerControl>();
//        //    if (footballerControl.Name() != senderDialog.Name()) // not the pressed footballer, disable
//        //        element.as<FootballerControl>().Content().as<Controls::Button>().IsEnabled(false);
//        //    else // change pressed footballer to red
//        //    {
//        //        element.as<FootballerControl>().Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
//        //        element.as<FootballerControl>().Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Red()));
//        //    }
//        //}
//        //for (auto element : MidPanel().Children())
//        //{
//        //    FootballerControl footballerControl = element.as<FootballerControl>();
//        //    if (footballerControl.Name() != senderDialog.Name()) // not the pressed footballer, disable
//        //        element.as<FootballerControl>().Content().as<Controls::Button>().IsEnabled(false);
//        //    else // change pressed footballer to red
//        //    {
//        //        element.as<FootballerControl>().Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
//        //        element.as<FootballerControl>().Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Red()));
//        //    }
//        //}
//        //for (auto element : FwdPanel().Children())
//        //{
//        //    FootballerControl footballerControl = element.as<FootballerControl>();
//        //    if (footballerControl.Name() != senderDialog.Name()) // not the pressed footballer, disable
//        //        element.as<FootballerControl>().Content().as<Controls::Button>().IsEnabled(false);
//        //    else // change pressed footballer to red
//        //    {
//        //        element.as<FootballerControl>().Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
//        //        element.as<FootballerControl>().Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Red()));
//        //    }
//        //}
//
//        string footballerPosition = footballer.getPosition();
//        if (footballerPosition == "Goalkeeper")
//        {
//            for (int column = 0; column < SubsGrid().ColumnDefinitions().Size(); ++column)
//            {
//                for (int row = 0; row < SubsGrid().RowDefinitions().Size(); row += 2)
//                {
//                    // Get the first and second child elements in the current column
//                    auto text = SubsGrid().Children().GetAt(column * 2).as<Controls::TextBlock>();
//                    auto footballerControl = SubsGrid().Children().GetAt(column * 2 + 1).as<FootballerControl>();
//                    if (to_string(text.Text()) == footballer.positionUpperAbbrv())
//                    {
//                        footballerControl.Content().as<Controls::Button>().Click(nullptr);
//                        footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
//                            {
//                                swapFootballerControls(pressedFootballerControl, footballerControl);
//                            });
//                        footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
//                        footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
//                    }
//                    else
//                        footballerControl.Content().as<Controls::Button>().IsEnabled(false);
//                }
//            }
//        }
//        else if (footballerPosition == "Defender")
//        {
//            if (defCount == 3) // Sub with defenders only
//            {
//                for (int column = 0; column < SubsGrid().ColumnDefinitions().Size(); ++column)
//                {
//                    for (int row = 0; row < SubsGrid().RowDefinitions().Size(); row += 2)
//                    {
//                        // Get the first and second child elements in the current column
//                        auto text = SubsGrid().Children().GetAt(column * 2).as<Controls::TextBlock>();
//                        auto footballerControl = SubsGrid().Children().GetAt(column * 2 + 1).as<FootballerControl>();
//                        if (to_string(text.Text()) == footballer.positionUpperAbbrv())
//                        {
//                            footballerControl.Content().as<Controls::Button>().Click(nullptr);
//                            footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
//                                {
//                                    swapFootballerControls(pressedFootballerControl, footballerControl);
//                                });
//                            footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
//                            footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
//                        }
//                        else
//                            footballerControl.Content().as<Controls::Button>().IsEnabled(false);
//                    }
//                }
//            }
//            else // Sub with all except goalkeeper
//            {
//                for (int column = 0; column < SubsGrid().ColumnDefinitions().Size(); ++column)
//                {
//                    for (int row = 0; row < SubsGrid().RowDefinitions().Size(); row += 2)
//                    {
//                        // Get the first and second child elements in the current column
//                        auto text = SubsGrid().Children().GetAt(column * 2).as<Controls::TextBlock>();
//                        auto footballerControl = SubsGrid().Children().GetAt(column * 2 + 1).as<FootballerControl>();
//                        if (to_string(text.Text()) != "GK")
//                        {
//                            footballerControl.Content().as<Controls::Button>().Click(nullptr);
//                            footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
//                                {
//                                    swapFootballerControls(pressedFootballerControl, footballerControl);
//                                });
//                            footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
//                            footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
//                        }
//                        else
//                            footballerControl.Content().as<Controls::Button>().IsEnabled(false);
//                    }
//                }
//            }
//        }
//        else if (footballerPosition == "Midfielder") // Sub with all except goalkeeper
//        {
//            for (int column = 0; column < SubsGrid().ColumnDefinitions().Size(); ++column)
//            {
//                for (int row = 0; row < SubsGrid().RowDefinitions().Size(); row += 2)
//                {
//                    // Get the first and second child elements in the current column
//                    auto text = SubsGrid().Children().GetAt(column * 2).as<Controls::TextBlock>();
//                    auto footballerControl = SubsGrid().Children().GetAt(column * 2 + 1).as<FootballerControl>();
//                    if (to_string(text.Text()) != "GK")
//                    {
//                        footballerControl.Content().as<Controls::Button>().Click(nullptr);
//                        footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
//                            {
//                                swapFootballerControls(pressedFootballerControl, footballerControl);
//                            });
//                        footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
//                        footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
//                    }
//                    else
//                        footballerControl.Content().as<Controls::Button>().IsEnabled(false);
//                }
//            }
//        }
//        else if (footballerPosition == "Forward")
//        {
//            if (fwdCount == 1) // Sub with forwards only
//            {
//                for (int column = 0; column < SubsGrid().ColumnDefinitions().Size(); ++column)
//                {
//                    for (int row = 0; row < SubsGrid().RowDefinitions().Size(); row += 2)
//                    {
//                        // Get the first and second child elements in the current column
//                        auto text = SubsGrid().Children().GetAt(column * 2).as<Controls::TextBlock>();
//                        auto footballerControl = SubsGrid().Children().GetAt(column * 2 + 1).as<FootballerControl>();
//                        if (to_string(text.Text()) == footballer.positionUpperAbbrv())
//                        {
//                            footballerControl.Content().as<Controls::Button>().Click(nullptr);
//                            footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
//                                {
//                                    swapFootballerControls(pressedFootballerControl, footballerControl);
//                                });
//                            footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
//                            footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
//                        }
//                        else
//                            footballerControl.Content().as<Controls::Button>().IsEnabled(false);
//                    }
//                }
//            }
//            else // Sub with all except goalkeeper
//            {
//                for (int column = 0; column < SubsGrid().ColumnDefinitions().Size(); ++column)
//                {
//                    for (int row = 0; row < SubsGrid().RowDefinitions().Size(); row += 2)
//                    {
//                        // Get the first and second child elements in the current column
//                        auto text = SubsGrid().Children().GetAt(column * 2).as<Controls::TextBlock>();
//                        auto footballerControl = SubsGrid().Children().GetAt(column * 2 + 1).as<FootballerControl>();
//                        if (to_string(text.Text()) != "GK")
//                        {
//                            footballerControl.Content().as<Controls::Button>().Click(nullptr);
//                            footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
//                                {
//                                    swapFootballerControls(pressedFootballerControl, footballerControl);
//                                });
//                            footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
//                            footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
//                        }
//                        else
//                            footballerControl.Content().as<Controls::Button>().IsEnabled(false);
//                    }
//                }
//            }
//        }
//    }
//    else // Footballer on the bench
//    {
//        string footballerPosition = footballer.getPosition();
//        if (footballerPosition == "Goalkeeper")
//        {
//            for (auto element : SubsGrid().Children())
//                if (element.as<FootballerControl>().Name() == senderDialog.Name())
//                {
//                    element.as<FootballerControl>().Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
//                    element.as<FootballerControl>().Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
//                    break;
//                }
//            GkPanel().Children().GetAt(0).as<FootballerControl>().Content().as<Controls::Button>().Click(nullptr);
//            GkPanel().Children().GetAt(0).as<FootballerControl>().Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
//                {
//                    swapFootballerControls(pressedFootballerControl, GkPanel().Children().GetAt(0).as<FootballerControl>());
//                });
//            GkPanel().Children().GetAt(0).as<FootballerControl>().Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
//            GkPanel().Children().GetAt(0).as<FootballerControl>().Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Red()));
//            for (auto element : DefPanel().Children())
//                element.as<FootballerControl>().Content().as<Controls::Button>().IsEnabled(false);
//            for (auto element : MidPanel().Children())
//                element.as<FootballerControl>().Content().as<Controls::Button>().IsEnabled(false);
//            for (auto element : FwdPanel().Children())
//                element.as<FootballerControl>().Content().as<Controls::Button>().IsEnabled(false);
//        }
//        else
//        {
//            GkPanel().Children().GetAt(0).as<FootballerControl>().Content().as<Controls::Button>().IsEnabled(false);
//            for (auto element : DefPanel().Children())
//            {
//                if (defCount > 3)
//                {
//                    element.as<FootballerControl>().Content().as<Controls::Button>().Click(nullptr);
//                    element.as<FootballerControl>().Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
//                        {
//                            swapFootballerControls(pressedFootballerControl, element.as<FootballerControl>());
//                        });
//                    element.as<FootballerControl>().Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
//                    element.as<FootballerControl>().Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Red()));
//                }
//            }
//            for (auto element : MidPanel().Children())
//            {
//                if (midCount > 2)
//                {
//                    element.as<FootballerControl>().Content().as<Controls::Button>().Click(nullptr);
//                    element.as<FootballerControl>().Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
//                        {
//                            swapFootballerControls(pressedFootballerControl, element.as<FootballerControl>());
//                        });
//                    element.as<FootballerControl>().Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
//                    element.as<FootballerControl>().Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Red()));
//                }
//            }
//            for (auto element : FwdPanel().Children())
//            {
//                if (fwdCount > 1)
//                {
//                    element.as<FootballerControl>().Content().as<Controls::Button>().Click(nullptr);
//                    element.as<FootballerControl>().Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
//                        {
//                            swapFootballerControls(pressedFootballerControl, element.as<FootballerControl>());
//                        });
//                    element.as<FootballerControl>().Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
//                    element.as<FootballerControl>().Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Red()));
//                }
//            }
//            for (int column = 0; column < SubsGrid().ColumnDefinitions().Size(); ++column)
//            {
//                for (int row = 0; row < SubsGrid().RowDefinitions().Size(); row += 2)
//                {
//                    // Get the first and second child elements in the current column
//                    auto text = SubsGrid().Children().GetAt(column * 2).as<Controls::TextBlock>();
//                    auto footballerControl = SubsGrid().Children().GetAt(column * 2 + 1).as<FootballerControl>();
//                    if (to_string(text.Text()) != "GK")
//                    {
//                        footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
//                        footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
//                        if (pressedFootballerControl == footballerControl)
//                        {
//
//                        }
//                        else
//                        {
//                            footballerControl.Content().as<Controls::Button>().Click(nullptr);
//                            footballerControl.Content().as<Controls::Button>().Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
//                                {
//                                    swapFootballerControls(pressedFootballerControl, footballerControl);
//                                });
//                        }
//                    }
//                    else
//                        footballerControl.Content().as<Controls::Button>().IsEnabled(false);
//                }
//            }
//
//        }
//    }
//
//}