#include "pch.h"
#include "AdminDataPage.xaml.h"
#if __has_include("AdminDataPage.g.cpp")
#include "AdminDataPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t AdminDataPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AdminDataPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void AdminDataPage::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}
