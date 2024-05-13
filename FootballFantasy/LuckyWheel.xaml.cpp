#include "pch.h"
#include "LuckyWheel.xaml.h"
#if __has_include("LuckyWheel.g.cpp")
#include "LuckyWheel.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t LuckyWheel::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void LuckyWheel::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

  
}


void winrt::FootballFantasy::implementation::LuckyWheel::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{

}
