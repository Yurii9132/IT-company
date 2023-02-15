//К проекту ITCompany добавить перегрузку сравнения, присваивания и вывода в консоль всех классов”

#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <memory>
using std::string;
using std::ostream;
using std::istream;
using std::endl;
using std::cout;
using std::cin;
using std::vector;
using std::unique_ptr;


struct DateOfBirth {
    int dd;
    int mm;
    int yy;
    DateOfBirth() {}
    DateOfBirth(int dd, int mm, int yy) : dd{ dd }, mm{ mm }, yy{ yy } {}
    friend ostream& operator << (std::ostream& out, const DateOfBirth& obj) {
        out << "Date of birth: " << obj.dd << "/" << obj.mm << "/" << obj.yy << "." << endl;
        return out;
    }
    bool operator == (const DateOfBirth& obj) {
        bool res = this->dd == obj.dd && this->mm == obj.mm && this->yy == obj.yy;
        return res;
    }
    void operator = (const DateOfBirth& obj) {
        this->dd = obj.dd;
        this->mm = obj.mm;
        this->yy = obj.yy;
    }
    bool operator < (const DateOfBirth& obj) {
        if (this->yy < obj.yy)  return true;
        else if (this->yy > obj.yy) return false;
        else {
            if (this->mm < obj.mm) return true;
            else if (this->mm > obj.mm) return false;
            else {
                if (this->dd < obj.dd) return true;
                else  return false;
            }
        }
    }
};


enum Sorting {
    NAME = 1, AGE, SALARY
};


template<typename T>
class Array {
private:
    T* arr;
public:
    int count;
    Array() :arr{ nullptr }, count{ 0 } {}
    Array(const Array<T>& obj) : arr{ nullptr }, count{ 0 } {
        if (obj.arr == this->arr || obj.arr == nullptr) return;
        this->arr = new T[obj.count];
        this->count = obj.count;
        for (int i = 0; i < obj.count; i++) {
            this->arr[i] = obj.arr[i];
        }
    }
    Array(int count) : count{ count } {
        arr = new T[count];
        for (int i = 0; i < count; i++) {
            cout << "Enter " << i + 1 << ":\t";
            cin >> arr[i];
        }
    }
    Array(std::initializer_list<T> obj) :arr{ nullptr }, count{ 0 } {
        count = obj.size();
        arr = new T[count];
        T* iter = arr;
        auto obj_iter = obj.begin();
        for (; iter < arr + count; iter++, obj_iter++) {
            *iter = *obj_iter;
        }
    }



    void operator=(const Array<T>& obj) {
        if (obj.arr == this->arr || obj.arr == nullptr) return;
        if (arr) delete[] arr;
        count = obj.count;
        arr = new T[obj.count];
        for (int i = 0; i < obj.count; i++) {
            arr[i] = obj.arr[i];
        }
    }
    ~Array() {
        if (arr != nullptr) {
            delete[] arr;
            arr = nullptr;
            count = 0;
        }
    }
    void insert(T obj) {
        T* temp = new T[count + 1];
        for (int i = 0; i < count; i++) {
            temp[i] = arr[i];
        }
        temp[count] = obj;
        delete[] arr;
        arr = temp;
        count++;
    }
    void erase(T& obj) {
        int idx = find(obj);
        if (idx != -1) {
            T* temp = new T[count - 1];
            for (int i = 0; i < idx; i++) {
                temp[i] = arr[i];
            }
            for (int i = idx; i < count - 1; i++) {
                temp[i] = arr[i + 1];
            }
            delete[] arr;
            arr = temp;
            count--;
        }
    }
    int find(T& obj) {
        int temp = -1;
        for (int i = 0; i < count; i++) {
            if (arr[i] == obj) {
                temp = i;
            }
        }
        return temp;
    }
    friend ostream& operator << (std::ostream& out, const Array<T>& arr) {
        for (int i = 0; i < arr.count; i++) {
            cout << arr.arr[i] << "\n";
        }
        cout << endl;
        return out;
    }
    bool operator==(const Array<T> obj) {
        if (obj.count != this->count) return false;
        for (int i = 0; i < this->count; i++) {
            if (!(obj.arr[i] == this->arr[i])) return false;
        }
        return true;
    }
};


