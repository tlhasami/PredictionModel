/**
 * <---------------- MADE BY TALHA SAMI ---------------->
 * <--------------------- I243118 ---------------------->
 * <---------------------- SE - B ---------------------->
 */

#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cfloat>
#include <cmath>

using namespace std;

/**
 * @brief created for Clearing Screen  For Better readability
 */
void clearScreen()
{
#ifdef _WIN32
    system("cls"); // Windows command to clear screen
#else
    system("clear"); // Linux/macOS command to clear screen
#endif
}

/**
 * @brief created for Pausing Screen  For Better readability
 */
void pauseScreen()
{
#ifdef _WIN32
    system("pause"); // Windows command to pause
#else
    cout << "Press Enter to continue...";
    cin.get(); // Wait for Enter key on Linux/macOS
#endif
}

/*        Forward Definition  Of struct to avoid Scope Issue */
struct GeoCoordinates;
struct Employees;
struct Products;
struct SalesData;
struct StoreAnalytics;
struct SalesForecast;
struct Store;
struct Centroid;
struct subCluster;
struct Cluster;
struct Report;

/**
 * @brief Gets the Location Of the Store where it is located
 */
struct GeoCoordinates
{
    double gLat;
    double gLong;
};

/**
 * @brief it contains the Data of the Manager and The Employee working in the store
 * @param eID it is the unique Employee ID which would be used for working in future if needed
 * @param eName itt is just random in our case
 * @param salary it is the salary majorly used for calculating the total cost of the store
 */
struct Employees
{
    int eID;
    char *eName;
    double salary;

    Employees()
    {
        eName = new char[5];
        eID = 0;
    }

    ~Employees()
    {
        delete[] eName;
    }
};

/**
 * @brief It contains the info of the products available Product in the Store
 * @param SKU it would always be the Unique ID of that product like a barcode which is used in future for identifying the product in future
 * @param pName it is the Name i have setted for the product along with its Id
 * @param unitPrice cost oof that function
 */
struct Products
{
    char *SKU;
    char *pName;
    double unitPrice;

    Products()
    {
        SKU = new char[7];
        pName = new char[50];
    }

    ~Products()
    {
        delete[] SKU;
        delete[] pName;
    }
};

/**
 * @brief It contains the Sales Info like where the sale happened in which store and which product got sold and how many product were sold
 * @param StoreID it keep the track that where the product was sold
 * @param numberProduct It is that how many products are sold
 * @param product it the list of the products that are sold along with their info
 * @param Date it is a struct created which keeps the track of when the product was sold
 * @param Time it is the product sold time
 * @param TotalSaleAmount it Keep the total record including the sum of all products unit price in the Sale
 */
struct SalesData
{
    int StoreID;
    int numberOfProducts;
    Products *product;
    struct Date
    {
        int dat, month, year;
    } date;
    string Time;
    double TotalSaleAmount;
};

/**
 * @brief it is the overall stats of the store of where it is lying
 * @param totalSalesAmount it keeps the track of all total amount of all the sales in the store
 * @param totalOperationalCost it keeps the track of how much Money is required to start the store
 * @param profit it is the difference of the totalSalesAmount and totalOperationalCost
 */
struct StoreAnalytics
{
    double totalSalesAmount;
    double totalOperationalCost;
    double profit;
};

/**
 * @brief it contain the things i used for the my prediction for my Sales model
 * @param month it is the name of next month
 * @param predictedSales it is the predicted sales I'll calculate using my working
 * @param ConfidencePercentage it is the ConfidenceLevel i have in my prediction
 * @param warningFlag is for prediction that a big loss can be happen because majorly store is in loss
 */
struct SalesForecast
{
    char *month;
    double predictedSales;
    int ConfidencePercentage;
    bool warningFlag;

    SalesForecast()
    {
        month = new char[10];
    }

    ~SalesForecast()
    {
        delete[] month;
    }
};

/**
 * @brief this contains the Information of the store we have set up at a particular location
 * @param sName it is the Name of the store
 * @param sID it is the unique id of the store in basis of which most of the work is done
 * @param Location it contains the Geographical location of the store
 * @param Manager it is the manager of the Store
 * @param employee_counter it is number of employees
 * @param Staff it in the Data of the Employees in the Store
 * @param sA it is the Store analytics of store
 * @param sF it is the Store Prediction or u can say forcast
 * @param totalSales it is the counter of how many sales were made by the store
 * @param monthlySales it is the number of sales in last 2 years
 * @param monthlySalesAmount it is the SalesAmount of the store per month
 */
struct Store
{
    char *sName;
    int sID;
    GeoCoordinates Location;
    double sMonthlyCost;
    Employees Manager;
    int employee_counter;
    Employees *Staff;
    StoreAnalytics sA;
    SalesForecast sF;
    int totalSales;
    int monthlySales[24] = {0};
    double monthlySalesAmount[24] = {0};

    Store()
    {
        employee_counter = 0;
        totalSales = 0;
        Staff = nullptr;
        sName = new char[40];
    }

    ~Store()
    {
        delete[] sName;
        delete[] Staff;
    }

    void display();
    void monthlySalesDetail();
};

/**
 * @brief it is a helper that keep the track of the centroid of the Cluster
 */
struct Centroid
{
    double x;
    double y;
};

//  /**
//   * @brief it is a helper that keep the track of the centroid of the Second Tier Cluster
//   */
//  struct SecondTierCentroid
//  {
//      double x;
//      double y;
//      double z;
//  };

/**
 * @brief it Contains the data of the store like which one store is added in which cluster
 * @param storeList it contains the stores Id which are included in the current cluster
 * @param storeListCounter it is the counter of the Stores in the Current cluster
 * @param subCenter it is the Centroid for the calculation of the clusters
 */
struct subCluster
{
    char *ID;
    char *Name;
    int *storesList;
    int storeListCounter;
    Centroid subCenter;

    subCluster()
    {
        storeListCounter = 0;
        ID = new char[5];
        Name = new char[50];
        storesList = nullptr;
    }

    ~subCluster()
    {
        delete[] ID;
        delete[] Name;
        delete[] storesList;
    }
};

/**
 * @brief it Contains the data of the store like which one store is added in which cluster
 * @param storeOuter it contains the stores Id which are included in the current cluster
 * @param storeOuterCounter it is the counter of the Stores in the Current cluster
 * @param center it is the Centroid for the calculation of the clusters
 * @param Store it contains the list of the store that are in the current cluster
 */
struct Cluster
{
    char *cID;
    char *Name;
    subCluster *subClusterList;
    Centroid center;
    Store *storeOuter;
    int storeOuterCount;

    Cluster()
    {
        cID = new char[6];   // 5 characters + 1 for null terminator
        Name = new char[50]; // Name can hold up to 50 characters
        subClusterList = nullptr;
        storeOuter = nullptr;
        storeOuterCount = 0;
    }

    ~Cluster()
    {
        delete[] cID;
        delete[] Name;
        delete[] subClusterList;
    }
};

/**
 * @brief it is the report for which contains the data of the top Stores and bottom stores
 */
struct Report
{
    int *topStoresID;
    int *bottomStoresID;
    Report()
    {
        topStoresID = nullptr;
        bottomStoresID = nullptr;
    }
    ~Report()
    {
        delete[] topStoresID;
        delete[] bottomStoresID;
    }
};

/**
 * @note it is the helper structure which is used in the making
 * report it keeps the Index if the Store and Store Id and
 * @param status it is the on what basis u want to make the report
 */
struct ranking
{
    int ID;
    int index;
    long double status;
};

/**
 * @note
 *
 *  All these function are defined after the main
 *
 * These function majorly includes the calculation and working of the Program and rest of Calling function
 * or in which u would take input would be defined separately
 *
 * and these are not all the function these are only the function which have to be called in main and
 * many helper function are to be defined in future as helper function which may or may not have the scope in
 * the main and all the function are in sequence so no other of the Scope issue should be disrupted
 *
 */
