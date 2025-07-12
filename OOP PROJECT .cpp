#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

double dearnessAllowanceRate = 0.0;
double hraRate = 0.0;
double professionalTax = 0.0;
double medicalAllowanceRate = 0.0;

class Employee {
protected:
    string name;
    string address;
    string designation;
    string department;
    double basicSalary;
    double incomeTax;
    string employeeType;
    string joiningDate;
    string employeeID;
    string bankAccount;
    string panNumber;

public:
    Employee(string type) : employeeType(type) {}

    virtual void inputDetails() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter employee ID: ";
        getline(cin, employeeID);
        cout << "Enter employee name: ";
        getline(cin, name);
        cout << "Enter address: ";
        getline(cin, address);
        cout << "Enter designation: ";
        getline(cin, designation);
        cout << "Enter department: ";
        getline(cin, department);
        cout << "Enter joining date (DD/MM/YYYY): ";
        getline(cin, joiningDate);
        cout << "Enter bank account number: ";
        getline(cin, bankAccount);
        cout << "Enter PAN number: ";
        getline(cin, panNumber);
        cout << "Enter basic salary: ";
        cin >> basicSalary;
        cout << "Enter income tax to be deducted: ";
        cin >> incomeTax;
    }

    virtual void displayDetails() const {
        cout << "\n========== EMPLOYEE DETAILS ==========" << endl;
        cout << left << setw(20) << "Employee Type:" << employeeType << endl;
        cout << setw(20) << "Employee ID:" << employeeID << endl;
        cout << setw(20) << "Name:" << name << endl;
        cout << setw(20) << "Address:" << address << endl;
        cout << setw(20) << "Designation:" << designation << endl;
        cout << setw(20) << "Department:" << department << endl;
        cout << setw(20) << "Joining Date:" << joiningDate << endl;
        cout << setw(20) << "Bank Account:" << bankAccount << endl;
        cout << setw(20) << "PAN Number:" << panNumber << endl;
        cout << setw(20) << "Basic Salary:" << fixed << setprecision(2) << basicSalary << endl;
        cout << setw(20) << "Income Tax:" << incomeTax << endl;


        double da = basicSalary * dearnessAllowanceRate / 100;
        double hra = basicSalary * hraRate / 100;
        double ma = basicSalary * medicalAllowanceRate / 100;
        double grossSalary = basicSalary + da + hra + ma;
        double deductions = incomeTax + professionalTax;
        double netSalary = grossSalary - deductions;

        cout << "\n========== SALARY DETAILS ==========" << endl;
        cout << setw(30) << "Dearness Allowance (" + to_string(dearnessAllowanceRate) + "%):" << da << endl;
        cout << setw(30) << "HRA (" + to_string(hraRate) + "%):" << hra << endl;
        cout << setw(30) << "Medical Allowance (" + to_string(medicalAllowanceRate) + "%):" << ma << endl;
        cout << setw(30) << "Professional Tax:" << professionalTax << endl;
        cout << setw(30) << "Gross Salary:" << grossSalary << endl;
        cout << setw(30) << "Total Deductions:" << deductions << endl;
        cout << setw(30) << "Net Salary:" << netSalary << endl;
        cout << "===================================" << endl;
    }

    virtual void generatePaySlip() const {
        double da = basicSalary * dearnessAllowanceRate / 100;
        double hra = basicSalary * hraRate / 100;
        double ma = basicSalary * medicalAllowanceRate / 100;
        double grossSalary = basicSalary + da + hra + ma;
        double deductions = incomeTax + professionalTax;
        double netSalary = grossSalary - deductions;

        cout << "\n========== PAY SLIP ==========" << endl;
        cout << "Employee Name: " << name << endl;
        cout << "Employee ID: " << employeeID << endl;
        cout << "Designation: " << designation << endl;
        cout << "Department: " << department << endl;
        cout << "Joining Date: " << joiningDate << endl;
        cout << "--------------------------------" << endl;
        cout << left << setw(30) << "Basic Salary:" << right << setw(10) << fixed << setprecision(2) << basicSalary << endl;
        cout << left << setw(30) << "Dearness Allowance (" + to_string(dearnessAllowanceRate) + "%):" << right << setw(10) << da << endl;
        cout << left << setw(30) << "HRA (" + to_string(hraRate) + "%):" << right << setw(10) << hra << endl;
        cout << left << setw(30) << "Medical Allowance (" + to_string(medicalAllowanceRate) + "%):" << right << setw(10) << ma << endl;
        cout << "--------------------------------" << endl;
        cout << left << setw(30) << "Gross Salary:" << right << setw(10) << grossSalary << endl;
        cout << "Deductions:" << endl;
        cout << left << setw(30) << "  Income Tax:" << right << setw(10) << incomeTax << endl;
        cout << left << setw(30) << "  Professional Tax:" << right << setw(10) << professionalTax << endl;
        cout << "--------------------------------" << endl;
        cout << left << setw(30) << "Net Salary:" << right << setw(10) << netSalary << endl;
        cout << "==============================" << endl;
        cout << "Bank Account: " << bankAccount << endl;
        cout << "PAN Number: " << panNumber << endl;
    }

    virtual double computeOvertime(int hours) const = 0;

    string getName() const { return name; }
    string getType() const { return employeeType; }
    string getEmployeeID() const { return employeeID; }
};

