#pragma once
#include <stdlib.h>
#include <iostream>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string>
#include <fstream>

#pragma comment (lib, "Ws2_32.lib")

using namespace std;
#define DEFAULT_BUFLEN 256
std::string ANSWER;

void insertData(string key, string data, string info);
string readData(string key);
void updateData(string key, string data, string info);
void deleteData(string key, string data);
void deleteAcc(string key);