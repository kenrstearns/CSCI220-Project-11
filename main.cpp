//Kenneth Stearns
//Project 11
//Due 12/9/21
//This program will take an input of a list of edges for a weighted graph and return the minimum spanning tree using kruskal's algorithm.
#include<iostream>
#include<fstream>

using namespace std;

//Defining the Partition class.
class Partition
{
public:
    static const int N = 100;

    Partition();    //Constructor
    int uf_find(int x);
    void uf_union(int x, int y);

private:
    int p[N];   //Data member
};

//Default constructor for partition. Sets all values to -1.
Partition::Partition()
{
    for(int i = 0; i < N; i++)
        p[i] = -1;
}

//uf_find function
//Pre: a value x to be searched in the partition.
//Post: returns the root of the tree the value exists in.
int Partition::uf_find(int x)
{
    int temp, t, root;
    temp = x;

    while(p[temp] >= 0)
        temp = p[temp];
    root = temp;

    temp = x;

    while(p[temp] >= 0)
    {
        t = temp;
        temp = p[temp];
        p[t] = root;
    }

    return root;
}

//uf_union function.
//Pre: Two values that are to be combined into the same tree.
//Post: Connects the two values into the same tree.
void Partition::uf_union(int x, int y)
{
    int xset = uf_find(x);
    int yset = uf_find(y);
    if(p[xset] < p[yset])
    {
        p[xset] += p[yset];
        p[yset] = xset;
    }
    else
    {
        p[yset] += p[xset];
        p[xset] = yset;
    }
}

//Defining the node structure utilized in the array.
struct node
{
    int x;
    int y;
    int weight;
};

//inSort function.
//Pre: an array of nodes that were defined above that a user wants to be sorted.
//Post: sorts the array from smallest to largest based on weight.
void inSort(node* a[], int n)
{
    int j, k, x, y;

    for(int i = 1; i < n; i++)
    {
        x = a[i] -> x;
        y = a[i] -> y;
        k = a[i] -> weight;
        j = i - 1;

        while(j >= 0 && a[j] -> weight > k)
        {
            a[j+1] -> weight = a[j] -> weight;
            a[j+1] -> x = a[j] -> x;
            a[j+1] -> y = a[j] -> y;
            j = j - 1;
        }

        a[j+1] -> x = x;
        a[j+1] -> y = y;
        a[j+1] -> weight = k;
    }

    return;
}

//Kruskal function.
//Pre: an array of nodes, an integer for the number of vertices, a partition p that is all set to -1, and the total number of edges in the array.
//Post: outputs to the terminal the edges that are required for the minimum spanning tree.
void kruskal(node* a[], int n, Partition p, int numEdges)
{
    cout << "Minimum spanning tree:" << endl;

    int total = 0;
    int edges = 0;
    int weight;

    while(edges < n - 1)
    {
        for(int i = 0; i < numEdges; i++)
        {
            if(edges >= n)
                break;

            if(p.uf_find(a[i] -> x) != p.uf_find(a[i] -> y))
            {
                cout << "\tEdge: = (v" << a[i] -> x << ",v" << a[i] -> y << "); cost = " << a[i] -> weight << endl;
                p.uf_union(a[i] -> x, a[i] -> y);
                weight = a[i] -> weight;
                total += weight;
                edges++;
            }
        }
    }

    cout << "Total cost = " << total << endl;
}

int main()
{
    string file;
    cout << "Enter the file name: ";
    cin >> file;

    ifstream myfile;
    myfile.open(file);

    if(!myfile.is_open())
    {
        cout << "Error opening file. ";
        return 0;
    }

    int n;

    myfile >> n;

    int maxEdges = ( n * (n + 1) ) / 2;

    Partition p;

    node* a[maxEdges];

    int edgeNum = 0;

    while(true)
    {
        int l;
        int j;
        int k;
        myfile >> l;
        myfile >> j;
        myfile >> k;

        node* temp = new node;
        temp -> x = l;
        temp -> y = j;
        temp -> weight = k;

        a[edgeNum] = temp;
        edgeNum++;

        if(!myfile.eof())
            continue;
        else
            break;
    }

    inSort(a, edgeNum);

    kruskal(a, n, p, edgeNum);

    return 0;
}
