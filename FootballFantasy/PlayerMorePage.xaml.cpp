#include "pch.h"
#include "PlayerMorePage.xaml.h"
#if __has_include("PlayerMorePage.g.cpp")
#include "PlayerMorePage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t PlayerMorePage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void PlayerMorePage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
    void winrt::FootballFantasy::implementation::PlayerMorePage::Return(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        Frame().GoBack();
    }

}
