#include<iostream>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

class Edge;
class Vertex;

class Edge {
  public:
    int DestinationVertexID;
  int weight;

  Edge() {}
  Edge(int destVID, int w) {
    DestinationVertexID = destVID;
    weight = w;
  }
  void setEdgeValues(int destVID, int w) {
    DestinationVertexID = destVID;
    weight = w;
  }
  void setWeight(int w) {
    weight = w;
  }

  int getDestinationVertexID() {
    return DestinationVertexID;
  }
  int getWeight() {
    return weight;
  }
};

class Vertex {
  public:
    int state_id;
  string state_name;

  list < Edge > edgeList;

  Vertex() {
    state_id = 0;
    state_name = "";
  }

  Vertex(int id, string sname) {
    state_id = id;
    state_name = sname;
  }

  int getStateID() {
    return state_id;
  }
  string getStateName() {
    return state_name;
  }
  void setID(int id) {
    state_id = id;
  }
  void setStateName(string sname) {
    state_name = sname;
  }

  list < Edge > getEdgeList() {
    return edgeList;
  }

  //  void addEdgeToEdgelist(int toVertexID, int weight)
  //  {
  //	  	Edge e(toVertexID,weight);
  //		edgeList.push_back(e); 
  //		cout<<"Edge between "<<state_id<<" and "<<toVertexID<<" added Successfully"<<endl; 	
  //  }

  void printEdgeList() {
    cout << "[";
    for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
      cout << it -> getDestinationVertexID() << "(" << it -> getWeight() << ") --> ";
    }
    cout << "]";
    cout << endl;
  }

  void updateVertexName(string sname) {
    state_name = sname;
    cout << "Vertex Name Updated Successfully";
  }

};

class Graph {

  vector < Vertex > vertices;

  public:

    bool checkIfVertexExistByID(int vid) {
      bool flag = false;
      for (int i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).getStateID() == vid) {
          return true;
        }
      }
      return flag;
    }

  void addVertex(Vertex newVertex) {
    bool check = checkIfVertexExistByID(newVertex.getStateID());
    if (check == true) {
      //cout << "Vertex with this ID already exist" << endl;
    } else {
      vertices.push_back(newVertex);
      //cout << "New Vertex Added Successfully" << endl;
    }
  }

  Vertex getVertexByID(int vid) {
    Vertex temp;
    for (int i = 0; i < vertices.size(); i++) {
      temp = vertices.at(i);
      if (temp.getStateID() == vid) {
        return temp;
      }
    }
    return temp;
  }

  bool checkIfEdgeExistByID(int fromVertex, int toVertex) {
    Vertex v = getVertexByID(fromVertex);
    list < Edge > e;
    e = v.getEdgeList();
    bool flag = false;
    for (auto it = e.begin(); it != e.end(); it++) {
      if (it -> getDestinationVertexID() == toVertex) {
        flag = true;
        return flag;
        break;
      }

    }
    return flag;
  }

  void updateVertex(int oldVID, string vname) {
    bool check = checkIfVertexExistByID(oldVID);
    if (check == true) {
      for (int i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).getStateID() == oldVID) {
          vertices.at(i).setStateName(vname);
          break;
        }
      }
      cout << "Vertex(State) Updated Successfully " << endl;
    }
  }

  void addEdgeByID(int fromVertex, int toVertex, int weight) {
    bool check1 = checkIfVertexExistByID(fromVertex);
    bool check2 = checkIfVertexExistByID(toVertex);

    bool check3 = checkIfEdgeExistByID(fromVertex, toVertex);
    if ((check1 && check2 == true)) {

      if (check3 == true) {
        //cout << "Edge between " << getVertexByID(fromVertex).getStateName() << "(" << fromVertex << ") and " << getVertexByID(toVertex).getStateName() << "(" << toVertex << ") Already Exist" << endl;
      } else {

        for (int i = 0; i < vertices.size(); i++) {

          if (vertices.at(i).getStateID() == fromVertex) {
            Edge e(toVertex, weight);
            //edgeList.push_back(e); 
            //vertices.at(i).addEdgeToEdgelist(toVertex,weight);
            vertices.at(i).edgeList.push_back(e);
          } else if (vertices.at(i).getStateID() == toVertex) {
            Edge e(toVertex, weight);
            //edgeList.push_back(e); 
            //vertices.at(i).addEdgeToEdgelist(fromVertex,weight);
            vertices.at(i).edgeList.push_back(e);
          }
        }

        //cout << "Edge between " << fromVertex << " and " << toVertex << " added Successfully" << endl;
      }
    } else {
      //cout << "Invalid Vertex ID entered.";
    }
  }

  void updateEdgeByID(int fromVertex, int toVertex, int newWeight) {
    bool check = checkIfEdgeExistByID(fromVertex, toVertex);
    if (check == true) {
      for (int i = 0; i < vertices.size(); i++) {

        if (vertices.at(i).getStateID() == fromVertex) {
          for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
            if (it -> getDestinationVertexID() == toVertex) {
              it -> setWeight(newWeight);
              break;
            }

          }

        } else if (vertices.at(i).getStateID() == toVertex) {
          for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
            if (it -> getDestinationVertexID() == fromVertex) {
              it -> setWeight(newWeight);
              break;
            }

          }
        }
      }
      cout << "Edge Weight Updated Successfully " << endl;
    } else {
      cout << "Edge between " << getVertexByID(fromVertex).getStateName() << "(" << fromVertex << ") and " << getVertexByID(toVertex).getStateName() << "(" << toVertex << ") DOES NOT Exist" << endl;
    }
  }

  void deleteEdgeByID(int fromVertex, int toVertex) {
    bool check = checkIfEdgeExistByID(fromVertex, toVertex);
    if (check == true) {
      for (int i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).getStateID() == fromVertex) {
          for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
            if (it -> getDestinationVertexID() == toVertex) {
              vertices.at(i).edgeList.erase(it);
              //cout<<"First erase"<<endl;
              break;
            }
          }
        }

        if (vertices.at(i).getStateID() == toVertex) {

          for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
            if (it -> getDestinationVertexID() == fromVertex) {
              vertices.at(i).edgeList.erase(it);
              //cout<<"second erase"<<endl;
              break;
            }
          }
        }
      }
      cout << "Edge Between " << fromVertex << " and " << toVertex << " Deleted Successfully." << endl;
    }
  }

  void deleteVertexByID(int vid) {
    int vIndex = 0;
    for (int i = 0; i < vertices.size(); i++) {
      if (vertices.at(i).getStateID() == vid) {
        vIndex = i;
      }
    }
    for (int i = 0; i < vertices.size(); i++) {
      for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
        if (it -> getDestinationVertexID() == vid) {
          vertices.at(i).edgeList.erase(it);
          break;
        }
      }

    }
    vertices.erase(vertices.begin() + vIndex);
    cout << "Vertex Deleted Successfully" << endl;
  }

  void getAllNeigborsByID(int vid) {
    cout << getVertexByID(vid).getStateName() << " (" << getVertexByID(vid).getStateID() << ") --> ";
    for (int i = 0; i < vertices.size(); i++) {
      if (vertices.at(i).getStateID() == vid) {
        cout << "[";
        for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
          cout << it -> getDestinationVertexID() << "(" << it -> getWeight() << ") --> ";
        }
        cout << "]";

      }
    }

  }

  void printGraph() {
    for (int i = 0; i < vertices.size(); i++) {
      Vertex temp;
      temp = vertices.at(i);
      cout << temp.getStateName() << " (" << temp.getStateID() << ") --> ";
      temp.printEdgeList();
    }
  }

};

