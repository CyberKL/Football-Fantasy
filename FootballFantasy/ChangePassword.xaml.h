#pragma once

#include "ChangePassword.g.h"

namespace winrt::FootballFantasy::implementation
{
    struct ChangePassword : ChangePasswordT<ChangePassword>
    {
        ChangePassword()
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
    struct ChangePassword : ChangePasswordT<ChangePassword, implementation::ChangePassword>
    {
    };
}
