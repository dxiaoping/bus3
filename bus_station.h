//
// Created by ƽ on 2017/12/31.
//

#ifndef BUS_BUS_STATION_H
#define BUS_BUS_STATION_H

#endif //BUS_BUS_STATION_H


#define MAX 100
#define road_max 20

//վ����Ϣ
typedef struct info{
    char name[10]; //վ������
    int number; //վ�����
    int road[road_max];
    struct info *next;
}stationInfo;


//������Ϣ
typedef struct bus{
    int bus_name;
    int station_number;
    stationInfo *stationInfoName;
}busLine;


//����ͼ
typedef struct {
    busLine AllBusLine[MAX];
    int line_number;
}bus_management;


bus_management* CreateBusGraph(bus_management *bus_management1);
void AddLine(bus_management *bus_management1);
void AddStation(bus_management *bus_management1);
void DeleteStation(bus_management *bus_management1);
void modifyStation(bus_management *bus_management1);
bus_management* load_bus_File();
void road_management(bus_management *bus_management1);
void visit_line(bus_management *bus_management1);
void save_bus_management(bus_management *bus_management1);
void search_line(bus_management *management1);
void search_station(bus_management *management1);
void search_load(bus_management *management1);
void DFS(bus_management *management1, char station1[10], char station2[10]);