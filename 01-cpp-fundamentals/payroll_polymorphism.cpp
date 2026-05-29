#include <iostream>
#include <memory>
#include <vector>

class Employee {
public:
    explicit Employee(std::string name) : name_(std::move(name)) {}
    virtual ~Employee() = default;

    virtual double monthly_pay() const = 0;
    const std::string& name() const { return name_; }

protected:
    std::string name_;
};

class SalariedEmployee : public Employee {
public:
    SalariedEmployee(std::string name, double annual_salary)
        : Employee(std::move(name)), annual_salary_(annual_salary) {}

    double monthly_pay() const override { return annual_salary_ / 12.0; }

private:
    double annual_salary_;
};

class HourlyEmployee : public Employee {
public:
    HourlyEmployee(std::string name, double hourly_rate, double hours)
        : Employee(std::move(name)), hourly_rate_(hourly_rate), hours_(hours) {}

    double monthly_pay() const override { return hourly_rate_ * hours_; }

private:
    double hourly_rate_;
    double hours_;
};

int main() {
    std::vector<std::unique_ptr<Employee>> payroll;
    payroll.push_back(std::make_unique<SalariedEmployee>("Jean P.", 72000));
    payroll.push_back(std::make_unique<HourlyEmployee>("Claire M.", 18.5, 168));

    double total = 0;
    for (const auto& employee : payroll) {
        total += employee->monthly_pay();
        std::cout << employee->name() << ": " << employee->monthly_pay() << '\n';
    }

    std::cout << "payroll total: " << total << '\n';
    return 0;
}
