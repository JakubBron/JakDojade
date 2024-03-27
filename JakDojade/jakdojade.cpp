#include <utility>
#include "Vector.h"
#include "Map.h"
#include "constants.hpp"
#include "helpers.h"
#include "workers.h"

#include <stdlib.h>
#include <stdio.h>

int main()
{
    int n, m, airRoutes = 0;
    scanf("%d %d\n", &n, &m);
    char** map;
    int** mapVisited;
    map = new char*[m];
    mapVisited = new int* [m];
    char lastReaded = 0;
    Vector<char>* names = new Vector<char>[n*m];
    pairInt* namesLocalisation = new pairInt[n*m];
    city* cities = new city[n*m];
    int* miasta = new int[n * m];
    UnorderedMap<int> namesHash;

    bool flag = false;

    int iter = 0;
    int iterCities = 0;
    bool cityNamePresent = false;

    for (int i = 0; i < n*m; i++)
    {
        cities[i].id = NEUTRAL_INT;
        cities[i].parentId = NEUTRAL_INT;
        miasta[i] = NEUTRAL_INT;
    }

    for (int i = 0; i < m; i++)
    {
        map[i] = new char[n];
        mapVisited[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            mapVisited[i][j] = NEUTRAL_INT;
            map[i][j] = getchar();
            if (map[i][j] >= 'A' || (map[i][j] >= '0' && map[i][j] <= '9'))
            {
                if (names[iter].size() == 0)
                {
                    namesLocalisation[iter].first = pointToInt(i, j, n);
                    namesLocalisation[iter].second = pointToInt(i, j, n);
                    names[iter].push_back(std::move(map[i][j]));
                    cityNamePresent = true;
                }
                else if (names[iter].size() > 0)
                {
                    names[iter].push_back(std::move(map[i][j]));
                    namesLocalisation[iter].second = pointToInt(i, j, n);
                    cityNamePresent = true;
                }
            }
            else if(names[iter].size() > 0)
            {
                iter++;
            }
            
            if (map[i][j] == '*')
            {
                miasta[pointToInt(i, j, n)] = iterCities;

                cities[iterCities].positionInt = pointToInt(i, j, n);
                cities[iterCities].id = iterCities;
                iterCities++;
            }
            
            lastReaded = map[i][j];    
        }

        getchar();
        lastReaded = 0;
    }
    
    if (cityNamePresent == true && iter == 0)
    {
        iter++;
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector<char> name;
    for (int i = 0; i < iter; i++)
    {
        int strBegg = namesLocalisation[i].first;
        int strEnd = namesLocalisation[i].second;
        name = std::move(names[i]);
        pairInt strBeg1 = intToPoint(strBegg, n);
        pairInt strEnd1 = intToPoint(strEnd, n);

        for (int x = -1; x <= 1; x++)
        {
            for (int y = -1; y <= 1; y++)
            {
                if (x == 0 && y == 0)
                    continue;

                if (strBeg1.first + x >= 0 && strBeg1.first + x < m && strBeg1.second + y >= 0 && strBeg1.second + y < n &&
                    miasta[pointToInt(strBeg1.first + x, strBeg1.second + y, n)] != NEUTRAL_INT)
                {
                    namesHash[name] = miasta[pointToInt(strBeg1.first + x, strBeg1.second + y, n)];
                    cities[miasta[pointToInt(strBeg1.first + x, strBeg1.second + y, n)]].name = std::move(name);
                    break;
                }

                if (strEnd1.first + x >= 0 && strEnd1.first + x < m && strEnd1.second + y >= 0 && strEnd1.second + y < n &&
                    miasta[pointToInt(strEnd1.first + x, strEnd1.second + y, n)] != NEUTRAL_INT)
                {
                    namesHash[name] = miasta[pointToInt(strEnd1.first + x, strEnd1.second + y, n)];
                    cities[miasta[pointToInt(strEnd1.first + x, strEnd1.second + y, n)]].name = std::move(name);
                    break;
                }
            }
        }
    }
    

    // Starting BFS
    Vector<graphNode>* graph = new Vector<graphNode>[iterCities];
    for (int i = 0; i < iterCities; i++)
    {
        BFS(i, intToPoint(cities[i].positionInt, n), graph, mapVisited, map, miasta, m, n, cities);
    }
    // Ending BFS

    // Reading air-routes
    scanf("%d\n", &airRoutes);
    Vector<char> arg1, arg2;
    int arg3 = NEUTRAL_INT;
    for (int i = 0; i < airRoutes; i++)
    {
        arg1.resize(0);
        arg2.resize(0);
        char read = '.';
        while (read != ' ')
        {
            read = getchar();
            if (read != ' ')
            {
                arg1.push_back(std::move(read));
            }
            else
                break;
        }
        read = '.';
        while (read != ' ')
        {
            read = getchar();
            if (read != ' ')
            {
                arg2.push_back(std::move(read));
            }
            else
                break;
        }
        scanf("%d\n", &arg3);

        int miasto1 = namesHash[arg1];
        int miasto2 = namesHash[arg2];

        graphNode temp;
        temp.cityId = miasto2;
        temp.distance = arg3;
        graph[miasto1].push_back(std::move(temp));
        
    }

    // Answering questions
    int query;
    scanf("%d\n", &query);
    arg3 = NEUTRAL_INT;
    bool* visited = new bool[iterCities];
    for (int i = 0; i < query; i++)
    {
        arg1.resize(0);
        arg2.resize(0);
        char read = '.';
        while (read != ' ')
        {
            read = getchar();
            if (read != ' ')
            {
                arg1.push_back(std::move(read));
            }
            else
                break;
        }
        read = '.';
        while (read != ' ')
        {
            read = getchar();
            if (read != ' ')
            {
                arg2.push_back(std::move(read));
            }
            else
                break;
        }
        scanf("%d\n", &arg3);

        int idStart = namesHash[arg1];
        int idEnd = namesHash[arg2];

        if (idStart == idEnd)
        {
            printf("0\n");
        }
        else
        {
            Dijkstra(idStart, idEnd, arg3, graph, visited, iterCities, iterCities + 15 + i, cities, flag);
        }
        
        for (int j = 0; j < iterCities; j++)
        {
            cities[j].parentId = NEUTRAL_INT;
        }
    }
    delete[] visited;
    
////////////////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < m; i++)
    {
        delete[] map[i];
        delete[] mapVisited[i];
    }
    delete[] map;
    delete[] mapVisited;
    delete[] names;
    delete[] namesLocalisation;
    delete[] cities;
    delete[] miasta;
    delete[] graph;
    return 0;
}


