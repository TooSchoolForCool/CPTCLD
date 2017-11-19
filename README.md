# CPTCLD - Charging Protocol based on Traffic Classification for LTE D2D Communication

## Definitions:
| Brief | Definition |
| :---: | --- |
| D2D | Device-to-Device |
| CPTCLD | Charging Protocol based on Traffic Classification for LTE D2D communication |
| BS | Base Station that manages D2D communication |
| UE | User Equipment involved in D2D communication |
| RB | Resource Block of LTE network |
| Request | Request for RB sent by UE |
| Scheduler | Scheduler at BS that allocates RB |
| SA | Scheduling Algorithm that Scheduler applies to RB allocaion |

## Introduction to CPTCLD
CPTCLD aims at reducing charging loss in LTE D2D communication caused by users' misbehavior (e.g., a UE uses RB allocated for voice communication, which might be free and unlimited in the monthly plan, to transmit other data like FTP files). Since the data flow normally will not go through BS in LTE D2D communication and it is the UE that is cheating, it is unrealistic to rely on the self-reports from UE because the cheaters will always provide the false information. Therefore, CPTCLD attacks this problem by classifying service into different traffic patterns, allocating RB based on Request and charging based on RB allocation.

## CPTCLD mainly consists of three parts:
### 1.  Traffic Pattern Table
CPTCLD classifies traffic patterns in LTE D2D communication into three main categories: Stream, Message and File, which are further classified into different subtypes (e.g., Stream1, Stream2, Stream3...). Every entry in the Traffic Pattern Table contains the specific pattern type and its attributes (e.g., Priority, Bandwidth, Delay, MaxReqSize, Price/RB). Here is and example of Traffic Pattern Table we used for our experiment:

| Classification || Attributes |||||
| :---: | :---: | --- | --- | --- | --- | --- |
| **Category** | **Type** | **Priority** | **BandWidth** | **Delay** | **MaxReqSize** | **Price/RB** |
| Stream | 1 | 1 | 20 | 20 | 100 | 0 |
| Stream | 2 | 2 | 100 | 20 | 200 | 2 |
| Stream | ... |
| Message | 1 | 1 | 10 | 0 | 40 | 0 |
| Message | 2 | 3 | 40 | 100 | 200 | 1 |
| Message | ... |
| File | 1 | 3 | 200 | 500 | 5000 | 2 |
| File | ... |

In the example, the meaning of the attributes are following:
- Priotity - The priority of being considered by Scheduler when performing RB allocation (e.g., Stream1 of Priority 1 will be considered prior to Stream2 of Priority 2).
- Bandwidth - The requested bandwidth (e.g., File1 of Bandwidth 200 requested to be allocated RB that satisify 200 bandwidth units). 
- Delay - The max delay between burst transmission (e.g., Stream1 of Delay 20 requested to be allocated RB in every period of 20 time units).
- MaxReqSize - The maximum requested size (e.g., every single request of Stream2 can't claim more RB than what makes up 200 size units. If the UE needs more than 200-unit size of Stream2, it needs to request more than once).

**Note that the format of the table is not final. In practice, the table can be extended by adding more categories, types or attributes.**

### 2.  UE Request Client
In LTE D2D communication, the UE must send Request for RB to BS if it wants to send data. Based on CPTCLD, the Request will be extended to contain the following items:
- ID - To indentify the UE device and post charging information.
- Type - To speicify the traffic pattern type of the requested service (e.g., a UE might request for Stream2 if it wants to make a video call of certain voice and video quality).
- Size - To indicate the requested size of resources (e.g., a UE can request for Stream1 of Size 80). **Larger value than corresponding MaxReqSize of requested traffic pattern type will be considered as MaxReqSize.**

To achieve this Request mechanism, every UE that complies with CPTCLD must have a client that generates Request based on the network traffic need of upper levels.

### 3.  Scheduler Modification
In practice, the BS will allocate RB after receiving Request from UE. The goal of existing SA is mainly focused on utilization and fairness. To apply CPTCLD for reducing cheating loss, SA must be modified to take more factors into consideration (mainly the attributes of the traffic pattern specified by Type in UE Request). Initially, we considered achieving this by adding a universal filter after the existing SA, which takes the output of SA (the allocation of RB) as input and modify it according to the traffic pattern in CPTCLD. However, we found this approach inpractical if we want to maintain utilization and fairness emphasized in original allocation output. Therefore, every different SA must be modified accordingly to work with CPTCLD. We propose the criteria of Scheduler Modification by giving examples of SA modification in experiment. 

## How CPTCLD Reduces Charging Loss
CPTCLD reduces charging loss by the usage limitation posed by the RB allocation based on UE Request. Since each UE has to indicate its intended traffic pattern in Request, the RB allocated to it will comply with the specific traffic pattern. If ensured that the service quality of traffic patterns with lower Price/RB cannot meet or can poorly support the requirement of the traffic patterns with higher Price/RB, the cheater will either find it impossible or unprofitable to cheat in RB usage. In the above example of UE using RB allocated for Stream1 to transmit FTP files, it will find that the transmission rate is too low to meet its need (e.g., it will take 100 times longer time to transmit a file with RB alocated for Stream1 than that for File1). In a word, as long as the unit price of relatively high-quality service is higher than that of relatively low-quality service, or the low-price service patterns are incompatible with high-price service patterns, loss caused by cheating will be significantly reduced.

## Experiment
To verify the practicality and effectiveness of CPTCLD, we conducted the experiments in the following way:
1.  Choose different SA and implement them with C++.
2.  Modify the original SA to comply with the RB allocation criteria specified by Request.
3.  Test both original and modified SA.
4.  Analyze the testing results and compare the differences between original and modified SA.
