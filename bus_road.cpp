//
// Created by 平 on 2017/12/31.
//

#include "bus.h"
#include "bus_station.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bus_management* CreateBusGraph(bus_management *bus_management1){
    bus_management1 = (bus_management*)malloc(sizeof(bus_management));
    bus_management1->line_number = 0;
    return bus_management1;
}

void AddLine(bus_management *bus_management1){
    int road;
    std::cout << "请输入线路的名称" << std::endl;
    std::cin >> road;
    for(int i=0; i < bus_management1->line_number; i++){
        if(bus_management1->AllBusLine[i].bus_name == road){
            std::cout << "该路线已经存在" <<std::endl;
            return;
        }
    }
    bus_management1->AllBusLine[bus_management1->line_number].bus_name = road;
    bus_management1->AllBusLine[bus_management1->line_number].station_number = 0;
    bus_management1->AllBusLine[bus_management1->line_number].stationInfoName = NULL;
    bus_management1->line_number++;
    save_bus_management(bus_management1);
}

void AddStation(bus_management *bus_management1){
    int i;
    std::cout << "请输入在哪条路线上添加站点" <<std::endl;
    std::cin >> i;
    for (int j = 0; j < bus_management1->line_number; j++) {
        if (bus_management1->AllBusLine[j].bus_name ==i){
            stationInfo *stationInfo1 = bus_management1->AllBusLine[j].stationInfoName;
            while (stationInfo1){
                stationInfo1 = stationInfo1->next;
            }
            stationInfo *station = (stationInfo*)malloc(sizeof(stationInfo));
            std::cout << "请输入站点名称" << std::endl;
            std::cin >> station->name;
            stationInfo *top;
            top = bus_management1->AllBusLine[j].stationInfoName;
            while(top){
                if(strcmp(bus_management1->AllBusLine[j].stationInfoName->name,station->name) ==0){
                    std::cout << "该站点已经存在" <<std::endl;
                    return;
                }
                top =top->next;
            }
            if(bus_management1->AllBusLine[j].station_number==0)station->number = bus_management1->AllBusLine[j].bus_name*100
                                                                                  +bus_management1->AllBusLine[j].station_number;
            else station->number = bus_management1->AllBusLine[j].stationInfoName->number+1;
            station->next = bus_management1->AllBusLine[j].stationInfoName;
            bus_management1->AllBusLine[j].stationInfoName = station;
            bus_management1->AllBusLine[j].station_number++;
        }
        else if(j==bus_management1->line_number)
            std::cout<< "该路线不存在" <<std::endl;
    }
    save_bus_management(bus_management1);
}

void DeleteStation(bus_management *bus_management1){
    int line_name;
    stationInfo *stationInfo1,*PreStationInfo;
    int stationNumber;
    std::cout << "请输入线路的名称" << std::endl;
    std::cin >> line_name;
    for(int i=0; i<bus_management1->line_number;i++){
        if (bus_management1->AllBusLine[i].bus_name == line_name){
            std::cout << "请输入站点的序号" << std::endl;
            std::cin >> stationNumber;
            PreStationInfo = stationInfo1 = bus_management1->AllBusLine[i].stationInfoName;
            while (stationInfo1){
                if (bus_management1->AllBusLine[i].stationInfoName->number == stationNumber){
                    bus_management1->AllBusLine[i].stationInfoName = stationInfo1->next;
                    bus_management1->AllBusLine[i].station_number--;
                    save_bus_management(bus_management1);
                    return;
                } else if (stationInfo1->number == stationNumber){
                    PreStationInfo->next = stationInfo1->next;
                    bus_management1->AllBusLine[i].station_number--;
                    save_bus_management(bus_management1);
                    return;
                }
                PreStationInfo = stationInfo1;
                stationInfo1 = stationInfo1->next;
            }
        }
    }
}

void modifyStation(bus_management *bus_management1){

}

void road_management(bus_management *bus_management1){
    while(1){
        printf("1.增加线路\n");
        printf("2.增加站点\n");
        printf("3.删除站点\n");
        printf("4.退出\n");
        int choice;
        std::cin >> choice;
        //bus_management1 = load_bus_File();
        switch (choice){
            case 1:AddLine(bus_management1);
                visit_line(bus_management1);
                break;
            case 2:visit_line(bus_management1);
                AddStation(bus_management1);
                break;
            case 3:visit_line(bus_management1);
                DeleteStation(bus_management1);
                break;
            case 4:
                return;
            default:printf("输入有误");
                break;
        }
    }

}

void visit_line(bus_management *bus_management1){
    for (int i = 0; i < bus_management1->line_number ; i++) {
        printf("线路：%d------",bus_management1->AllBusLine[i].bus_name);
        stationInfo *stationInfo1 = bus_management1->AllBusLine[i].stationInfoName;
        while (stationInfo1){
            printf("%d:%s-",stationInfo1->number,stationInfo1->name);
            stationInfo1 = stationInfo1->next;
        }
        printf("\n");
    }
}

void save_bus_management(bus_management *bus_management1){
    FILE *bus_data=NULL;
    bus_data=fopen("bus_data.txt","wt");
    fwrite(bus_management1, sizeof(bus_management),1,bus_data);
    for (int i = 0; i < bus_management1->line_number; ++i) {
        stationInfo *tempRoad = bus_management1->AllBusLine[i].stationInfoName;
        while (tempRoad){
            fwrite(tempRoad, sizeof(stationInfo),1,bus_data);
            tempRoad = tempRoad->next;
        }
    }
    fclose(bus_data);
}

