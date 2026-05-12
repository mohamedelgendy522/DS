#include<iostream>
#include<vector>
#include <queue>
using namespace std;


class EmergencyRoom {
private:
    struct Patient {
        int id;
        string name;
        int severity;
        int arrivalTime;
    };
    vector<Patient> heap;

    
    bool higherPriority(Patient a, Patient b) {

        if (a.severity > b.severity)
            return true;

        if (a.severity < b.severity)
            return false;

        return a.arrivalTime < b.arrivalTime;
    }

    void heapifyUp(int index) {

        while (index > 0) {

            int parent = (index - 1) / 2;

            if (higherPriority(heap[index], heap[parent])) {

                swap(heap[index], heap[parent]);

                index = parent;
            }
            else {
                break;
            }
        }
    }

    void heapifyDown(int index) {

        int size = heap.size();

        while (true) {

            int left = index * 2 + 1;
            int right = index * 2 + 2;

            int highest = index;

            if (left < size &&
                higherPriority(heap[left], heap[highest])) {

                highest = left;
            }

            if (right < size &&
                higherPriority(heap[right], heap[highest])) {

                highest = right;
            }

            if (highest != index) {

                swap(heap[index], heap[highest]);

                index = highest;
            }
            else {
                break;
            }
        }
    }

public:

    void insertPatient(Patient p) {

        heap.push_back(p);

        heapifyUp(heap.size() - 1);
    }

    void treatNextPatient() {            

        if (heap.empty()) {
            cout << "No patients\n";
            return;
        }

        cout << "Treating: " << heap[0].name << endl;   

        heap[0] = heap.back();                      

        heap.pop_back();

        if (!heap.empty())
            heapifyDown(0);
    }

    void updateSeverity(int id, int newSeverity) {

        for (int i = 0; i < heap.size(); i++) {

            if (heap[i].id == id) {

                int oldSeverity = heap[i].severity;

                heap[i].severity = newSeverity;

                cout << "Updated: " << heap[i].name << "'s severity from " << oldSeverity << " to " << newSeverity << "\n";

                if (newSeverity > oldSeverity)
                    heapifyUp(i);

                else
                    heapifyDown(i);

                return;
            }
        }

        cout << "Patient not found\n";
    }

    void viewNextPatient() {

        if (heap.empty()) {
            cout << "No patients\n";
            return;
        }

        cout << "Next Patient: "
            << heap[0].name
            << "  | Severity: "
            << heap[0].severity
            << endl;
    }

    void displayPatients() {

        for (Patient p : heap) {

            cout << "ID: " << p.id
                << " | Name: " << p.name
                << " | Severity: " << p.severity
                << " | Arrival: " << p.arrivalTime
                << endl;
        }
    }

};


class EmergencyRoom2 {

private:

    struct Patient {

        int id;
        string name;
        int severity;
        int arrivalTime;
    };


    class ComparePatients {

    public:

        bool operator()(Patient a, Patient b) {

            if (a.severity != b.severity)
                return a.severity < b.severity;

            return a.arrivalTime > b.arrivalTime;
        }
    };


    priority_queue< Patient,vector<Patient>,ComparePatients> pq;


public:

    void insertPatient(int id,string name,int severity,int arrivalTime){

        Patient p;

        p.id = id;
        p.name = name;
        p.severity = severity;
        p.arrivalTime = arrivalTime;

        pq.push(p);
    }


    void treatNextPatient() {

        if (pq.empty()) {

            cout << "No patients\n";
            return;
        }

        Patient p = pq.top();

        cout << "Treating: "
            << p.name
            << endl;

        pq.pop();
    }


    void updateSeverity(int id, int newSeverity) {

        vector<Patient> temp;

        bool found = false;

        while (!pq.empty()) {

            Patient p = pq.top();
            pq.pop();

            if (p.id == id) {
                cout << "Updated: " << p.name << "'s severity from " << p.severity << " to " << newSeverity << "\n";
                p.severity = newSeverity;
                found = true;
            }

            temp.push_back(p);
        }

        for (auto& p : temp)
            pq.push(p);

        if (!found)
            cout << "Patient not found\n";
    }