void addProductFromFile(Products *&products, int &numProducts);
void displayAvailableProducts(Products *products, const int numProducts);
void displayAllStores(Store *&stores, int &numStores);
static void LoadStoresFromFile(Store *&stores, int &numStores);
bool checkFile(Store *&stores, int &numStores);
void readSalesData(SalesData *&sales, int &numSales, Products *products, int numProducts);
void addProductFromFile(Products *&products, int &numProducts);
void displaySalesData(SalesData *sales, int numSales);
void checkingSalePerMonth(Store *&stores, int &numStores, SalesData *&sales, int &numSales);
void monthlySalesCalculation(Store *&stores, int &numStores, SalesData *&sales, int &numSales, int i, int j);
void CustomerSalesDisplay(Store *&stores, int &numStores);
int whichStoreDetail(int &numStores);
void displayStoreAnalytics(Store *stores, int numStores);
void calculateStoreAnalytics(Store *&stores, int numStores);
void setRanking(Store *stores, int numStores, Report &report);
void MakingCluster(Cluster *&quadrant_type);
void DisplayCluster(Cluster *&quadrant_type);
double Calculation(Cluster *&quadrant_type, const Store *stores, const int &store_number, const int &cluster_number);
void TierOneCluster(Cluster *&quadrant_type, const Store *stores, int &numsStore);
void updateCentroid(Cluster *&quadrant_type, const Store *stores, const int &store_number, const int &index);
void copyStore(Cluster *&quadrant_type, int index, int storeIndex, const Store *stores, const int &store_number, const int &numberOfStores);
void makingSubClusters(Cluster *&quadrant_type);
void calculateSecondTierCentroid(Cluster *&quadrant_type, Store *&stores, int &numStores, SalesData *sales, int numSales);
void SecondTierClustering(Cluster *&);
int menuRanking();

double getRandomDouble(double min, double max)
{
    return min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (max - min)));
}

// Function to generate a random 4-letter name
string getRandomName()
{
    string name;
    for (int i = 0; i < 4; i++)
    {
        name += static_cast<char>('A' + rand() % 26);
    }
    return name;
}
int getRandomInt(int min, int max)
{
    return min + rand() % (max - min + 1);
}

// Function to generate a random product SKU in format "0001" - "0050"
string generateSKU()
{
    int skuNum = getRandomInt(1, 50);
    return (skuNum < 10) ? "000" + to_string(skuNum) : "00" + to_string(skuNum);
}

void generateData(int n)
{
    srand(static_cast<unsigned>(time(0))); // Seed the random number generator

    ofstream output("salesData.txt"); // Open file for writing
    if (!output)
    {
        cerr << "Error opening file!" << endl;
        EXIT_FAILURE;
    }

    int numEntries;

    // Input with validation
    do
    {
        cout << "Enter the number of sales transactions (1 - 100000): ";
        cin >> numEntries;

        if (cin.fail() || numEntries < 1 || numEntries > 100000)
        {
            cout << "Invalid input! Please enter a number between 1 and 100000.\n";
            cin.clear();            // Clear error flags
            cin.ignore(1000, '\n'); // Discard invalid input
        }
        else
        {
            break;
        }
    } while (true);
    output << numEntries << endl;
    for (int i = 0; i < numEntries; i++)
    {
        int storeID = getRandomInt(1, n);   // Random store ID (1-100)
        int numProducts = getRandomInt(1, 3); // Random number of products (1-3)

        output << storeID << " " << numProducts << " ";

        double totalSaleAmount = 0.0;

        // Generate product SKUs and unit prices
        for (int j = 0; j < numProducts; j++)
        {
            string sku = generateSKU();
            output << sku << " ";
        }

        int day = getRandomInt(1, 30);         // Random day (1-30)
        int month = getRandomInt(1, 12);       // Random month (1-12)
        int year = (rand() % 2) ? 2025 : 2026; // Random year (2025 or 2026)
        int hour = getRandomInt(0, 23);        // Random hour (00-23)
        int minute = getRandomInt(0, 59);      // Random minute (00-59)

        // Writing formatted data to the file
        output << day << " " << month << " " << year << " "
               << setw(2) << setfill('0') << hour << ":"
               << setw(2) << setfill('0') << minute << endl;
    }

    output.close();
    cout << "Random data saved to random_data.txt" << endl;
}

void generateStore()
{
    srand((time(0)));

    ofstream output("storesData.txt");
    if (!output)
    {
        cerr << "Error opening file!" << endl;
        EXIT_FAILURE;
    }

    int numStores;

    // Input with validation
    do
    {
        cout << "Enter the number of stores : ";
        cin >> numStores;

        if (cin.fail() || numStores < 1 || numStores > 1000)
        {
            cout << "Invalid input! Please enter a number between 1 and 1000.\n";
            cin.clear();            
            cin.ignore(1000, '\n'); 
        }
        else
        {
            break;
        }
    } while (true);

    output << numStores << endl; 

    for (int i = 1; i <= numStores; i++)
    {
        output << i << endl;
        output << "Store " << i << endl;
        output << fixed << setprecision(4) << getRandomDouble(-90, 90) << " " << getRandomDouble(-180, 180) << endl; // Random coordinates
        output << 100 + i << endl;                                                                                   // Store manager ID
        output << getRandomName() << endl;                                                                           // Store manager name
        int managerSale = rand() % 5000 + 2000;
        output << managerSale << endl;
        const int numEmployees = rand() % 3 + 1; // 1 to 2 employees per store
        int *sal = new int[numEmployees];        // Dynamically allocated array
        int priceTotal = 0;
        output << numEmployees << endl;
        for (int j = 0; j < numEmployees; j++)
        {
            output << 200 + (i * 10) + j << endl; // Employee ID
            output << getRandomName() << endl;    // Employee name
            sal[j] = rand() % 2000 + 1000;
            priceTotal += sal[j];
            output << sal[j] << endl;
        }
        output << priceTotal + 50 + managerSale << endl;
        delete[] sal;
    }

    output.close();
    cout << "Random data saved to random_data.txt" << endl;
    generateData(numStores);
    return;
}


/**
 * @note
 *
 * These are the options the User would majorly have like it can only check whether what are
 * the current reports according to the menu that is to be given by programmer
 *
 * it majorly have 11 options as it is given is @param getUserChoice
 *
 */
void generator();
int getUserChoice();
void option1(Store *&stores, int &numStores);
void option2(Products *products, const int numProducts);
void option3(SalesData *sales, int numSales, Store *&stores, int &numStores);
void option4(Store *stores, int numStores);
void option5(Store *stores, int numStores, Report &report);
void option6(Cluster *&quadrant_type);
void option7(Cluster *&);
void option8(Store *&stores, int &numStores);
void option9(Store *&stores, int &numStores);
void option10(Store *&stores, int &numStores, SalesData *sales, int numSales, Cluster *&quadrant_type);
void option11(bool &);

int main()
{

    generator();

    pauseScreen();
    clearScreen();
    /*
    These are the major variable or Dynamic arrays that would be needed for further
    calculations of th program currently all
    -> Static variable are setted to zero
    -> Dynamic Array are setted to nullptr to avoid memory leaks
     */
    int numStores = 0, numProducts = 0, numSales = 0;
    Store *stores = nullptr;
    Products *available = nullptr;
    SalesData *sales = nullptr;
    Report report;
    Cluster *quadrant_type = nullptr;

    cout << endl;
    /*
    All these function are majorly calculating th info that would be required in the
    future program first calculate the All the things and then the user would majorly
    call the display functions that are created
    */
    LoadStoresFromFile(stores, numStores);                                          // loads Stores from the Files
    addProductFromFile(available, numProducts);                                     // loads products from the Files
    readSalesData(sales, numSales, available, numProducts);                         // loads Sales from the Files
    checkingSalePerMonth(stores, numStores, sales, numSales);                       // it initialize the Store Monthly sales and Sales amount monthly that which Store have sold how many products in which month and was the cost
    calculateStoreAnalytics(stores, numStores);                                     // it calculate the Store Analytics of the store
    MakingCluster(quadrant_type);                                                   // making Cluster
    TierOneCluster(quadrant_type, stores, numStores);                               // separate store according to location
    makingSubClusters(quadrant_type);                                               // making subClusters in Cluster for Tier2 clustering
    calculateSecondTierCentroid(quadrant_type, stores, numStores, sales, numSales); // it calculates the centroids for all subClusters in all clusters
    SecondTierClustering(quadrant_type);                                            // it separate the Store on th basis of their performance

    cout << endl
         << " ";
    pauseScreen();

    bool start = true;
    while (start)
    {
        clearScreen();
        // Ask user for choice ...
        int choice = getUserChoice();
        switch (choice)
        {
        case 1:
        {
            // Setup of Stores
            option1(stores, numStores);
            break;
        }
        case 2:
        {
            // to see the Details of Product
            option2(available, numProducts);
            break;
        }
        case 3:
        {
            // to See the Sales Detail
            option3(sales, numSales, stores, numStores);
            break;
        }
        case 4:
        {
            // to Calculate Total Operation Cost (See Sales Analytics)
            option4(stores, numStores);
            break;
        }
        case 5:
        {
            // to see the Ranking of Stores on Different Bases
            option5(stores, numStores, report);
            break;
        }
        case 6:
        {
            // to See the Tier-1 K-MEAN-CLUSTERING on Basis of LOCATION
            option6(quadrant_type);
            break;
        }
        case 7:
        {
            // to see Tier-2 Clustering On Basis of overall Stats
            option7(quadrant_type);
            clearScreen();
            break;
        }
        case 8:
        {
            // to see the Prediction of Next Month
            option8(stores, numStores);
            clearScreen();
            break;
        }
        case 9:
        {
            // Monthly Sales Detail
            option9(stores, numStores);
            break;
        }
        case 10:
        {
            // Monthly Sales Detail Chart
            option10(stores, numStores, sales, numSales, quadrant_type);
            break;
        }
        case 11:
        {
            // Exit
            option11(start);
            break;
        }
        }
    }

    /**
     * @note '
     *
     * Deallocating the memory as it is compulsory other wise runtime Error would occur
     *
     */

    delete[] stores;
    delete[] available;
    delete[] sales;
    delete[] quadrant_type;

    return 0;
}

