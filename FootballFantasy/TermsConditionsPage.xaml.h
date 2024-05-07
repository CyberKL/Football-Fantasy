#pragma once

#include "TermsConditionsPage.g.h"

namespace winrt::FootballFantasy::implementation
{
    struct TermsConditionsPage : TermsConditionsPageT<TermsConditionsPage>
    {
        TermsConditionsPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct TermsConditionsPage : TermsConditionsPageT<TermsConditionsPage, implementation::TermsConditionsPage>
    {
    };
}
