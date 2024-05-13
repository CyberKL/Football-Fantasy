#pragma once

#include "LuckyWheel.g.h"

namespace winrt::FootballFantasy::implementation
{
    struct LuckyWheel : LuckyWheelT<LuckyWheel>
    {
        LuckyWheel()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct LuckyWheel : LuckyWheelT<LuckyWheel, implementation::LuckyWheel>
    {
    };
}
