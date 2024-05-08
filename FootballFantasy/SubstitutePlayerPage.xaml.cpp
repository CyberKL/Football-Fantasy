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
    void SubstitutePlayerPage::updateTempSquad()
    {
        unordered_map<int, bool> tempSquad;

        for (auto element : GkPanel().Children())
            tempSquad[stoi(to_string(element.as<FootballerControl>().Name()))] = true;
        for (auto element : DefPanel().Children())
            tempSquad[stoi(to_string(element.as<FootballerControl>().Name()))] = true;
        for (auto element : MidPanel().Children())
            tempSquad[stoi(to_string(element.as<FootballerControl>().Name()))] = true;
        for (auto element : FwdPanel().Children())
            tempSquad[stoi(to_string(element.as<FootballerControl>().Name()))] = true;
        for (auto element :SubsGrid().Children())
            if (element.try_as<FootballerControl>())
                tempSquad[stoi(to_string(element.as<FootballerControl>().Name()))] = false;
        
        Presenter::getInstance()->setTempSquad(tempSquad);
        Presenter::getInstance()->setSquadEdited(true);
    }
}


void winrt::FootballFantasy::implementation::SubstitutePlayerPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    for (auto item : Frame().Parent().as<Controls::NavigationView>().MenuItems())
        item.as<Controls::NavigationViewItem>().IsEnabled(false);
    Frame().Parent().as<Controls::NavigationView>().IsBackEnabled(false);
    Frame().Parent().as<Controls::NavigationView>().SettingsItem().as<Controls::NavigationViewItem>().IsEnabled(false);

    int pressedFootballerControlId = Presenter::getInstance()->getPressedFootballerControlId();

    unordered_map<int, struct UiFootballer> footballers;
    int captainId;
    int viceCaptainId;
    if (Presenter::getInstance()->getSquadEdited())
    {
        footballers = Presenter::getInstance()->loadTempSquad();
    }
    else
    {
        footballers = Presenter::getInstance()->loadPickTeamPage();
    }

    if (Presenter::getInstance()->getCaptaincyEdited())
    {
        captainId = Presenter::getInstance()->getTempCaptainId();
        viceCaptainId = Presenter::getInstance()->getTempViceCaptainId();
    }
    else
        Presenter::getInstance()->getCaptainsIds(captainId, viceCaptainId);

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

                    if (footballer.id == captainId)
                        footballerControl.CaptaincyIcon(L"\uE735");
                    else if (footballer.id == viceCaptainId)
                        footballerControl.CaptaincyIcon(L"\uE7C6");
                    else
                        footballerControl.CaptaincyIcon(L"");

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
                    footballerControl.CaptaincyIcon(L"");
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
                if (footballer.id == captainId)
                    footballerControl.CaptaincyIcon(L"\uE735");
                else if (footballer.id == viceCaptainId)
                    footballerControl.CaptaincyIcon(L"\uE7C6");
                else
                    footballerControl.CaptaincyIcon(L"");

                footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
                footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Red()));
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
                footballerControl.CaptaincyIcon(L"");
                footballerControl.Content().as<Controls::Button>().BorderThickness(ThicknessHelper::FromLengths(2, 2, 2, 2));
                footballerControl.Content().as<Controls::Button>().BorderBrush(Media::SolidColorBrush(Windows::UI::Colors::Green()));
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

    int captainId;
    int viceCaptainId;
    if (Presenter::getInstance()->getCaptaincyEdited())
    {
        captainId = Presenter::getInstance()->getTempCaptainId();
        viceCaptainId = Presenter::getInstance()->getTempViceCaptainId();
    }
    else
        Presenter::getInstance()->getCaptainsIds(captainId, viceCaptainId);

    int pressedPlayerId = stoi(to_string(pressedPlayer.Name()));
    int substitutePlayerId = stoi(to_string(substitutePlayer.Name()));

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

        // dealing with captaincy
        if (pressedPlayerId == captainId)
        {
            Presenter::getInstance()->setTempCaptainId(substitutePlayerId);
            Presenter::getInstance()->setTempViceCaptainId(viceCaptainId);
            Presenter::getInstance()->setCaptaincyEdited(true);
        }
        else if (pressedPlayerId == viceCaptainId)
        {
            Presenter::getInstance()->setTempCaptainId(captainId);
            Presenter::getInstance()->setTempViceCaptainId(substitutePlayerId);
            Presenter::getInstance()->setCaptaincyEdited(true);
        }

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

            // dealing with captaincy
            if (substitutePlayerId == captainId)
            {
                Presenter::getInstance()->setTempCaptainId(pressedPlayerId);
                Presenter::getInstance()->setTempViceCaptainId(viceCaptainId);
                Presenter::getInstance()->setCaptaincyEdited(true);
            }
            else if (substitutePlayerId == viceCaptainId)
            {
                Presenter::getInstance()->setTempCaptainId(captainId);
                Presenter::getInstance()->setTempViceCaptainId(pressedPlayerId);
                Presenter::getInstance()->setCaptaincyEdited(true);
            }
        }
        else // substitute player was benched (both were on the bench)
        {
            int pressedPlayerColumn = Controls::Grid::GetColumn(pressedPlayer);
            int substitutePlayerColumn = Controls::Grid::GetColumn(substitutePlayer);

            hstring pressedPlayerPosition = SubsGrid().Children().GetAt(pressedPlayerColumn * 2).as<Controls::TextBlock>().Text();
            hstring substitutePlayerPosition = SubsGrid().Children().GetAt(substitutePlayerColumn * 2).as<Controls::TextBlock>().Text();
            SubsGrid().Children().GetAt(pressedPlayerColumn * 2).as<Controls::TextBlock>().Text(substitutePlayerPosition);
            SubsGrid().Children().GetAt(substitutePlayerColumn * 2).as<Controls::TextBlock>().Text(pressedPlayerPosition);

            uint32_t pressedIndex;
            uint32_t substituteIndex;
            SubsGrid().Children().IndexOf(pressedPlayer, pressedIndex);
            SubsGrid().Children().RemoveAt(pressedIndex);
            SubsGrid().Children().IndexOf(substitutePlayer, substituteIndex);
            SubsGrid().Children().RemoveAt(substituteIndex);


            SubsGrid().Children().InsertAt(pressedIndex, substitutePlayer);
            SubsGrid().SetRow(substitutePlayer, 1);
            SubsGrid().SetColumn(substitutePlayer, pressedPlayerColumn);
            substitutePlayer.HorizontalAlignment(HorizontalAlignment::Center);
            
            SubsGrid().Children().InsertAt(substituteIndex, pressedPlayer);
            SubsGrid().SetRow(pressedPlayer, 1);
            SubsGrid().SetColumn(pressedPlayer, substitutePlayerColumn);
            pressedPlayer.HorizontalAlignment(HorizontalAlignment::Center);
        }
    }
    updateTempSquad();
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerTeamPickTeamPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}

void winrt::FootballFantasy::implementation::SubstitutePlayerPage::CancelChanges(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    for (auto item : Frame().Parent().as<Controls::NavigationView>().MenuItems())
        item.as<Controls::NavigationViewItem>().IsEnabled(true);
    Frame().Parent().as<Controls::NavigationView>().IsBackEnabled(true);
    Frame().Parent().as<Controls::NavigationView>().SettingsItem().as<Controls::NavigationViewItem>().IsEnabled(true);

    Presenter::getInstance()->setSquadEdited(false);
    Presenter::getInstance()->setCaptaincyEdited(false);
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerTeamPickTeamPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}

void winrt::FootballFantasy::implementation::SubstitutePlayerPage::ConfirmChanges(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    for (auto item : Frame().Parent().as<Controls::NavigationView>().MenuItems())
        item.as<Controls::NavigationViewItem>().IsEnabled(true);
    Frame().Parent().as<Controls::NavigationView>().IsBackEnabled(true);
    Frame().Parent().as<Controls::NavigationView>().SettingsItem().as<Controls::NavigationViewItem>().IsEnabled(true);

    Presenter::getInstance()->confirmChangesInPickTeam();
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerTeamPickTeamPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}