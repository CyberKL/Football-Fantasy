#include "pch.h"
#include "ChangePassword.xaml.h"
#if __has_include("ChangePassword.g.cpp")
#include "ChangePassword.g.cpp"
#endif

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

}