class Human {
protected:
    std::string name;
    DateOfBirth dateOfBirth;
public:
    Human() {}
    Human(std::string name, DateOfBirth dateOfBirth) : name{ name }, dateOfBirth{ dateOfBirth } {}
    virtual void show() {
        cout << "Name: " << name << "\t" << "Date of birth: " << dateOfBirth << endl;
    }
    void human_func() {
        cout << "Hello from human\n";
    }

    DateOfBirth getDateOfBirth() const { return dateOfBirth; }

    friend ostream& operator<<(ostream& out, const Human& obj) {
        out << "Name: " << obj.name << "\t" << "Date of birth: " << obj.dateOfBirth << endl;
        return out;
    }
    void operator = (const Human& obj) {
        this->name = obj.name;
        this->dateOfBirth = obj.dateOfBirth;
    }
};





class Worker : public Human {
protected:
    string department;
    double salery;
    int weeklyHours;
public:
    Worker() : Human() {}
    //Worker(const Worker& obj) { cout << "Copy CTOR"; }
    Worker(string department, double salery, int weeklyHours) :
        Human("", DateOfBirth(1, 1, 1900)),
        department{ department },
        salery{ salery },
        weeklyHours{ weeklyHours }
    {}
    Worker(string name, DateOfBirth dateOfBirth, string department, double salery, int weeklyHours) :
        Human(name, dateOfBirth),
        department{ department },
        salery{ salery },
        weeklyHours{ weeklyHours }
    {}
    virtual void show() {
        Human::show();
        cout << "Department: " << department << "\tsalery: " << salery << "\tweeklyHours: " << weeklyHours << endl;
    }
    void worker_func() {
        cout << "Hello from worker\n";
    }
    friend ostream& operator << (std::ostream& out, const Worker& obj) {
        out << "Department: " << obj.department << "\tsalery: " << obj.salery << "\tweeklyHours: " << obj.weeklyHours << endl;
        return out;
    }
    bool operator == (const Worker& obj) {
        bool res = (this->name == obj.name && this->dateOfBirth == obj.dateOfBirth &&
            this->department == obj.department &&
            this->salery == obj.salery &&
            this->weeklyHours == obj.weeklyHours);
        return res;
    }
    void operator = (const Worker& obj) {
        this->name = obj.name;
        this->dateOfBirth = obj.dateOfBirth;
        this->department = obj.department;
        this->salery = obj.salery;
        this->weeklyHours = obj.weeklyHours;
    }
    double get_salery() const {
        return salery;
    }
    bool operator < (const Worker& obj) {
        return (this->salery < obj.salery ? true : false);
    }
    bool operator > (const Worker& obj) {
        return (this->salery > obj.salery ? true : false);
    }
};



class QA : virtual public Worker {
protected:
    std::vector<string> testTask;
public:
    QA() {}
    QA(string name, DateOfBirth dateOfBirth,
        string department, double salery, int weeklyHours,
        std::vector<string> testTask) :
        Worker(name, dateOfBirth, department, salery, weeklyHours)
    {
        this->testTask = testTask;

    }
    string get_firstTask() const {
        return testTask[0];
    }
    virtual void Show() {
        if (testTask.size() != 0) {
            cout << "List of tasks: " << endl;
            for (auto it = testTask.cbegin(); it != testTask.cend(); it++)
            {
                cout << *it << "\n";
            }
        }
        else {
            cout << "No tasks\n";
        }
    }
    void QA_func() {
        cout << "Hello from QA\n";
    }
    friend ostream& operator<<(ostream& out, const QA& obj) {
        out << obj.name << "\t" << obj.dateOfBirth << endl;
        out << obj.department << "\t" << obj.weeklyHours << "\t" << obj.salery << endl;
        for (auto it = obj.testTask.cbegin(); it != obj.testTask.cend(); it++)
        {
            cout << *it << "\n";
        }
        return out;
    }
    bool operator == (const QA& obj) {
        bool res = (this->name == obj.name &&
            this->dateOfBirth == obj.dateOfBirth &&
            this->department == obj.department &&
            this->salery == obj.salery &&
            this->testTask == obj.testTask);
        return res;
    }
    void operator = (const QA& obj) {
        this->name = obj.name;
        this->dateOfBirth = obj.dateOfBirth;
        this->department = obj.department;
        this->salery = obj.salery;
        this->weeklyHours = obj.weeklyHours;
        this->testTask = obj.testTask;
    }
};



