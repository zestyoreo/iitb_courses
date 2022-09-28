/*
 * Description:
 *    Experiment for n uplink flows, from n STAs to one AP
 *      A sender at STA0 and sink at AP
 *      A sender at STA1 and sink at AP
 *            			...
 *      A sender at STA{n-1} and sink at AP
 *
 * Usage instructions:
 *    To run from cli, with default values:
 *      ./waf --run "nsta-udp"
 *
 *    To run from cli, with 5 STAs and 1 AP:
 *     ./waf --run "nsta-udp --uplinks=5"
 *
 *    To get more info about the command line options:
 *      ./waf --run "nsta-udp --help"
 *
 * Important constants about 802.11a:
 *    PHY header = 20 us
 *    DIFS = 34 us
 *    SIFS = 16 us
 *    802.11 ACK = 30us
 *    slot time = 9 us
 *    CW_min = 15
 **/

#include "ns3/applications-module.h"
#include "ns3/attribute.h"
#include "ns3/core-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/stats-module.h"
#include "ns3/wifi-module.h"

using namespace ns3;

class NodesThroughput {
public:
  NodesThroughput(uint32_t nSta, ApplicationContainer apps[],
                  std::string filename);
  ~NodesThroughput();

  void CalculateThroughput(int stepsTime);

private:
  Ptr<FileAggregator> m_output;
  uint32_t m_nSta;

  Ptr<PacketSink> *m_sinks; // Using dynamic array
  uint64_t *m_lastTotalRx;  // Using dynamic array
};

NodesThroughput::NodesThroughput(uint32_t nSta, ApplicationContainer apps[],
                                 std::string filename) {
  m_nSta = nSta;
  m_sinks = new Ptr<PacketSink>[m_nSta];
  m_lastTotalRx = new uint64_t[m_nSta];

  // 0 is for STA0's sink and so on
  for (uint32_t i = 0; i < m_nSta; i++) {
    m_sinks[i] = StaticCast<PacketSink>(apps[i].Get(0));
    m_lastTotalRx[i] = 0; // Initialize the member to 0.
  }

  // Create the output file
  m_output = CreateObject<FileAggregator>(filename, FileAggregator::FORMATTED);

  // Set heading like "Time AP->STA0 STA1->AP STA2->AP ..."
  std::ostringstream os;
  os << "Time\t";
  for (uint32_t i = 0; i < m_nSta; i++) {
    os << "STA" << i << "->AP\t";
  }
  m_output->SetHeading(os.str());
}

NodesThroughput::~NodesThroughput() {
  delete[] m_sinks;
  delete[] m_lastTotalRx;
}

void NodesThroughput::CalculateThroughput(int stepsTime) {
  double curTput[m_nSta];

  // initialize all element so of array to 0
  for (uint32_t i = 0; i < m_nSta; i++) {
    curTput[i] = 0;
  }

  // 0 is for STA0's sink and so on
  for (uint32_t i = 0; i < m_nSta; i++) {
    // Convert Application RX Packets to MBits, sent in last 0.1s: Mbits/s
    curTput[i] = (m_sinks[i]->GetTotalRx() - m_lastTotalRx[i]) * (double)8 /
                 (1e6 * stepsTime);

    m_lastTotalRx[i] = m_sinks[i]->GetTotalRx(); // Save for next calculation;
  }

  std::ostringstream os;

  // Return the simulator's virtual time
  Time now = Simulator::Now();

  // Prepare an output line of current time and throughputs of each flow
  os.flush();
  os << "%f";

  // Add 1 output line for each flow
  for (uint32_t i = 0; i < m_nSta; i++) {
    os << "\t" << curTput[i];
  }
  std::string str = os.str();

  m_output->Set1dFormat(str);
  m_output->Write1d("throughputs", now.GetSeconds());

  Simulator::Schedule(MilliSeconds(1000), &NodesThroughput::CalculateThroughput,
                      this, stepsTime);
}

