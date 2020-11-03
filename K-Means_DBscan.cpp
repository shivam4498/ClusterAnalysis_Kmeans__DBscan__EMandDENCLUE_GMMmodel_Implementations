#include <bits/stdc++.h>
#define dd long double
using namespace std;
#define k 3
#define maxim 1000000
#define mindiff 0.001
#define maxDBeps 0.6
#define minpoints 3
// ************************************************* K-Means Algorithm***********************************************

void takeinputdataset(vector<vector<dd>> &mydataset,map<vector<dd>,string> &originalclass)
{
    ifstream in("irisdataset.txt");
    string str;
    vector<dd> temp;

    while (getline(in, str))
    {   string classs;
        temp.clear();
        while (str.size())
        {
            string flag;
            if (str.find(',') != -1)
            {
                flag = str.substr(0, str.find(','));
                temp.push_back(stod(flag));
                str = str.substr(str.find(',') + 1, str.length() - str.find(',') - 1);
            }
            else
            {   classs=str;
                str = "";
            }
        }
        mydataset.push_back(temp);
        originalclass[temp]=classs;
        //cout<<classs<<"\n";
    }
}

void showdataset(vector<vector<dd>> mydataset)
{
    for (int i = 0; i < mydataset.size(); i++)
    {
        for (int j = 0; j < mydataset[i].size(); j++)
            cout << mydataset[i][j] << " ";
        cout << "\n";
    }
}
void show(map<vector<dd>,string> classs)
{ // cout<<"YYYessssssssssss";
  for(auto itr=classs.begin();itr!=classs.end();itr++){
      cout<<itr->second<<" ";
      for(int i=0;i<itr->first.size();i++)
      cout<<itr->first[i];
  }
}

void calculateSSE(vector<dd> mean[k], vector<vector<dd>> cluster[k])
{
    dd SSE = 0;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < cluster[i].size(); j++)
        {
            for (int p = 0; p < mean[0].size(); p++)
            {
                SSE += (long double)pow(cluster[i][j][p] - mean[i][p], 2);
            }
        }
    }
    cout << "For the " << k << " Number of cluster total SSE: " << SSE << "\n";
    freopen("output.txt", "w", stdout);
    for (int i = 0; i < k; i++)
    {
        cout << "Cluster-" << i + 1 << " {\n";
        for (int j = 0; j < cluster[i].size(); j++)
        {
            for (int p = 0; p < mean[0].size(); p++)
            {
                cout << cluster[i][j][p] << " ";
            }
            cout << "\n";
        }
        cout << "\n}\n\n";
    }
}

// ********************************************************************************************************************
dd distance(vector<dd> v1, vector<dd> v2)
{
    dd dis = 0;
    for (int i = 0; i < v1.size(); i++)
        dis += (long double)pow(v1[i] - v2[i], 2);
    return (long double)pow(dis, 0.5);
}

void DENSITY_CONNECTED(map<vector<dd>, vector<vector<dd>>> &Eneighbours, set<vector<dd>> &corepoints, map<vector<dd>, int> &assign, vector<dd> core, vector<vector<dd>> &neighbour, int currcluster)
{
    for (int i = 0; i < neighbour.size(); i++)
    {
        if (!assign[neighbour[i]])
        {
            assign[neighbour[i]] = currcluster;
            if (corepoints.count(neighbour[i]))
                DENSITY_CONNECTED(Eneighbours, corepoints, assign, neighbour[i], Eneighbours[neighbour[i]], currcluster);
        }
    }
}

// ****************************************************************************************************************************

void ClassificationError( vector<vector<dd>> cluster[],map<vector<dd>,string> originalclass,int kk,dd totalpp){
    int error=0;
    dd total=0;
    map<string,int> map;
    for(int i=0;i<kk;i++){
        map.clear();
        total+=cluster[i].size();
        if(cluster[i].size()){
            for(int j=0;j<cluster[i].size();j++){
                if(map.count(originalclass[cluster[i][j]])){
                    map[originalclass[cluster[i][j]]]++;
                }
                else{
                 map[originalclass[cluster[i][j]]]=1;
                }
            }
        }
        int max=0;
        for(auto itr=map.begin();itr!=map.end();itr++){
            if(itr->second>max)
            max=itr->second;
        }
        error+=(cluster[i].size()-max);
    }

cout<<"Total Classification Error points: "<<error<<"\n";
total*=1.0;

dd acc=(total-error);
acc=acc/totalpp;
acc*=100;
cout<<"Accuracy: "<<acc<<"%\n";
}

