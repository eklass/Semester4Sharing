#define _USE_MATH_DEFINES
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <regex>
#include <vector>
#include <map>
#include <limits>
#include <sstream>
#include <stdio.h>
#include <math.h>
#include <GLUT/GLUT.h>
#include <unistd.h>

using namespace std;
#if !defined(BUFSIZE)
#define BUFSIZE 512
#endif
#define BEZIERMODEON 1
#define BEZIERMODEOFF 0
#define BEZIERPATH "/Users/erichklassen/Documents/Studium/Uni/Bielefeld/Semester4/Computergrafik/Pr/08..eig.07/obj-Files/beziercurvePrak.obj"
#define OBJPATH1 "/Users/erichklassen/Documents/Studium/Uni/Bielefeld/Semester4/Computergrafik/Pr/08..eig.07/obj-Files/RoboMitTexasHut.obj"
#define OBJPATH2 "/Users/erichklassen/Documents/Studium/Uni/Bielefeld/Semester4/Computergrafik/Pr/08..eig.07/obj-Files/stanford_bunny_closed.obj"
#define SPEED 0.5f

struct vert{
    float x, y, z;
};

//Method deklaration
void divideCasteljauCurve(vector<vert*> *source, vector<vert*> *target, float t);
void loadObjectFile(string path);
void showBezierCurve();
void drawPoint(float xcoord, float ycoord, float zcoord, float color[3], float size);

// Global vars :
float size = 1;			//Kreisgroesse
float rotate_x = 0;		//W・felausrichtung
float rotate_y = 0;
float rotate_z = 0;
float sphereXPOS = 0.0f;
float sphereYPOS = 0.0f;
float sphereZPOS = 0.0f;
float ORG[3] = { 0, 0, 0 };
float XP[3] = { 5, 0, 0 }, XN[3] = { -5, 0, 0 },
YP[3] = { 0, 5, 0 }, YN[3] = { 0, -5, 0 },
ZP[3] = { 0, 0, 5 }, ZN[3] = { 0, 0, -5 };
int drawBBox = 1;

//Der Beziermodus wechsel quasi zwischen der Aufgabe 6 u 7. Warum?.. um die Aufgaben ineinanderzufuehren
int modus=0;

//bezierZeichnen dient daf殲 in der Beziermodeoff die bezierkurve an oder auszuschalten
int bezierZeichnen=0;


float precision = 50;
float tn = 1 / precision;
//float tn = -1;
vector<vert *> initialPoints; //vector holding our initial vertices
vector<vector<vert*>> loopList;
vector<vert *> bezierPoints;
int speed = 100;
bool drawZwischen = 1;

//<--Ende Global Vars

//declaration
struct HE_edge;
struct HE_vert;
struct HE_face;
vector<string> split(string str, char delimiter);


// structs for reading the .obj content!
struct VERT_LIST{
    float x;
    float y;
    float z;
    
};
struct FACE_LIST{
    vector<int> vertices;
};
vector<VERT_LIST*> vertList_HEAD;
vector<FACE_LIST*> faceList_HEAD;
//<--



//definition of Half-Edge structs
struct HE_edge {
    HE_vert *vert;// start-vertex of the half-edge
    HE_edge *pair;// oppositely oriented adjacent half-edge
    HE_face *face;// face the half-edge borders
    HE_edge *next;// next half-edge around the face
    
};

struct HE_vert {
    float x;
    float y;
    float z;
    HE_edge *edge;// one of the half-edges emanating from the vertex
};

struct HE_face {
    HE_edge *edge;// one of the half-edges bordering the face
};

vector<HE_edge*> edgeList;
vector<HE_vert*> vertexList;
vector<HE_face*> faceList;

