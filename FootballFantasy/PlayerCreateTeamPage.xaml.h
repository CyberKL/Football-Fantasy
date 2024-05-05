#pragma once

#include "PlayerCreateTeamPage.g.h"

namespace winrt::FootballFantasy::implementation
{
    struct PlayerCreateTeamPage : PlayerCreateTeamPageT<PlayerCreateTeamPage>
    {
        PlayerCreateTeamPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void AddFootballer(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void SubmitBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void removeFootballer(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct PlayerCreateTeamPage : PlayerCreateTeamPageT<PlayerCreateTeamPage, implementation::PlayerCreateTeamPage>
    {
    };
}
