#include "pch.h"
#include "ChangePassword.xaml.h"
#if __has_include("ChangePassword.g.cpp")
#include "ChangePassword.g.cpp"
#endif
#include "winrt/Microsoft.UI.Xaml.Controls.h"
#include <string>
#include "Presenter.h"
using namespace std;

using namespace winrt;
using namespace Microsoft::UI::Xaml;
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t ChangePassword::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void ChangePassword::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
     
}


void winrt::FootballFantasy::implementation::ChangePassword::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    string oldPass = Presenter::getInstance()->getLoggedInPlayerPassword();
    string inputOldPass = to_string (oldPasswordBox().Password());
    string inputNewPass = to_string(newPasswordBox().Password());
    string inputConfirmPass = to_string(confirmPasswordBox().Password());
    
    if (oldPass != inputOldPass || inputConfirmPass != inputNewPass)
    {
        MatchingPass().Text(L"They don't Match!");

        // Setting text content
        return;
    }
    MatchingPass().Text(L"");
    Presenter::getInstance()->changePassword(inputNewPass);

    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.LoginPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Presenter::getInstance()->logOut();
    Frame().Parent().as<Controls::NavigationView>().Parent().as<Controls::Page>().Frame().Navigate(page);
}
