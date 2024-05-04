#include "pch.h"
#include "SignUpPage.xaml.h"
#if __has_include("SignUpPage.g.cpp")
#include "SignUpPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t SignUpPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void SignUpPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void SignUpPage::CheckPasswords()
    {
        string password = to_string(PasswordBox().Password());
        string comfirmPassword = to_string(ConfirmPasswordBox().Password());
        if (password.length() < 8)
        {
            PasswordBox().Password().empty() ? PasswordError().Text(L"") : PasswordError().Text(PASSWORD_ERROR_TEXT);
            SignUpBtn().IsEnabled(false);
        }
        else if (password != comfirmPassword)
        {
            ConfirmPasswordBox().Password().empty() ? ConfirmPasswordError().Text(L"") : ConfirmPasswordError().Text(CONFIRM_PASSWORD_ERROR_TEXT);
            SignUpBtn().IsEnabled(false);
        }
        else
        {
            PasswordError().Text(L"");
            ConfirmPasswordError().Text(L"");
            SignUpBtn().IsEnabled(true);
        }
    }
}


void winrt::FootballFantasy::implementation::SignUpPage::Hyperlink_Click(winrt::Microsoft::UI::Xaml::Documents::Hyperlink const& sender, winrt::Microsoft::UI::Xaml::Documents::HyperlinkClickEventArgs const& args)
{
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.LoginPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}


void winrt::FootballFantasy::implementation::SignUpPage::SignUpBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    hstring duplicateError = L"Username is already taken";
    hstring emptyError = L"Please enter a username";
    string username = to_string(UsernameBox().Text());
    string password = to_string(PasswordBox().Password());
    if (UsernameBox().Text().empty())
        UsernameError().Text(emptyError);
    else if (Presenter::getInstance()->isUsernameDuplicate(username))
        // Handle duplicate username
        UsernameError().Text(duplicateError);
    else
    {
        Presenter::getInstance()->signUp(username, password);
        winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.LoginPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
        Frame().Navigate(page);
    }
}


void winrt::FootballFantasy::implementation::SignUpPage::UsernameBox_GotFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    UsernameError().Text(L"");
}


void winrt::FootballFantasy::implementation::SignUpPage::PasswordBox_PasswordChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    string password = to_string(PasswordBox().Password());
    password.length() < 8 ? PasswordError().Text(PASSWORD_ERROR_TEXT) : PasswordError().Text(L"");
    CheckPasswords();
}


void winrt::FootballFantasy::implementation::SignUpPage::ConfirmPasswordBox_PasswordChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    string password = to_string(PasswordBox().Password());
    string confirmPassword = to_string(ConfirmPasswordBox().Password());
    password != confirmPassword ? ConfirmPasswordError().Text(CONFIRM_PASSWORD_ERROR_TEXT) : ConfirmPasswordError().Text(L"");
    CheckPasswords();
}

void winrt::FootballFantasy::implementation::SignUpPage::PasswordBox_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    string password = to_string(PasswordBox().Password());
    if (PasswordBox().Password().empty())
        PasswordError().Text(L"");
    else if (password.length() >= 8)
        PasswordError().Text(L"");
    else
        PasswordError().Text(PASSWORD_ERROR_TEXT);
}


void winrt::FootballFantasy::implementation::SignUpPage::ConfirmPasswordBox_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    string password = to_string(PasswordBox().Password());
    string confirmPassword = to_string(ConfirmPasswordBox().Password());
    if (ConfirmPasswordBox().Password().empty())
        ConfirmPasswordError().Text(L"");
    else if (password == confirmPassword)
        ConfirmPasswordError().Text(L"");
    else
        ConfirmPasswordError().Text(CONFIRM_PASSWORD_ERROR_TEXT);
}
