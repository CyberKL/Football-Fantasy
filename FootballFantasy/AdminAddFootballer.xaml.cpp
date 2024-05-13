#include "pch.h"
#include "AdminAddFootballer.xaml.h"
#if __has_include("AdminAddFootballer.g.cpp")
#include "AdminAddFootballer.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;

namespace winrt::FootballFantasy::implementation
{
    int32_t AdminAddFootballer::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AdminAddFootballer::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void AdminAddFootballer::FootballerPrice_ValueChanged(NumberBox const& sender, NumberBoxValueChangedEventArgs const& args)
    {
        int32_t newValue = static_cast<int32_t>(args.NewValue());
        if (newValue < 3000)
        {
            sender.Value(3000); // Set minimum value
        }
        else if (newValue > 15000)
        {
            sender.Value(15000); // Set maximum value
        }
        else
        {
            // Round newValue to the nearest 100
            int32_t roundedValue = ((newValue + 50) / 100) * 100;
            sender.Value(roundedValue);
        }
    }
}


void winrt::FootballFantasy::implementation::AdminAddFootballer::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.AdminPanelPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}
