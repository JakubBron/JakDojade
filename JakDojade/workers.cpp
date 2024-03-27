#include "workers.h"
#include "PriorityQueue.h"
#include "constants.hpp"
#include "limits.h"
#include <stdio.h>

void BFS(int markerVisited, pairInt start, Vector<graphNode>* graph, int** visited, char** map, int* miasta, int m, int n, city* cities)
{
    struct ToVisit {
        pairInt pos;
        int dist;
    };

    Queue<ToVisit> q; // { {x, y}, dystans}
    q.push({ start, 0 });
    visited[start.first][start.second] = markerVisited;

    while (!q.empty())
    {
        pairInt currentPosition = q.front().pos;
        int currentDistance = q.front().dist;
        q.pop();

        if (map[currentPosition.first][currentPosition.second] == '*' && (currentPosition.first != start.first || currentPosition.second != start.second))
        {
            graphNode node;
            node.distance = currentDistance;
            node.cityId = miasta[pointToInt(currentPosition.first, currentPosition.second, n)];

            graph[miasta[pointToInt(start.first, start.second, n)]].push_back(std::move(node));
            continue;
        }

        pairInt changes[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

        for (auto change : changes)
        {
            if (currentPosition.first + change.first >= 0 && currentPosition.first + change.first < m &&
                currentPosition.second + change.second >= 0 && currentPosition.second + change.second < n &&
                map[currentPosition.first + change.first][currentPosition.second + change.second] < '.' &&
                visited[currentPosition.first + change.first][currentPosition.second + change.second] < markerVisited)
            {

                q.push({ {currentPosition.first + change.first, currentPosition.second + change.second}, currentDistance + 1 });
                visited[currentPosition.first + change.first][currentPosition.second + change.second] = markerVisited;
            }
        }
    }
}

void Dijkstra(int start, int end, int printPath, Vector<graphNode>* graph, bool visited[], int size, int marker, city* cities, bool flag)
{
    struct pair3 {
        int distance;
        int prevVertex;
        int parentId;

        bool operator < (const pair3& other) const
        {
            return (distance > other.distance);
        }
    };

    int* distances = new int[size];
    for (int i = 0; i < size; i++)
        distances[i] = INT_MAX;

    distances[start] = 0;
    PriorityQueue< pair3 >pq; // {distance, prevVertex, parentId }
    pair3 pairStart = { 0, start, -1 };
    pq.push( std::move(pairStart) );
    int dist, dest, parent;
    while (!pq.empty())
    {
        dist = pq.top().distance;
        dest = pq.top().prevVertex;
        parent = pq.top().parentId;
        pq.pop();

        if (cities[dest].parentId == NEUTRAL_INT)
        {
            cities[dest].parentId = parent;
        }

        if (visited[dest] == true)
            continue;

        if (dest == end)
        {
            break;
        }

        for (int i = 0; i < graph[dest].size(); i++)
        {
            if (visited[graph[dest][i].cityId] == true)
                continue;
            if (distances[graph[dest][i].cityId] > dist + graph[dest][i].distance)
            {
                distances[graph[dest][i].cityId] = dist + graph[dest][i].distance;
                pq.push({ distances[graph[dest][i].cityId], graph[dest][i].cityId, dest });
            }
        }
    }


    printf("%d ", distances[end]);
    if (printPath == 1 && flag == false)
    {
        Vector<int> visitedCities;
        int currentCity = end;
        while (currentCity != start)
        {
            if (currentCity < 0)
            {
                throw currentCity;
            }
            currentCity = cities[currentCity].parentId;
            visitedCities.push_back(std::move(currentCity) );
        }
        for (int i = visitedCities.size() - 2; i >= 0; i--)
        {
            for(int j=0; j<cities[visitedCities[i]].name.size(); j++) {
                putchar(cities[visitedCities[i]].name[j]);
            } 
            putchar(' ');
        }
    }
    printf("\n");
    delete[] distances;

    return;
}
