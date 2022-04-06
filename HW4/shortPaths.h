#ifndef SHORTPATH_H_
#define SHORTPATH_H_

#include <queue>
#include "myHeap.full.h"  // This is my version of HW 2.  You can include your own binary heap

#define LARGE1 9999999

using namespace std;


struct arc {
    struct arc *next;
    int length;
    int end;
};

typedef struct node {
    struct arc *first; /* first arc in linked list */
    int id;  // The number of the vertex in this node
    int key;  /* Distance estimate, named key to reuse heap code*/
    int P;  /* Predecessor node in shortest path */
    int position;  /* Position of node in heap, from 0 to Nm, where 0 is best */
} nodeitem;

void BellmanFord(nodeitem N[], int Or, int Nm) {
    // You program this, a  Bellman Ford algorithm that uses a work queue.  
    // DO NOT implement this as 3 for loops.
    // That can be very slow, and waste many iterations.

    // March 23rd slide 59 "Better Bellman-Ford Implementation"
    // Initialize D[s] = 0; D[v] = inf; pred[v] = null
    int u, v, curr_v;
    queue<int> work_queue;
    N[Or].position = 1;
    N[Or].key = 0;
    work_queue.push(Or);

    struct arc *curr_edge;
    // While Q is not empty:
    while(work_queue.size() != 0) {
        // Select u out of queue, mark inqueue[u] = false 
        u = work_queue.front();
        N[u].position = -1;
        work_queue.pop();
        // For each edge (u,v) in E:
        curr_edge = N[u].first;
        while(curr_edge != NULL) {
            // If D[v] > D[u] + w(u, v)
            v = curr_edge->end;
            curr_v = N[u].key + curr_edge->length;
            if(N[v].key > curr_v) {
                // Set D[v] = D[u] + w(u, v)
                N[v].key = curr_v;
                // Set pred[v] = u
                N[v].P = u;
                // if inqueue[v] = false 
                if(N[v].position == -1) {
                    // add v to Q
                    work_queue.push(v);
                    // mark inqueue[v] = true
                    N[v].position = 1;
                }
            }
            if(curr_edge->next == NULL) break;
            // // For each edge (u,v) in E:
            else curr_edge = curr_edge->next;
        }
    }

}/* end Bellman-Ford */


void Dijkstra(nodeitem N[], int Or, int Nm) {
    int Mark[Nm + 1];
    struct arc *edge;
    int v, dv, min_d, min_v, finished;
    for (int i = 1; i <= Nm; i++) {
        Mark[i] = -1;
    }
    N[Or].key = 0;
    Mark[Or] = 1;
    finished = 1;
    min_v = Or;
    min_d = 0;
    while (finished < Nm) {
        edge = N[min_v].first;  //update distances
        while (edge != NULL) { // explore the outgoing arcs of u
            v = edge->end;
            dv = min_d + edge->length;
            if (N[v].key > dv) {
                N[v].key = dv;
                N[v].P = min_v;
            }//if D > dv
            edge = edge->next;
        }// while edge

        min_d = LARGE1;
        for (int j = 0; j <= Nm; j++) {
            if (Mark[j] < 1) {
                if (N[j].key < min_d) {
                    min_d = N[j].key;
                    min_v = j;
                }
            }
        }
        Mark[min_v] = 1;
        finished++;
    }
} /* end Dijkstra */


void DijkstraHeap(nodeitem N[], int Or, int Nm) {
    Heap<nodeitem> *thisHeap;
    struct arc *edge;
    nodeitem *node;

    // You write a Dijkstra algorithm using a binary heap; you can reuse the one from HW 2 with minor variations

    // March 23rd slide 33
    // https://www.geeksforgeeks.org/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/


} /* end DijkstraHeap */
#endif