class PermanentEmployee : public Employee {
private:
    double overtimeRate;
    int leaveBalance;

public:
    PermanentEmployee() : Employee("Permanent") {
        overtimeRate = 1.5;
        leaveBalance = 30;
    }

    void inputDetails() override {
        Employee::inputDetails();
        cout << "Enter leave balance: ";
        cin >> leaveBalance;
    }

    void displayDetails() const override {
        Employee::displayDetails();
        cout << left << setw(20) << "Overtime Rate:" << overtimeRate << "x" << endl;
        cout << left << setw(20) << "Leave Balance:" << leaveBalance << " days" << endl;
        cout << "===================================" << endl;
    }

    double computeOvertime(int hours) const override {
        return hours * (basicSalary / 160) * overtimeRate;
    }
};

class ContractualEmployee : public Employee {
private:
    double overtimeRate;
    string contractEndDate;

public:
    ContractualEmployee() : Employee("Contractual") {
        overtimeRate = 1.2;
    }

    void inputDetails() override {
        Employee::inputDetails();
        cin.ignore();
        cout << "Enter contract end date (DD/MM/YYYY): ";
        getline(cin, contractEndDate);
    }

    void displayDetails() const override {
        Employee::displayDetails();
        cout << left << setw(20) << "Overtime Rate:" << overtimeRate << "x" << endl;
        cout << left << setw(20) << "Contract End Date:" << contractEndDate << endl;
        cout << "===================================" << endl;
    }

    double computeOvertime(int hours) const override {
        return hours * (basicSalary / 160) * overtimeRate;
    }
};

vector<Employee*> employees;

void addNewEmployee() {
    int choice;
    cout << "\n1. Permanent Employee\n2. Contractual Employee\nEnter choice: ";
    cin >> choice;

    Employee* emp = nullptr;
    if (choice == 1) {
        emp = new PermanentEmployee();
    } else if (choice == 2) {
        emp = new ContractualEmployee();
    } else {
        cout << "Invalid choice!" << endl;
        return;
    }

    emp->inputDetails();
    employees.push_back(emp);
    cout << "Employee added successfully!" << endl;
}

