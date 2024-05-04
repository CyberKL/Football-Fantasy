#pragma once

#include "LoginPage.g.h"
#include "Presenter.h"

namespace winrt::FootballFantasy::implementation
{
    struct LoginPage : LoginPageT<LoginPage>
    {
        LoginPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void Hyperlink_Click(winrt::Microsoft::UI::Xaml::Documents::Hyperlink const& sender, winrt::Microsoft::UI::Xaml::Documents::HyperlinkClickEventArgs const& args);
        void LoginBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::FootballFantasy::factory_implementation
{
    struct LoginPage : LoginPageT<LoginPage, implementation::LoginPage>
    {
    };
}