// menu for user to ask for option
int getUserChoice()
{
    cout << "\n  Enter Which Task you want to check: \n"
         << "  1. Setup of Stores\n"
         << "  2. Want to see the Details of Product\n"
         << "  3. Want to See the Sales Detail\n"
         << "  4. Want to Calculate Total Operation Cost (See Sales Analytics)\n"
         << "  5. Want to see the Ranking of Stores on Different Bases\n"
         << "  6. Want to See the Tier-1 K-MEAN-CLUSTERING on Basis of LOCATION\n"
         << "  7. Want to see Tier-2 Clustering On Basis of overall Stats\n"
         << "  8. Want to see the Prediction of Next Month\n"
         << "  9. Monthly Sales Detail\n"
         << "  10. Show Charts \n"
         << "  11. Exit\n"
         << "  Enter your choice (1-11): ";

    int choice;
    cin >> choice;

    // Validate input
    while (cin.fail() || choice < 1 || choice > 11)
    {
        cin.clear();                                         // Clear error flag
        cin.ignore(1000, '\n'); // Ignore invalid input
        cout << " Invalid choice! Please enter a number between 1 and 11: ";
        cin >> choice;
    }

    return choice;
}

/**
 * it just initialize the names and Id i setted according to my working
 */
void MakingCluster(Cluster *&quadrant_type)
{
    quadrant_type = new Cluster[4]; // Allocate 4 clusters

    strcpy(quadrant_type[0].cID, "0001");
    strcpy(quadrant_type[0].Name, "Right_upper_Quadrant");
    quadrant_type[0].center.x = 45;
    quadrant_type[0].center.y = 90;

    strcpy(quadrant_type[1].cID, "0002");
    strcpy(quadrant_type[1].Name, "Left_upper_Quadrant");
    quadrant_type[1].center.x = -45;
    quadrant_type[1].center.y = 90;

    strcpy(quadrant_type[2].cID, "0003");
    strcpy(quadrant_type[2].Name, "Left_lower_Quadrant");
    quadrant_type[2].center.x = -45;
    quadrant_type[2].center.y = -90;

    strcpy(quadrant_type[3].cID, "0004");
    strcpy(quadrant_type[3].Name, "Right_lower_Quadrant");
    quadrant_type[3].center.x = 45;
    quadrant_type[3].center.y = -90;
}

/*it copys all the information of the stores and make a deep copy to
avoid runtime Crash*/
void copyStore(Cluster *&quadrant_type, int index, int storeIndex, const Store *stores, const int &store_number, const int &numberOfStores)
{

    // Ensure storeOuter array exists before accessing it
    if (quadrant_type[index].storeOuter == nullptr)
    {
        quadrant_type[index].storeOuter = new Store[numberOfStores]; // Allocate memory
    }

    quadrant_type[index].storeOuter[storeIndex].sName = new char[strlen(stores[store_number].sName) + 1];
    strcpy(quadrant_type[index].storeOuter[storeIndex].sName, stores[store_number].sName);

    // Copy data
    quadrant_type[index].storeOuter[storeIndex].sID = stores[store_number].sID;
    quadrant_type[index].storeOuter[storeIndex].sMonthlyCost = stores[store_number].sMonthlyCost;
    quadrant_type[index].storeOuter[storeIndex].employee_counter = stores[store_number].employee_counter;
    quadrant_type[index].storeOuter[storeIndex].totalSales = stores[store_number].totalSales;
    quadrant_type[index].storeOuter[storeIndex].Location = stores[store_number].Location;
    quadrant_type[index].storeOuter[storeIndex].Manager = stores[store_number].Manager;
    quadrant_type[index].storeOuter[storeIndex].sA = stores[store_number].sA;
    quadrant_type[index].storeOuter[storeIndex].sF = stores[store_number].sF;

    // Allocate memory for Staff
    if (stores[store_number].employee_counter > 0)
    {
        quadrant_type[index].storeOuter[storeIndex].Staff = new Employees[stores[store_number].employee_counter];
        for (int i = 0; i < stores[store_number].employee_counter; i++)
        {
            quadrant_type[index].storeOuter[storeIndex].Staff[i] = stores[store_number].Staff[i];
        }
    }
    else
    {
        quadrant_type[index].storeOuter[storeIndex].Staff = nullptr;
    }

    // Copy sales data
    for (int i = 0; i < 24; i++)
    {
        quadrant_type[index].storeOuter[storeIndex].monthlySales[i] = stores[store_number].monthlySales[i];
        quadrant_type[index].storeOuter[storeIndex].monthlySalesAmount[i] = stores[store_number].monthlySalesAmount[i];
    }
}

/**
 * it calculates that which cluster belongs where and
 * then adds it details their
 *
 * it is Tier 1 which
 * separates according to the location of the store
 */
void TierOneCluster(Cluster *&quadrant_type, const Store *stores, int &numsStore)
{
    for (int i = 0; i < 4; i++)
        quadrant_type[i].storeOuterCount = 0;

    for (int store_number = 0; store_number < numsStore; store_number++)
    {
        int index = -1;
        double minimum_distance = DBL_MAX;

        for (int cluster_number = 0; cluster_number < 4; cluster_number++)
        {
            double distance = Calculation(quadrant_type, stores, store_number, cluster_number);
            if (distance < minimum_distance)
            {
                minimum_distance = distance;
                index = cluster_number;
            }
        }

        // Allocate memory for storeOuter if not already allocated
        if (quadrant_type[index].storeOuter == nullptr)
        {
            quadrant_type[index].storeOuter = new Store[numsStore]; // Allocate memory
        }

        updateCentroid(quadrant_type, stores, store_number, index);

        copyStore(quadrant_type, index, quadrant_type[index].storeOuterCount, stores, store_number, numsStore);
        quadrant_type[index].storeOuterCount++;
    }
}

// Calculates Euclidean Distance
double Calculation(Cluster *&quadrant_type, const Store *stores, const int &store_number, const int &cluster_number)
{

    double X = pow((quadrant_type[cluster_number].center.x - stores[store_number].Location.gLat), 2.0);
    double Y = pow((quadrant_type[cluster_number].center.y - stores[store_number].Location.gLong), 2.0);

    return sqrt(X + Y);
}

// it updates the centroid by compiling the added store info
void updateCentroid(Cluster *&quadrant_type, const Store *stores, const int &store_number, const int &index)
{
    double X[] = {quadrant_type[index].center.x, stores[store_number].Location.gLat};
    double Y[] = {quadrant_type[index].center.y, stores[store_number].Location.gLong};

    quadrant_type[index].center.x = (X[0] + X[1]) / 2.0;
    quadrant_type[index].center.y = (Y[0] + Y[1]) / 2.0;
}

// it is function just the display which stores belongs where
void DisplayCluster(Cluster *&quadrant_type)
{
    cout << "   ------------ Tier 1 Clustering ---------" << endl;

    for (int i = 0; i < 4; i++)
    {
        cout << "  <--- Cluster Name: " << quadrant_type[i].Name
             << " contains " << quadrant_type[i].storeOuterCount << " Stores --->" << endl;

        for (int j = 0; j < quadrant_type[i].storeOuterCount; j++)
        {
            cout << "  " << j + 1 << ". Store ID: " << quadrant_type[i].storeOuter[j].sID
                 << " Store Location: (" << quadrant_type[i].storeOuter[j].Location.gLat
                 << ", " << quadrant_type[i].storeOuter[j].Location.gLong << ")" << endl;
        }
    }
}

// it is the menu on basis of which u want to see the ranking
int menuRanking()
{
    cout << " 1. For overall Ranking " << endl
         << " 2. By Profit " << endl
         << " 3. By growth rate " << endl
         << " 4. Total number of Sales " << endl;
    int choice;
    do
    {
        cout << "  Enter your choice (1-4): ";
        cin >> choice;
        if (choice < 1 || choice > 4)
        {
            cout << "  Invalid choice. Please enter a number between 1 and 3." << endl;
        }
    } while (choice < 1 || choice > 4);
    return choice;
}

