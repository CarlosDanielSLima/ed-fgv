#include <iostream>
#include <cstring>
#include "PatientArray.h"

using std::cin, std::cout, std::endl;
using namespace PatientArrayTAD;


int main() {
    // Initialize test
    PatientArray* pa = initializePatientArray();

    // Insert test
    insertPatient(pa, Patient{"Test_insert_remove", 23, "23h54"});

    cout << "#################### Print test ####################" << endl;
    printPatients(pa);
    
    cout << "#################### Remove test ####################" << endl;
    removePatient(pa, 0);
    removePatient(pa, 0); // Remove invalid
    printPatients(pa);
    cout << endl << endl;
    
    cout << "#################### 1/4 and 3/4 threshoulds test (at least 4) ####################" << endl;
    insertPatient(pa, Patient{"Carlos", 23, "23h55"});
    insertPatient(pa, Patient{"Daniel", 05, "23h54"});
    printPatients(pa);
    insertPatient(pa, Patient{"de Souza", 20, "23h53"});
    printPatients(pa);
    removePatient(pa, 1);
    removePatient(pa, 1);
    printPatients(pa);
    cout << endl << endl;

    cout << "#################### Find test ####################" << endl;
    insertPatient(pa, Patient{"Lima", 23, "23h52"});
    printPatients(pa);
    int preferred_patient = findNextPatient(pa);
    if (preferred_patient >= 0) {  // Only valids patients
        cout << "Name: " << pa->patients[preferred_patient].name << "\nSeverity: " << pa->patients[preferred_patient].severity << " \nTime: " << pa->patients[preferred_patient].arrival_time << endl;
    }
    cout << endl << endl;

    cout << "#################### Pop test ####################" << endl;
    printPatients(pa);
    Patient p = popNextPatient(pa);
    printPatients(pa);
    cout << "Next patient: " << p.name << "\nSeverity: " << p.severity << "\nTime: " << p.arrival_time << endl << endl;
    removePatient(pa, 0);
    printPatients(pa);
    p = popNextPatient(pa); // Pop a empty PatientArray
    cout << "Next patient: " << p.name << "\nSeverity: " << p.severity << "\nTime: " << p.arrival_time << endl << endl;
    return 0;
}