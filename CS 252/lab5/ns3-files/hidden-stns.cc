/*
 * Description:
 *    Experiment for comparing the performance of RTS/CTS
 *      There are three nodes n0, n1, n2 in the network.
 *      The stations are configured such that
 *        n1-n0 can hear each other,
 *        n2-n0 can hear each other,
 *        but n1-n2 cannot hear each other.
 *      Thus n1, n2 are hidden terminals w.r.t. each other.
 *
 *    When contention is disabled,
 *      n1 sends packets to n0 without any interference
 *
 *    When contention is enabled,
 *      Both n1 and n2 send packets to n0 causing interference
 *
 * Usage instructions:
 *    To run from cli, with default values:
 *      ./waf --run "hidden-stns"
 *
 *    To run from cli, with RTS/CTS enabled and contention enabled:
 *     ./waf --run "hidden-stns --enable_rts --contention"
 *
 *    To get more info about the command line options:
 *      ./waf --run "hidden-stns --help"
 **/

#include "ns3/boolean.h"
#include "ns3/command-line.h"
#include "ns3/config.h"
#include "ns3/constant-position-mobility-model.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/ipv4-flow-classifier.h"
#include "ns3/on-off-helper.h"
#include "ns3/propagation-delay-model.h"
#include "ns3/propagation-loss-model.h"
#include "ns3/string.h"
#include "ns3/udp-echo-helper.h"
#include "ns3/uinteger.h"
#include "ns3/yans-wifi-channel.h"
#include "ns3/yans-wifi-helper.h"

using namespace ns3;

