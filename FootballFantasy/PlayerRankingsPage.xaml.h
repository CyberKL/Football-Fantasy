#pragma once

#include "PlayerRankingsPage.g.h"

namespace winrt::FootballFantasy::implementation
{
    struct PlayerRankingsPage : PlayerRankingsPageT<PlayerRankingsPage>
    {
        PlayerRankingsPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct PlayerRankingsPage : PlayerRankingsPageT<PlayerRankingsPage, implementation::PlayerRankingsPage>
    {
    };
}
