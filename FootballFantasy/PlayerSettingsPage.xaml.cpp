#include "pch.h"
#include "PlayerSettingsPage.xaml.h"
#if __has_include("PlayerSettingsPage.g.cpp")
#include "PlayerSettingsPage.g.cpp"
#endif
#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.h>
#include "Presenter.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FootballFantasy::implementation
{
    int32_t PlayerSettingsPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void PlayerSettingsPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}



void winrt::FootballFantasy::implementation::PlayerSettingsPage::Terms_Conditions_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.TermsConditionsPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}


void winrt::FootballFantasy::implementation::PlayerSettingsPage::RateApp_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    // Create a ContentDialog
    Controls::ContentDialog dialog;
    dialog.XamlRoot(this->XamlRoot());

    Controls::RatingControl rating;

    // Add the panel to the dialog
    dialog.Content(rating);

    // Set dialog properties
    dialog.PrimaryButtonText(L"Submit");
    dialog.PrimaryButtonClick([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& e)
        {
            Presenter::getInstance()->updateRate(rating.Value());
        });
    dialog.CloseButtonText(L"Cancel"); // Optionally, add a cancel button
    dialog.ShowAsync();
}


void winrt::FootballFantasy::implementation::PlayerSettingsPage::ShareApp_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    Controls::ContentDialog dialog;
    dialog.XamlRoot(this->XamlRoot());

    Controls::StackPanel s;
    s.Orientation(Controls::Orientation::Horizontal);
    Controls::TextBox link;
    link.Text(to_hstring(L"https://github.com/CyberKL/Football-Fantasy"));
    link.IsReadOnly(true);
    s.Children().Append(link);
    Controls::Button copyBtn;
    copyBtn.Background(Media::SolidColorBrush(Windows::UI::Colors::White()));
    copyBtn.RequestedTheme(ElementTheme::Light);
    Controls::FontIcon f;
    f.Glyph(L"\uE8C8");
    f.Foreground(Media::SolidColorBrush(Windows::UI::Colors::Black()));
    copyBtn.Content(f);
    copyBtn.Click([=](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
        {
            Windows::ApplicationModel::DataTransfer::DataPackage dataPackage;
            dataPackage.SetText(link.Text());

            Windows::ApplicationModel::DataTransfer::Clipboard::SetContent(dataPackage);
            f.Glyph(L"\uE73E");
        });
    s.Children().Append(copyBtn);
    s.Spacing(10);

    dialog.Content(s);
    dialog.CloseButtonText(L"Done");
    dialog.ShowAsync();
}


void winrt::FootballFantasy::implementation::PlayerSettingsPage::ChangePassword_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.ChangePassword", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}


void winrt::FootballFantasy::implementation::PlayerSettingsPage::Logout_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    Presenter::getInstance()->logOut();
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.SignUpPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Parent().as<Controls::NavigationView>().Parent().as<Controls::Page>().Frame().Navigate(page);
}


void winrt::FootballFantasy::implementation::PlayerSettingsPage::DeleteAccount_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.DeleteAccount", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}


