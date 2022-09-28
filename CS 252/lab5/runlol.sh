#!/bin/bash
rm *.pcap
./waf --run "nsta-udp --uplinks=1"
echo "clients=1"
python summarize.py > clients_1.txt
rm *.pcap
./waf --run "nsta-udp --uplinks=5"
echo "clients=5"
python summarize.py > clients_5.txt
rm *.pcap
./waf --run "nsta-udp --uplinks=10"
echo "clients=10"
python summarize.py > clients_10.txt
rm *.pcap
./waf --run "nsta-udp --uplinks=20"
echo "clients=20"
python summarize.py > clients_20.txt
rm *.pcap
./waf --run "nsta-udp --uplinks=30"
echo "clients=30"
python summarize.py > clients_30.txt