//Parse the file Input and fill two lists with vertices and faces for futher processing:
void fillLists(string input){
    regex vertex("v.+");
    regex face("f.+");
    vector<string> splitted = split(input, ' ');
    if (input[0] == 'v'&&input[1] != 't'&&input[1] != 'n'){
        //add new vertex
        VERT_LIST * vertListTmp = new VERT_LIST;
        vertListTmp->x = stof(splitted[1]);
        vertListTmp->y = stof(splitted[2]);
        vertListTmp->z = stof(splitted[3]);
        //append new node:
        vertList_HEAD.push_back(vertListTmp);
    }
    //    else if (regex_match(input, face)){
    else if (input[0] == 'f'){
        //add new face
        FACE_LIST *faceListTmp = new FACE_LIST;
        for (unsigned int i = 1; i < splitted.size(); i++){
            faceListTmp->vertices.push_back(stoi(splitted[i]) - 1);
        }
        //append new node:
        faceList_HEAD.push_back(faceListTmp);
        
    }
}

void ReplaceStringInPlace(string& subject, const string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
}

void readFile(string filename){
    ifstream quelle(filename);
    if (!quelle){
        cerr << "File: " << filename << " not Found!";
    }
    else {
        while (quelle){
            string zeile;
            getline(quelle, zeile);
            //cout << zeile + "\n";
            ReplaceStringInPlace(zeile, "  ", " "); // doppeltes leerzeichen entfernen!
            fillLists(zeile);
        }
    }
}

