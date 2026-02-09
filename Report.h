#ifndef REPORT_H
#define REPORT_H
#include <string>
#include <vector>
#include <fstream>
#include "CustomerEntity.h"

class Report {
private:
    // Struct to hold the individual report data for each customer
    struct CustomerReport {
        std::string customerID;
        int currentHappiness;
        int maxHappiness;
        int reputationBoost;
        int boostCount;
        int reputationAttack;
        int attackCount;
    };

    std::vector<CustomerReport> customerReports; // Vector to hold all customer reports
    std::string levelName; // The name of the level for which the report is generated
    int finalPlayerReputation; // The player's final reputation at the end of the level

public:
    // Overloaded Constructor to initialize the report with a level name
    Report(const std::string& level);

    // Add a customer report with specific details
    void addCustomerHappiness(const std::string& customerID, int currentHappiness, int maxHappiness, int reputationBoost, int boostCount, int reputationAttack, int attackCount);

    // Display the report on the console terminal for verification
    void displayReport() const;

    // Save the report to a file which can be retrieved in this folder
    void saveReportToFile() const;

    // Method to set the player's final reputation
    void setFinalPlayerReputation(int reputation);

    // Destructor
    ~Report();
};
#endif