int main()
{
    vector<vector<dd>> mydataset;
    map<vector<dd>,string> originalclass;
    takeinputdataset(mydataset,originalclass);
    dd totalpoints=mydataset.size();
    // show(originalclass);
    int opp = 0;
    cout << "Operation-1: for K-Means Algorithm\n";
    cout << "Operation-2: for DB-Scan Algorithm\n";
    cout << "Enter the operation: ";
    cin >> opp;
    if (opp == 1)
    {
        vector<dd> mean[k];
        vector<dd> currmean[k];
        vector<vector<dd>> cluster[k];
        int dim = mydataset[0].size();
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < mydataset[i].size(); j++)
            {
                mean[i].push_back(mydataset[i][j]);
            }
        }
        dd SSE = maxim;
        int cc = 0;
        while (SSE > mindiff)
        {
            cc++;
            for (int i = 0; i < k; i++)
            {
                cluster[i].clear();
                currmean[i].clear();
            }
            int clusterno = 0;
            dd mindis = maxim;
            dd currdis = 0;

            for (int i = 0; i < mydataset.size(); i++)
            {
                currdis = 0;
                mindis = maxim;
                for (int j = 0; j < k; j++)
                {
                    currdis = 0;
                    for (int p = 0; p < mydataset[i].size(); p++)
                    {
                        dd dis = mydataset[i][p] - mean[j][p];
                        currdis += (long double)pow(dis, 2);
                    }
                    if (currdis < mindis)
                    {
                        mindis = currdis;
                        clusterno = j;
                    }
                }
                cluster[clusterno].push_back(mydataset[i]);
            }
            for (int i = 0; i < k; i++)
            {
                currdis = 0;
                for (int j = 0; j < dim; j++)
                {
                    currdis = 0;
                    for (int p = 0; p < cluster[i].size(); p++)
                    {
                        currdis += cluster[i][p][j];
                    }
                    if (cluster[i].size())
                        currmean[i].push_back(currdis / cluster[i].size());
                    else
                    {
                        currmean[i].push_back(0);
                    }
                }
            }

            currdis = 0;
            for (int i = 0; i < k; i++)
            {
                for (int j = 0; j < dim; j++)
                {
                    dd dis = mean[i][j] - currmean[i][j];
                    currdis += (long double)pow(dis, 2);
                    mean[i][j] = currmean[i][j];
                }
            }
            SSE = currdis;
          //  cout << SSE << "\n";
        }

       cout<<"Total no of iterations: "<<cc<<"\n";
       cout<<"Final mean values: \n";
       for(int i=0;i<k;i++){
           cout<<"Cluster-"<<i+1<<"[ ";
           for(int j=0;j<dim;j++){
            cout<<mean[i][j]<<" ";
           }
           cout<<"]\n";
       }
        ClassificationError(cluster,originalclass,k,totalpoints);
        calculateSSE(mean, cluster);
    }

    else
    {

        set<vector<dd>> se;
        for (int i = 0; i < mydataset.size(); i++)
            se.insert(mydataset[i]);
        int duplicate = mydataset.size() - se.size();
        dd dim = mydataset[0].size();
        map<vector<dd>, int> assign;
        for (int i = 0; i < mydataset.size(); i++)
            assign[mydataset[i]] = 0;
        set<vector<dd>> corepoints;
        map<vector<dd>, vector<vector<dd>>> Eneighbours;
        for (int i = 0; i < mydataset.size(); i++)
        {
            int curr = 0;
            for (int j = 0; j < mydataset.size(); j++)
            {
                if (distance(mydataset[i], mydataset[j]) <= maxDBeps)
                {
                    Eneighbours[mydataset[i]].push_back(mydataset[j]);
                    curr++;
                }
            }
            if (curr >= minpoints)
                corepoints.insert(mydataset[i]);
        }

        int currcluster = 1;
        int totalcore = corepoints.size();
        for (auto itr = corepoints.begin(); itr != corepoints.end(); itr++)
        {
            if (!assign[*itr])
            {
                assign[*itr] = currcluster;
                DENSITY_CONNECTED(Eneighbours, corepoints, assign, *itr, Eneighbours[*itr], currcluster);
                currcluster++;
            }
        }
        int curr = 0;
        for (auto itr = assign.begin(); itr != assign.end(); itr++)
        {
            if (!itr->second)
                curr++;
        }
        int tnoise = curr;
        int tborder = mydataset.size() - corepoints.size() - tnoise - duplicate;
        cout << "Total Sample points: " << mydataset.size() << "\n";
        cout << "Total Core-Points for Range " << maxDBeps << " are: " << corepoints.size() << "\n";
        cout << "Total Border-Points are: " << tborder << "\n";
        cout << "Total Noise-Points are: " << tnoise << "\n";
        cout << "Total duplicate points: " << duplicate << "\n";
        cout << "Total Clusters: " << currcluster - 1 << "\n";
        vector<vector<dd>> cluster[currcluster-1];
        multimap<int, vector<dd>> classs;
        for (auto itr = assign.begin(); itr != assign.end(); itr++)
        {
            if (itr->second){
                classs.insert({itr->second, itr->first});
            cluster[itr->second-1].push_back(itr->first);
            }
                
        }
        ClassificationError(cluster,originalclass,currcluster-1,totalpoints);
        curr = 0;
        freopen("output.txt", "w", stdout);
        for (auto itr = classs.begin(); itr != classs.end(); itr++)
        {
            if (itr->first == curr)
            {
                for (int i = 0; i < itr->second.size(); i++)
                    cout << itr->second[i] << " ";
                cout << "\n";
            }
            else
            {
                if (curr)
                    cout << " }*******************************************\n";
                curr++;
                cout << "Cluster-" << curr << ": { \n";
                for (int i = 0; i < itr->second.size(); i++)
                    cout << itr->second[i] << " ";
                cout << "\n";
            }
        }
    }

    return 0;
}