bus_management* load_bus_File(){
    bus_management *bus_management1 = CreateBusGraph(bus_management1);
    FILE *bus_data;
    if(fopen("bus_data.txt","r")!=NULL)
    {
        bus_data=fopen("bus_data.txt","r");
        fread(bus_management1, sizeof(bus_management),1,bus_data);
        for (int i = 0; i <bus_management1->line_number; ++i) {
            bus_management1->AllBusLine[i].stationInfoName = NULL;
            for (int j = 0; j <bus_management1->AllBusLine[i].station_number; ++j) {

                stationInfo *tempRoad = (stationInfo *)malloc(sizeof(stationInfo));
                fread(tempRoad, sizeof(stationInfo),1,bus_data);
                tempRoad->next = bus_management1->AllBusLine[i].stationInfoName;
                bus_management1->AllBusLine[i].stationInfoName= tempRoad;
            }
        }
        fclose(bus_data);
    }
    return bus_management1;
}

void search_station(bus_management *management1) {
    char stationName[10];
    printf("请输入站点的名称");
    std::cin >> stationName;
    for (int i = 0; i < management1->line_number ; ++i) {
        stationInfo *stationInfo1 = management1->AllBusLine[i].stationInfoName;
        while (stationInfo1){
            if (strcmp(stationInfo1->name,stationName) == 0){
                printf("经过的公交为：%d\n",management1->AllBusLine[i].bus_name);
            }
            stationInfo1 = stationInfo1->next;
        }
    }
}

void search_line(bus_management *management1) {
    int line;
    std::cout << "请输入公交线路" <<std::endl;
    std::cin >> line;
    for (int i = 0; i <management1->line_number ; ++i) {
        if (management1->AllBusLine[i].bus_name == line){
            stationInfo *stationInfo1 = management1->AllBusLine[i].stationInfoName;
            while (stationInfo1){
                printf("%d,%s\n",stationInfo1->number,stationInfo1->name);
                stationInfo1=stationInfo1->next;
            }
        }
    }
}

void search_load(bus_management *management1) {
    stationInfo *station1,*station2;
    station1 = (stationInfo*)malloc(sizeof(stationInfo));
    station2 = (stationInfo*)malloc(sizeof(stationInfo));
    printf("请输入第一个站点的");
    std::cin >> station1->name;
    printf("请输入第二个站点");
    std::cin >> station2->name;
    DFS(management1,station1,station2);
}

void DFS(bus_management *management1, stationInfo *station1, stationInfo *station2) {
    int road_count=0;
    int road_count2=0;
    int line1[20],line2[20];
    for (int i = 0; i < management1->line_number ; ++i) {
        stationInfo *stationInfo1 = management1->AllBusLine[i].stationInfoName;
        while (stationInfo1){
            if (strcmp(stationInfo1->name,station1->name) == 0){
                station1->road[road_count] = management1->AllBusLine[i].bus_name;
                line1[road_count] = i;
                road_count++;
            }
            stationInfo1 = stationInfo1->next;
        }
    }
    for (int i = 0; i < management1->line_number ; ++i) {
        stationInfo *stationInfo2 = management1->AllBusLine[i].stationInfoName;
        while (stationInfo2){
            if (strcmp(stationInfo2->name,station2->name) == 0){
                station2->road[road_count2] = management1->AllBusLine[i].bus_name;
                line2[road_count2] = i;
                road_count2++;
            }
            stationInfo2 = stationInfo2->next;
        }
    }
//    for (int j = 0; j < road_count; ++j) {
//        std::cout<<station1->road[j]<<std::endl;
//        std::cout<<line1[j]<<std::endl;
//    }
//    for (int j = 0; j < road_count2; ++j) {
//        std::cout<<station2->road[j]<<std::endl;
//        std::cout<<line2[j]<<std::endl;
//    }
    for (int  k = 0; k < road_count; ++k) {
        stationInfo *station_1=management1->AllBusLine[line1[k]].stationInfoName;
        while(station_1){
            if(strcmp(station1->name,station_1->name)==0){
                station1 = station_1;
                break;
            }
            station_1 = station_1->next;
        }
        for (int i = 0; i < road_count2; ++i) {
            stationInfo *station_2=management1->AllBusLine[line2[i]].stationInfoName;
            while(station_2){
                if(strcmp(station2->name,station_2->name) == 0){
                    station2 = station_2;
                    break;
                }
                station_2 = station_2->next;
            }
            if (management1->AllBusLine[line1[k]].bus_name == management1->AllBusLine[line2[i]].bus_name){
                while(station_1!=station_2){
                    printf("%s->",station_1->name);
                    station_1 = station_1->next;
                }
                std::cout << station_1->name <<std::endl;
                continue;
            }
            stationInfo *stationInfo1=management1->AllBusLine[line1[k]].stationInfoName;
            stationInfo *stationInfo2;
            while(stationInfo1){
                bool if_exit= false;
                stationInfo2 = management1->AllBusLine[line2[i]].stationInfoName;
                while (stationInfo2){
                    if(strcmp(stationInfo1->name,stationInfo2->name)==0&&station1->number >= stationInfo1->number&&stationInfo2->number >= station2->number){
                        printf("\n");
                    std::cout <<"找到一条换乘方式"<<std::endl;
                    std::cout <<"换乘地点为："<<stationInfo1->name<<std::endl;
                        station_1=station1;station_2=station2;
                        while (station_1->name!=stationInfo1->name){
                           printf("%s->",station_1->name);
                            station_1 = station_1->next;
                        }
                        while (stationInfo2->name!=station2->name){
                            printf("%s->",stationInfo2->name);
                            stationInfo2 = stationInfo2->next;
                        }
                        printf("%s",stationInfo2->name);
                        if_exit= true;
                        break;
                    }
                    stationInfo2=stationInfo2->next;
                }
                if (if_exit)break;
                stationInfo1=stationInfo1->next;
            }
        }
    }
}