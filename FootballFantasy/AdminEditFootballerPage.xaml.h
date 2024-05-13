#pragma once

#include "AdminEditFootballerPage.g.h"

namespace winrt::FootballFantasy::implementation
{
    struct AdminEditFootballerPage : AdminEditFootballerPageT<AdminEditFootballerPage>
    {
        AdminEditFootballerPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ChangeTeam_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RemoveFootballer_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void AddFootballer_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct AdminEditFootballerPage : AdminEditFootballerPageT<AdminEditFootballerPage, implementation::AdminEditFootballerPage>
    {
    };
}