class Programmer : virtual public Worker {
protected:
    std::vector<string> quantityOfProjects;
public:
    Programmer() {}
    Programmer(string name, DateOfBirth dateOfBirth,
        string department, double salery, int weeklyHours,
        std::vector<string>& projects) :
        Worker(name, dateOfBirth, department, salery, weeklyHours)
    {
        quantityOfProjects = projects;
    }
    Programmer(std::vector<string>& projects) :
        Worker("", DateOfBirth(1, 1, 1900), "", 0, 0)
    {
        quantityOfProjects = projects;
    }
    Programmer(const Programmer& prog) {
        for (auto i = prog.quantityOfProjects.begin(); i != prog.quantityOfProjects.end(); i++) {
            this->quantityOfProjects.push_back(*i);
        }
        //std::copy(prog.quantityOfProjects.begin(), prog.quantityOfProjects.end(), quantityOfProjects.begin());
        name = prog.name;
        dateOfBirth = prog.dateOfBirth;
        department = prog.department;
        salery = prog.salery;
        weeklyHours = prog.weeklyHours;
        cout << "CTOR copy\n";
    }
    Programmer(const Programmer&& prog) {
        cout << "CTOR move\n";
    }
    ~Programmer() {
        cout << name << " DTOR\n";
    }
    void interact(const QA& obj) {
        quantityOfProjects.push_back(obj.get_firstTask());
        cout << "interact &\n";
    }
    void interact(QA&& obj) {
        quantityOfProjects.push_back(obj.get_firstTask());
        cout << "interact &&\n";
    }
    virtual void show() {
        Worker::show();
        if (quantityOfProjects.size() != 0) {
            cout << "List of projects: " << endl;
            for (auto it = quantityOfProjects.cbegin(); it != quantityOfProjects.cend(); it++)
            {
                cout << *it << "\n";
            }
        }
        else {
            cout << "No projects\n";
        }
    }
    void programmer_func() {
        cout << "Hello from programmer\n";
    }

    bool operator>(const Programmer& obj) {

    }
    friend bool compare(const Programmer& obj, int sort_by) {

    }

    string get_name() const {
        return this->name;
    }

    friend ostream& operator<<(ostream& out, const Programmer& obj) {
        out << obj.name << "\t" << obj.dateOfBirth << endl;
        out << obj.department << "\t" << obj.weeklyHours << "\t" << obj.salery << endl;
        for (auto it = obj.quantityOfProjects.cbegin(); it != obj.quantityOfProjects.cend(); it++)
        {
            cout << *it << "\n";
        }
        return out;
    }
    bool operator == (const Programmer& obj) {
        bool res = (this->name == obj.name &&
            this->dateOfBirth == obj.dateOfBirth &&
            this->department == obj.department &&
            this->salery == obj.salery &&
            this->quantityOfProjects == obj.quantityOfProjects);
        return res;
    }
    void operator = (const Programmer& obj) {
        this->name = obj.name;
        this->dateOfBirth = obj.dateOfBirth;
        this->department = obj.department;
        this->salery = obj.salery;
        this->weeklyHours = obj.weeklyHours;
        this->quantityOfProjects = obj.quantityOfProjects;
    }
};








class Admin : virtual public Worker {
protected:
    vector<string> adminTestTask;
public:
    Admin() {}
    Admin(string name, DateOfBirth dateOfBirth,
        string department, double salery, int weeklyHours,
        vector<string> adminTestTask) :
        Worker(name, dateOfBirth, department, salery, weeklyHours)
    {
        this->adminTestTask = adminTestTask;
    }
    Admin(vector<string> adminTestTask) :
        Worker("", DateOfBirth(1, 1, 1900), "", 0, 0)
    {
        this->adminTestTask = adminTestTask;
    }
    virtual void show() {
        if (adminTestTask.size() != 0) {
            cout << "List of admin tasks: " << endl;
            for (auto it = adminTestTask.cbegin(); it != adminTestTask.cend(); it++)
            {
                cout << *it << "\n";
            }
        }
        else {
            cout << "No admin tasks\n";
        }
    }
    void admin_func() {
        cout << "Hello from admin\n";
    }
    friend ostream& operator<<(ostream& out, const Admin& obj) {
        out << obj.name << "\t" << obj.dateOfBirth << endl;
        out << obj.department << "\t" << obj.weeklyHours << "\t" << obj.salery << endl;
        for (auto it = obj.adminTestTask.cbegin(); it != obj.adminTestTask.cend(); it++)
        {
            cout << *it << "\n";
        }
        return out;
    }
    bool operator == (const Admin& obj) {
        bool res = (this->name == obj.name &&
            this->dateOfBirth == obj.dateOfBirth &&
            this->department == obj.department &&
            this->salery == obj.salery &&
            this->adminTestTask == obj.adminTestTask);
        return res;
    }
    void operator = (const Admin& obj) {
        this->name = obj.name;
        this->dateOfBirth = obj.dateOfBirth;
        this->department = obj.department;
        this->salery = obj.salery;
        this->weeklyHours = obj.weeklyHours;
        this->adminTestTask = obj.adminTestTask;
    }
};


