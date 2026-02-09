#include "Report.h"
#include <iostream>

// Overloaded Constructor to initialize the report with a level name
Report::Report(const std::string& level)
    : levelName(level), finalPlayerReputation(0) {}

// Add a customer report with specific details
void Report::addCustomerHappiness(const std::string& customerID, int currentHappiness, int maxHappiness, int reputationBoost, int boostCount, int reputationAttack, int attackCount) {
    customerReports.push_back({ customerID, currentHappiness, maxHappiness, reputationBoost, boostCount, reputationAttack, attackCount });
}

// Display the report on the console terminal for verification
void Report::displayReport() const {
    std::cout << "Report for Level: " << levelName << "\n";
    std::cout << "Player Final Reputation: " << finalPlayerReputation << "\n"; // Display final reputation
    std::cout << "Customer Happiness Summary:\n";
    for (const auto& report : customerReports) {
        std::cout << "Customer " << report.customerID << ":\n"
            << "  Current Happiness: " << report.currentHappiness << "\n"
            << "  Max Happiness: " << report.maxHappiness << "\n"
            << "  Reputation Boost: " << report.reputationBoost << " (Boosted " << report.boostCount << " times)\n"
            << "  Reputation Attack: " << report.reputationAttack << " (Attacked " << report.attackCount << " times)\n";
    }
    std::cout << "\n";
}

// Save the report to a file which can be retrieved in this folder
void Report::saveReportToFile() const {
    std::ofstream reportFile(levelName + "_report.txt");
    if (reportFile.is_open()) {
        reportFile << "Report for Level: " << levelName << "\n";
        reportFile << "Player Final Reputation: " << finalPlayerReputation << "\n"; // Save final reputation
        reportFile << "Customer Happiness Summary:\n";
        for (const auto& report : customerReports) {
            reportFile << "Customer " << report.customerID << ":\n"
                << "  Current Happiness: " << report.currentHappiness << "\n"
                << "  Max Happiness: " << report.maxHappiness << "\n"
                << "  Reputation Boost: " << report.reputationBoost << " (Boosted " << report.boostCount << " times)\n"
                << "  Reputation Attack: " << report.reputationAttack << " (Attacked " << report.attackCount << " times)\n";
        }
        reportFile.close();
        std::cout << "Report saved to " << levelName + "_report.txt\n";
    }
    else {
        std::cerr << "Error: Could not open file for saving report.\n";
    }
}

// Method to set the player's final reputation
void Report::setFinalPlayerReputation(int reputation) {
    finalPlayerReputation = reputation;
}

// Destructor
Report::~Report() {}