void buildHalfEdge2(){ //1000x schneller, aber next wird  nicht immer gesetzt...
    map< pair<int, int>, HE_edge* > Edges;
    map< tuple<float, float, float>, HE_vert*> Vertices;
    // faceList hingegen ist eine globale (vorerst leere) Liste die Faces h獲t
    for (FACE_LIST* F : faceList_HEAD){
        HE_face* localFace = new HE_face;
        faceList.push_back(localFace);
        //Half-Edges erstellen:   (n,n+1) = new edge, (n,m) = new edge, (m,n) = new edge; n>m;
        for (unsigned int u = 0; u < F->vertices.size() - 1; u++){
            Edges[pair<int, int>(F->vertices[u], F->vertices[u + 1])] = new HE_edge;
            HE_edge * localEdge = Edges[pair<int, int>(F->vertices[u], F->vertices[u + 1])];
            localEdge->face = localFace;
            edgeList.push_back(localEdge);
            
            //dazugehoeriger Vertex
            if (Vertices.find(tuple<float, float, float>(vertList_HEAD[F->vertices[u]]->x, vertList_HEAD[F->vertices[u]]->y, vertList_HEAD[F->vertices[u]]->z)) == Vertices.end()){ // if vertex doesnt exist yet:
                
                Vertices[tuple<float, float, float>(vertList_HEAD[F->vertices[u]]->x, vertList_HEAD[F->vertices[u]]->y, vertList_HEAD[F->vertices[u]]->z)] = new HE_vert; //initialize new vert
                HE_vert *newVert = Vertices[tuple<float, float, float>(vertList_HEAD[F->vertices[u]]->x, vertList_HEAD[F->vertices[u]]->y, vertList_HEAD[F->vertices[u]]->z)]; // 'copy' to local variable
                newVert->edge = localEdge;
                newVert->x = vertList_HEAD[F->vertices[u]]->x;
                newVert->y = vertList_HEAD[F->vertices[u]]->y;
                newVert->z = vertList_HEAD[F->vertices[u]]->z;
                vertexList.push_back(newVert);
                localEdge->vert = newVert;
            }
            else {
                localEdge->vert = Vertices[tuple<float, float, float>(vertList_HEAD[F->vertices[u]]->x, vertList_HEAD[F->vertices[u]]->y, vertList_HEAD[F->vertices[u]]->z)];
            }
        }
        //manually create  last->front edge:
        Edges[pair<int, int>(F->vertices.back(), F->vertices.front())] = new HE_edge;
        HE_edge *lastEdge = Edges[pair<int, int>(F->vertices.back(), F->vertices.front())];
        
        
        if (Vertices.find(tuple<float, float, float>(vertList_HEAD[F->vertices.back()]->x, vertList_HEAD[F->vertices.back()]->y, vertList_HEAD[F->vertices.back()]->z)) == Vertices.end()){ // if vertex doesnt exist yet:
            
            Vertices[tuple<float, float, float>(vertList_HEAD[F->vertices.back()]->x, vertList_HEAD[F->vertices.back()]->y, vertList_HEAD[F->vertices.back()]->z)] = new HE_vert; //initialize new vert
            HE_vert *newVert = Vertices[tuple<float, float, float>(vertList_HEAD[F->vertices.back()]->x, vertList_HEAD[F->vertices.back()]->y, vertList_HEAD[F->vertices.back()]->z)]; // 'copy' to local variable
            newVert->edge = lastEdge;
            newVert->x = vertList_HEAD[F->vertices.back()]->x;
            newVert->y = vertList_HEAD[F->vertices.back()]->y;
            newVert->z = vertList_HEAD[F->vertices.back()]->z;
            vertexList.push_back(newVert);
            lastEdge->vert = newVert;
        }
        else {
            lastEdge->vert = Vertices[tuple<float, float, float>(vertList_HEAD[F->vertices.back()]->x, vertList_HEAD[F->vertices.back()]->y, vertList_HEAD[F->vertices.back()]->z)];
        }
        
        lastEdge->face = localFace;
        localFace->edge = lastEdge;
        edgeList.push_back(lastEdge);
        
        //Half-Edge-> next binden : set Edges[pair(u, v)]->nextHalfEdge to next half - edge in F
        for (unsigned int i = 0; i < F->vertices.size() - 1; i++){
            
            if (i < F->vertices.size() - 3){
                //cout << "inner loop:(" << F->vertices[i] + 1 << "," << F->vertices[i + 1] + 1 << ") -> (" << F->vertices[i + 1] + 1 << "," << F->vertices[i + 2] + 1 << ")" << endl;
                Edges[pair<int, int>(F->vertices[i], F->vertices[i + 1])]->next = Edges[pair<int, int>(F->vertices[i + 1], F->vertices[i + 2])];
            }
            
            //define pairs: (
            if (Edges.find(pair<int, int>(F->vertices[i + 1], F->vertices[i])) != Edges.end()){
                
                Edges[pair<int, int>(F->vertices[i], F->vertices[i + 1])]->pair = Edges[pair<int, int>(F->vertices[i + 1], F->vertices[i])];
                Edges[pair<int, int>(F->vertices[i + 1], F->vertices[i])]->pair = Edges[pair<int, int>(F->vertices[i], F->vertices[i + 1])];
            }
        }
        //manually bind last 3 next's:
        //cout << "outer loop:(" << F->vertices[F->vertices.size() - 3] + 1 << "," << F->vertices[F->vertices.size() - 2] + 1 << ") -> (" << F->vertices[F->vertices.size() - 2] + 1 << "," << F->vertices[F->vertices.size() - 1] + 1 << ")" << endl;
        //cout << "outer loop:(" << F->vertices[F->vertices.size() - 2] + 1 << "," << F->vertices[F->vertices.size() - 1] + 1 << ") -> (" << F->vertices[F->vertices.size() - 1] + 1 << "," << F->vertices[0] + 1 << ")" << endl;
        Edges[pair<int, int>(F->vertices[F->vertices.size() - 3], F->vertices[F->vertices.size() - 2])]->next = Edges[pair<int, int>(F->vertices[F->vertices.size() - 2], F->vertices[F->vertices.size() - 1])];
        Edges[pair<int, int>(F->vertices[F->vertices.size() - 2], F->vertices[F->vertices.size() - 1])]->next = Edges[pair<int, int>(F->vertices[F->vertices.size() - 1], F->vertices[0])]; //HIER WAR DER FEHLER! da stand F->vertices[F->vertices[0]] anstatt F->vertices[0]!! daemlich^^
        Edges[pair<int, int>(F->vertices.back(), F->vertices.front())]->next = Edges[pair<int, int>(F->vertices[0], F->vertices[1])]; // Hier genauso!
        
        //check last possible pairs: (first-last / last-first)
        if (Edges.find(pair<int, int>(F->vertices.front(), F->vertices.back())) != Edges.end()){
            Edges[pair<int, int>(F->vertices.front(), F->vertices.back())]->pair = Edges[pair<int, int>(F->vertices.back(), F->vertices.front())];
            Edges[pair<int, int>(F->vertices.back(), F->vertices.front())]->pair = Edges[pair<int, int>(F->vertices.front(), F->vertices.back())];
        }
        
    }
}

