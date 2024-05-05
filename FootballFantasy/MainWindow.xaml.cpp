#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::Navigate(hstring pageName)
    {
        winrt::Windows::UI::Xaml::Interop::TypeName page = { pageName, winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
        FrameContainer().Navigate(page);
    }
}

void winrt::FootballFantasy::implementation::MainWindow::Window_Activated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowActivatedEventArgs const& args)
{
    Navigate(L"FootballFantasy.SignUpPage"); // SignUpPage
}