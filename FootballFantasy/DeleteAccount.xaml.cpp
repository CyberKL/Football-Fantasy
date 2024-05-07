#include "pch.h"
#include "DeleteAccount.xaml.h"
#if __has_include("DeleteAccount.g.cpp")
#include "DeleteAccount.g.cpp"
#endif
#include <string>
#include "Presenter.h"
using namespace std;
using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t DeleteAccount::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void DeleteAccount::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
    void winrt::FootballFantasy::implementation::DeleteAccount::Return(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        Frame().GoBack();
    }

   
}


void winrt::FootballFantasy::implementation::DeleteAccount::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    int ID = Presenter::getInstance()->getLoggedInPlayerID();
    string Pass = Presenter::getInstance()->getLoggedInPlayerPassword();
    string Username = Presenter::getInstance()->getLoggedInPlayerUsername();
    string inputPass = to_string(PasswordBox().Password());
    string inputUsername = to_string(UsernameBox().Text());

    if (Pass != inputPass || Username != inputUsername)
    {
        Matching().Text(L"They don't Match!");

        // Setting text content
        return;
    }
    Matching().Text(L"");
    Presenter::getInstance()->deleteAccount(ID);
}