class Manager : virtual public Worker {
protected:
    vector<string> appointments;
public:
    Manager() {}
    Manager(string name, DateOfBirth dateOfBirth,
        string department, double salery, int weeklyHours,
        vector<string> appointments) :
        Worker(name, dateOfBirth, department, salery, weeklyHours)
    {
        this->appointments = appointments;
    }
    virtual void Show() {
        if (appointments.size() != 0) {
            cout << "List of appointments: " << endl;
            for (auto it = appointments.cbegin(); it != appointments.cend(); it++)
            {
                cout << *it << "\n";
            }
        }
        else {
            cout << "No appointments\n";
        }
    }
    void manager_func() {
        cout << "Hello from manager\n";
    }
    friend ostream& operator<<(ostream& out, const Manager& obj) {
        out << obj.name << "\t" << obj.dateOfBirth << endl;
        out << obj.department << "\t" << obj.weeklyHours << "\t" << obj.salery << endl;
        for (auto it = obj.appointments.cbegin(); it != obj.appointments.cend(); it++)
        {
            cout << *it << "\n";
        }
        return out;
    }
    bool operator == (const Manager& obj) {
        bool res = (this->name == obj.name &&
            this->dateOfBirth == obj.dateOfBirth &&
            this->department == obj.department &&
            this->salery == obj.weeklyHours &&
            this->weeklyHours == obj.salery &&
            this->appointments == obj.appointments);
        return res;
    }
    void operator = (const Manager& obj) {
        this->name = obj.name;
        this->dateOfBirth = obj.dateOfBirth;
        this->department = obj.department;
        this->salery = obj.salery;
        this->weeklyHours = obj.weeklyHours;
        this->appointments = obj.appointments;
    }
};




class ProgrammerAdmin : public Programmer, public Admin {
public:
    ProgrammerAdmin() {}
    ProgrammerAdmin(string name, DateOfBirth dateOfBirth,
        string department, double salery, int weeklyHours,
        std::vector<string> quantityOfProjects,
        vector<string> adminTestTask) :
        Worker(name, dateOfBirth, department, salery, weeklyHours),
        Programmer(quantityOfProjects),
        Admin(adminTestTask)
    {}


    virtual void show() {
        Programmer::show();
        Admin::show();
    }
    void ProgrammerAdmin_func() {
        cout << "Hello from ProgrammerAdmin\n";
    }
    friend ostream& operator<<(ostream& out, const ProgrammerAdmin& obj) {
        out << obj.name << "\t" << obj.dateOfBirth << endl;
        out << obj.department << "\t" << obj.weeklyHours << "\t" << obj.salery << endl;
        for (auto it = obj.quantityOfProjects.cbegin(); it != obj.quantityOfProjects.cend(); it++)
        {
            cout << *it << "\n";
        }
        for (auto it = obj.adminTestTask.cbegin(); it != obj.adminTestTask.cend(); it++)
        {
            cout << *it << "\n";
        }
        return out;
    }
    bool operator == (const ProgrammerAdmin& obj) {
        bool res = (this->name == obj.name &&
            this->dateOfBirth == obj.dateOfBirth &&
            this->department == obj.department &&
            this->salery == obj.salery &&
            this->quantityOfProjects == obj.quantityOfProjects &&
            this->adminTestTask == this->adminTestTask);
        return res;
    }
    void operator = (const ProgrammerAdmin& obj) {
        this->name = obj.name;
        this->dateOfBirth = obj.dateOfBirth;
        this->department = obj.department;
        this->salery = obj.salery;
        this->weeklyHours = obj.weeklyHours;
        this->quantityOfProjects = obj.quantityOfProjects;
        this->adminTestTask = obj.adminTestTask;
    }
};




