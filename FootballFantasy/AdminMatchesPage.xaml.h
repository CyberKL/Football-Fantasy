#pragma once

#include "AdminMatchesPage.g.h"

namespace winrt::FootballFantasy::implementation
{
    struct AdminMatchesPage : AdminMatchesPageT<AdminMatchesPage>
    {
        AdminMatchesPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct AdminMatchesPage : AdminMatchesPageT<AdminMatchesPage, implementation::AdminMatchesPage>
    {
    };
}
