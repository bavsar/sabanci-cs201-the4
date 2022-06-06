#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Berkay Avsar 27782

//Function to sort elements:
void SelectSort(vector<string> &ids, vector<string> &names, vector<string> &lastnames, vector<double> &points)
{
    int j, k, minIndex, numElts = points.size();
    double tempPoint;
    string tempName, tempLastname, tempId;
    for (k = 0; k < numElts - 1; k++)
    {
        minIndex = k; //Minimal element index
        for (j = k + 1; j < numElts; j++)
            if (points[j] > points[minIndex])
            {
                minIndex = j; //New min, store index
            }
            else if (points[j] == points[minIndex])
            {
                if (lastnames[j] < lastnames[minIndex])
                {
                    minIndex = j; //New min, store index
                }
            }

        //Swap Points:
        tempPoint = points[k]; //Swap min and k-th elements
        points[k] = points[minIndex];
        points[minIndex] = tempPoint;
        //Swap Names:
        tempName = names[k];
        names[k] = names[minIndex];
        names[minIndex] = tempName;
        //Swap Lastnames:
        tempLastname = lastnames[k];
        lastnames[k] = lastnames[minIndex];
        lastnames[minIndex] = tempLastname;
        //Swap Ids:
        tempId = ids[k];
        ids[k] = ids[minIndex];
        ids[minIndex] = tempId;
    }
}
//Function to check if file opens properly:
bool checkFileOpens(ifstream &file_str, string fileName)
{
    file_str.open(fileName.c_str());
    if (file_str.fail())
    {
        cout << "Can not find the requested file. Terminating application ..." << endl;
        return false;
    }
    return true;
}
//Function to check if a string exists in a vector:
int existsInVector(vector<string> &data, string str)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i] == str)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    vector<string> names;
    vector<string> lastnames;
    vector<string> ids;
    vector<double> points;

    string grades_fn, names_fn;
    ifstream grades_f, names_f;

    //Getting filenames:
    cout << "Please enter a filename for Students Grades Results: ";
    cin >> grades_fn;
    if (!checkFileOpens(grades_f, grades_fn))
    {
        return 1;
    }

    cout << "Please enter a filename for Students Names: ";
    cin >> names_fn;
    if (!checkFileOpens(names_f, names_fn))
    {
        return 1;
    }

    //Getting grades of students:
    string line;
    string id;
    double grade;
    double percent_for_grading_type;
    while (getline(grades_f, line))
    {
        if (line.length() == 0)
        {
            continue;
        }
        else if (line == "***HOMEWORK***")
        {
            percent_for_grading_type = 0.1;
        }
        else if (line == "***MIDTERM***")
        {
            percent_for_grading_type = 0.2;
        }
        else if (line == "***FINAL***")
        {
            percent_for_grading_type = 0.3;
        }
        else
        {
            istringstream linestream(line);
            linestream >> id >> grade;

            int idx = existsInVector(ids, id);
            if (idx != -1)
            {
                points[idx] = points[idx] + (percent_for_grading_type * grade);
            }
            else
            {
                //Filling id, name and surname vectors:
                string line;
                string student_id, student_name, student_surname;
                bool getout = true;
                while (getline(names_f, line) && getout == true)
                {
                    istringstream linestream(line);
                    linestream >> student_id >> student_name >> student_surname;
                    if (id == student_id)
                    {
                        ids.push_back(id);
                        names.push_back(student_name);
                        lastnames.push_back(student_surname);
                        points.push_back(percent_for_grading_type * grade);
                        names_f.clear();
                        names_f.seekg(0);
                        getout = false;
                    }
                }
            }
        }
    }

    SelectSort(ids, names, lastnames, points);

    cout << "Enter the rank you want to query (enter 0 to exit): ";
    int rank;
    cin >> rank;
    while (rank != 0)
    {
        if (rank < 0 || rank > ids.size())
        {
            cout << "Rank needs to be greater than 0 and smaller than " << ids.size() + 1 << "!" << endl;
        }
        else
        {
            rank = rank - 1;
            cout << rank + 1 << ", " << ids[rank] << ", " << names[rank] << " " << lastnames[rank] << ", " << points[rank] << endl;
        }
        cout << "Enter the rank you want to query (enter 0 to exit): ";
        cin >> rank;
    }
    cout << "Exiting..." << endl;
}