// Run single 8 seconds experiment
void experiment(bool contention, double simulationTime) {

  ////////////////////////////////////////////////////////////////////////////////////
  // Nodes n0, n1, n2
  NodeContainer nodes;
  nodes.Create(3);
  for (uint8_t i = 0; i < 3; ++i) {
    nodes.Get(i)->AggregateObject(
        CreateObject<ConstantPositionMobilityModel>());
  }
  ////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////
  // Create propagation loss matrix
  Ptr<MatrixPropagationLossModel> lossModel =
      CreateObject<MatrixPropagationLossModel>();
  lossModel->SetDefaultLoss(200); // Set default loss to 200 dB - No coverage
  // set symmetric loss n0 <-> n1, n0 <-> n2 to 50 dB, good coverage
  lossModel->SetLoss(nodes.Get(0)->GetObject<MobilityModel>(),
                     nodes.Get(1)->GetObject<MobilityModel>(), 50);
  lossModel->SetLoss(nodes.Get(0)->GetObject<MobilityModel>(),
                     nodes.Get(2)->GetObject<MobilityModel>(), 50);
  ////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////
  // Create a YANS Wifi Channel
  Ptr<YansWifiChannel> wifiChannel = CreateObject<YansWifiChannel>();
  wifiChannel->SetPropagationLossModel(lossModel);
  wifiChannel->SetPropagationDelayModel(
      CreateObject<ConstantSpeedPropagationDelayModel>());

  // Declare a wifi helper
  WifiHelper wifi;
  wifi.SetStandard(WIFI_PHY_STANDARD_80211a);
  wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager", "DataMode",
                               StringValue("OfdmRate54Mbps"));

  // Create the wifi Phy helper
  YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default();
  wifiPhy.SetChannel(wifiChannel);

  // Declare a WifiMac helper
  WifiMacHelper wifiMac;
  wifiMac.SetType("ns3::AdhocWifiMac"); // use ad-hoc MAC

  // Create the actual devices
  NetDeviceContainer devices = wifi.Install(wifiPhy, wifiMac, nodes);

  // Do the usual routine for Internet stack installation
  InternetStackHelper internet;
  // Install it on all the nodes
  internet.Install(nodes);

  // Declare the address helper
  Ipv4AddressHelper ipv4;
  ipv4.SetBase("10.0.0.0", "255.0.0.0");
  ipv4.Assign(devices); // Assign IP addresses to device interfaces
  ////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////
  // Declare the application container
  ApplicationContainer cbrApps;
  uint16_t cbrPort = 12345;    // port for the CBR stream
  uint32_t payloadSize = 2200; // Transport layer payload size in bytes.

  // OnOff source helpers - (n1, n2) to n0
  OnOffHelper ooHelper("ns3::UdpSocketFactory",
                       InetSocketAddress(Ipv4Address("10.0.0.1"), cbrPort));
  ooHelper.SetConstantRate(DataRate("100Mbps"), payloadSize);

  // Flow 1: Node n1 -> Node n0
  ooHelper.SetAttribute("StartTime", TimeValue(Seconds((double)101 / 100)));
  cbrApps.Add(ooHelper.Install(nodes.Get(1)));

  if (contention) {
    // Flow 2: Node n2 -> Node n0
    ooHelper.SetAttribute("StartTime", TimeValue(Seconds((double)102 / 100)));
    cbrApps.Add(ooHelper.Install(nodes.Get(2)));
  }
  ////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////
  // UDP pingers due to lack of Address Resolution Protocol
  ApplicationContainer pingApps;
  uint16_t echoPort = 9;

  UdpEchoClientHelper echoClientHelper(Ipv4Address("10.0.0.1"), echoPort);
  echoClientHelper.SetAttribute("MaxPackets", UintegerValue(1));
  echoClientHelper.SetAttribute("Interval", TimeValue(Seconds(0.1)));
  echoClientHelper.SetAttribute("PacketSize", UintegerValue(10));

  echoClientHelper.SetAttribute("StartTime",
                                TimeValue(Seconds((double)1 / 1000)));
  pingApps.Add(echoClientHelper.Install(nodes.Get(1)));

  if (contention) {
    echoClientHelper.SetAttribute("StartTime",
                                  TimeValue(Seconds((double)2 / 1000)));
    pingApps.Add(echoClientHelper.Install(nodes.Get(2)));
  }
  ////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////
  // Install FlowMonitor on all nodes
  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll();

  // Run simulation for simulationTime
  Simulator::Stop(Seconds(simulationTime));
  Simulator::Run();

  // Print per flow statistics
  monitor->CheckForLostPackets();
  Ptr<Ipv4FlowClassifier> classifier =
      DynamicCast<Ipv4FlowClassifier>(flowmon.GetClassifier());
  FlowMonitor::FlowStatsContainer stats = monitor->GetFlowStats();
  double totalTput = 0.0;
  uint8_t skip = contention ? 2 : 1;
  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i =
           stats.begin();
       i != stats.end(); ++i) {
    // first skip FlowIds are for ECHO apps, we don't want to display them
    if (i->first > skip) {
      // Duration for throughput measurement is (simulationTime - 1) seconds,
      // since
      //   StartTime of the OnOffApplication is at about 1 second
      // and
      //   Simulator::Stops at "second simulationTime".
      Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow(i->first);
      std::cout << "Flow " << i->first - skip << " (" << t.sourceAddress
                << " -> " << t.destinationAddress << ")\n";
      std::cout << "  Tx Packets: " << i->second.txPackets << "\n";
      std::cout << "  Tx Bytes:   " << i->second.txBytes << "\n";
      std::cout << "  TxOffered:  "
                << i->second.txBytes * 8.0 / (simulationTime - 1) / 1000 / 1000
                << " Mbps\n";
      std::cout << "  Rx Packets: " << i->second.rxPackets << "\n";
      std::cout << "  Rx Bytes:   " << i->second.rxBytes << "\n";
      std::cout << "  Throughput: "
                << i->second.rxBytes * 8.0 / (simulationTime - 1) / 1000 / 1000
                << " Mbps\n";
      totalTput += i->second.rxBytes * 8.0 / (simulationTime - 1) / 1000 / 1000;
    }
  }
  std::cout << "Total channel throughput = " << totalTput << " Mbps"
            << std::endl;
  // Cleanup
  Simulator::Destroy();
  ////////////////////////////////////////////////////////////////////////////////////
}

int main(int argc, char **argv) {
  /* Default parameters */
  bool enable_rts = false;   // Enable RTS/CTS.
  bool contention = false;   // Enable contention.
  double simulationTime = 8; // Simulation time in seconds.

  /* Command line arguments */
  CommandLine cmd;
  cmd.AddValue("enable_rts", "Enable RTS/CTS", enable_rts);
  cmd.AddValue("contention", "Enable contention", contention);
  cmd.AddValue("simtime", "Total simulation time in seconds", simulationTime);
  cmd.Parse(argc, argv);

  if (contention) {
    std::cout << "Hidden station experiment ";
  } else {
    std::cout << "Single uplink experiment ";
  }

  if (enable_rts) {
    std::cout << "with RTS/CTS enabled\n";
  } else {
    std::cout << "with RTS/CTS disabled\n";
  }

  Config::SetDefault("ns3::WifiRemoteStationManager::FragmentationThreshold",
                     StringValue("999999"));
  UintegerValue ctsThr =
      (enable_rts ? UintegerValue(99) : UintegerValue(999999));
  Config::SetDefault("ns3::WifiRemoteStationManager::RtsCtsThreshold", ctsThr);

  experiment(contention, simulationTime);

  return 0;
}