// it Sets the rank according to the choice of the user
void setRanking(Store *stores, int numStores, Report &report)
{
    // Allocate dynamic memory for rankings
    ranking *rankings = new ranking[numStores];

    int choice = menuRanking();

    switch (choice)
    {
    case 1: // Overall Ranking
        for (int i = 0; i < numStores; i++)
        {
            rankings[i] = {stores[i].sID, i,
                           (stores[i].sA.profit * 0.50) +
                               ((stores[i].sA.totalSalesAmount / 24.0) * 0.25) +
                               ((stores[i].totalSales / 2.0) * 0.25)};
        }
        cout << "  Store Rankings based on Overall Performance:\n";
        break;

    case 2: // By Profit
        for (int i = 0; i < numStores; i++)
        {
            rankings[i] = {stores[i].sID, i, stores[i].sA.profit};
        }
        cout << "  Store Rankings based on Profit:\n";
        break;

    case 3: // By Growth Rate
        for (int i = 0; i < numStores; i++)
        {
            rankings[i] = {stores[i].sID, i, stores[i].sA.totalSalesAmount / 24.0};
        }
        cout << "  Store Rankings based on Growth Rate:\n";
        break;

    case 4: // By Total Number of Sales
        for (int i = 0; i < numStores; i++)
        {
            rankings[i] = {stores[i].sID, i, stores[i].totalSales / 2.0};
        }
        cout << "  Store Rankings based on Total Number of Sales:\n";
        break;

    default:
        cout << "  Invalid choice.\n";
        delete[] rankings;
        return;
    }

    // Brute-force sorting (Bubble Sort)
    for (int i = 0; i < numStores - 1; i++)
    {
        for (int j = 0; j < numStores - i - 1; j++)
        {
            if (rankings[j].status < rankings[j + 1].status)
            {
                ranking temp = rankings[j];
                rankings[j] = rankings[j + 1];
                rankings[j + 1] = temp;
            }
        }
    }

    // Display top 10 stores
    int topCount = min(10, numStores);
    cout << "  ->  Top 10 Stores:\n";
    for (int i = 0; i < topCount; i++)
    {
        cout << "  " << i + 1 << ". Store ID: " << rankings[i].ID
             << ", Name: " << stores[rankings[i].index].sName
             << ", Status: " << fixed << setprecision(2) << rankings[i].status << "\n";
    }

    // Display bottom 3 stores
    int bottomCount = min(3, numStores);
    cout << "  ->  Bottom 3 Stores:\n";
    for (int i = numStores - bottomCount; i < numStores; i++)
    {
        cout << "  " << (numStores - i) << ". Store ID: " << rankings[i].ID
             << ", Name: " << stores[rankings[i].index].sName
             << ", Status: " << fixed << setprecision(2) << rankings[i].status << "\n";
    }

    report.topStoresID = new int[10];
    report.bottomStoresID = new int[3];
    for (int i = 0; i < topCount; i++)
    {
        report.topStoresID[i] = stores[rankings[i].index].sID;
    }

    for (int i = 0; i < bottomCount; i++)
    {
        report.bottomStoresID[i] = stores[rankings[numStores - 1 - i].index].sID;
    }

    delete[] rankings;
}

// it calculates All the analytical Details
void calculateStoreAnalytics(Store *&stores, int numStores)
{
    for (int i = 0; i < numStores; i++)
    {
        stores[i].sA.totalOperationalCost = stores[i].sMonthlyCost * 24;
        stores[i].sA.profit = stores[i].sA.totalSalesAmount - stores[i].sA.totalOperationalCost;
    }
}

// it is a display function of the Store Analytics
void displayStoreAnalytics(Store *stores, int numStores)
{
    for (int i = 0; i < numStores; i++)
    {
        cout << "   ----------------------------------------" << endl
             << "   Store ID: " << stores[i].sID << endl
             << "   Store Name: " << stores[i].sName << endl
             << "   Total Number of Sales : " << stores[i].totalSales << endl
             << "   Total Sales Amount: $" << stores[i].sA.totalSalesAmount << endl
             << "   Total Operational Cost: $" << stores[i].sA.totalOperationalCost << endl
             << "   Profit: $" << stores[i].sA.profit << endl
             << "   ----------------------------------------" << endl;
    }
}

/**
 * it set the values of the Store monthlySales and MonthlySalesAmount of the
 * store accordingly
 * */
void monthlySalesCalculation(Store *&stores, int &numStores, SalesData *&sales, int &numSales, int i, int j)
{
    int month = sales[i].date.month;
    int year = sales[i].date.year;
    int index = ((year == 2025) ? 0 : 1) * 12 + month;
    index--;
    stores[j].monthlySales[index] += 1;
    stores[j].monthlySalesAmount[index] += sales[i].TotalSaleAmount;
    stores[j].sA.totalSalesAmount += sales[i].TotalSaleAmount;
}

/**
 * it initialize the Store Monthly sales and Sales amount monthly that which Store have
 * sold how many products in which month and was the cost
 */
void checkingSalePerMonth(Store *&stores, int &numStores, SalesData *&sales, int &numSales)
{
    for (int i = 0; i < numSales; i++)
    {
        for (int j = 0; j < numStores; j++)
        {
            if (stores[j].sID == sales[i].StoreID)
            {
                stores[j].totalSales += 1;
                monthlySalesCalculation(stores, numStores, sales, numSales, i, j);
                break;
            }
        }
    }
}

// it display the sales data like which store have sale which product fro how much
void displaySalesData(SalesData *sales, int numSales)
{
    if (!sales)
    {
        cout << "  No sales data available." << endl;
        return;
    }

    cout << "   Sales Data:" << endl;
    for (int i = 0; i < numSales; i++)
    {
        cout << "  --------------------------\n";
        cout << "  Store ID: " << sales[i].StoreID << endl;
        cout << "  Date: " << sales[i].date.dat << "-" << sales[i].date.month << "-" << sales[i].date.year << " Time: " << sales[i].Time << endl;
        cout << "  Total Sale Amount: $" << sales[i].TotalSaleAmount << endl;
        cout << "  Products Sold:" << endl;

        for (int j = 0; j < sales[i].numberOfProducts; j++)
        {
            cout << "    SKU: " << sales[i].product[j].SKU
                 << " | Name: " << sales[i].product[j].pName
                 << " | Price: $" << sales[i].product[j].unitPrice << endl;
        }
    }
    cout << "  --------------------------\n";
}

// it reads data from the file
void readSalesData(SalesData *&sales, int &numSales, Products *products, int numProducts)
{
    ifstream file("salesData.txt");
    if (!file.is_open())
    {
        cout << " Error opening sales data file." << endl;
        return;
    }

    file >> numSales;
    file.ignore(); // Ignore newline
    // cout << "Number of sales records: " << numSales << endl;

    sales = new SalesData[numSales];

    for (int i = 0; i < numSales; i++)
    {
        file >> sales[i].StoreID; // Read Store ID
        // cout << "\nReading sale record " << i + 1 << ":" << endl;
        // cout << "Store ID: " << sales[i].StoreID << endl;
        file >> sales[i].numberOfProducts; // Read size of product list
        // cout << "Number of products in this sale: " << productCount << endl;

        sales[i].product = new Products[sales[i].numberOfProducts]; // Allocate memory for product list
        double totalAmount = 0.0;                                   // To calculate total sales amount

        for (int j = 0; j < sales[i].numberOfProducts; j++)
        {
            char SKU[7];
            file >> SKU; // Read SKU
            // cout << "  Reading product SKU: " << SKU << endl;

            bool found = false;
            // it puts all the information of where the Product SKu matches
            for (int k = 0; k < numProducts; k++)
            {
                if (strcmp(products[k].SKU, SKU) == 0)
                {
                    strcpy(sales[i].product[j].SKU, products[k].SKU);
                    strcpy(sales[i].product[j].pName, products[k].pName);
                    sales[i].product[j].unitPrice = products[k].unitPrice;
                    totalAmount += products[k].unitPrice; // Add to total

                    // cout << "    Matched product: " << products[k].pName < " | Price: " << products[k].unitPrice << endl;

                    break;
                }
            }
        }

        file >> sales[i].date.dat >> sales[i].date.month >> sales[i].date.year >> sales[i].Time; // Read date and time
        // cout << "Date: " << sales[i].date.dat << sales[i].date.month << sales[i].date.year << " Time: " << sales[i].Time << endl;

        sales[i].TotalSaleAmount = totalAmount; // Assign total sales amount
        // cout << "Total Sale Amount: $" << sales[i].TotalSaleAmount << endl;
    }

    file.close();
    cout << "  Sales data loaded successfully." << endl;
}

