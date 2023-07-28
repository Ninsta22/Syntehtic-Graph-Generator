#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include <boost/dynamic_bitset.hpp>

using namespace std;
using namespace boost;

int main(int argc, char *argv[]){
    srand(time(0));
    //The variables below are ones that must be passed
    int numberNodes = stoi(argv[1]);
    int numberLayers = stoi(argv[2]);
    int motifType = stoi(argv[3]);
    int avgDegree = stoi(argv[4]);
    double edgeRatio = stod(argv[5]);
    double plantedMotifRatio = stod(argv[6]);
    double mutationRate = stod(argv[7]);
    int graphType = stoi(argv[8]);

    string fileName = "graph_"+to_string(numberNodes)+"Nodes_"+to_string(numberLayers)+"Layers"
    +to_string(avgDegree)+"AvgDegree"+to_string(motifType)+"MotifType"+to_string(mutationRate)+"MutationRate"
    +to_string(graphType)+"GraphType";
    string fileExtension = ".txt";

    //The variables below are ones that can be solved using the variables above
    int numberEdges = (avgDegree*numberNodes)/2;
    int totalEdgesLeft = (avgDegree*numberNodes)/2;
    int totalNodesLeft = numberNodes;
    int greenRatio = ceil(plantedMotifRatio*numberLayers);
    int edgeShuffles = ceil((mutationRate*numberEdges)/2);

    //This map represents the average degree for each node being used
    //unordered_map<int, int> nodeMap;
    vector<pair<int, int>> nodeMap;

    //The vector below represents the first layer that we are basing the entire network off of
    vector<dynamic_bitset<> > adjacencyGraph(numberNodes, dynamic_bitset<>(numberNodes));

    //The vector below represents every layer, for the entire multilayer network
    vector<vector<dynamic_bitset<> > > multiLayerGraph;

    //The vectors below are for easier management with specific motif choosing
    vector<int> nodesOffLimit;
    vector<pair<int, int>> edgeOffLimits;
    vector<pair<int, int>> green;

    if((motifType == 1 || motifType == 2 || motifType == 3 || motifType == 4)){
        int numberEdgesinMotif;
        if(motifType == 1 || motifType == 2) numberEdgesinMotif = 4;
        else numberEdgesinMotif = 3;
        int numberPlantedMotifs = ceil((avgDegree*edgeRatio*numberNodes)/(2*numberEdgesinMotif));

        vector<int> nodesOffLimit;
        vector<pair<int, int>> edgeOffLimits;
        vector<pair<int, int>> green;
        for(int i = 0; i < numberPlantedMotifs; i++){
            vector<int> temporaryMotif;
            while(temporaryMotif.size() < numberEdgesinMotif){
                int randomNode = rand() % (numberNodes);
                if(find(nodesOffLimit.begin(), nodesOffLimit.end(), randomNode) != nodesOffLimit.end()) continue;
                else{
                    if((temporaryMotif.size() == 0) || (temporaryMotif.size() > 0 && (find(temporaryMotif.begin(), temporaryMotif.end(), randomNode) == temporaryMotif.end()))){
                        temporaryMotif.push_back(randomNode);
                        nodesOffLimit.push_back(randomNode);
                        nodeMap.push_back(make_pair(0, randomNode));
                        //nodeMap[randomNode] = 0;
                        totalNodesLeft--;
                    }
                }
            }

            if(motifType == 1){
                adjacencyGraph[temporaryMotif[0]][temporaryMotif[1]] = 1;
                adjacencyGraph[temporaryMotif[0]][temporaryMotif[3]] = 1;
                adjacencyGraph[temporaryMotif[2]][temporaryMotif[1]] = 1;
                adjacencyGraph[temporaryMotif[2]][temporaryMotif[3]] = 1;

                for(auto& p: nodeMap){
                    if(p.second == temporaryMotif[0]) p.first = p.first+2;
                    else if(p.second = temporaryMotif[1]) p.first = p.first+2;
                    else if(p.second = temporaryMotif[2]) p.first = p.first+2;
                    else if(p.second = temporaryMotif[3]) p.first = p.first+2;
                }
                //nodeMap[temporaryMotif[0]] = nodeMap[temporaryMotif[0]] + 2;
                //nodeMap[temporaryMotif[1]] = nodeMap[temporaryMotif[1]] + 2;
                //nodeMap[temporaryMotif[2]] = nodeMap[temporaryMotif[2]] + 2;
                //nodeMap[temporaryMotif[3]] = nodeMap[temporaryMotif[3]] + 2;
            }else if(motifType == 2){
                adjacencyGraph[temporaryMotif[0]][temporaryMotif[1]] = 1;
                adjacencyGraph[temporaryMotif[0]][temporaryMotif[2]] = 1;
                adjacencyGraph[temporaryMotif[1]][temporaryMotif[3]] = 1;
                adjacencyGraph[temporaryMotif[2]][temporaryMotif[3]] = 1;

                for(auto& p: nodeMap){
                    if(p.second == temporaryMotif[0]) p.first = p.first+2;
                    else if(p.second = temporaryMotif[1]) p.first = p.first+2;
                    else if(p.second = temporaryMotif[2]) p.first = p.first+2;
                    else if(p.second = temporaryMotif[3]) p.first = p.first+2;
                }
                //nodeMap[temporaryMotif[0]] = nodeMap[temporaryMotif[0]] + 2;
                //nodeMap[temporaryMotif[1]] = nodeMap[temporaryMotif[1]] + 2;
                //nodeMap[temporaryMotif[2]] = nodeMap[temporaryMotif[2]] + 2;
                //nodeMap[temporaryMotif[3]] = nodeMap[temporaryMotif[3]] + 2;
            }else if(motifType == 3){
                adjacencyGraph[temporaryMotif[0]][temporaryMotif[1]] = 1;
                adjacencyGraph[temporaryMotif[1]][temporaryMotif[2]] = 1;
                adjacencyGraph[temporaryMotif[2]][temporaryMotif[0]] = 1;

                for(auto& p: nodeMap){
                    if(p.second == temporaryMotif[0]) p.first = p.first+2;
                    else if(p.second = temporaryMotif[1]) p.first = p.first+2;
                    else if(p.second = temporaryMotif[2]) p.first = p.first+2;
                }
                //nodeMap[temporaryMotif[0]] = nodeMap[temporaryMotif[0]] + 2;
                //nodeMap[temporaryMotif[1]] = nodeMap[temporaryMotif[1]] + 2;
                //nodeMap[temporaryMotif[2]] = nodeMap[temporaryMotif[2]] + 2;
            }else if(motifType == 4){
                adjacencyGraph[temporaryMotif[0]][temporaryMotif[1]] = 1;
                adjacencyGraph[temporaryMotif[1]][temporaryMotif[2]] = 1;
                adjacencyGraph[temporaryMotif[0]][temporaryMotif[2]] = 1;

                for(auto& p: nodeMap){
                    if(p.second == temporaryMotif[0]) p.first = p.first+2;
                    else if(p.second = temporaryMotif[1]) p.first = p.first+2;
                    else if(p.second = temporaryMotif[2]) p.first = p.first+2;
                }
                //nodeMap[temporaryMotif[0]] = nodeMap[temporaryMotif[0]] + 2;
                //nodeMap[temporaryMotif[1]] = nodeMap[temporaryMotif[1]] + 2;
                //nodeMap[temporaryMotif[2]] = nodeMap[temporaryMotif[2]] + 2;
            }
            totalEdgesLeft = totalEdgesLeft - numberEdgesinMotif;
        }

        int totalDegreeValue = 0;
        for(auto& p: nodeMap){
            totalDegreeValue += p.first;
        }

        if(motifType == 1){
            for (int i = 0; i < nodesOffLimit.size(); i = i + 4) {
                edgeOffLimits.push_back(make_pair(nodesOffLimit[i], nodesOffLimit[i + 1]));
                edgeOffLimits.push_back(make_pair(nodesOffLimit[i], nodesOffLimit[i + 3]));
                edgeOffLimits.push_back(make_pair(nodesOffLimit[i + 2], nodesOffLimit[i + 1]));
                edgeOffLimits.push_back(make_pair(nodesOffLimit[i + 2], nodesOffLimit[i + 3]));
            }
        }else if(motifType == 2){
            for (int i = 0; i < nodesOffLimit.size(); i = i + 4) {
                edgeOffLimits.push_back(make_pair(nodesOffLimit[i], nodesOffLimit[i + 1]));
                edgeOffLimits.push_back(make_pair(nodesOffLimit[i], nodesOffLimit[i + 2]));
                edgeOffLimits.push_back(make_pair(nodesOffLimit[i + 1], nodesOffLimit[i + 3]));
                edgeOffLimits.push_back(make_pair(nodesOffLimit[i + 2], nodesOffLimit[i + 3]));
            }
        }else if(motifType == 3){
            for (int i = 0; i < nodesOffLimit.size(); i = i + 3) {
                edgeOffLimits.push_back(make_pair(nodesOffLimit[i], nodesOffLimit[i + 1]));
                edgeOffLimits.push_back(make_pair(nodesOffLimit[i + 1], nodesOffLimit[i + 2]));
                edgeOffLimits.push_back(make_pair(nodesOffLimit[i + 2], nodesOffLimit[i]));
            }
        }else if(motifType == 4){
            for (int i = 0; i < nodesOffLimit.size(); i = i + 3) {
                edgeOffLimits.push_back(make_pair(nodesOffLimit[i], nodesOffLimit[i + 1]));
                edgeOffLimits.push_back(make_pair(nodesOffLimit[i + 1], nodesOffLimit[i + 2]));
                edgeOffLimits.push_back(make_pair(nodesOffLimit[i], nodesOffLimit[i + 2]));
            }
        }

        if(graphType == 1){
            while(totalEdgesLeft != 0){
                int node1 = rand() % numberNodes;
                int node2 = rand() % numberNodes;

                bool addEdge = true;
                for(int i = 0; i < edgeOffLimits.size(); i++){
                    if(edgeOffLimits[i].first == node1 && edgeOffLimits[i].second == node2) addEdge = false;
                }
                for(int i = 0; i < green.size(); i++){
                    if(green[i].first == node1 && green[i].second == node2) addEdge = false;
                }

                if(addEdge){
                    green.push_back(make_pair(node1, node2));
                    totalEdgesLeft--;
                    adjacencyGraph[node1][node2] = 1;
                }
            }
        }else if(graphType == 2){
            int kian = 0;
            while(totalEdgesLeft != 0){
                kian++;
                int node1 = rand() % numberNodes;
                bool noRepeat = false;
                while(!noRepeat){
                    node1 = rand() % numberNodes;
                    noRepeat = true;
                    for(auto& p: nodeMap){
                        if(p.second == node1 && p.first > 0) noRepeat = false;
                    }
                }

                int edgePerNewNode = ceil(totalEdgesLeft/totalNodesLeft);
                if(totalEdgesLeft-edgePerNewNode < 0) edgePerNewNode = totalEdgesLeft;
                totalEdgesLeft=totalEdgesLeft-edgePerNewNode;
                totalNodesLeft--;

                //Add finding the proper node based off their edges from previous code
                sort(nodeMap.begin(), nodeMap.end());

                for(int i = 0; i < edgePerNewNode; i++){
                    int node2 = -1;
                    int tempSum = 0;
                    int randomTarget = rand() % totalDegreeValue;
                    for(auto& p: nodeMap){
                        if(tempSum + p.first < randomTarget) tempSum += p.first;
                        else{
                            node2 = p.second;
                            p.first++;
                            break;
                        }
                    }

                    totalDegreeValue++;
                    if(i == 0) nodeMap.push_back(make_pair(1, node1));
                    else{
                        for(auto& p: nodeMap){
                            if(p.second == node1) p.first++;
                        }
                    }

                    green.push_back(make_pair(node1, node2));
                    adjacencyGraph[node1][node2] = 1;
                }
            }
        }

        multiLayerGraph.push_back(adjacencyGraph);

        //The following below will only shuffle green edges
        for(int i = 1; i < greenRatio; i++){
            //Below is the first part of actually shuffling all of the edges
            vector<pair<int, int>> tempEdgeOffLimits = edgeOffLimits;
            vector<pair<int, int>> tempGreenEdges = green;
            for(int j = 0; j < edgeShuffles; j++){
                int random1 = rand() % tempGreenEdges.size();
                int random2 = rand() % tempGreenEdges.size();

                int firstNode = tempGreenEdges[random1].first;
                int secondNode = tempGreenEdges[random1].second;
                int thirdNode = tempGreenEdges[random2].first;
                int fourthNode = tempGreenEdges[random2].second;

                bool cantSwap = true;
                while(cantSwap){
                    //cout << firstNode << " is firstNode. " << secondNode << " is secondNode. " << thirdNode << " is thirdNode. " << fourthNode << " is fourthNode. " << endl;
                    if(firstNode != thirdNode && secondNode != fourthNode){
                        bool makeItFalse = true;
                        for(int k = 0; k < tempGreenEdges.size(); k++){
                            if((firstNode == tempGreenEdges[k].first && fourthNode == tempGreenEdges[k].second) 
                            ||
                            (thirdNode == tempGreenEdges[k].first && secondNode == tempGreenEdges[k].second)){
                                makeItFalse = false;
                            }
                        }

                        if(makeItFalse) cantSwap = false;
                        else{
                            random1 = rand() % tempGreenEdges.size();
                            random2 = rand() % tempGreenEdges.size();

                            firstNode = tempGreenEdges[random1].first;
                            secondNode = tempGreenEdges[random1].second;
                            thirdNode = tempGreenEdges[random2].first;
                            fourthNode = tempGreenEdges[random2].second;
                        }
                    }else{
                        random1 = rand() % tempGreenEdges.size();
                        random2 = rand() % tempGreenEdges.size();

                        firstNode = tempGreenEdges[random1].first;
                        secondNode = tempGreenEdges[random1].second;
                        thirdNode = tempGreenEdges[random2].first;
                        fourthNode = tempGreenEdges[random2].second;
                    }
                }
                
                tempGreenEdges[random1].second = fourthNode;
                tempGreenEdges[random2].second = secondNode;
            }


            //The below creates this layers specific adjacencyList and adds it to the Multilayer Network
            vector<dynamic_bitset<> > tempAdjacencyGraph(numberNodes, dynamic_bitset<>(numberNodes));
            for(int j = 0; j < tempEdgeOffLimits.size(); j++){
                int temp1 = tempEdgeOffLimits[j].first;
                int temp2 = tempEdgeOffLimits[j].second;
                tempAdjacencyGraph[temp1][temp2] = 1;
            }

            for(int j = 0; j < tempGreenEdges.size(); j++){
                int temp1 = tempGreenEdges[j].first;
                int temp2 = tempGreenEdges[j].second;
                tempAdjacencyGraph[temp1][temp2] = 1;
            }

            multiLayerGraph.push_back(tempAdjacencyGraph);
        }
        

        //The following below will shuffle any type of edges
        for(int i = greenRatio; i < numberLayers; i++){
            vector<pair<int, int>> totalEdges(numberEdges);
            merge(edgeOffLimits.begin(), edgeOffLimits.end(), green.begin(), green.end(), totalEdges.begin());

            for(int j = 0; j < edgeShuffles; j++){
                int random1 = rand() % totalEdges.size();
                int random2 = rand() % totalEdges.size();

                int firstNode = totalEdges[random1].first;
                int secondNode = totalEdges[random1].second;
                int thirdNode = totalEdges[random2].first;
                int fourthNode = totalEdges[random2].second;

                bool cantSwap = true;
                while(cantSwap){
                    if(firstNode != thirdNode && secondNode != fourthNode){
                        bool makeItFalse = true;
                        for(int k = 0; k < totalEdges.size(); k++){
                            if((firstNode == totalEdges[k].first && fourthNode == totalEdges[k].second) 
                            ||
                            (thirdNode == totalEdges[k].first && secondNode == totalEdges[k].second)){
                                makeItFalse = false;
                            }
                        }

                        if(makeItFalse) cantSwap = false;
                        else{
                            random1 = rand() % totalEdges.size();
                            random2 = rand() % totalEdges.size();

                            firstNode = totalEdges[random1].first;
                            secondNode = totalEdges[random1].second;
                            thirdNode = totalEdges[random2].first;
                            fourthNode = totalEdges[random2].second;
                        }
                    }else{
                        random1 = rand() % totalEdges.size();
                        random2 = rand() % totalEdges.size();

                        firstNode = totalEdges[random1].first;
                        secondNode = totalEdges[random1].second;
                        thirdNode = totalEdges[random2].first;
                        fourthNode = totalEdges[random2].second;
                    }
                }
                
                totalEdges[random1].second = fourthNode;
                totalEdges[random2].second = secondNode;
            }


            //The below creates this layers specific adjacencyList and adds it to the Multilayer Network
            vector<dynamic_bitset<> > tempAdjacencyGraph(numberNodes, dynamic_bitset<>(numberNodes));
            for(int j = 0; j < totalEdges.size(); j++){
                int temp1 = totalEdges[j].first;
                int temp2 = totalEdges[j].second;
                tempAdjacencyGraph[temp1][temp2] = 1;
            }

            multiLayerGraph.push_back(tempAdjacencyGraph);
        }
    }

    ofstream finalGraph;
    finalGraph.open(fileName+fileExtension);
    for(auto& l: multiLayerGraph){
        for(int i = 0; i < l.size(); i++){
            if(l[i].count() > 0){
                for(int j = 0; j < l[i].size(); j++){
                    if(l[i][j] == 1) finalGraph << i << "\t" << j << endl;
                }
            }
        }
        finalGraph << "-----------" << endl;
    }
    finalGraph.close();
}