#include <iostream>
#include <algorithm>
#include <vector>
#include "Database.h"

using namespace std;

class SortStrategy {
    public:
        virtual void sortData(vector<int>& data) = 0;
};

class BalanceSort : public SortStrategy {
    public:
        void sortData(vector<int>& data) override {
            sort(data.begin(), data.end(), [](int a, int b) {
                FinancialCommitment balanceA, balanceB;

                for (FinancialCommitment commitment : Database::getInstance()->getFinancialCommitments()) {
                    if (commitment.getStudentID() == a) balanceA = commitment;
                    if (commitment.getStudentID() == b) balanceB = commitment;
                }

                float balanceValueA = balanceA.getTotalTuitionFee() + balanceA.getAdditionalFees() - balanceA.getPaidAmount();
                float balanceValueB = balanceB.getTotalTuitionFee() + balanceB.getAdditionalFees() - balanceB.getPaidAmount();

                // Sort by balance in ascending order
                return balanceValueA < balanceValueB;
            });
        }
};

class IDSort : public SortStrategy {
    public:
        void sortData(vector<int>& data) override {}
};

class GradesSort : public SortStrategy {
    public:
        void sortData(vector<int>& data) override {}
};

class AttendanceSort : public SortStrategy {
    public:
        void sortData(vector<int>& data) override {
            sort(data.begin(), data.end(), [](int a, int b) {
                Attendance attendanceA, attendanceB;
                for (Attendance attendance : Database::getInstance()->getAttendance()) {
                    if (attendance.getStudentID() == a) attendanceA = attendance;
                    else if (attendance.getStudentID() == b) attendanceB = attendance;
                }

                //point system
                float valueA = attendanceA.getAbsents() + (attendanceA.getLates()*0.5);
                float valueB = attendanceB.getAbsents() + (attendanceB.getLates()*0.5);
                return valueA < valueB;
            });
        }
};

class SortContext {
    private:
        SortStrategy* strategy;
    
    public:
        SortContext(SortStrategy* strategy) : strategy(strategy) {}

        void setSortStrategy(SortStrategy* strat) {strategy = strat;}

        void sortData(vector<int>& data) {
            strategy->sortData(data);
        }

};