enum IT { prog, admin, qa, manag, prog_admin };
class IT_company {
    vector<Programmer> programmers;
    vector<Admin> admins;
    vector<QA> QAs;
    vector<Manager> managers;
    vector<ProgrammerAdmin> programmer_admins;
public:
    void add_worker(Worker* obj) {
        Programmer* prog = dynamic_cast<Programmer*>(obj);
        if (prog) {
            programmers.push_back(*prog);
        }

        Admin* admin = dynamic_cast<Admin*>(obj);
        if (admin) {
            admins.push_back(*admin);
        }

        QA* qa = dynamic_cast<QA*>(obj);
        if (qa) {
            QAs.push_back(*qa);
        }

        Manager* mng = dynamic_cast<Manager*>(obj);
        if (mng) {
            managers.push_back(*mng);
        }

        ProgrammerAdmin* prog_admin = dynamic_cast<ProgrammerAdmin*>(obj);
        if (prog_admin) {
            programmer_admins.push_back(*prog_admin);
        }
    }
    void show_info() {
        if (!programmers.empty()) {
            cout << "List of programmers: " << endl;
            std::ostream_iterator<Programmer> out(cout, "-----------------------------------\n");
            copy(programmers.begin(), programmers.end(), out);
        }
        if (!admins.empty()) {
            cout << "List of admins: " << endl;
            std::ostream_iterator<Admin> out(cout, "-----------------------------------\n");
            copy(admins.begin(), admins.end(), out);
        }
        if (!QAs.empty()) {
            cout << "List of QAs: " << endl;
            std::ostream_iterator<QA> out(cout, "-----------------------------------\n");
            copy(QAs.begin(), QAs.end(), out);
        }
        if (!managers.empty()) {
            cout << "List of managers: " << endl;
            std::ostream_iterator<Manager> out(cout, "-----------------------------------\n");
            copy(managers.begin(), managers.end(), out);
        }
        if (!programmer_admins.empty()) {
            cout << "List of programmer_admins: " << endl;
            std::ostream_iterator<ProgrammerAdmin> out(cout, "-----------------------------------\n");
            copy(programmer_admins.begin(), programmer_admins.end(), out);
        }
    }

    std::pair<string, double> find_prog_salery(double salery) {
        auto res = std::find_if(programmers.begin(), programmers.end(),

            [salery](const Programmer& prog) {
                return (prog.get_salery() == salery);
            });

        if (res != programmers.end()) {
            return std::pair<string, double>(res->get_name(), res->get_salery());
        }
        else {
            return std::pair<string, double>("No found", 0);
        }
    }

    vector< std::pair<string, double>> find_progs_salery(double salery) {

        vector< std::pair<string, double>> vec;

        //auto res = std::find_if(programmers.begin(), programmers.end(),

        for (auto i = programmers.begin(); i != programmers.end(); i++) {
            
            if (i->get_salery() == salery) {
                vec.push_back(std::pair<string, double>(i->get_name(), i->get_salery()));
            }
        }

        return vec;
    }

    double getTotalSaleries() {
        double count = 0;
        for (auto progy : programmers) count += progy.get_salery();
        for (auto admy : admins) count += admy.get_salery();
        for (auto QAch : QAs) count += QAch.get_salery();
        for (auto managy : managers) count += managy.get_salery();
        for (auto progy_adm : programmer_admins) count += progy_adm.get_salery();
        return count;
    }

    void sortListWorkers() {
        vector<Worker> all;
        for (auto progy : programmers) all.push_back(progy);
        for (auto admy : admins) all.push_back(admy);
        for (auto QAch : QAs) all.push_back(QAch);
        for (auto managy : managers) all.push_back(managy);
        for (auto progy_adm : programmer_admins) all.push_back(progy_adm);

        //std::sort(all.begin(),all.end());
        std::sort(all.begin(), all.end(),
            [](Worker& obj, Worker& objNext) {
                if (obj.getDateOfBirth() < objNext.getDateOfBirth()) return true;
            });

        std::for_each(all.begin(), all.end(),
            [](Worker& obj) { obj.show(); });
    }
};




