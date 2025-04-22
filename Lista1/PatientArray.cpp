#include <iostream>
#include <cstring>
#include "PatientArray.h"
using std::cin, std::cout, std::endl;


namespace PatientArrayTAD{   
    PatientArray* initializePatientArray() {
        // Create a empty PatientArray with capacity 4
        Patient* patients_list = new Patient[4];
        PatientArray* Patients_Array = new PatientArray{patients_list, 0, 4};
        return Patients_Array;
    }

    void printPatients(PatientArray *pa) {
        if (pa == nullptr || pa->patients == nullptr) { return; }
        // Show list of pacients
        Patient current_pacient;
        cout << "Capacity: " << pa->capacity << "\nCurrent size: " << pa->size << endl << endl;
        cout << "Patients:\n";
        for (int each_patient = 0; each_patient < pa->size; each_patient++) {
            Patient current_patient = pa->patients[each_patient];
            cout << current_patient.arrival_time << " | " << current_patient.severity << " | " << current_patient.name << endl;
        }
        cout << endl << endl;
    }

    void fill(Patient* p, Patient *new_p, int fill_start, int fill_end, int new_index) {
        if (p == nullptr || new_p == nullptr) { return; }
        // Fill a new patients_list from start to end limits
        for (int index = fill_start; index < fill_end; index++, new_index++) {
            new_p[new_index] = p[index];
        }
    }

    void insertPatient(PatientArray *pa, Patient p) {
        if (pa == nullptr || pa->patients == nullptr) { return; }
        // Expand if reaches 3/4 of capacity
        if (pa->size+1 >= (3*pa->capacity)/4){
            pa->capacity *= 2;
            Patient* new_patients_list = new Patient[pa->capacity];
            fill(pa->patients, new_patients_list, 0, pa->size, 0);
            delete[] pa->patients;
            pa->patients = new_patients_list;
        }
        // Insert new patient
        pa->patients[pa->size] = p;
        pa->size++;
    }

    int comparePatients(Patient p1, Patient p2) {
        // Decide whether to change patients p1 and p2 by severity and date
        int change_patient = 0;
        if (p1.severity < p2.severity) {
            change_patient = 1;
        } else if (p1.severity == p2.severity) {
            change_patient = strcmp(p1.arrival_time, p2.arrival_time);
        }

        return change_patient;
    }

    int findNextPatient(PatientArray *pa) {
        if (pa == nullptr || pa->patients == nullptr) { return -1; }
        if (pa->size == 0) { return -1; }
        // Traverse PatientArray comparing patients while retaining preferred patient
        int preferred_patient = 0;
        for (int alternative_patient = 1; alternative_patient < pa->size; alternative_patient++) {
            if (comparePatients(pa->patients[preferred_patient], pa->patients[alternative_patient])) {
                preferred_patient = alternative_patient;
            }
        }
        return preferred_patient;
    }

    void removePatient(PatientArray *pa, int index) {
        if (pa == nullptr || pa->patients == nullptr) { return; }
        if (index >= pa->size || index < 0) { return; }
        // Reduce if patients_list is bellow 1/4 capacity, keeping at least 4
        if ((pa->size-1 <= pa->capacity/4) && (pa->capacity > 4)) {
            pa->capacity /= 2;
            Patient* new_patients_list = new Patient[pa->capacity];
            fill(pa->patients, new_patients_list, 0, index, 0);
            // Free old patients_list memory and update it
            delete[] pa->patients;
            pa->patients = new_patients_list;
        }
        // Overwrites the patient of the specified index (maybe the last patient is duplicate, but his duplicate will be replaced)
        fill(pa->patients, pa->patients, index+1, pa->size, index);
        pa->size--;
    }


    Patient popNextPatient(PatientArray *pa) {
        if (pa == nullptr || pa->patients == nullptr) { return Patient{"Null", 0, "Null"}; }
        // Find next Patient
        int index_next_patient = findNextPatient(pa);
        if (index_next_patient < 0) { return Patient{"Null", 0, "Null"}; }
        Patient next_patient = pa->patients[index_next_patient];
        // Remove next Patient from patients list
        removePatient(pa, index_next_patient);

        return next_patient;
    }
}