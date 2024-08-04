#include <iostream> 
#include <fstream> // <- for file opening and reading
#include <vector> 
#include <unordered_set>
#include <string>
using namespace std;

// This code is using both vectors and sets to complete this. 



//Description: "Function to construct an undirected graph from an edge list (Adjacency List)"
vector<unordered_set<string>> constructGraph(const string& filename) 
{
    // Specify the file
    ifstream file(filename);

    // If the file is unable to open
    if (!file.is_open()) 
    {
        // Throw a runtime error if the file cannot be opened
        throw runtime_error("Unable to open file: " + filename);
    }

    // Declare a vector of unordered sets of strings
    vector<unordered_set<string>> graph;

    string user1, user2, ignore; // <- Ignore the third column

    while (file >> user1 >> user2 >> ignore)
    {
        int index1 = stoul(user1);
        int index2 = stoul(user2);

        int maxIndex = max(index1, index2);
        if (maxIndex >= graph.size()) 
        {
            graph.resize(maxIndex + 1);
        }
        // Add unsigned integer edges to the graph
        graph[index1].insert(user2);
        graph[index2].insert(user1);
    }

    // Clsoe the file & return the constructed graph
    file.close();
    return graph;
}

//Description: "Function to compute the average degree over all vertices"
double computeAvgDegree(const vector<unordered_set<string>>& graph)
{
    double totalDegree = 0.0;
    double totalVertices = static_cast<double>(graph.size());

    // Loop through each vertex in the graph
    for (const auto& neighbors : graph) 
    {
        // For each vertex, add its degree 
        totalDegree += static_cast<double>(neighbors.size());
    }

    // Calculate the average degree by dividing the total degree by the total number of vertices
    return totalDegree / totalVertices;
}

//Description: "Function to compute the number of vertices with degree >= 100"
int countVerticesWithDegree100OrMore(const vector<unordered_set<string>>& graph) 
{
    int count = 0;

    for (const auto& neighbors : graph) 
    {
        if (neighbors.size() >= 100) 
        {
            count++;
        }
    }

    return count;
}

//Description: "Function to compute the overall average degree of all users' friends"
double computeOverallAvgDegreeOfFriends(const vector<unordered_set<string>>& graph)
{
    double totalDegree = 0.0;
    double totalVertices = 0.0;

    // Loop through each vertex in the graph
    for (const auto& neighbors : graph)
    {
        // For each vertex, add the total degree of friends
        totalDegree += static_cast<double>(neighbors.size());

        // Increment the total number of vertices
        totalVertices += 1.0;
    }

    // Calculate the overall average degree by dividing the total degree by the total number of vertices
    return totalDegree / totalVertices;
}


int main() 
{
    string fileName = "facebook-links.txt";

        // Construct the graph using adjacency list
        vector<unordered_set<string>> facebookGraph = constructGraph(fileName);

        double avgDegree = computeAvgDegree(facebookGraph);
        cout << "Average Degree: " << avgDegree << endl;

        // Calculate the overall average degree of all users' friends
        double overallAvgDegreeOfFriends = computeOverallAvgDegreeOfFriends(facebookGraph);
        cout << "Overall Average Degree of All Users' Friends: " << overallAvgDegreeOfFriends << endl;

        int verticesWithDegree100OrMore = countVerticesWithDegree100OrMore(facebookGraph);
        cout << "Number of Vertices with Degree >= 100: " << verticesWithDegree100OrMore << endl;

    return 0;
}
