/*
  EDS.cpp
  Event Driven Simulator using Priority Queue
  Data Structures and Algorithms Lab - CS293
  Author: P Balasubramanian
  Rollno: 200050103
*/  
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <time.h>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std::chrono;
using namespace std;

struct packet{
    double trigger_time;
    int size;
    bool error;
    int source_node,destination_node;
    packet()
    {
        error = false;
        size = rand()%951+50;
    }
    bool compare(packet rhs)
    {
        return ( trigger_time == rhs.trigger_time) && ( size == rhs.size) && ( source_node == rhs.source_node) && ( destination_node == rhs.destination_node);
    }
};

class Heap
{
  packet heap[1000];
  long long empty_pos;

  int parent_of(int index)
  {return (floor((index+1)/2)-1);}
  int left_child_of(int index)
  {return ((2*(index+1))-1);}
  int right_child_of(int index)
  {return (2*(index+1));}

public:
  Heap()
  {empty_pos=0;}

  double min()
  {return heap[0].trigger_time;}

  bool insert(packet new_elem)
  {
    heap[empty_pos]=new_elem;
    if(empty_pos==0)
    {
      empty_pos++;
      return true;
    }
    int pos_of_new_elem=empty_pos;

    while(pos_of_new_elem!=0 && heap[parent_of(pos_of_new_elem)].trigger_time>new_elem.trigger_time)
    {
      packet temp=heap[parent_of(pos_of_new_elem)];
      heap[parent_of(pos_of_new_elem)] = new_elem;
      heap[pos_of_new_elem] = temp;
      pos_of_new_elem = parent_of(pos_of_new_elem);
    }
    empty_pos++;
    return true;
  }

  void heapify(int pos)
  {
    int index=pos;

    while( (right_child_of(index)<empty_pos && left_child_of(index)<empty_pos) || (right_child_of(index)<empty_pos && heap[index].trigger_time>heap[right_child_of(index)].trigger_time) || (left_child_of(index)<empty_pos && heap[index].trigger_time>heap[left_child_of(index)].trigger_time) )
    {
      packet temp = heap[index];
      if(heap[right_child_of(index)].trigger_time<heap[left_child_of(index)].trigger_time)
      {
        heap[index] = heap[right_child_of(index)];
        heap[right_child_of(index)] = temp;
        index = right_child_of(index);
      }
      else
      {
        heap[index] = heap[left_child_of(index)];
        heap[left_child_of(index)] = temp;
        index = left_child_of(index);
      }
    }
  }

  packet del_min()
  {
    packet mini=heap[0];
    heap[0]=heap[empty_pos-1];
    empty_pos--;
    heapify(0);
    return mini;
  }

  void print_heap()
  {
    cout<<endl;
    for(long long i=0;i<empty_pos;i++)
      cout<<heap[i].trigger_time<<" ";
    cout<<endl;
  }

  bool isEmpty()
  {
    return empty_pos==0;
  } 
};

void packet_transmit(packet p, packet on_air[1000], int &num_on_air,double reach_time[1000])
{
    on_air[num_on_air] = p;
    reach_time[num_on_air] = p.trigger_time+(((double)(p.size))/1000);
    num_on_air++;

    cout<<"Packet transmitted from node "<<p.source_node<<" at time "<<p.trigger_time<<endl;

    if(num_on_air>1)
    {
        for (int i = 0; i < num_on_air; i++)
        {
            on_air[i].error = true;
        }  
    }
}
void packet_receive(packet p, packet on_air[1000], int &num_on_air,double reach_time[1000])
{
    int index;
    for(int i = 0; i < num_on_air; i++)
    {
        if(p.compare(on_air[i]))
            index=i;
    } 

    if(p.error)
        cout<<"ERROR: Packet was not received succesfully in destination node "<<p.destination_node<<" at time "<<reach_time[index]<<endl;
    else
        cout<<"Packet was received succesfully in destination node "<<p.destination_node<<" at time "<<reach_time[index]<<endl;

    for (int i = index; i < num_on_air-1; i++)
    {
        on_air[i] = on_air[i+1];
        reach_time[i] = reach_time[i+1];
    }
    num_on_air--;
   
}
double least_reach_time(double reach_time[1000],int num_on_air)
{
    if(num_on_air==0)
        return 10000;

    double smallest_reach_time = reach_time[0];
    for(int i = 0; i < num_on_air; i++)
    {
        if(reach_time[i]<smallest_reach_time)
            smallest_reach_time = reach_time[i];
    }
    return smallest_reach_time;
}
packet least_reach_time_pack_onroute(packet on_air[1000],double reach_time[1000],int num_on_air)
{
    double smallest_reach_time = reach_time[0];
    int index=0;
    for(int i = 0; i < num_on_air; i++)
    {
        if(reach_time[i]<smallest_reach_time)
        {
            smallest_reach_time = reach_time[i];
            index = i;
        }    
    }
    return on_air[index];
}
void end_event(double t, int T, int num_on_air)
{
    if(t>=T)
    {
        if(num_on_air==0)
            cout<<"All packets transmitted were received."<<endl;
        else
            cout<<num_on_air<<" packets were lost during transmission as the simulation was shutdown"<<endl;

    }
}
void print_on_air(packet on_air[1000],int num_on_air)  //mainly for demo purpose
{
    for (int i = 0; i < num_on_air; i++)
    {
        cout<<"size:"<<on_air[i].size<<" ";
    }  
    cout<<endl;
}

int main(int argc,char* argv[])
{
    int N,T, num_packets = 5;
    N = atoi(argv[1]);
    T = atoi(argv[2]);
    packet on_air[1000];
    int num_on_air=0;
    Heap x;
    double reach_time[1000];
    double t=0;
    srand(777);
    //scheduling the package trigger times
    for (int i = 0; i < num_packets; i++)
    {
        packet a;
        a.source_node = rand()%N+1;
        a.destination_node = rand()%N+1;
        cout<<a.source_node<<" "<<a.destination_node<<endl;
        a.trigger_time = ((double)(rand()%(100*T)))/10000;
        x.insert(a);
    }
    
    //simulation
    int flag=1;
    while(t<T)
    {
        if (flag==0)
        {
            if(x.isEmpty() && num_on_air==0)
                break;
        }
        if(num_on_air==0)
        {
            packet next = x.del_min();
            t = next.trigger_time;
            packet_transmit(next, on_air, num_on_air,reach_time);
        } 
        else if(x.isEmpty() && num_on_air!=0)
        {
            packet next = least_reach_time_pack_onroute(on_air,reach_time,num_on_air);
            t = least_reach_time(reach_time,num_on_air);
            packet_receive(next, on_air, num_on_air, reach_time);
        }   
        else if(x.min()>least_reach_time(reach_time,num_on_air))
        {
            packet next = least_reach_time_pack_onroute(on_air,reach_time,num_on_air);
            t = least_reach_time(reach_time,num_on_air);
            packet_receive(next, on_air, num_on_air, reach_time);
        }
        else
        {
            packet next = x.del_min();
            t = next.trigger_time;
            packet_transmit(next, on_air, num_on_air,reach_time);
        }
        flag=0;
    }

    end_event(t,T,num_on_air);
    return 0;
}