int main() {
    vector<string> arr0({ "test1","test2","test3" });
    vector<string> arr1({ "t1","t2","t3","t4" });
    vector<string> arr2({ "1test","2test" });


    Programmer prog0("Yurii", DateOfBirth(1, 1, 1990), "Training and development", 1400, 40, arr0);
    Programmer prog1("Sergei", DateOfBirth(1, 1, 1991), "Health care", 1000, 40, arr1);
    Programmer prog2("Ivan", DateOfBirth(1, 1, 1992), "Promotion", 1400, 40, arr2);

    Admin admin1("Yurii", DateOfBirth(12, 12, 1990), "Training and development", 444, 55, arr2);
    QA qa1("Sergei", DateOfBirth(2, 2, 1991), "Health care", 1400, 40, arr0);

    cout << qa1.get_firstTask() << endl;

    /*IT_company comp;

    comp.add_worker(&prog0);
    comp.add_worker(&prog1);
    comp.add_worker(&prog2);
    comp.add_worker(&admin1);
    comp.add_worker(&qa1);*/

    Programmer prog3(Programmer("Yurii", DateOfBirth(1, 1, 1990), "Training and development", 1400, 40, arr1));
    prog3.interact(qa1);
    prog3.interact(QA("Sergei", DateOfBirth(2, 2, 1991), "Health care", 1400, 40, arr0));
    prog3.show();

    vector<unique_ptr<Programmer>> ptr_progs;

    ptr_progs.push_back(unique_ptr<Programmer>(new Programmer("Peter", DateOfBirth(1, 1, 1990), "Training and development", 1400, 40, arr0)));
    ptr_progs.push_back(unique_ptr<Programmer>(new Programmer("John", DateOfBirth(1, 1, 1991), "Health care", 1000, 40, arr1)));
    ptr_progs.push_back(unique_ptr<Programmer>(new Programmer("Alex", DateOfBirth(1, 1, 1992), "Promotion", 1400, 40, arr2)));




    /*comp.show_info();



    //cout << "Total company costs: " << comp.getTotalSaleries() << endl;

    auto vec = comp.find_progs_salery(1400);

    std::ostream_iterator<std::pair<string, double>> out(cout, "-------------------------\n");

    if (!vec.empty()) {

        for (auto i = vec.begin(); i != vec.end(); i++) {
            cout << i->first << " | " << i->second << endl;
        }

    }
    cout << endl;
    //vector<Worker>* allWorkers = comp.listWorkers();
    //for (auto workers : *comp.listWorkers()) cout << workers << endl;


    comp.sortListWorkers();

    /*vector<Programmer> progs;
    progs.push_back(prog1);
    progs.push_back(prog0);
    progs.push_back(prog2);
    //К проекту ITCompany добавить перегрузку сравнения, присваивания и вывода в консоль всех классов”
    for (auto it = progs.cbegin(); it != progs.cend(); it++)
    {
        cout << *it << "\n";
        
    }*/

    /*Manager obj0("Yurii", DateOfBirth(1, 1, 1990), "operator", 1400, 40, arr0);
   Manager obj1("Sergei", DateOfBirth(1, 1, 1991), "operator", 1400, 40, arr1);
   Manager obj2("Ivan", DateOfBirth(1, 1, 1992), "operator", 1400, 40, arr2);*/

   /*Admin obj0("Yurii", DateOfBirth(1, 1, 1990), "operator", 1400, 40, arr0);
   Admin obj1("Sergei", DateOfBirth(1, 1, 1991), "operator", 1400, 40, arr1);
   Admin obj2("Ivan", DateOfBirth(1, 1, 1992), "operator", 1400, 40, arr2);*/

   /*QA obj0("Yurii", DateOfBirth(1, 1, 1990), "operator", 1400, 40, arr0);
   QA obj1("Sergei", DateOfBirth(1, 1, 1991), "operator", 1400, 40, arr1);
   QA obj2("Ivan", DateOfBirth(1, 1, 1992), "operator", 1400, 40, arr2);

   ProgrammerAdmin obj0("Yurii", DateOfBirth(1, 1, 1993), "operator", 1900, 40, arr0, arr1);
   ProgrammerAdmin obj1("Sergei", DateOfBirth(1, 1, 1995), "operator", 2000, 40, arr1, arr2);
   ProgrammerAdmin obj2("Ivan", DateOfBirth(1, 1, 2007), "operator", 1000, 40, arr2, arr0);
   */
}