// reads the available product in the Store form the file
void addProductByFile(Products *&products, int &numProducts)
{
    ifstream file("products.txt");
    if (!file.is_open())
    {
        cout << "   Error opening product data file." << endl;
        return;
    }

    file >> numProducts;
    products = new Products[numProducts];

    for (int i = 0; i < numProducts; i++)
    {
        file.ignore();
        file.getline(products[i].SKU, 7);
        file.getline(products[i].pName, 50);
        file >> products[i].unitPrice;
    }

    file.close();
    cout << "   Product data loaded successfully." << endl;
}

// it displays the monthly sales details
void Store::monthlySalesDetail()
{
    cout << "   ----------------------------------------" << endl;
    cout << "   Monthly Customer Count for the last 24 months:" << endl;
    for (int i = 0; i < 24; i++)
    {
        cout << "  Month " << i + 1 << " : " << monthlySales[i] << " Customers " << endl
             << " Total Sales Amount per Month : "
             << monthlySalesAmount[i] << endl;
    }
    cout << "   ----------------------------------------" << endl;
}

// it is to display all the store monthly sales details
void CustomerSalesDisplay(Store *&stores, int &numStores)
{
    cout << "   ----------------------------------------" << endl;
    for (int i = 0; i < numStores; i++)
    {
        stores[i].monthlySalesDetail();
    }
}

// it display the store infor excluding the monthly sales
void Store::display()
{
    cout << "  ----------------------------------------" << endl
         << "   Store ID: " << sID << endl
         << "   Store Name: " << sName << endl
         << "   Location: (" << Location.gLat << ", " << Location.gLong << ")" << endl
         << "   Monthly Operational Cost: $" << sMonthlyCost << endl
         << "   Manager ID: " << Manager.eID << endl
         << "   Manager Name: " << Manager.eName << endl
         << "   Manager Salary: $" << Manager.salary << endl;

    cout << "   Number of Employees: " << employee_counter << endl;

    for (int i = 0; i < employee_counter; i++)
    {
        cout << " ----- Employee No. " << i + 1 << "-----" << endl
             << "  Employee ID: " << Staff[i].eID << endl
             << "  Employee Name: " << Staff[i].eName << endl
             << "  Employee Salary: $" << Staff[i].salary << endl;
    }
    cout << "----------------------------------------" << endl;
}

// it is to display all stores
void displayAllStores(Store *&stores, int &numStores)
{
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < numStores; i++)
    {
        stores[i].display();
    }
}

// it checks the file whether is their any data or not
bool checkFile(Store *&stores, int &numStores)
{
    ifstream file("storesData.txt");
    if (!file.is_open())
    {
        cout << " No existing store data file found. Proceeding with new data entry." << endl;
        return false;
    }

    file >> numStores;
    stores = new Store[numStores];

    for (int i = 0; i < numStores; i++)
    {
        file >> stores[i].sID;
        file.ignore();
        file.getline(stores[i].sName, 10);
        file >> stores[i].Location.gLat >> stores[i].Location.gLong;
        file >> stores[i].Manager.eID;
        file.ignore();
        file.getline(stores[i].Manager.eName, 5);
        file >> stores[i].Manager.salary;

        // Read number of employees
        file >> stores[i].employee_counter;
        stores[i].Staff = new Employees[stores[i].employee_counter]; // Dynamically allocate Staff array

        for (int j = 0; j < stores[i].employee_counter; j++)
        {
            file >> stores[i].Staff[j].eID;
            file.ignore();
            file.getline(stores[i].Staff[j].eName, 5);
            file >> stores[i].Staff[j].salary;
        }
        file >> stores[i].sMonthlyCost;
    }

    file.close();
    cout << "  Store data loaded successfully." << endl;
    return true;
}

// it loads Store data from the file only once
static void LoadStoresFromFile(Store *&stores, int &numStores)
{
    if (checkFile(stores, numStores))
    {
        cout << "  Data is Successfully Retrieved" << endl;
        return;
    }
}

// it display the available products
void displayAvailableProducts(Products *products, const int numProducts)
{
    cout << "Available Products:" << endl
         << "----------------------------------------" << endl;
    for (int i = 0; i < numProducts; i++)
    {
        cout << "Product SKU: " << products[i].SKU << endl
             << "Product Name: " << products[i].pName << endl
             << "Unit Price: $" << products[i].unitPrice << endl
             << "----------------------------------------" << endl;
    }
}

// it reads the file and put those products into our products Dynamic array
void addProductFromFile(Products *&products, int &numProducts)
{
    ifstream file("products.txt");
    if (!file.is_open())
    {
        cout << "Error opening product data file." << endl;
        return;
    }

    file >> numProducts;
    products = new Products[numProducts];

    for (int i = 0; i < numProducts; i++)
    {
        file.ignore();
        file.getline(products[i].SKU, 7);
        file.getline(products[i].pName, 50);
        file >> products[i].unitPrice;
    }

    file.close();
    // displayAvailableProducts(products,numProducts);
    cout << "  Product data loaded successfully." << endl;
}

// it ask for which store u want to perform action
int whichStoreDetail(int &numStores)
{
    cout << "  Enter the Store ID for which you want to check: ";
    int choice;

    while (true)
    {
        cin >> choice;

        // Validate that choice is within the valid range
        if (choice > 0 && choice <= numStores)
        {
            break; // Valid input, exit loop
        }

        cout << "Invalid choice! Please enter a number between 1 and " << numStores << ": ";
    }
    return choice - 1;
}

void option1(Store *&stores, int &numStores)
{
    clearScreen();
    cout << "Do you want to check all Store or for one Store (1/0) : ";
    int check;
    // Input validation loop
    while (true)
    {
        cin >> check;
        if (check == 0 || check == 1)
        {
            break; // Valid input
        }
        cout << "Invalid input! Please enter 1 for all stores or 0 for a single store: ";
    }

    if (check)
    {
        clearScreen();
        displayAllStores(stores, numStores);
    }
    else
    {
        int c = whichStoreDetail(numStores);
        clearScreen();
        stores[c].display();
    }

    pauseScreen();
}

void option2(Products *products, const int numProducts)
{
    clearScreen();
    displayAvailableProducts(products, numProducts);
    pauseScreen();
}

// it is created to display only one store details instead of all
void OneStoreSales(SalesData *sales, int numSales, Store *&stores, int &numStores, int indexStore)
{
    if (!sales)
    {
        cout << "  No sales data available." << endl;
        return;
    }

    cout << "  Store ID: " << stores[indexStore].sID << endl;
    int count = 0;
    cout << "  Sales Data : " << endl;
    cout << "   --------------------------\n";
    for (int i = 0; i < numSales; i++)
    {
        if (sales[i].StoreID == stores[indexStore].sID)
        {
            cout << "  Sale number : " << ++count << " ";
            cout << "  Date: " << sales[i].date.dat << "-" << sales[i].date.month << "-" << sales[i].date.year << " Time: " << sales[i].Time << endl;
            cout << "  Total Sale Amount: $" << sales[i].TotalSaleAmount << endl;
            cout << "  Products Sold:" << endl;

            for (int j = 0; j < sales[i].numberOfProducts; ++j)
            {
                cout << "    SKU: " << sales[i].product[j].SKU
                     << " | Name: " << sales[i].product[j].pName
                     << " | Price: $" << sales[i].product[j].unitPrice << endl;
            }
        }
    }
    cout << "   --------------------------\n";
}

void option3(SalesData *sales, int numSales, Store *&stores, int &numStores)
{
    clearScreen();
    cout << "  Do you want to check all Store Sales or for one Store Sales (1/0) : ";
    int check;
    // Input validation loop
    while (true)
    {
        cin >> check;
        if (check == 0 || check == 1)
        {
            break; // Valid input
        }
        cout << "  Invalid input! Please enter 1 for all stores or 0 for a single store: ";
    }

    if (check)
    {
        clearScreen();
        displaySalesData(sales, numSales);
    }
    else
    {
        int index = whichStoreDetail(numStores);
        clearScreen();
        OneStoreSales(sales, numSales, stores, numSales, index);
    }

    pauseScreen();
}

// it is created Display all stores analytics
void displayOneStoreAnalytics(Store *stores, int numStores, int index)
{

    cout << "----------------------------------------" << endl
         << "Store ID: " << stores[index].sID << endl
         << "Store Name: " << stores[index].sName << endl
         << "Total Number of Sales : " << stores[index].totalSales << endl
         << "Total Sales Amount : $" << stores[index].sA.totalSalesAmount << endl
         << "Total Operational Cost: $" << stores[index].sA.totalOperationalCost << endl
         << "Profit: $" << stores[index].sA.profit << endl
         << "----------------------------------------" << endl;
}

