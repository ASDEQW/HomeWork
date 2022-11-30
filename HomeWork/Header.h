#pragma once
#include <vector>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
#include "time.h"

using namespace std;

vector <int> algoritm_floyda(vector <vector<int>>& a);
vector <int> algoritm_li(vector <vector<bool>>& a);
vector <vector<int>> form_matrix_int(int n);
vector <vector<bool>> form_matrix_bool(int n);
vector <int> AStar_Algo(vector<vector<int>> graph);
vector <int> algoritm_forda_belmana(vector <vector<int>>& a);
vector <int> Dijkstra(vector <vector<int>>& a);
