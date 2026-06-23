#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
using namespace std;
namespace fs = std::filesystem;
string nombreExamen;

struct Pregunta{
    string pregunta;
    string op1;
    string op2;
    string op3;
    string op4;
    int correcta;
    int puntaje;
};

struct Nodo{
    Pregunta dato;
    int respuestaAlumno = -1;
    Nodo *sig;
    Nodo *ant;
};

struct Lista{
    Nodo *inicio;
    Nodo *fin;
};

struct Alumno{
    string nombre;
    string id;
    int puntaje;
};

void iniciarLista(Lista &examen){
    examen.inicio = NULL;
    examen.fin = NULL;
}

void capturarDatos(Pregunta &p){
    cout << "Pregunta: "; cin.ignore();
    getline(cin,p.pregunta);
    cout << "Opcion 1: ";
    getline(cin,p.op1);
    cout << "Opcion 2: ";
    getline(cin,p.op2);
    cout << "Opcion 3: ";
    getline(cin,p.op3);
    cout << "Opcion 4: ";
    getline(cin,p.op4);
    cout << "Respuesta correcta: ";
    cin >> p.correcta;
    cout << "Puntaje: ";
    cin >> p.puntaje;
}

void insertarNodo(Lista &examen, Pregunta p, Nodo*&actual){
    Nodo *nuevo = new Nodo;
    nuevo->dato = p;
    nuevo->sig = NULL;
    nuevo->ant = NULL;
    if(examen.inicio == NULL){
        examen.inicio = nuevo;
        examen.fin = nuevo;
    }
    else{
        nuevo->ant = examen.fin;
        examen.fin->sig = nuevo;
        examen.fin = nuevo;
    }
    if(actual == NULL){
        actual = examen.inicio;
    }
}

void insertarFin(Lista &examen, Nodo *&actual){
    Pregunta p;
    capturarDatos(p);
    insertarNodo(examen, p, actual);
}

void mostrarActual(Nodo *act){
    if(act == NULL){
        cout << "No hay preguntas";
        return;
    }
    cout << endl;
    cout << act->dato.pregunta << endl;
    cout << "a) " << act->dato.op1 << endl;
    cout << "b) " << act->dato.op2 << endl;
    cout << "c) " << act->dato.op3 << endl;
    cout << "d) " << act->dato.op4 << endl;
    cout << "Correcta: " << act->dato.correcta << endl;
    cout << "Puntaje: " << act->dato.puntaje << endl;
    cout << endl;
}

void mostrarLista(Lista &examen){ 
    Nodo *aux = examen.inicio; 
    while(aux!=NULL){ 
        cout << aux->dato.pregunta << endl; 
        cout << "a) " << aux->dato.op1 << endl; 
        cout << "b) " << aux->dato.op2 << endl; 
        cout << "c) " << aux->dato.op3 << endl; 
        cout << "d) " << aux->dato.op4 << endl; 
        cout << "Correcta: " << aux->dato.correcta << endl; 
        cout << "Puntaje: " << aux->dato.puntaje << endl; 
        aux = aux->sig; 
    } 
}

void siguiente(Nodo *&act){
    if(act == NULL){
        return;
    }
    if(act->sig != NULL){
        act = act->sig;
    }
}

void anterior(Nodo *&act){
    if(act == NULL){
        return;
    }
    if(act->ant != NULL){
        act = act->ant;
    }
}

void guardarArchivo(Lista &examen, bool preguntarNombre = true){
    if(preguntarNombre){
        cout << "Nombre del examen: ";
        cin >> nombreExamen;
    }
    ofstream arch(nombreExamen + ".txt");
    if(!arch){
        cout << "No se creo el archivo";
        return;
    }
    Nodo *aux = examen.inicio;
    while(aux != NULL){
        arch << ":p;" << aux->dato.pregunta << endl;
        arch << ":op1;" << aux->dato.op1 << endl;
        arch << ":op2;" << aux->dato.op2 << endl;
        arch << ":op3;" << aux->dato.op3 << endl;
        arch << ":op4;" << aux->dato.op4 << endl;
        arch << ":r;op" << aux->dato.correcta << endl;
        arch << aux->dato.puntaje << "." << endl;
        arch << endl;
        aux = aux->sig;
    }
    arch.close();
}

