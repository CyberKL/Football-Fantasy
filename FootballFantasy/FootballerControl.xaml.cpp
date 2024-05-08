#include "pch.h"
#include "FootballerControl.xaml.h"
#if __has_include("FootballerControl.g.cpp")
#include "FootballerControl.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    //winrt::Microsoft::UI::Xaml::DependencyProperty FootballerControl::PlayerName = DependencyProperty::Register(L"PlayerName", Windows::UI::Xaml::Interop::TypeName{ L"Controls.TextBlock.TextProperty" }, Windows::UI::Xaml::Interop::TypeName{L"FootballFantasy.FootballerControl", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom}, PropertyMetadata{nullptr});
    winrt::Microsoft::UI::Xaml::DependencyProperty FootballerControl::s_PlayerNameProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"PlayerName",
            winrt::Windows::UI::Xaml::Interop::TypeName{ L"winrt.hstring" },
            winrt::Windows::UI::Xaml::Interop::TypeName{ L"FootballFantasy.FootballerControl" },
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr });
    winrt::Microsoft::UI::Xaml::DependencyProperty FootballerControl::s_PlayerInfoProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"PlayerInfo",
            winrt::Windows::UI::Xaml::Interop::TypeName{ L"winrt.hstring" },
            winrt::Windows::UI::Xaml::Interop::TypeName{ L"FootballFantasy.FootballerControl" },
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr });
    winrt::Microsoft::UI::Xaml::DependencyProperty FootballerControl::s_CaptaincyIconProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"CaptaincyIcon",
            winrt::Windows::UI::Xaml::Interop::TypeName{ L"winrt.hstring" },
            winrt::Windows::UI::Xaml::Interop::TypeName{ L"FootballFantasy.FootballerControl" },
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr });

    int32_t FootballerControl::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void FootballerControl::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}