void option4(Store *stores, int numStores)
{
    clearScreen();
    cout << "  Do you want to check all Store Sales or for one Store Sales (1/0) : ";
    int check;
    // Input validation loop
    while (true)
    {
        cin >> check;
        if (check == 0 || check == 1)
        {
            break; // Valid input
        }
        cout << "   Invalid input! Please enter 1 for all stores or 0 for a single store: ";
    }

    if (check)
    {
        clearScreen();
        displayStoreAnalytics(stores, numStores);
    }
    else
    {
        int index = whichStoreDetail(numStores);
        clearScreen();
        displayOneStoreAnalytics(stores, numStores, index);
    }

    pauseScreen();
}

// it is created to check rank of a particular store
void CheckStoreRanking(Store *stores, int numStores, int index)
{
    // Allocate dynamic memory for rankings
    ranking *rankings = new ranking[numStores];

    int choice = menuRanking();

    switch (choice)
    {
    case 1: // Overall Ranking
        for (int i = 0; i < numStores; i++)
        {
            rankings[i] = {stores[i].sID, i,
                           (stores[i].sA.profit * 0.50) +
                               ((stores[i].sA.totalSalesAmount / 24.0) * 0.25) +
                               ((stores[i].totalSales / 2.0) * 0.25)};
        }
        cout << "    Store Rankings based on Overall Performance:\n";
        break;

    case 2: // By Profit
        for (int i = 0; i < numStores; i++)
        {
            rankings[i] = {stores[i].sID, i, stores[i].sA.profit};
        }
        cout << "    Store Rankings based on Profit:\n";
        break;

    case 3: // By Growth Rate
        for (int i = 0; i < numStores; i++)
        {
            rankings[i] = {stores[i].sID, i, stores[i].sA.totalSalesAmount / 24.0};
        }
        cout << "    Store Rankings based on Growth Rate:\n";
        break;

    case 4: // By Total Number of Sales
        for (int i = 0; i < numStores; i++)
        {
            rankings[i] = {stores[i].sID, i, stores[i].totalSales / 2.0};
        }
        cout << "    Store Rankings based on Total Number of Sales:\n";
        break;

    default:
        cout << "    Invalid choice.\n";
        delete[] rankings;
        return;
    }

    // Brute-force sorting (Bubble Sort)
    for (int i = 0; i < numStores - 1; i++)
    {
        for (int j = 0; j < numStores - i - 1; j++)
        {
            if (rankings[j].status < rankings[j + 1].status)
            {
                ranking temp = rankings[j];
                rankings[j] = rankings[j + 1];
                rankings[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < numStores; i++)
    {
        if (stores[index].sID == rankings[i].ID)
        {
            cout << "    Store " << stores[index].sID << " Rank -> " << i + 1 << endl;
            break;
        }
    }

    delete[] rankings;
}

void option5(Store *stores, int numStores, Report &report)
{
    clearScreen();
    cout << "   Do you want to check List of Ranks or want to check a Store rank (1/0) : ";
    int check;
    // Input validation loop
    while (true)
    {
        cin >> check;
        if (check == 0 || check == 1)
        {
            break; // Valid input
        }
        cout << "  Invalid input! Please enter 1 for all stores or 0 for a single store: ";
    }

    if (check)
    {
        clearScreen();
        setRanking(stores, numStores, report);
    }
    else
    {
        int index = whichStoreDetail(numStores);
        clearScreen();
        CheckStoreRanking(stores, numStores, index);
    }

    pauseScreen();
}

void option6(Cluster *&quadrant_type)
{
    clearScreen();
    cout << "  ------------ Tier 1 Clustering ---------" << endl
         << endl;
    cout << "  Do you want to check All Clustering or for Only single cluster  (1/0) : ";
    int check;
    // Input validation loop
    while (true)
    {
        cin >> check;
        if (check == 0 || check == 1)
        {
            break; // Valid input
        }
        cout << "  Invalid input! Please enter 1 for all Clusters or 0 for a single Cluster: ";
    }
    if (check == 0)
    {

        cout << "  1. First Cluster " << endl
             << "  2. Second Cluster " << endl
             << "  3. Third Cluster " << endl
             << "  4. Fourth Cluster " << endl;

        int index;
        cout << "  Enter Choice : ";
        while (true)
        {
            cin >> index;
            if (index == 1 || index == 2 || index == 3 || index == 4)
            {
                break; // Valid input
            }
            cout << "  Invalid input! Please enter between 1 to 4 : ";
        }
        index--;
        clearScreen();
        cout << "   <--- Cluster Name: " << quadrant_type[index].Name
             << " contains " << quadrant_type[index].storeOuterCount << " Stores --->" << endl;
        for (int j = 0; j < quadrant_type[index].storeOuterCount; j++)
        {
            cout << " " << j + 1 << ". Store ID: " << quadrant_type[index].storeOuter[j].sID
                 << " Store Location: (" << quadrant_type[index].storeOuter[j].Location.gLat
                 << ", " << quadrant_type[index].storeOuter[j].Location.gLong << ")" << endl;
        }
    }
    else
    {
        clearScreen();
        DisplayCluster(quadrant_type);
    }
    pauseScreen();
}

// it is just initializing the the subClusters
void makingSubClusters(Cluster *&quadrant_type)
{
    // Space Allocated
    for (int i = 0; i < 4; i++)
    {
        quadrant_type[i].subClusterList = new subCluster[3];
    }

    for (int i = 0; i < 4; i++)
    {
        strcpy(quadrant_type[i].subClusterList[0].ID, "0001");
        strcpy(quadrant_type[i].subClusterList[0].Name, "TopPerforming");
        strcpy(quadrant_type[i].subClusterList[1].ID, "0002");
        strcpy(quadrant_type[i].subClusterList[1].Name, "AveragePerforming");
        strcpy(quadrant_type[i].subClusterList[2].ID, "0003");
        strcpy(quadrant_type[i].subClusterList[2].Name, "UnderPerforming");
    }
}

// calculates X and y coordinates for SubCluster
void calculateX_Y(Cluster *&quadrant_type, Store *&stores, int &numStores, SalesData *&sales, int &numSales, int &i)
{
    double maximum_sales_amount = DBL_MIN, minimum_sales_amount = DBL_MAX;

    int numberS = quadrant_type[i].storeOuterCount;
    for (int j = 0; j < numberS; j++)
    {

        if (quadrant_type[i].storeOuter[j].sA.totalSalesAmount > maximum_sales_amount)
        {
            maximum_sales_amount = quadrant_type[i].storeOuter[j].sA.totalSalesAmount;
        }

        if (quadrant_type[i].storeOuter[j].sA.totalSalesAmount < minimum_sales_amount)
        {
            minimum_sales_amount = quadrant_type[i].storeOuter[j].sA.totalSalesAmount;
        }
    }
    // According to sales Amount
    quadrant_type[i].subClusterList[0].subCenter.x = maximum_sales_amount;
    quadrant_type[i].subClusterList[2].subCenter.x = minimum_sales_amount;
    quadrant_type[i].subClusterList[1].subCenter.x = (maximum_sales_amount + minimum_sales_amount) / 2.0;

    // according to Avr.sales.amount/Day
    quadrant_type[i].subClusterList[0].subCenter.y = (maximum_sales_amount / 24) / 30;
    quadrant_type[i].subClusterList[2].subCenter.y = (minimum_sales_amount / 24) / 30;
    quadrant_type[i].subClusterList[1].subCenter.y = (((maximum_sales_amount + minimum_sales_amount) / 2.0) / 24 / 30);
}

// calculates Z coordinate for SubCluster
void calculateZ(Cluster *&quadrant_type, Store *&stores, int &numStores, SalesData *&sales, int &numSales, int &i)
{
    int numberS = quadrant_type[i].storeOuterCount;
    int maximum_sales = INT_MIN, minimum_sales = INT_MAX;
    for (int j = 0; j < numberS; j++)
    {

        if (quadrant_type[i].storeOuter[j].totalSales > maximum_sales)
        {
            maximum_sales = quadrant_type[i].storeOuter[j].totalSales;
        }

        if (quadrant_type[i].storeOuter[j].totalSales < minimum_sales)
        {
            minimum_sales = quadrant_type[i].storeOuter[j].totalSales;
        }
    }
}

/**
 * Calculates the Centroids of Clusters on the basis of the Sales
 * , SalesAmount and Profit making 3 coordinates X Y and Z
 */
void calculateSecondTierCentroid(Cluster *&quadrant_type, Store *&stores, int &numStores, SalesData *sales, int numSales)
{
    for (int i = 0; i < 4; i++)
    {
        // calculation
        calculateX_Y(quadrant_type, stores, numStores, sales, numSales, i);

        calculateZ(quadrant_type, stores, numStores, sales, numSales, i);
    }
}

// Euclidean Distance calculation for 3 variable XYZ
double secondTierDistanceCalculation(Cluster *&quadrant_type, int &cluster_number, int &sub_CN, int &storeNumber)
{

    double temp_sales_amount = quadrant_type[cluster_number].storeOuter[storeNumber].sA.totalSalesAmount;
    double temp_profit_amount = quadrant_type[cluster_number].storeOuter[storeNumber].sA.profit;
    double X = pow(quadrant_type[cluster_number].subClusterList[sub_CN].subCenter.x - temp_sales_amount, 2.0);

    double Y = pow(quadrant_type[cluster_number].subClusterList[sub_CN].subCenter.y - temp_sales_amount, 2.0);

    return sqrt(X + Y);
}

// it updates the Centroid of subCluster after every iteration
void updateSecondTierCentroid(Cluster *&quadrant_type, int &cluster_number, int &sub_CN, int &storeNumber)
{
    double temp_sales_amount = quadrant_type[cluster_number].storeOuter[storeNumber].sA.totalSalesAmount;
    double temp_profit_amount = quadrant_type[cluster_number].storeOuter[storeNumber].sA.profit;

    double X[] = {quadrant_type[cluster_number].subClusterList[sub_CN].subCenter.x, temp_sales_amount};
    double Y[] = {quadrant_type[cluster_number].subClusterList[sub_CN].subCenter.y, temp_profit_amount};

    quadrant_type[cluster_number].subClusterList[sub_CN].subCenter.x = (X[0] + X[1]) / 2.0;
    quadrant_type[cluster_number].subClusterList[sub_CN].subCenter.y = (Y[0] + Y[1]) / 2.0;
}

// it starts calculating the second tier clustering
void SecondTierClustering(Cluster *&quadrant_type)
{
    for (int cluster_number = 0; cluster_number < 4; cluster_number++)
    {
        int storeNumbers = quadrant_type[cluster_number].storeOuterCount;
        for (int j = 0; j < storeNumbers; j++)
        {
            int index = -1;
            double minimum_distance = DBL_MAX;

            for (int sub_CN = 0; sub_CN < 3; sub_CN++)
            {
                double distance = secondTierDistanceCalculation(quadrant_type, cluster_number, sub_CN, j);

                if (distance < minimum_distance)
                {
                    minimum_distance = distance;
                    index = sub_CN;
                }
            }
            if (quadrant_type[cluster_number].subClusterList[index].storesList == nullptr)
            {
                quadrant_type[cluster_number].subClusterList[index].storesList = new int[storeNumbers]; // Allocate memory
            }

            // update --------------- centroid
            updateSecondTierCentroid(quadrant_type, cluster_number, index, j);
            int idx = quadrant_type[cluster_number].subClusterList[index].storeListCounter;
            quadrant_type[cluster_number].subClusterList[index].storesList[idx] = quadrant_type[cluster_number].storeOuter[j].sID;
            quadrant_type[cluster_number].subClusterList[index].storeListCounter++;
        }
    }
}

// it is display function of subClusters
void SecondTierDisplay(Cluster *&quadrant_type, const int &num, const int &subCN)
{

    int storeNumber = quadrant_type[num].storeOuterCount;
    int subCcount = quadrant_type[num].subClusterList[subCN].storeListCounter;

    if (subCN == 0)
    {
        cout << "   <--- The Top Performing Stores ---> " << endl;
    }
    else if (subCN == 1)
    {
        cout << "   <--- The Average Performing Stores ---> " << endl;
    }
    else
    {
        cout << "   <--- The Under Performing Stores ---> " << endl;
    }

    for (int i = 0; i < subCcount; i++)
    {
        for (int j = 0; j < storeNumber; j++)
            if (quadrant_type[num].storeOuter[j].sID == quadrant_type[num].subClusterList[subCN].storesList[i])
            {
                cout << " " << i + 1 << " -> Store ID: " << quadrant_type[num].storeOuter[j].sID << "\n     Store Name : " << quadrant_type[num].storeOuter[j].sName << "\n     Total Number of Sale : " << quadrant_type[num].storeOuter[j].totalSales
                     << "\n     Total Amount Earned from Sales : " << quadrant_type[num].storeOuter[j].sA.totalSalesAmount
                     << "\n     Total Profit : " << quadrant_type[num].storeOuter[j].sA.profit << endl;

                break;
            }
    }
}

// It is a Chart of the store on basis of their profits
void TopRankingSetChart(Store *stores, int numStores)
{
    // Allocate dynamic memory for rankings
    ranking *rankings = new ranking[numStores];

    for (int i = 0; i < numStores; i++)
    {
        rankings[i] = {stores[i].sID, i, stores[i].sA.profit};
    }

    // Brute-force sorting (Bubble Sort)
    for (int i = 0; i < numStores - 1; i++)
    {
        for (int j = 0; j < numStores - i - 1; j++)
        {
            if (rankings[j].status < rankings[j + 1].status)
            {
                ranking temp = rankings[j];
                rankings[j] = rankings[j + 1];
                rankings[j + 1] = temp;
            }
        }
    }

    // Display top 10 stores
    int topCount = min(10, numStores);

    // Find max profit for scaling
    double maxProfit = rankings[0].status;

    cout << "\n   <--- Bar Chart (Profit) in Ranking --->\n"
         << endl;
    cout << setw(5) << "ID" << setw(12) << "Profit" << "            Bar Chart" << endl;
    cout << "----------------------------------------------" << endl;

    // Display ranking with horizontal bar chart
    for (int i = 0; i < numStores; i++)
    {
        int barLength = static_cast<int>((rankings[i].status / maxProfit) * 70);
        
        if (barLength <= 0)
        {
            cout << " All The Remaining Stores are in Debt " << endl;
            break;
        }

        if (rankings[i].status > 0)
        {
            cout << "  " << setw(6) << left << rankings[i].ID << "|   " << setw(6) << fixed << setprecision(0) << rankings[i].status << "|";
        }
        else
        {
            cout << "  " << setw(6) << left << rankings[i].ID << "|" << setw(10) << fixed << setprecision(0) << " In Loss |";
        }

        for (int j = 0; j < barLength; j++)
        {
            cout << "=";
        }
        cout << endl;
    }

    delete[] rankings;
}

void option7(Cluster *&quadrant_type)
{
    clearScreen();
    cout << " ------------ Tier 2 Clustering ---------" << endl;

    cout << "   1. Right Upper Cluster " << endl
         << "   2. Left Upper Cluster " << endl
         << "   3. Left Lower Cluster " << endl
         << "   4. Right Lower Cluster " << endl;

    int index;
    cout << "  Enter Choice For Which SubClusters U want to check : ";
    while (true)
    {
        cin >> index;
        if (index == 1 || index == 2 || index == 3 || index == 4)
        {
            break; // Valid input
        }
        cout << " Invalid input! Please enter between 1 to 4 : ";
    }
    index--;
    cout << "  <--- Cluster Name: " << quadrant_type[index].Name
         << " contains " << quadrant_type[index].storeOuterCount << " Stores --->" << endl;

    cout << "  Do you want to check All SUB Clusters or for Only single Cluster  (1/0) : ";
    int check;
    // Input validation loop
    while (true)
    {
        cin >> check;
        if (check == 0 || check == 1)
        {
            break; // Valid input
        }
        cout << " Invalid input! Please enter 1 for all Clusters or 0 for a single Cluster : ";
    }
    if (check == 0)
    {
        cout << "  1. Best Performing Store " << endl
             << "  2. Average Performing Store " << endl
             << "  3. Under Performing Store " << endl;
        cout << " Enter which Cluster of Store U want to see (1/2/3) : ";
        int which = 0;
        while (true)
        {
            cin >> which;
            if (which == 1 || which == 2 || which == 3)
            {
                break;
            }

            cout << " Enter a valid Option : ";
        }
        which--;
        cout << endl;
        clearScreen();
        SecondTierDisplay(quadrant_type, index, which);
    }
    else
    {
        clearScreen();
        for (int i = 0; i < 3; i++)
        {
            SecondTierDisplay(quadrant_type, index, i);
            cout << endl;
        }
    }
    pauseScreen();
}

void option9(Store *&stores, int &numStores)
{
    clearScreen();
    cout << "  Do you want to check all Store Monthly count or for one Store (1/0) : ";
    int che;
    // Input validation loop
    while (true)
    {
        cin >> che;
        if (che == 0 || che == 1)
        {
            break; // Valid input
        }
        cout << "  Invalid input! Please enter 1 for all stores or 0 for a single store: ";
    }

    if (che)
        CustomerSalesDisplay(stores, numStores);
    else
        stores[whichStoreDetail(numStores)].monthlySalesDetail();
    pauseScreen();
}

// it is monthly sales chart of a Store
void monthlySalesStoreChart(Store *&stores, int &numStores)
{
    int choice = whichStoreDetail(numStores);
    int maximum = INT_MIN;
    int *check = new int[24];
    for (int i = 0; i < 24; i++)
    {
        check[i] = stores[choice].monthlySales[i];
        if (maximum < stores[choice].monthlySales[i])
        {
            maximum = stores[choice].monthlySales[i];
        }
    }

    clearScreen();
    cout << "   <--- Chart on Basis of monthly Sales ---> " << endl;

    cout << "\n   (Sale)  " << endl;
    for (int i = maximum; i > 0; i--)
    {
        cout << setw(7) << i << " | ";
        for (int j = 0; j < 24; j++)
        {
            if (i == check[j])
            {
                cout << " * ";
                check[j]--;
            }
            else
            {
                cout << "   ";
            }
        }
        cout << endl;
    }
    cout << " ------+-";
    for (int i = 0; i < 24; i++)
    {
        cout << "---";
    }
    cout << endl
         << " (Month)| ";
    for (int i = 0; i < 24; i++)
    {
        cout << setw(2) << i + 1 << " ";
    }
    cout << "\n ";
    delete[] check;
}

// it cluster Wise chart on the basis of Profit
void ClusterProfitWiseChart(Cluster *&quadrant_type, int clusterNumber)
{

    int size = quadrant_type[clusterNumber].storeOuterCount;

    int *check = new int[size];
    int maximum = 0; // Fixed initialization

    // Store profit values and find the maximum
    for (int i = 0; i < size; i++)
    {
        check[i] = static_cast<int>(quadrant_type[clusterNumber].storeOuter[i].sA.profit);
        if (check[i] > maximum)
        { // Fixed condition
            maximum = check[i];
        }
    }
    cout << endl;

    pauseScreen();
    clearScreen();

    cout << "   <--- Chart on Basis of Same Cluster Store Profit ---> " << endl;
    cout << "\n  (Profit)  " << endl;

    // Print the chart in descending order
    for (int i = maximum; i > 0; i -= 750)
    {
        cout << "  " << setw(5) << i << " | ";
        for (int j = 0; j < size; j++)
        {
            if (check[j] >= i)
            { // Corrected condition
                cout << "  * ";
            }
            else
            {
                cout << "    "; // Maintain spacing
            }
        }
        cout << endl;
    }

    // Print horizontal separator line
    cout << "   -----+-";
    for (int i = 0; i < size; i++)
    {
        cout << "----";
    }
    cout << endl;

    // Print store IDs
    cout << " (Store)| ";
    for (int i = 0; i < size; i++)
    {
        cout << setw(3) << quadrant_type[clusterNumber].storeOuter[i].sID << " ";
    }
    cout << "\n";

    delete[] check; // Free allocated memory
}

// ask user for which cluster
void clusterWiseChart(Cluster *&quadrant_type)
{

    cout << "  1. First Cluster " << endl
         << "  2. Second Cluster " << endl
         << "  3. Third Cluster " << endl
         << "  4. Fourth Cluster " << endl;

    int index;
    cout << "  Enter Choice : ";
    while (true)
    {
        cin >> index;
        if (index == 1 || index == 2 || index == 3 || index == 4)
        {
            break; // Valid input
        }
        cout << "  Invalid input! Please enter between 1 to 4 : ";
    }

    index--;
    ClusterProfitWiseChart(quadrant_type, index);
    pauseScreen();
}

void option10(Store *&stores, int &numStores, SalesData *sales, int numSales, Cluster *&quadrant_type)
{
    clearScreen();
    cout << "  1. Monthly sales Chart of a Store " << endl
         << "  2. Comparative store Performance " << endl
         << "  3. Cluster-wise Profit Distribution " << endl;
    cout << "    Enter Choice : ";
    int choice = 0;
    while (true)
    {
        cin >> choice;

        if (choice >= 1 && choice <= 3)
        {
            break;
        }
        cout << "  Enter a Valid choice (1/2/3) : " << endl;
    }
    if (choice == 1)
    {
        monthlySalesStoreChart(stores, numStores);
    }
    else if (choice == 2)
    {
        TopRankingSetChart(stores, numStores);
    }
    else
    {
        clusterWiseChart(quadrant_type);
    }

    pauseScreen();
}

// Exits
void option11(bool &start)
{
    clearScreen();
    start = false;
    cout << "  Leaving the Program Soon" << endl;
}

// it calculates the prediction of next Month Sales
void workingOfPrediction(Store *&stores, int &numStores, int choice)
{
    cout << "     <---- Prediction of Sales ----> " << endl;
    cout << "      <-----" << stores[choice].sName << "---->       " << endl;

    bool *incOrDec = new bool[21];
    double temp = 0, totalGrowthRate = 0;

    // Calculate moving average and determine trend
    for (int i = 0; i < 21; i++)
    {
        double check = (stores[choice].monthlySales[i] + stores[choice].monthlySales[i + 1] +
                        stores[choice].monthlySales[i + 2] + stores[choice].monthlySales[i + 3]) /
                       4.0;

        incOrDec[i] = (check > temp);
        if (temp != 0) // Avoid division by zero
        {
            totalGrowthRate += ((check - temp) / temp) * 100; // Percentage change
        }

        temp = check;
    }

    // Average growth rate
    double avgGrowthRate = totalGrowthRate / 21.0;

    stores[choice].sF.predictedSales = (temp * 4) - (stores[choice].monthlySales[23] +
                                                     stores[choice].monthlySales[22] +
                                                     stores[choice].monthlySales[21]);

    stores[choice].sF.predictedSales *= (1 + avgGrowthRate / 100.0);

    double pos = 0, neg = 0;
    for (int i = 0; i < 21; i++)
    {
        if (incOrDec[i])
            pos++;
        else
            neg++;
    }

    stores[choice].sF.ConfidencePercentage = max((pos / 21.0) * 100, (neg / 21.0) * 100);

    cout << "  Negative % : " << (neg / 21.0) * 100 << "%" << endl;
    cout << "  Positive % : " << (pos / 21.0) * 100 << "%" << endl;

    stores[choice].sF.warningFlag = ((neg / 21.0) * 100 > 60);

    pos = 0, neg = 0;
    for (int i = 20; i >= 0; i--)
    {
        if (incOrDec[i])
            pos++;
        else
            break;
    }

    for (int i = 20; i >= 0; i--)
    {
        if (!incOrDec[i])
            neg++;
        else
            break;
    }

    if (stores[choice].sF.warningFlag)
        cout << "            ---- Warning Alert -----" << endl;

    if (pos > 0)
        cout << "  The Sales are Increasing Continuously for LAST - " << pos << " Months " << endl;
    else
        cout << "  The Sales are Decreasing Continuously for LAST - " << neg << " Months " << endl;

    cout << "  Growth Rate: " << fixed << setprecision(0) << avgGrowthRate << "%" << endl;
    cout << "  The Predicted Sales for Next Month -> " << static_cast<int>(stores[choice].sF.predictedSales) << " Sales " << endl;
    cout << "  Confidence Level on Prediction: " << stores[choice].sF.ConfidencePercentage << "%" << endl
         << endl;

    pauseScreen();
    delete[] incOrDec;
}

void option8(Store *&stores, int &numStores)
{
    clearScreen();
    cout << "  1. Do you want to check Prediction of Sales for all Stores. \n  2. Want to check a Full Prediction Of One Store  \n  Enter choice : ";

    int check;
    // Input validation loop
    while (true)
    {
        cin >> check;
        if (check == 2 || check == 1)
        {
            break; // Valid input
        }
        cout << "  Invalid input! Please enter 1 for all stores or 2 for a single store: ";
    }

    if (!check)
    {
        int choice = whichStoreDetail(numStores);
        workingOfPrediction(stores, numStores, choice);
    }
    else
    {
        for (int i = 0; i < numStores; i++)
        {
            clearScreen();
            workingOfPrediction(stores, numStores, i);
        }
    }
}

void generator()
{
    cout << " 1. Generate New Data\n"
         << " 2. Use previous Data\n"
         << " Enter choice : ";
    int choice;
    while (true)
    {
        cin >> choice;
        if (choice == 1 || choice == 2)
            break;
        cout << " Enter valid choice (1/2): ";
    }

    if (choice == 1){
        generateStore();
    }

    
}

/**
 * <----------------- All Five Task Are Done ----------------->
 * <------------------------ THE END ------------------------->
 */