void leerArchivo(Lista &examen, Nodo *&act, string nombre){
    iniciarLista(examen);
    act = NULL;
    nombreExamen = nombre;
    ifstream arch(nombreExamen + ".txt");
    if(!arch){
        cout << "No se abrio el archivo" << nombreExamen << ".txt" << endl;
        system("pause");
        return;
    }
    Pregunta p;
    string linea;
    while(getline(arch,linea)){
        if(linea ==""){
            continue;
        }
        if(linea.substr(0,3) == ":p;"){
            p.pregunta = linea.substr(3);
        } else if(linea.substr(0,5) == ":op1;"){
            p.op1 = linea.substr(5);
        } else if(linea.substr(0,5) == ":op2;"){
            p.op2 = linea.substr(5);
        } else if(linea.substr(0,5) == ":op3;"){
            p.op3 = linea.substr(5);
        } else if(linea.substr(0,5) == ":op4;"){
            p.op4 = linea.substr(5);
        } else if(linea.substr(0,5) == ":r;op"){
            p.correcta = linea[5] - '0';
        } else if(linea[linea.size()-1] == '.'){
            linea.erase(linea.size()-1);
            p.puntaje = stoi(linea);
            insertarNodo(examen,p,act);
        } 
    }
}

void generarExamen(Lista &examen, Nodo *&actual){
    system("cls");
    int opc;
    do{
        cout << "Agregar pregunta...........1" << endl;
        cout << "Mostrar actual.............2" << endl;     
        cout << "Siguiente..................3" << endl;
        cout << "Anterior...................4" << endl;
        cout << "MostrarLista...............5" << endl;
        cout << "Guardar y regresar.........6" << endl;
        cin >> opc;
        system("cls");
        switch(opc){
            case 1: insertarFin(examen, actual); break;
            case 2: mostrarActual(actual);
                    system("pause"); break;
            case 3: siguiente(actual); break;
            case 4: anterior(actual); break;
            case 5: mostrarLista(examen); break;
            default: cout << "Opcion no valida" << endl;
        }
    }while(opc!=6);
    guardarArchivo(examen);
}

void modificarPreguntas(Nodo *actual){
    if(actual==NULL){
        return;
    }
    cin.ignore();
    cout << "Nueva pregunta: ";
    getline(cin, actual->dato.pregunta);
    system("cls");
}

void modificarOpciones(Nodo* actual){
    if(actual == NULL){
        return;
    }
    cin.ignore();
    cout << "a) "; getline(cin, actual->dato.op1);
    cout << "b) "; getline(cin, actual->dato.op2);
    cout << "c) "; getline(cin, actual->dato.op3);
    cout << "d) "; getline(cin, actual->dato.op4);
    system("cls");
}

void modificarRespuesta(Nodo *actual){
    if(actual == NULL){
        return;
    }
    cin.ignore();
    cout << "Nueva respuesta: ";
    cin >> actual->dato.correcta;
    system("cls");
}

void modificarPuntaje(Nodo *actual){
    if(actual == NULL){
        return;
    }    
    cin.ignore();
    cout << "Nuevo puntaje: "; 
    cin >> actual->dato.puntaje;
    system("cls");
}

string seleccionarExamen(){
    vector<string> examenes;
    int opc;
    for(const auto &archivo : fs::directory_iterator(".")){
        if(archivo.path().extension() == ".txt"){
            examenes.push_back(archivo.path().stem().string());
        }
    }
    if(examenes.empty()){
        cout<<"No hay examenes disponibles" << endl;
        return "";
    }
    cout << "-----Examenes disponibles-----" << endl;
    for(int i=0; i<examenes.size();i++){
        cout << examenes[i] << "........." << i+1 << endl;
    }
    do{
        cin >> opc;
    }while(opc < 1 || opc > examenes.size());
    system("cls");
    return examenes[opc-1];
}

