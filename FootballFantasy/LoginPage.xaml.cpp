#include "pch.h"
#include "LoginPage.xaml.h"
#if __has_include("LoginPage.g.cpp")
#include "LoginPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t LoginPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void LoginPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}


void winrt::FootballFantasy::implementation::LoginPage::Hyperlink_Click(winrt::Microsoft::UI::Xaml::Documents::Hyperlink const& sender, winrt::Microsoft::UI::Xaml::Documents::HyperlinkClickEventArgs const& args)
{
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.SignUpPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}


void winrt::FootballFantasy::implementation::LoginPage::LoginBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    string username = to_string(UsernameBox().Text());
    string password = to_string(PasswordBox().Password());
    if (Presenter::getInstance()->login(username, password))
    {
        // Handle successful login
        LoginError().Text(L"");
        winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.PlayerPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
        Frame().Navigate(page);
    }
    else
    {
        // Handle unsuccessful login
        LoginError().Text(L"Invalid username or password please try again");
    }
}