void generatePaySlip() {
    if (employees.empty()) {
        cout << "No employees available!" << endl;
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string name;
    cout << "Enter employee name or ID: ";
    getline(cin, name);

    bool found = false;
    for (const auto& emp : employees) {
        if (emp->getName() == name || emp->getEmployeeID() == name) {
            emp->generatePaySlip();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Employee not found!" << endl;
    }
}

void setDearnessAllowanceRate() {
    cout << "Current Dearness Allowance Rate: " << dearnessAllowanceRate << "%" << endl;
    cout << "Enter new rate: ";
    cin >> dearnessAllowanceRate;
    cout << "Dearness Allowance rate updated successfully!" << endl;
}

void setHRARate() {
    cout << "Current HRA Rate: " << hraRate << "%" << endl;
    cout << "Enter new rate: ";
    cin >> hraRate;
    cout << "HRA rate updated successfully!" << endl;
}

void setProfessionalTax() {
    cout << "Current Professional Tax: " << professionalTax << endl;
    cout << "Enter new amount: ";
    cin >> professionalTax;
    cout << "Professional tax updated successfully!" << endl;
}

void setMedicalAllowanceRate() {
    cout << "Current Medical Allowance Rate: " << medicalAllowanceRate << "%" << endl;
    cout << "Enter new rate: ";
    cin >> medicalAllowanceRate;
    cout << "Medical Allowance rate updated successfully!" << endl;
}

void displayEmployeeDetails() {
    if (employees.empty()) {
        cout << "No employees available!" << endl;
        return;
    }

    int choice;
    cout << "\n1. Display all employees\n2. Search by name or ID\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        cout << "\n========== ALL EMPLOYEES ==========" << endl;
        for (const auto& emp : employees) {
            emp->displayDetails();
        }
    } else if (choice == 2) {
        string searchTerm;
        cout << "Enter employee name or ID to search: ";
        getline(cin, searchTerm);

        bool found = false;
        for (const auto& emp : employees) {
            if (emp->getName() == searchTerm || emp->getEmployeeID() == searchTerm) {
                emp->displayDetails();
                found = true;
            }
        }

        if (!found) {
            cout << "No employee found with that name or ID." << endl;
        }
    } else {
        cout << "Invalid choice!" << endl;
    }
}

void computeOvertimeDues() {
    if (employees.empty()) {
        cout << "No employees available!" << endl;
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string name;
    cout << "Enter employee name or ID: ";
    getline(cin, name);

    int hours;
    cout << "Enter overtime hours: ";
    cin >> hours;

    bool found = false;
    for (const auto& emp : employees) {
        if (emp->getName() == name || emp->getEmployeeID() == name) {
            double overtime = emp->computeOvertime(hours);
            cout << "\nOvertime Dues for " << emp->getName() << " (" << emp->getType() << "): "
                 << fixed << setprecision(2) << overtime << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Employee not found!" << endl;
    }
}

void mainMenu() {
    while (true) {
        cout << "\n========== PAYROLL SYSTEM ==========" << endl;
        cout << "1. New Employee" << endl;
        cout << "2. Generate Pay Slip" << endl;
        cout << "3. Set Dearness Allowance Rate" << endl;
        cout << "4. Set HRA Rate" << endl;
        cout << "5. Set Professional Tax" << endl;
        cout << "6. Set Medical Allowance Rate" << endl;
        cout << "7. Display Employee Details" << endl;
        cout << "8. Compute Overtime Dues" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addNewEmployee();
                break;
            case 2:
                generatePaySlip();
                break;
            case 3:
                setDearnessAllowanceRate();
                break;
            case 4:
                setHRARate();
                break;
            case 5:
                setProfessionalTax();
                break;
            case 6:
                setMedicalAllowanceRate();
                break;
            case 7:
                displayEmployeeDetails();
                break;
            case 8:
                computeOvertimeDues();
                break;
            case 9:

                for (auto& emp : employees) {
                    delete emp;
                }
                employees.clear();
                cout << "Exiting program..." << endl;
                return;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
}

int main() {

    dearnessAllowanceRate = 12.0;
    hraRate = 20.0;
    professionalTax = 200.0;
    medicalAllowanceRate = 5.0;

    mainMenu();
    return 0;
}