    void viewNextPatient() {

        if (pq.empty()) {

            cout << "No patients\n";
            return;
        }

        Patient p = pq.top();

        cout << "Next Patient: "
            << p.name
            << " | Severity: "
            << p.severity
            << endl;
    }


    void displayPatients() {

        if (pq.empty()) {

            cout << "No patients\n";
            return;
        }

        priority_queue<
            Patient,
            vector<Patient>,
            ComparePatients
        > temp = pq;

        cout << "\nPatients:\n";

        while (!temp.empty()) {

            Patient p = temp.top();

            cout << "ID: " << p.id
                << " | Name: " << p.name
                << " | Severity: " << p.severity
                << " | Arrival: " << p.arrivalTime
                << endl;

            temp.pop();
        }
    }
};




int main() {

    cout << "================ MANUAL HEAP =================\n";

    EmergencyRoom er1;

    er1.insertPatient({ 1, "Ahmed", 7, 1 });
    er1.insertPatient({ 2, "Omar", 9, 2 });
    er1.insertPatient({ 3, "Sara", 5, 3 });
    er1.insertPatient({ 4, "Ali", 6, 4 });
    er1.insertPatient({ 5, "Mona", 8, 5 });
    er1.insertPatient({ 6, "Youssef", 4, 6 });
    er1.insertPatient({ 7, "Hassan", 10, 7 });
    er1.insertPatient({ 8, "Nour", 3, 8 });
    er1.insertPatient({ 9, "Kareem", 6, 9 });
    er1.insertPatient({ 10, "Hana", 7, 10 });
    er1.insertPatient({ 11, "Mostafa", 9, 11 });
    er1.insertPatient({ 12, "Laila", 5, 12 });
    er1.insertPatient({ 13, "Tarek", 8, 13 });
    er1.insertPatient({ 14, "Salma", 6, 14 });
    er1.insertPatient({ 15, "Ziad", 7, 15 });
    er1.insertPatient({ 16, "Nada", 4, 16 });
    er1.insertPatient({ 17, "Adel", 10, 17 });
    er1.insertPatient({ 18, "Reem", 2, 18 });
    er1.insertPatient({ 19, "Farah", 6, 19 });
    er1.insertPatient({ 20, "Walid", 8, 20 });

    er1.viewNextPatient();
    er1.treatNextPatient();
    er1.updateSeverity(3, 10);
    er1.viewNextPatient();
    er1.treatNextPatient();
    cout << "\n\n";
    er1.displayPatients();


    cout << "\n================ PRIORITY_QUEUE =================\n";

    EmergencyRoom2 er2;

    er2.insertPatient(1, "Ahmed", 7, 1);
    er2.insertPatient(2, "Omar", 9, 2);
    er2.insertPatient(3, "Sara", 5, 3);
    er2.insertPatient(4, "Ali", 6, 4);
    er2.insertPatient(5, "Mona", 8, 5);
    er2.insertPatient(6, "Youssef", 4, 6);
    er2.insertPatient(7, "Hassan", 10, 7);
    er2.insertPatient(8, "Nour", 3, 8);
    er2.insertPatient(9, "Kareem", 6, 9);
    er2.insertPatient(10, "Hana", 7, 10);
    er2.insertPatient(11, "Mostafa", 9, 11);
    er2.insertPatient(12, "Laila", 5, 12);
    er2.insertPatient(13, "Tarek", 8, 13);
    er2.insertPatient(14, "Salma", 6, 14);
    er2.insertPatient(15, "Ziad", 7, 15);
    er2.insertPatient(16, "Nada", 4, 16);
    er2.insertPatient(17, "Adel", 10, 17);
    er2.insertPatient(18, "Reem", 2, 18);
    er2.insertPatient(19, "Farah", 6, 19);
    er2.insertPatient(20, "Walid", 8, 20);

    er2.viewNextPatient();
    er2.treatNextPatient();
    er2.updateSeverity(3, 10);
    er2.viewNextPatient();
    er2.treatNextPatient();
    cout << "\n\n";
    er2.displayPatients();

    return 0;
}