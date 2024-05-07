#include "pch.h"
#include "PlayerSettingsPage.xaml.h"
#if __has_include("PlayerSettingsPage.g.cpp")
#include "PlayerSettingsPage.g.cpp"
#endif

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

    // Create a StackPanel to hold the stars
    Controls::StackPanel panel;
    panel.Orientation(Controls::Orientation::Horizontal);
    panel.HorizontalAlignment(HorizontalAlignment::Center); // Center-align the stars


    // Create five Buttons representing the stars
    for (int i = 0; i < 5; ++i)
    {
        Controls::Button starButton;
        starButton.Content(winrt::box_value(L"\u2606")); // Unicode for a blank star
        starButton.Click([this, i](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
            // Handle star click event, e.g., set the rating
           // SetRating(i + 1); // Assuming SetRating is a method to handle the rating
           // dialog.Hide(); // Hide the dialog after rating
            });
        panel.Children().Append(starButton);
    }

    // Add the panel to the dialog
    dialog.Content(panel);

    // Set dialog properties
    dialog.CloseButtonText(L"Cancel"); // Optionally, add a cancel button
    dialog.ShowAsync();
}


void winrt::FootballFantasy::implementation::PlayerSettingsPage::ShareApp_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    Controls::ContentDialog dialog;
    dialog.XamlRoot(this->XamlRoot());
    Controls::Button shareButton;
    shareButton.Content(winrt::box_value(L"https://github.com/CyberKL/Football-Fantasy"));
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
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.SignUpPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}


void winrt::FootballFantasy::implementation::PlayerSettingsPage::DeleteAccount_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.DeleteAccount", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}


