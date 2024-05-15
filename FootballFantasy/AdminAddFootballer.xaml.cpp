#include "pch.h"
#include "AdminAddFootballer.xaml.h"
#if __has_include("AdminAddFootballer.g.cpp")
#include "AdminAddFootballer.g.cpp"
#endif
#include <string>
#include "Presenter.h"
using namespace std;
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
    string newFootballerName = to_string(FootballerName().Text());
    int newFootballerTeam = stoi (to_string(FootballerTeam().SelectedItem().as<Controls::ComboBoxItem>().Name()));
    string newFootballerPosition = to_string((FootballerPosition().SelectedItem().as<Controls::ComboBoxItem>().Content().as<winrt::hstring>()));
    int newFootballerPrice = FootballerPrice().Value();

    Presenter::getInstance()->addedFootballer(newFootballerName, newFootballerPrice, newFootballerPosition, newFootballerTeam);

    winrt::Windows::UI::Xaml::Interop::TypeName page = { L"FootballFantasy.AdminMatchesPage", winrt::Windows::UI::Xaml::Interop::TypeKind::Custom }; // Set Page
    Frame().Navigate(page);
}

void winrt::FootballFantasy::implementation::AdminAddFootballer::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    unordered_map<int, FootballTeam*> footballteams = Presenter::getInstance()->getFootballTeams();
    unordered_map<int, FootballTeam*> ::iterator it;
    for (it = footballteams.begin(); it != footballteams.end(); it++) {
        Controls::ComboBoxItem item;
        item.Content(winrt::box_value(to_hstring(it->second->getName())));
        item.Name(to_hstring(it->second->getId()));
        FootballerTeam().Items().Append(item);
    }
}