void printStatistics(){
    //Faces:
    cout << "Anzahl Faces: " << faceList.size() << endl;
    vector<int> faceValenz(20, 0);
    for (HE_face *f : faceList){
        HE_edge *e = f->edge;
        int tmpVal = 0;
        do{
            tmpVal++;
            e = e->next;
        } while (e != f->edge);
        faceValenz[tmpVal] = faceValenz[tmpVal] + 1;
    }
    for (unsigned int i = 0; i < faceValenz.size(); i++){
        if (faceValenz[i] != 0){
            cout << "Faces mit Valenz " << i << ": " << faceValenz[i] << endl;
        }
    }
    //Vertices
    cout << "Anzahl Vertices: " << vertexList.size() << endl;
    /* Valenzen funktionieren noch nicht auf Mayaobj!
     vector<int> vertValenz(20, 0);
     for (HE_vert *v : vertexList){
     HE_edge *e = v->edge;
     int tmpVal = 0;
     do{
     e = e->pair->next;
     tmpVal++;
     } while (v->edge != e);
     vertValenz[tmpVal] = vertValenz[tmpVal] + 1;
     }
     for (unsigned int i = 0; i < vertValenz.size(); i++){
     if (vertValenz[i] != 0){
     cout << "Vertices mit Valenz " << i << ": " << vertValenz[i] << endl;
     }
     }*/
    
    //Edges:
    cout << "Anzahl Edges: " << edgeList.size() << endl;
}

void testHES(){
    //edges
    for (unsigned int i = 0; i < edgeList.size(); i++){
        //alles gesetzt?
        if (edgeList[i]->face == NULL){
            cout << "edge: face null! " << i << endl;
        }
        if (edgeList[i]->next == NULL){
            cout << "edge: next null!" << i << endl;
        }
        if (edgeList[i]->vert == NULL){
            cout << "edge: vert null!" << i << endl;
        }
        if (edgeList[i]->pair == NULL){
            cout << "edge: pair null!" << i << endl;
        }
        if (edgeList[i]->vert != edgeList[i]->pair->next->vert){
            cout << "edge: edge->pair->next zeigt nicht auf edge->vert!" << i << endl;
        }
        //pair konsistent?
        if (edgeList[i]->pair->pair != edgeList[i]){
            cout << "edge: pair nicht konsistent!" << endl;
        }
    }
    //faces
    for (unsigned int a = 0; a < faceList.size(); a++){
        //durchlaufen aller edges:
        HE_edge * e = faceList[a]->edge;
        do{
            //pair:
            if (e->pair->pair != e){
                cout << "face: pair inkonsistent!" << a << endl;
            }
            //zeigt edge auf aktuelles face?
            if (e->face != faceList[a]){
                cout << "face: edge zeigt nicht auf face!" << a << endl;
            }
            e = e->next;
        } while (faceList[a]->edge != e);
    }
    //vertices
    for (unsigned int n = 0; n < vertexList.size(); n++){
        //durchlaufen aller kanter durch edge->pair->next->pair->next->...
        HE_edge * e = vertexList[n]->edge;
        do{
            //pair konsistent?
            if (e->pair->pair != e){
                cout << "vert: pair inkonsistent!" << n << endl;
            }
            //nachbarvertices konsistent mit halfedges verbunden?
            if (e->vert->edge == NULL){
                cout << "vert: vert hat keine edge!" << n << endl;
            }
            if (e->vert != e->pair->next->vert){
                cout << "vert: e->pair->next zeigt nicht auf e->vert!" << n << endl;
            }
            
            e = e->pair; //wechsle zum pair!
            
            if (e->pair->pair != e){
                cout << "vert: pair inkonsistent!" << n << endl;
            }
            //nachbarvertices konsistent mit halfedges verbunden?
            if (e->vert->edge == NULL){
                cout << "vert: vert hat keine edge!" << n << endl;
            }
            if (e->vert != e->pair->next->vert){
                cout << "vert: e->pair->next zeigt nicht auf e->vert!" << n << endl;
            }
            e = e->next;
            
            
        } while (vertexList[n]->edge != e);
        
    }
    cout << "all tests done." << endl;
}

