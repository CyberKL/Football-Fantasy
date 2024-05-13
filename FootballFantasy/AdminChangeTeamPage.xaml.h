#pragma once

#include "AdminChangeTeamPage.g.h"
#include "Footballer.h"
namespace winrt::FootballFantasy::implementation
{
    struct AdminChangeTeamPage : AdminChangeTeamPageT<AdminChangeTeamPage>
    {
        AdminChangeTeamPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void pickFootballer_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateListView(winrt::Microsoft::UI::Xaml::Controls::ListView& listView, Footballer footballer);
    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct AdminChangeTeamPage : AdminChangeTeamPageT<AdminChangeTeamPage, implementation::AdminChangeTeamPage>
    {
    };
}
