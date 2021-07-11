#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// Number of individuals in each generation
#define POPULATION_SIZE 100
#define SSIZE 10
int g_array[SSIZE];//genetic array input
    int t_array[SSIZE];//target array


void genetic_sort();

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(int arr[], int n, int i)
{
	int largest = i; // Initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2

	// If left child is larger than root
	if (l < n && arr[l] > arr[largest])
		largest = l;

	// If right child is larger than largest so far
	if (r < n && arr[r] > arr[largest])
		largest = r;

	// If largest is not root
	if (largest != i) {
		swap(arr[i], arr[largest]);

		// Recursively heapify the affected sub-tree
		heapify(arr, n, largest);
	}
}

// main function to do heap sort
void heapSort(int arr[], int n)
{
	// Build heap (rearrange array)
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// One by one extract an element from heap
	for (int i = n - 1; i >= 0; i--) {
		// Move current root to end
		swap(arr[0], arr[i]);

		// call max heapify on the reduced heap
		heapify(arr, i, 0);
	}
}

    // Function to generate random numbers in given range
int random_num(int start, int end)
{
    int range = (end-start)+1;
    int random_int = start+(rand()%range);
    return random_int;
}

// Create random genes for mutation
//return a
int mutated_genes()
{
    //int len = GENES.size();
    int r = random_num(0, 50-1);
    return g_array[r];
}
// create chromosome or string of genes
//return a node
int* create_gnome()
{
    int len = SSIZE;
   // for (int i=0;i<50;i++)
   //  n_array[i]=0;//temp array
   int *n_array=new int[SSIZE];//temp array
    for(int i = 0;i<len;i++)
        n_array[i]= mutated_genes();
    return n_array;
}




   void genetic()
    {
        int num;
        for (int i=0;i<SSIZE;i++) //loop for give input array
        {
            cout<<"enter an number"<< i+1<<": ";
            cin>>num;
            cout<<endl;
            g_array[i]=num;
            t_array[i]=num;
        }
        int n = sizeof(t_array) / sizeof(t_array[0]);
        heapSort(t_array,n);

        genetic_sort();
    }



// Class representing individual in population
class Individual
{
public:
    int chromosome_array[50];
    int fitness;
    Individual(int ch[])
    {
        for(int i;i<SSIZE;i++)
    this->chromosome_array[i] = ch[i];
    fitness = cal_fitness();
    }
    Individual mate(Individual parent2);
    int cal_fitness();
    void printArray() /* A utility function to print array of size n */
{

	for (int i = 0; i < SSIZE; ++i)
		cout << chromosome_array[i] << " ";

}
};

// Perform mating and produce new offspring
Individual Individual::mate(Individual par2)
{
    // chromosome for offspring
    int *child_chromosome=new int [SSIZE] ;

    int len = SSIZE,k=0;
    for(int i = 0;i<len;i++)
    {
        // random probability
        float p = random_num(0, 100)/100;

        // if prob is less than 0.45, insert gene
        // from parent 1
        if(p < 0.45)
            {child_chromosome[k]= this->chromosome_array[i];
            k++;
            }
        // if prob is between 0.45 and 0.90, insert
        // gene from parent 2
        else if(p < 0.90)
            {child_chromosome[k]= par2.chromosome_array[i];
            k++;
            }

        // otherwise insert random gene(mutate),
        // for maintaining diversity
        else
            child_chromosome[k]= mutated_genes();
                k++;
    }

    // create new Individual(offspring) using
    // generated chromosome for offspring
    return Individual(child_chromosome);
};


// Calculate fittness score, it is the number of
// block in array which differ from target
// array.
int Individual::cal_fitness()
{
    int len = SSIZE;
    int fitness = 0;
    for(int i = 0;i<len;i++)
    {
        if(chromosome_array[i] != t_array[i])
            fitness++;
    }
    return fitness;
};

// Overloading < operator
bool operator<(const Individual &ind1, const Individual &ind2)
{
    return ind1.fitness < ind2.fitness;
}

void genetic_sort()
{
    srand((unsigned)(time(0)));

    // current generation
    int generation = 0;

    vector<Individual> population;
    bool found = false;

    // create initial population
    for(int i = 0;i<POPULATION_SIZE;i++)
    {
        int *gnome = create_gnome();
        population.push_back(Individual(gnome));
    }

    while(! found)
    {
        // sort the population in increasing order of fitness score
        sort(population.begin(), population.end());

        // if the individual having lowest fitness score ie.
        // 0 then we know that we have reached to the target
        // and break the loop
        if(population[0].fitness <= 0)
        {
            found = true;
            break;
        }

        // Otherwise generate new offsprings for new generation
        vector<Individual> new_generation;

        // Perform Elitism, that mean 10% of fittest population
        // goes to the next generation
        int s = (10*POPULATION_SIZE)/100;
        for(int i = 0;i<s;i++)
            new_generation.push_back(population[i]);

        // From 50% of fittest population, Individuals
        // will mate to produce offspring
        s = (90*POPULATION_SIZE)/100;
        for(int i = 0;i<s;i++)
        {
           // int len = population.size();
            int r = random_num(0, 50);
            Individual parent1 = population[r];
            r = random_num(0, 50);
            Individual parent2 = population[r];
            Individual offspring = parent1.mate(parent2);
            new_generation.push_back(offspring);
        }
        population = new_generation;
        cout<< "Generation: " << generation << "\t";
        cout<< "Array: ";population[0].printArray();cout<<"\t";
        cout<< "Fitness: "<< population[0].fitness << "\n";

        generation++;
     }
     cout<< "Generation: " << generation << "\t";
    cout<< "Array: "; population[0].printArray(); cout<<"\t";
    cout<< "Fitness: "<< population[0].fitness << "\n";
}

int main()
{

genetic();
    return 0;
}