vector<string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;
    
    while (getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    
    return internal;
}

void drawBoundingBox(){
    float lowx = 0, lowy = 0, lowz = 0;
    float highx = 0, highy = 0, highz = 0;
    for (VERT_LIST* vert : vertList_HEAD){
        if (lowx > vert->x){
            lowx = vert->x;
        }
        if (lowy > vert->y){
            lowy = vert->y;
        }
        if (lowz > vert->z){
            lowz = vert->z;
        }
        if (highx < vert->x){
            highx = vert->x;
        }
        if (highy < vert->y){
            highy = vert->y;
        }
        if (highz < vert->z){
            highz = vert->z;
        }
    }
    //scale:
    lowx = lowx*0.1*size;
    highx = highx*0.1*size;
    lowy = lowy*0.2*size;
    highy = highy*0.2*size;
    lowz = lowz*0.1*size;
    highz = highz*0.1*size;
    //<--
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    //vorne
    glVertex3d(lowx, lowy, lowz);
    glVertex3d(lowx, highy, lowz);
    glVertex3d(highx, lowy, lowz);
    glVertex3d(highx, highy, lowz);
    glVertex3d(lowx, lowy, lowz);
    glVertex3d(highx, lowy, lowz);
    glVertex3d(lowx, highy, lowz);
    glVertex3d(highx, highy, lowz);
    //hinten
    glVertex3d(lowx, lowy, highz);
    glVertex3d(lowx, highy, highz);
    glVertex3d(highx, lowy, highz);
    glVertex3d(highx, highy, highz);
    glVertex3d(lowx, lowy, highz);
    glVertex3d(highx, lowy, highz);
    glVertex3d(lowx, highy, highz);
    glVertex3d(highx, highy, highz);
    //seiten
    glVertex3d(lowx, highy, lowz);
    glVertex3d(lowx, highy, highz);
    glVertex3d(lowx, lowy, lowz);
    glVertex3d(lowx, lowy, highz);
    glVertex3d(highx, highy, lowz);
    glVertex3d(highx, highy, highz);
    glVertex3d(highx, lowy, lowz);
    glVertex3d(highx, lowy, highz);
    glEnd();
}

void drawMagic(){
    
    if (modus==BEZIERMODEOFF){
        glLoadIdentity();
        glTranslatef(0.0f, -1.0f, -10.0f);
    }
    glRotatef(rotate_x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotate_y, 0.0f, 1.0f, 0.0f);
    glRotatef(rotate_z, 0.0f, 0.0f, 1.0f);
    //glBegin(GL_POLYGON);
    
    for (HE_face *f : faceList){
        glBegin(GL_POLYGON);
        HE_edge * edd = f->edge;
        do{
            glVertex3d(edd->vert->x*0.1*size, edd->vert->y*0.2*size, edd->vert->z*0.1*size);
            //cout << "\nx: " << edd->vert->x << " y= " << edd->vert->y << " z= " << edd->vert->z;
            
            edd = edd->next;
        } while (f->edge != edd);
        glEnd();
    }
    
    if (drawBBox){
        drawBoundingBox();
    }
}

void drawMagicForBezier(){
    glRotatef(rotate_x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotate_y, 0.0f, 1.0f, 0.0f);
    glRotatef(rotate_z, 0.0f, 0.0f, 1.0f);
    //glBegin(GL_POLYGON);
    
    for (HE_face *f : faceList){
        glBegin(GL_POLYGON);
        HE_edge * edd = f->edge;
        do{
            glVertex3d(edd->vert->x*0.1*size, edd->vert->y*0.2*size, edd->vert->z*0.1*size);
            //cout << "\nx: " << edd->vert->x << " y= " << edd->vert->y << " z= " << edd->vert->z;
            
            edd = edd->next;
        } while (f->edge != edd);
        glEnd();
    }
    
    if (drawBBox){
        drawBoundingBox();
    }
}