int main(int argc, char *argv[]) {
  /* Default parameters */
  uint32_t nSta = 1;                // Number of stations
  uint32_t payloadSize = 1472;      // Transport layer payload size in bytes.
  std::string dataRate = "100Mbps"; // Application layer datarate.
  std::string phyRate = "OfdmRate54Mbps"; // Physical layer bitrate.
  double simulationTime = 5;              // Simulation time in seconds.
  int stepsTime = 1; // Time steps for throughput calculation
  std::string filename = "out-nsta-udp.txt"; // Output filename

  /* Command line arguments */
  CommandLine cmd;
  cmd.AddValue("uplinks", "Number of Uplinks", nSta);
  cmd.AddValue("payloadSize", "Payload size in bytes", payloadSize);
  cmd.AddValue("dataRate", "Application datarate", dataRate);
  cmd.AddValue("phyRate", "Physical layer bitrate", phyRate);
  cmd.AddValue("file", "File to get the output", filename);
  cmd.Parse(argc, argv);

  /* Current parameters */
  std::cout << "\nCurrent parameters:\n";
  std::cout << "Number of Uplinks: " << nSta << "\n";
  std::cout << "Payload size in bytes: " << payloadSize << "\n";
  std::cout << "Application datarate: " << dataRate << "\n";
  std::cout << "Physical layer bitrate: " << phyRate << "\n";
  std::cout << "File to get the output: " << filename << "\n";

  /* No fragmentation and no RTS/CTS */
  Config::SetDefault("ns3::WifiRemoteStationManager::FragmentationThreshold",
                     StringValue("999999"));
  Config::SetDefault("ns3::WifiRemoteStationManager::RtsCtsThreshold",
                     StringValue("999999"));

  WifiMacHelper wifiMac;
  wifiMac.SetType("ns3::StaWifiMac", "QosSupported", BooleanValue(true));

  WifiHelper wifiHelper;
  wifiHelper.SetStandard(WIFI_PHY_STANDARD_80211a);

  /* Set up Legacy Channel */
  YansWifiChannelHelper wifiChannel;
  wifiChannel.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
  wifiChannel.AddPropagationLoss("ns3::FriisPropagationLossModel", "Frequency",
                                 DoubleValue(5e9));

  /* Setup Physical Layer */
  YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default();
  wifiPhy.SetChannel(wifiChannel.Create());
  wifiPhy.Set("TxPowerStart", DoubleValue(10.0));
  wifiPhy.Set("TxPowerEnd", DoubleValue(10.0));
  wifiPhy.Set("TxPowerLevels", UintegerValue(1));
  wifiPhy.Set("TxGain", DoubleValue(0));
  wifiPhy.Set("RxGain", DoubleValue(0));
  wifiPhy.Set("RxNoiseFigure", DoubleValue(10));
  wifiPhy.Set("CcaEdThreshold", DoubleValue(-79));
  wifiPhy.Set("RxSensitivity", DoubleValue(-79 + 3));
  wifiPhy.SetErrorRateModel("ns3::YansErrorRateModel");
  wifiHelper.SetRemoteStationManager("ns3::ConstantRateWifiManager", "DataMode",
                                     StringValue(phyRate), "ControlMode",
                                     StringValue("OfdmRate6Mbps"));

  NodeContainer apWifiNode;
  apWifiNode.Create(1);
  NodeContainer staWifiNodes;
  staWifiNodes.Create(nSta);

  /* Configure AP */
  Ssid ssid = Ssid("n-node-network");
  wifiMac.SetType("ns3::ApWifiMac", "Ssid", SsidValue(ssid));
  NetDeviceContainer apDevice;
  apDevice = wifiHelper.Install(wifiPhy, wifiMac, apWifiNode);

  /* Configure STA */
  wifiMac.SetType("ns3::StaWifiMac", "Ssid", SsidValue(ssid));
  NetDeviceContainer staDevices;
  staDevices = wifiHelper.Install(wifiPhy, wifiMac, staWifiNodes);

  /* Mobility model */
  MobilityHelper mobility;
  Ptr<ListPositionAllocator> positionAlloc =
      CreateObject<ListPositionAllocator>();
  positionAlloc->Add(Vector(0.0, 0.0, 0.0)); // AP
  for (uint32_t i = 0; i < nSta; i++) {
    positionAlloc->Add(Vector(0.0, 5.0 + i * 0.1, 0.0)); // STAs
  }

  mobility.SetPositionAllocator(positionAlloc);
  mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobility.Install(apWifiNode);
  mobility.Install(staWifiNodes);

  /* Internet stack */
  InternetStackHelper stack;
  stack.Install(apWifiNode);
  stack.Install(staWifiNodes);

  Ipv4AddressHelper address;
  address.SetBase("10.0.0.0", "255.255.255.0");
  Ipv4InterfaceContainer apInterface;
  apInterface = address.Assign(apDevice);
  Ipv4InterfaceContainer staInterface;
  staInterface = address.Assign(staDevices);

  /* Populate routing table */
  Ipv4GlobalRoutingHelper::PopulateRoutingTables();

  /* n receivers (sinks) on AP, and n senders, one on each of n STAs*/
  ApplicationContainer senderApps[nSta];
  ApplicationContainer sinkApps[nSta];

  wifiPhy.SetPcapDataLinkType(YansWifiPhyHelper::DLT_IEEE802_11_RADIO);
  wifiPhy.EnablePcap("AccessPoint", apDevice);
  wifiPhy.EnablePcap("Station", staDevices);

  // Install one sender on each STA, starting from STA0
  for (uint32_t i = 0; i < nSta; i++) {
    OnOffHelper OnOff = OnOffHelper(
        "ns3::UdpSocketFactory",
        InetSocketAddress(apInterface.GetAddress(0),
                          i + 10)); // Each sender on STA sends to port numbers
                                    // 10, 11, 12, ... on AP
    OnOff.SetConstantRate(DataRate(dataRate), payloadSize);
    senderApps[i] = OnOff.Install(staWifiNodes.Get(i));
    senderApps[i].Start(Seconds(0.001));
    senderApps[i].Stop(Seconds(simulationTime));
  }

  // Install sinks on AP ports 10, 11, 12, ..., one for each STA
  for (uint32_t i = 0; i < nSta; i++) {
    PacketSinkHelper sinkHelper(
        "ns3::UdpSocketFactory",
        InetSocketAddress(Ipv4Address::GetAny(), i + 10));
    sinkApps[i] = sinkHelper.Install(apWifiNode.Get(0));
    sinkApps[i].Start(Seconds(0.001));
    sinkApps[i].Stop(Seconds(simulationTime));
  }

  /* Throughput Calculator*/
  NodesThroughput tputs = NodesThroughput(nSta, sinkApps, filename);

  Simulator::Schedule(Seconds(1), &NodesThroughput::CalculateThroughput, &tputs,
                      stepsTime);

  /* Node Addresses, just for reference */
  std::cout << "\nUDP Traffic: Per second uplink throughput for " << nSta
            << " STAs"
            << "\n";
  std::cout << "----------------------------------------------------"
            << "\n\n";
  std::cout << "Network Layout:"
            << "\n";
  std::cout << "Node\t"
            << "Address\t\t"
            << "Location" << std::endl;
  std::cout << "AP\t" << apWifiNode.Get(0)->GetDevice(0)->GetAddress() << "\t"
            << apWifiNode.Get(0)->GetObject<MobilityModel>()->GetPosition()
            << std::endl;
  for (uint32_t i = 0; i < nSta; i++) {
    std::cout << "STA" << i << "\t"
              << staWifiNodes.Get(i)->GetDevice(0)->GetAddress() << "\t"
              << staWifiNodes.Get(i)->GetObject<MobilityModel>()->GetPosition()
              << std::endl;
  }

  /* Start Simulation */
  Simulator::Stop(Seconds(simulationTime + 1));
  Simulator::Run();

  std::cout << "\nOutput in file: " << filename
            << " (per second throughput for all uplink flows)\n\n";

  Simulator::Destroy();

  return 0;
}
