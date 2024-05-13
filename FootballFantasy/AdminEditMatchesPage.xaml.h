#pragma once

#include "AdminEditMatchesPage.g.h"
#include "Footballer.h"

namespace winrt::FootballFantasy::implementation
{
    struct AdminEditMatchesPage : AdminEditMatchesPageT<AdminEditMatchesPage>
    {
        AdminEditMatchesPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void AddFootballer(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateListView(winrt::Microsoft::UI::Xaml::Controls::ListView& listView, Footballer footballer);
        void AddFootballerToUI(winrt::Windows::Foundation::IInspectable const& dialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
        void FootballerOptions(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void SubstituteFootballer(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void SubstituteFootballer_Dialog_Click(winrt::Windows::Foundation::IInspectable const& dialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
        void Confirm_Stats(winrt::Windows::Foundation::IInspectable const& dialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
        void ConfirmBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct AdminEditMatchesPage : AdminEditMatchesPageT<AdminEditMatchesPage, implementation::AdminEditMatchesPage>
    {
    };
}
