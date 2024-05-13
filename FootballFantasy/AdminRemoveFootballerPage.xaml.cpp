#include "pch.h"
#include "AdminRemoveFootballerPage.xaml.h"
#if __has_include("AdminRemoveFootballerPage.g.cpp")
#include "AdminRemoveFootballerPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t AdminRemoveFootballerPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AdminRemoveFootballerPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void AdminRemoveFootballerPage::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}