void drawcircle(float size)
{
    glBegin(GL_LINE_STRIP);
    
    for (float i = 0; i <= 360; i++)
    {
        float angle = i / 360 * 2.0f * M_PI;
        
        float x = sinf(angle);
        float y = cosf(angle);
        
        glVertex2f(x*size, y*size);
    }
    glEnd();
}

void drawSphere(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    static float rotateTmp = 0;
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    //draw coord system:
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);  glVertex3fv(ORG);  glVertex3fv(XP);    // X axis is red.
    glColor3f(0, 1, 0);  glVertex3fv(ORG);  glVertex3fv(YP);    // Y axis is green.
    glColor3f(0, 0, 1);  glVertex3fv(ORG);  glVertex3fv(ZP);    // z axis is blue.
    glEnd();
    //<--
    glPopMatrix();
    
    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    drawMagic();
    glPopMatrix();
    
    /*                      draw newObejktintoSphere!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                  */
    glColor3f(0, 1, 1);
    glPushMatrix();
//    glRotatef(rotateTmp, 0, 1, 0);
//    glTranslatef(2.0f, 0, 0); // Verschiebung
    if(bezierZeichnen){
        showBezierCurve();
    }
    glPopMatrix();
    
    rotateTmp += SPEED;
    if (rotateTmp == 360){
        rotateTmp = 0;
    }
    
    
}

void bezierScaleAndTranslate(){
    float lowx = numeric_limits<float>::max(), lowy = numeric_limits<float>::max(), lowz = numeric_limits<float>::max(); // numeric_limits<float>::max() = maxValue
    float highx = 0, highy = 0, highz = 0;
    
    for (vert* v : initialPoints){
        if (v->x < lowx){
            lowx = v->x;
        }
        if (v->y < lowy){
            lowy = v->y;
        }
        if (v->z < lowz){
            lowz = v->z;
        }
        if (v->x > highx){
            highx = v->x;
        }
        if (v->y > highy){
            highy = v->y;
        }
        if (v->z > highz){
            highz = v->z;
        }
    }
    //scale -> get highest value:
    float highest = 0;
    if (highest < highx){
        highest = highx;
    }
    if (highest < highy){
        highest = highy;
    }
    if (highest < highz){
        highest = highz;
    }
    //translate!
    
    glTranslatef(-((lowx + highx) / 2), 0, 0);
    glTranslatef(0, -((lowy + highy) / 2), 0);
    glTranslatef(0, 0, -((lowz + highz) / 2));
    
    cout << "tx: " << -((lowx + highx) / 2) << endl;
    
    
    //glScalef(1 / highest, 1 / highest, 1 / highest);
}

void drawPoint(float xcoord, float ycoord, float zcoord, float color[3], float size){
    glPushMatrix();
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(xcoord, 0, 0);
    glTranslatef(0, ycoord, 0);
    glTranslatef(0, 0, zcoord);
    glutSolidSphere(size, 10, 10);
    glPopMatrix();
}

void drawCone(float xcoord, float ycoord, float zcoord, float color[3]){
    glPushMatrix();
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(xcoord, 0, 0);
    glTranslatef(0, ycoord, 0);
    glTranslatef(0, 0, zcoord);
    if (bezierPoints.size()){
        vert * v = bezierPoints.back();
        float entfernung = sqrt((pow((xcoord - v->x), 2) + (pow((ycoord - v->y), 2) + (pow((zcoord - v->z), 2)) )));
        float winkel = cos(entfernung / (M_PI / 2));
        cout << "winkel: " << winkel * 180 / M_PI << endl;
        //* 180/ M_PI
//        glRotatef(90 + winkel * 180 / M_PI, 1, 0, 0);
    }
    
    
    glRotatef(180, 0,0,0);
    //glutSolidCone(0.05, 0.2, 20, 20);
    
    //###HierMussDasObjektHin###
    glColor3f(1.0, 1.0, 0.0);
    drawMagicForBezier();
    //    glutSolidCone(0.05, 0.1, 20, 20);
    glPopMatrix();
}

