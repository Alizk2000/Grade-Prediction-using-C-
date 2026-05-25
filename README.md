# 🎓 ML Grade Predictor (Hardcore C++ Edition)

A lightweight Machine Learning model built entirely in C++ from the ground up. 

**Zero Standard Template Libraries (STL). Zero C++ Templates.**

This project manages raw memory allocation and custom data structures directly to implement the **K-Nearest Neighbors (KNN)** algorithm. It predicts a student's final letter grade based on historical data.


## 🧠 How It Works (The Math & ML)
The system uses the **K-Nearest Neighbors** algorithm. When you input a new student's data, the program calculates the **Euclidean Distance** between the new student and every student in the historical database.

The formula used to find the closest neighbors:
$$d = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2 + (z_2 - z_1)^2}$$

*(Where x = Study Hours, y = Attendance, z = Previous Score)*

It then sorts these distances to find the `K` closest matches and takes a "majority vote" of their grades to predict the new student's outcome.

## 🛠️ Data Structures Built From Scratch
To demonstrate low-level memory management and algorithm design, this project intentionally avoids C++ STL containers (`std::vector`, `std::map`) and avoids C++ templates entirely. Everything is explicitly typed.

* **`StudentArray`:** A custom dynamic array that manages heap allocation for `Student` structs, automatically doubling its capacity when full.
* **`NeighborArray`:** A custom array for tracking distance calculations, paired with a custom **Bubble Sort** algorithm to rank neighbors.
* **`VoteArray`:** A custom array to track frequency counts, replacing the need for a Hash Map.

## 🚀 Getting Started

### Prerequisites
* A C++ compiler (I used Visual Studio Community Edition)
* `student_data.csv` (included in this repository)

