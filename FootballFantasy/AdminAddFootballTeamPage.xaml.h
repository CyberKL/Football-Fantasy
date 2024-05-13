#pragma once

#include "AdminAddFootballTeamPage.g.h"

namespace winrt::FootballFantasy::implementation
{
    struct AdminAddFootballTeamPage : AdminAddFootballTeamPageT<AdminAddFootballTeamPage>
    {
        AdminAddFootballTeamPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct AdminAddFootballTeamPage : AdminAddFootballTeamPageT<AdminAddFootballTeamPage, implementation::AdminAddFootballTeamPage>
    {
    };
}
