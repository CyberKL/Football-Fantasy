#pragma once

#include "PlayerTransfersPage.g.h"
#include "Footballer.h"

namespace winrt::FootballFantasy::implementation
{
    struct PlayerTransfersPage : PlayerTransfersPageT<PlayerTransfersPage>
    {
        PlayerTransfersPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
        void Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void FootballerControl_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateListView(winrt::Microsoft::UI::Xaml::Controls::ListView& , Footballer);
        void dialogButtonClickHandler(winrt::Windows::Foundation::IInspectable const& dialog, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& args);
        void ConfirmBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ResetBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void UndoTransfer();
        void UndoBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct PlayerTransfersPage : PlayerTransfersPageT<PlayerTransfersPage, implementation::PlayerTransfersPage>
    {
    };
}