vert* getNewPoint(vert* p1, vert* p2, float division){
    vert * newVert = new vert;
    float distance = sqrt(pow((p2->x - p1->x), 2) + pow((p2->y - p1->y), 2) + pow((p2->z - p1->z), 2));
    newVert->x = (1 - division)*p1->x + division * p2->x;
    newVert->y = (1 - division)*p1->y + division * p2->y;
    newVert->z = (1 - division)*p1->z + division * p2->z;
    return newVert;
}

void divideCasteljauCurve(vector<vert*> *source, vector<vert*> *target, float t){
    for (unsigned int i = 0; i < (*source).size() - 1; i++){
        vert* pi = getNewPoint((*source)[i], (*source)[i + 1], t);
        (*target).push_back(pi);
        
        if ((*source).size() == 2){
            float color[] {0, 0, 1};
            drawCone(pi->x, pi->y, pi->z, color);
            bezierPoints.push_back(pi);
        }
        else {
            if (drawZwischen){
                float color[] {0, 1, 0};
                drawPoint(pi->x, pi->y, pi->z, color, 0.02);
            }
        }
    }
    //draw connecting lines
    if (drawZwischen){
        glBegin(GL_LINE_STRIP);
        glColor3f(0, 1, 0);
        for (vert* v : (*target)){
            glVertex3d(v->x, v->y, v->z);
        }
        glEnd();
    }
}

void readFileBezier(string filename){
    vector<int> controlPoints; //vector containing control points
    int deg; // degree of curve
    //-->
    //Read inputFile & fill dataStructures
    ifstream quelle(filename);
    if (!quelle){
        cerr << "File: " << filename << " not Found!";
        exit(0);
    }
    else {
        while (quelle){
            string zeile;
            getline(quelle, zeile);
            if (zeile == ""){
                break;
            }
            ReplaceStringInPlace(zeile, "  ", " "); // doppeltes leerzeichen entfernen!
            vector<string> splitted = split(zeile, ' ');
            if (splitted[0] == "v"){
                vert* tmpVert = new vert;
                tmpVert->x = stof(splitted[1]);
                tmpVert->y = stof(splitted[2]);
                tmpVert->z = stof(splitted[3]);
                initialPoints.push_back(tmpVert);
            }
            else if (splitted[0] == "deg"){
                deg = stoi(splitted[1]);
            }
            else if (splitted[0] == "curv"){
                for (unsigned int i = 1; i < splitted.size(); i++){
                    controlPoints.push_back(stoi(splitted[i]));
                }
            }
        }
    }
    loopList.push_back(initialPoints);
}


