#pragma once

#include "AdminEditFootballteamPage.g.h"

namespace winrt::FootballFantasy::implementation
{
    struct AdminEditFootballteamPage : AdminEditFootballteamPageT<AdminEditFootballteamPage>
    {
        AdminEditFootballteamPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void AddFootballTeam_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RemoveFootballTeam_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct AdminEditFootballteamPage : AdminEditFootballteamPageT<AdminEditFootballteamPage, implementation::AdminEditFootballteamPage>
    {
    };
}
