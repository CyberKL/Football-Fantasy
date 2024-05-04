#pragma once

#include "PlayerPage.g.h"

namespace winrt::FootballFantasy::implementation
{
    struct PlayerPage : PlayerPageT<PlayerPage>
    {
        PlayerPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
        void Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Navigate(hstring pageName);
        void NavView_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);
    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct PlayerPage : PlayerPageT<PlayerPage, implementation::PlayerPage>
    {
    };
}
