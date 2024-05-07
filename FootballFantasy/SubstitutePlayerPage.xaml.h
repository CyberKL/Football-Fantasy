#pragma once

#include "SubstitutePlayerPage.g.h"

namespace winrt::FootballFantasy::implementation
{
    struct SubstitutePlayerPage : SubstitutePlayerPageT<SubstitutePlayerPage>
    {
        SubstitutePlayerPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
        void Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void SwapFootballer(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CancelChanges(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ConfirmChanges(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void updateTempSquad();
    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct SubstitutePlayerPage : SubstitutePlayerPageT<SubstitutePlayerPage, implementation::SubstitutePlayerPage>
    {
    };
}
