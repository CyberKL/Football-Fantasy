#pragma once

#include "FootballerControl.g.h"

namespace winrt::FootballFantasy::implementation
{
    struct FootballerControl : FootballerControlT<FootballerControl>
    {
        FootballerControl()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        //static winrt::Microsoft::UI::Xaml::DependencyProperty PlayerName;

        int32_t MyProperty();
        void MyProperty(int32_t value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty PlayerNameProperty() noexcept
        {
            return s_PlayerNameProperty;
        }
        auto PlayerName() const noexcept
        {
            return winrt::unbox_value<winrt::hstring>(GetValue(PlayerNameProperty()));
        }
        void PlayerName(winrt::hstring const& value)
        {
            SetValue(PlayerNameProperty(), winrt::box_value(value));
        }
        static winrt::Microsoft::UI::Xaml::DependencyProperty PlayerInfoProperty() noexcept
        {
            return s_PlayerInfoProperty;
        }
        auto PlayerInfo() const noexcept
        {
            return winrt::unbox_value<winrt::hstring>(GetValue(PlayerInfoProperty()));
        }
        void PlayerInfo(winrt::hstring const& value)
        {
            SetValue(PlayerInfoProperty(), winrt::box_value(value));
        }

    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_PlayerNameProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_PlayerInfoProperty;
    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct FootballerControl : FootballerControlT<FootballerControl, implementation::FootballerControl>
    {
    };
}