void showBezierCurve(){
    
    if(modus==BEZIERMODEON) {
        usleep(speed);
        //draw initial points and connect them
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
    }
    //draw points
    for (vert* v : initialPoints){
        float color[] = { 1, 0, 0 };
        drawPoint(v->x, v->y, v->z, color, 0.04);
    }
    //draw connecting lines
    glBegin(GL_LINE_STRIP);
    glColor3f(0, 1, 1);
    for (vert* v : initialPoints){
        glVertex3d(v->x, v->y, v->z);
    }
    glEnd();
    //<--
    while (loopList.back().size() != 1){
        vector<vert *>   tmpVertices;
        divideCasteljauCurve(&(loopList.back()), &tmpVertices, tn);
        loopList.push_back(tmpVertices);
    }
    loopList.erase(loopList.begin() + 1, loopList.begin() + loopList.size());
    
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 0);
    for (vert *v : bezierPoints){
        glVertex3d(v->x, v->y, v->z);
    }
    glEnd();
    
    
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    
    if (modus==BEZIERMODEON){
        showBezierCurve();
    }
    else if (modus==BEZIERMODEOFF)
    {
        drawSphere();
    }
    
    // tn gibt den Speed an?!?!
    if (speed < 1000){
        tn += 0.5 / precision;
    }
    
    // (tn>=2)....tn=-1
    if (tn >= 1){
        tn = 1/precision;
        bezierPoints.erase(bezierPoints.begin(), bezierPoints.begin() + bezierPoints.size());
    }
    glutSwapBuffers();
}
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);  //Hintergrundfarbe  (gelb: 1 1 0 0)
    glShadeModel(GL_FLAT);
}
void reshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y)
{
    
    switch (key) {
            
        case '+':
            size = size * 1.5f;		//Kreis vergrern
            
            
            glScalef(1.1, 1.1, 1.1);
            
            glutPostRedisplay();
            break;
        case '-':
            size = size / 1.5f;		//Kreis verkleinern
            glScalef(0.9, 0.9, 0.9);
            glutPostRedisplay();
            break;
        case 'x':
            rotate_x = rotate_x + 1;	//W・fel um x drehen
            sphereXPOS += 0.01f;
            glutPostRedisplay();
            break;
        case 'y':
            rotate_y = rotate_y + 1;	//W・fel um y drehen
            sphereYPOS += 0.01f;
            glutPostRedisplay();
            break;
        case 'z':
            rotate_z = rotate_z + 1;	//W・fel um z drehen
            glutPostRedisplay();
            sphereZPOS += 0.01f;
            break;
        case 'X':
            rotate_x = rotate_x - 1;	//W・fel um x drehen
            sphereXPOS -= 0.01f;
            glutPostRedisplay();
            break;
        case 'Y':
            rotate_y = rotate_y - 1;	//W・fel um y drehen
            sphereYPOS -= 0.01f;
            glutPostRedisplay();
            break;
        case 'Z':
            rotate_z = rotate_z - 1;	//W・fel um z drehen
            glutPostRedisplay();
            sphereZPOS -= 0.01f;
            break;
            
        case 'b':
            if (precision > 5){
                precision -= 5;
            }
            else {
                precision = 5;
            }
            glutPostRedisplay();
            break;
        case 'B':
            precision += 5;
            glutPostRedisplay();
            break;
        case 'k':
            if (speed > 100){
                speed -= 100;
            }
            else {
                speed = 0;
            }
            glutPostRedisplay();
            break;
        case 'K':
            speed += 100;
            glutPostRedisplay();
            break;
        case 'v':
            if (drawZwischen){
                drawZwischen = 0;
            }
            else {
                drawZwischen = 1;
            }
            glutPostRedisplay();
            break;
    }
    
}

void specialkey(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_LEFT:
            cout << "left" << endl;
            glTranslatef(-0.5, 0, 0);
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            glTranslatef(0.5, 0, 0);
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            glTranslatef(0, 0.5, 0);
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            glTranslatef(0, -0.5, 0);
            glutPostRedisplay();
            break;
            
    }
}


void loadObjectFile(string path){
    readFile(path);
    buildHalfEdge2();
    printStatistics();
    //    testHES();
    
    string tmp;
    //cin >> tmp;
}

int loadHES = true;
int main(int argc, char** argv)
{
    modus=BEZIERMODEOFF;
    bezierZeichnen=1;
    if (modus==BEZIERMODEOFF){
        cout<<"Beziermode ist aus!"<<endl;
        if (loadHES){
            //loadObjectFile(OBJPATH1);
            /* The Merge between bezierCurve & Sphere */
            static bool read = 0;
            if (!read){
                readFileBezier(BEZIERPATH);
                readFile(OBJPATH1);
                buildHalfEdge2();
                read = 1;
            }
            loadHES = false;
        }
    }
    else if(modus==BEZIERMODEON){
        cout<<"Beziermode ist an!"<<endl;
        static bool read = 0;
        if (!read){
            readFileBezier(BEZIERPATH);
            readFile(OBJPATH1);
            buildHalfEdge2();
            printStatistics();
            read = 1;
        }
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Aufgabenblatt 1");
    init();
    glEnable(GL_DEPTH_TEST);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkey);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    
    
    
    glutIdleFunc(display);
    
    
    
    glutMainLoop();
    return 0;
}
