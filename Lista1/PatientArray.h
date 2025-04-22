#ifndef PATIENTARRAY_H
#define PATIENTARRAY_H

struct Patient {
    char name[50];
    int severity;         // Número positivo. Quanto maior, mais severo.
    char arrival_time[6]; // Formato "XXhYY"
};

struct PatientArray {
    Patient *patients; // Ponteiro para o array de pacientes
    int size;          // Número atual de pacientes armazenados
    int capacity;      // Capacidade total do array
};

namespace PatientArrayTAD{
    PatientArray * initializePatientArray();

    void printPatients(PatientArray *pa);

    void fill(Patient* p, Patient *new_p, int fill_untill);
    void insertPatient(PatientArray *pa, Patient p);

    int comparePatients(Patient p1, Patient p2);
    int findNextPatient(PatientArray *pa);

    void removePatient(PatientArray *pa, int index);

    Patient popNextPatient(PatientArray *pa);
}

#endif