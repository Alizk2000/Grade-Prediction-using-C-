#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

// --- 1. CORE BLUEPRINTS ---
struct Student {
    int id;
    double studyHours;
    double attendance;
    double previousScore;
    string grade;
};

struct Neighbor {
    double distance;
    string grade;
};

struct Vote {
    string grade;
    int count;
};

// --- 2. CUSTOM DATA STRUCTURES (No Templates Allowed) ---

// Dynamic Array specifically for Students
class StudentArray {
private:
    Student* arr;
    int capacity;
    int currentSize;
public:
    StudentArray() {
        capacity = 2;
        currentSize = 0;
        arr = new Student[capacity];
    }
    ~StudentArray() { delete[] arr; }

    void push_back(Student data) {
        if (currentSize == capacity) {
            capacity *= 2;
            Student* temp = new Student[capacity];
            for (int i = 0; i < currentSize; i++) temp[i] = arr[i];
            delete[] arr;
            arr = temp;
        }
        arr[currentSize++] = data;
    }
    Student& get(int index) const { return arr[index]; }
    int size() const { return currentSize; }
};

// Dynamic Array specifically for Neighbors (includes a custom swap method for sorting)
class NeighborArray {
private:
    Neighbor* arr;
    int capacity;
    int currentSize;
public:
    NeighborArray() {
        capacity = 2;
        currentSize = 0;
        arr = new Neighbor[capacity];
    }
    ~NeighborArray() { delete[] arr; }

    void push_back(Neighbor data) {
        if (currentSize == capacity) {
            capacity *= 2;
            Neighbor* temp = new Neighbor[capacity];
            for (int i = 0; i < currentSize; i++) temp[i] = arr[i];
            delete[] arr;
            arr = temp;
        }
        arr[currentSize++] = data;
    }
    Neighbor& get(int index) const { return arr[index]; }
    int size() const { return currentSize; }
    
    void swapElements(int i, int j) {
        Neighbor temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
};

// Dynamic Array specifically for Votes (acts like a custom hash map)
class VoteArray {
private:
    Vote* arr;
    int capacity;
    int currentSize;
public:
    VoteArray() {
        capacity = 2;
        currentSize = 0;
        arr = new Vote[capacity];
    }
    ~VoteArray() { delete[] arr; }

    void push_back(Vote data) {
        if (currentSize == capacity) {
            capacity *= 2;
            Vote* temp = new Vote[capacity];
            for (int i = 0; i < currentSize; i++) temp[i] = arr[i];
            delete[] arr;
            arr = temp;
        }
        arr[currentSize++] = data;
    }
    Vote& get(int index) const { return arr[index]; }
    int size() const { return currentSize; }
};


// --- 3. ALGORITHMS ---

// Math: Euclidean Distance
double calculateDistance(const Student& a, const Student& b) {
    return sqrt(pow(a.studyHours - b.studyHours, 2) +
                pow(a.attendance - b.attendance, 2) +
                pow(a.previousScore - b.previousScore, 2));
}

// Machine Learning: K-Nearest Neighbors (from scratch)
string predictGrade(const StudentArray& trainingData, Student newStudent, int k) {
    NeighborArray neighbors;

    // Step 1: Calculate distance to all known students
    for (int i = 0; i < trainingData.size(); i++) {
        Student current = trainingData.get(i);
        double dist = calculateDistance(newStudent, current);
        Neighbor n;
        n.distance = dist;
        n.grade = current.grade;
        neighbors.push_back(n);
    }

    // Step 2: Custom Bubble Sort to sort neighbors by distance
    for (int i = 0; i < neighbors.size() - 1; i++) {
        for (int j = 0; j < neighbors.size() - i - 1; j++) {
            if (neighbors.get(j).distance > neighbors.get(j + 1).distance) {
                neighbors.swapElements(j, j + 1);
            }
        }
    }

    // Step 3: Custom Frequency Counter to tally votes for the top K neighbors
    VoteArray gradeVotes;
    
    for (int i = 0; i < k; i++) {
        string currentGrade = neighbors.get(i).grade;
        bool found = false;
        
        for (int v = 0; v < gradeVotes.size(); v++) {
            if (gradeVotes.get(v).grade == currentGrade) {
                gradeVotes.get(v).count++;
                found = true;
                break;
            }
        }
        if (!found) {
            Vote v;
            v.grade = currentGrade;
            v.count = 1;
            gradeVotes.push_back(v);
        }
    }

    // Step 4: Find the grade with the most votes
    string predictedGrade = "";
    int maxVotes = 0;
    for (int i = 0; i < gradeVotes.size(); i++) {
        if (gradeVotes.get(i).count > maxVotes) {
            maxVotes = gradeVotes.get(i).count;
            predictedGrade = gradeVotes.get(i).grade;
        }
    }

    return predictedGrade;
}

// --- 4. UTILITIES ---
void loadData(string filename, StudentArray& dataset) {
    ifstream file(filename);
    string line;
    
    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return;
    }

    // Skip the header row
    getline(file, line);

    while (getline(file, line)) {
        Student s;
        int comma1 = line.find(',');
        int comma2 = line.find(',', comma1 + 1);
        int comma3 = line.find(',', comma2 + 1);
        int comma4 = line.find(',', comma3 + 1);

        s.id = stoi(line.substr(0, comma1));
        s.studyHours = stod(line.substr(comma1 + 1, comma2 - comma1 - 1));
        s.attendance = stod(line.substr(comma2 + 1, comma3 - comma2 - 1));
        s.previousScore = stod(line.substr(comma3 + 1, comma4 - comma3 - 1));
        s.grade = line.substr(comma4 + 1);

        dataset.push_back(s);
    }
}

int main() {
    StudentArray trainingData;

    cout << "Loading Machine Learning dataset..." << endl;
    loadData("student_data.csv", trainingData);
    cout << "Successfully loaded " << trainingData.size() << " student records into custom StudentArray!\n\n";

    Student newStudent;
    newStudent.id = 999;
    
    cout << "--- ML GRADE PREDICTOR ---" << endl;
    cout << "Enter study hours per week (e.g., 8.5): ";
    cin >> newStudent.studyHours;
    cout << "Enter attendance percentage (e.g., 85): ";
    cin >> newStudent.attendance;
    cout << "Enter previous test score (e.g., 78): ";
    cin >> newStudent.previousScore;

    string predicted = predictGrade(trainingData, newStudent, 3);

    cout << "\n=========================================\n";
    cout << ">>> PREDICTION: Expected Grade is [" << predicted << "] <<<";
    cout << "\n=========================================\n";

    return 0;
}
