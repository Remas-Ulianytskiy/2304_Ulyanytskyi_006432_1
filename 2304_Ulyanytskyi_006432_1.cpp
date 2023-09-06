#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

class Worker {
protected:
    string name;
    bool job_status;

public:
    Worker(string name) : name(name), job_status(false) {}

    string get_name() const { return name; }
    bool get_job_status() { return job_status; }
    void set_job_status(bool status) { job_status = status; }
};

class Department {
private:
    string department_name;
    vector<Worker*> workers;

public:
    Department(const string& department_name) : department_name(department_name) {}

    string get_department_name() { return department_name; }

    void add(Worker* worker)
    {
        workers.push_back(worker);
        worker->set_job_status(true);
    }    

    void transfer_worker(Department& other_dept, Worker* worker)
    {
        auto worker_iterator = find(workers.begin(), workers.end(), worker);

        if (worker_iterator != workers.end())
        {
            workers.erase(worker_iterator);
            other_dept.add(worker);
            cout << worker->get_name() << " was transferred to ";
            cout << other_dept.get_department_name() << endl;
        }            
    }

    void dismiss_worker(Worker* worker, string reason = "Absenteeism")
    {
        auto worker_iterator = find(workers.begin(), workers.end(), worker);

        if (worker_iterator != workers.end())
        {
            workers.erase(worker_iterator);
            worker->set_job_status(false);
            cout << worker->get_name() << " was dismissed from his post. ";
            cout << "Reason: " << reason << endl;

        }
    }

    friend ostream& operator<<(ostream& os, const Department& dept)
    {
        os << "Department Workers: ";
        for (const auto& worker : dept.workers)
            os << worker->get_name() << " ";
        os << "\n";
        return os;
    }

    ~Department()
    {
        workers.clear();
        cout << "All participants were removed from the department. ";
        cout << department_name << " is disbanded.\n\n";
    }
};

void print_workers_list_status(const vector<Worker*>& workers_list)
{
    for (const auto& worker : workers_list)
    {
        cout << worker->get_name();
        if (worker->get_job_status())
            cout << " still working";
        else
            cout << " doesn't work anymore";
        cout << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const string DEPARTMENT_DESIGNERS_NAME = "Department of designers";
    const string DEPARTMENT_DEVELOPERS_NAME = "Development department";

    Worker* w1 = new Worker("Антін");
    Worker* w2 = new Worker("Івасик");
    Worker* w3 = new Worker("Євген");
    Worker* w4 = new Worker("Їржик");

    vector<Worker*> workers_list {w1, w2, w3, w4};

    Department department_developers (DEPARTMENT_DEVELOPERS_NAME);
    department_developers.add(w4);

    {
        Department department_designers (DEPARTMENT_DESIGNERS_NAME);
        department_designers.add(w1);
        department_designers.add(w2);
        department_designers.add(w3);

        cout << DEPARTMENT_DESIGNERS_NAME << endl << department_designers << endl;
        cout << DEPARTMENT_DESIGNERS_NAME << " will disbanded soon!\n\n";

        for (auto& worker : workers_list)
            department_designers.transfer_worker(department_developers, worker);
        cout << endl;
    }

    department_developers.dismiss_worker(w2);
    cout << endl;

    print_workers_list_status(workers_list);

    cout << "\nThe company will soon stop working!\n\n";

    for (auto& worker : workers_list)
        if (worker->get_job_status())
            department_developers.dismiss_worker(worker, "the company is closing down");

    cout << endl;
    print_workers_list_status(workers_list);
    cout << endl;

    delete w1;
    delete w2;
    delete w3;
    delete w4;

    return 0;
}
