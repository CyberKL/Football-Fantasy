#pragma once

#include "AdminAddFootballer.g.h"

namespace winrt::FootballFantasy::implementation
{
    struct AdminAddFootballer : AdminAddFootballerT<AdminAddFootballer>
    {
        AdminAddFootballer()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void FootballerPrice_ValueChanged(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args);
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct AdminAddFootballer : AdminAddFootballerT<AdminAddFootballer, implementation::AdminAddFootballer>
    {
    };
}
