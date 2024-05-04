#pragma once

#include "SignUpPage.g.h"
#include "Presenter.h"

namespace winrt::FootballFantasy::implementation
{
    struct SignUpPage : SignUpPageT<SignUpPage>
    {
        SignUpPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        const hstring PASSWORD_ERROR_TEXT = L"Password must be at least 8 characters long";
        const hstring CONFIRM_PASSWORD_ERROR_TEXT = L"Passwords don't match";

        void Hyperlink_Click(winrt::Microsoft::UI::Xaml::Documents::Hyperlink const& sender, winrt::Microsoft::UI::Xaml::Documents::HyperlinkClickEventArgs const& args);
        void SignUpBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void UsernameBox_GotFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CheckPasswords();
        void ConfirmPasswordBox_PasswordChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void PasswordBox_PasswordChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void PasswordBox_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ConfirmPasswordBox_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct SignUpPage : SignUpPageT<SignUpPage, implementation::SignUpPage>
    {
    };
}