void modificarExamen(Lista &examen, Nodo *&actual){
    string nombre = seleccionarExamen();
    if(nombre == ""){
        return;
    }
    leerArchivo(examen, actual, nombre);
    int opc;
    do{
        mostrarActual(actual);
        cout << "Modificar pregunta.............1" << endl;
        cout << "Modificar opciones.............2" << endl;
        cout << "Modificar respuesta............3" << endl;
        cout << "Modificar puntaje..............4" << endl;
        cout << "Pregunta anterior..............5" << endl;
        cout << "Pregunta siguiente.............6" << endl;
        cout << "Guardar y salir................7" << endl;
        cin >> opc;
        switch(opc){
            case 1: modificarPreguntas(actual); break;
            case 2: modificarOpciones(actual); break; 
            case 3: modificarRespuesta(actual); break;
            case 4: modificarPuntaje(actual); break;
            case 5: anterior(actual); break;
            case 6: siguiente(actual); break;
        }
        system("cls");
    }while(opc != 7);
    guardarArchivo(examen, false);
}

void responderPregunta(Nodo *actual){
    do{
        cout << "Respuesta (1 - 4): ";
        cin >> actual->respuestaAlumno;
    }while(actual->respuestaAlumno < 1 || actual->respuestaAlumno > 4);
    system("cls");
}

void resultados(Alumno alu, Lista &examen){
    int suma=0, total=0;
    Nodo *aux = examen.inicio;
    while(aux!=NULL){
        total += aux->dato.puntaje;
        if(aux->respuestaAlumno == aux->dato.correcta){
            suma += aux->dato.puntaje;
        }
        aux = aux->sig;
    }
    cout << "Nombre: " << alu.nombre << endl;
    cout << "Id: " << alu.id << endl;
    cout << "Puntaje: " << suma << "/" << total << endl;
    system("pause");
}

void aplicarExamen(Lista &examen, Nodo *actual){
    string nombre = seleccionarExamen();
    int opc;
    if(nombre == ""){
        return;
    }
    leerArchivo(examen, actual, nombre);
    Alumno alu;
    cin.ignore();
    cout << "Nombre: "; getline(cin,alu.nombre);
    cout << "ID: "; getline(cin, alu.id);
    do{
        system("cls");
        cout << actual->dato.pregunta << endl;
        cout << "a) " << actual->dato.op1 << endl;
        cout << "b) " << actual->dato.op2 << endl;
        cout << "c) " << actual->dato.op3 << endl;
        cout << "d) " << actual->dato.op4 << endl << endl;
        if(actual->respuestaAlumno != 1){
            cout << "Respuesta seleccionada: " << actual->respuestaAlumno << endl;
        }
        
        cout << "Responder.................1" << endl;
        cout << "Pregunta anterior.........2" << endl;
        cout << "Pregunta siguiente........3" << endl;
        cout << "Terminar examen...........4" << endl;
        cin >> opc;
        switch(opc){
            case 1: responderPregunta(actual); break;
            case 2: anterior(actual); break;
            case 3: siguiente(actual); break;
            case 4: resultados(alu, examen);
                    opc = 5; break;
            default: cout << "Opcion no valida" << endl;
        }
    }while(opc != 5);
}

int main(){
    system("cls");
    Nodo *actual = NULL;
    Lista examen;
    iniciarLista(examen);
    int opc;
    do{
        cout << "------------MENU------------" << endl;
        cout << "Generar examen.............1" << endl;
        cout << "Modificar examen...........2" << endl;
        cout << "Aplicar examen.............3" << endl;
        cout << "Salir......................4" << endl;
        cin >> opc;
        switch(opc){
            case 1: iniciarLista(examen);
                    actual = NULL;
                    generarExamen(examen, actual); break;
            case 2: iniciarLista(examen);
                    actual = NULL;
                    modificarExamen(examen, actual); 
                    system("pause"); break;
            case 3: iniciarLista(examen);
                    actual = NULL;
                    aplicarExamen(examen, actual); break;
            default: cout << "Opcion no valida" << endl;
        }
        system("cls");
    }while(opc!=4);
    return 0;
}