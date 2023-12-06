#include <iostream>
#include <ctime>

using namespace std;
//colores de texto
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define WHITE   "\x1B[37m"
#define RESET   "\x1b[0m"
//Colores de fondo
#define BG_WHITE   "\x1B[47m"
#define BG_BLUE    "\x1B[44m"
//Variables Globales
char tablero [3][3] = {' '};
int dificultad;//1 facil , 2 dificil
struct Estadisticas {
	int partidasHumanoVsHumano;
	int partidasHumanoVsComputadora;
	int partidasGanadasHumano1;
	int partidasGanadasHumano2;
	int partidasGanadasComputadora;
	int partidasEmpatadas;
	int partidasCanceladas;
	Estadisticas():
		partidasHumanoVsHumano(0),
		partidasHumanoVsComputadora(0),
		partidasGanadasHumano1(0),
		partidasGanadasHumano2(0),
		partidasGanadasComputadora(0),
		partidasEmpatadas(0),
		partidasCanceladas(0) 
	{}
};
//Metodos y funciones
void configuracionInicial();
char getJugarDeNuevo();
char getJugador();
void menuPrincipal();
void inicializaTablero();
void imprimirTablero();
void setDificultad();
bool hayGanador(char);
bool prediceVictoria(char [3][3],char);
bool tableroLleno();
bool realizarJugada(int, int, char);
bool simulaJugada(char [3][3],int,char);
bool esGanadorProximoMovimiento(int, int, char);
void jugadaMaquinaFacil();
void movimientoMaquinaDificil() ;
void jugarHumanoVsHumano(Estadisticas& estadisticas) ;
void jugarContraMaquina(Estadisticas& estadisticas);
void mostrarEstadisticas(const Estadisticas& estadisticas);
void muestraInstrucciones();

int main() {
	
	try {
		configuracionInicial();
		menuPrincipal();
	}
	catch(...) {
		cout << "Ha ocurrido un error inesperado..." << endl;
	}
	return 0;
	
	
}

void muestraInstrucciones(){
	bool bandera;
	bandera = true;
	int opc;
	do{
		bool bandera2;
		bandera2 = true;
		do{
			system("cls");
			cout<<"\tSelecciona las instrucciones que deseas consultar :"<<endl;
			cout<<"\t1. Instrucciones de juego."<<endl;
			cout<<"\t2. Instrucciones del programa."<<endl;
			cout<<"\t3. Regresar al men˙ principal."<<endl;
			cin>>opc;
			if(opc>=1 && opc<=3)
				bandera2=false;
			else{
				cout << RED<<BG_WHITE<<"OpciÛn no valida" << RESET << endl;
				cin.clear();
				cin.ignore();
				cin.get();
			}
			
		}while(bandera2);
		
		
		switch (opc)	{
		case 1:
			system("cls");
			cout << BLUE <<BG_WHITE << "Instrucciones del juego del gato:" << RESET << endl;
			cout<<"Se puede jugar con m·ximo dos jugadores."<<endl;
			cout<<"El juego tiene dos modos : Multijugador y Contra la computadora"<<endl;
			cout<<"En el modo Multijugador podr·n jugar dos jugadores (X y O) y Contra la computadora , seria un jugador (X) contra la maquina(O)."<<endl;
			cout<<"Si estas jugando en modo Multijugador el juego lo iniciar·° el jugador X , seguido del jugador O. Cada jugador deber·° seleccionar una posiciÛn del tablero del gato que va del 1 al 9 por cada turno."<<endl;
			cout<<"Si estas jugando contra la computadora , deber· seleccionar quien inicia primero , la maquina siempre ser· el jugador O. (La maquina puede jugar en modo difÌcil o modo f·cil , consulta como cambiar de modo en las instrucciones del programa)."<<endl;
			cout<<"Las casillas ya ocupadas por los jugadores estar·°n marcadas por X Û O."<<endl;
			cout<<"Un jugador gana si consigue tener una lÌnea horizontal, vertical o diagonal de tres de sus simbolos (X Û O) ."<<endl;
			cout<<"En caso de que todos las casillas del tablero est·n ya marcadas por los jugadores y no exista ganador, entonces se declarar·° un empate."<<endl;
			cout<<"!! Disfruta del juego !!"<<endl;
			cout<<"\nPresiona Enter para regresar al Men˙ anterior"<<endl;
			cin.clear();
			cin.ignore();
			cin.get();
			break;
		case 2:
			system("cls");
			cout << BLUE <<BG_WHITE << "Instrucciones del programa" << RESET << endl;
			cout<<"Al iniciar el programa , mostrar·° un men˙ principal en el cual aparecer·n las siguientes opciones:"<<endl;
			cout<<"\n1 .- Jugar Multijuador : Podr·n jugar dos jugadores , donde el primer turno ser· el jugador X y el segundo turno el jugador O. Al terminar la partida se guardar· que jugador gano , si fue empate o se cancelar· el juego y cuantas partidas han jugador en este modo."<<endl;
			cout<<"Para cancelar la partida , en lugar de teclear un n˙mero de la casilla , solo deber· teclear el n˙mero 0."<<endl;
			cout<<"El juego acepta , n˙mero y caracteres como respuesta , es muy importante siempre teclear las opciones que se te piden. En el caso de multijugador los jugadores para seleccionar la casilla donde tirar , siempre deben introducir un numero de la casilla que este disponible ( 0 al 9 ) . Si la casilla esta ocupada  , la casilla tendr· en lugar del n˙mero de casilla el sÌmbolo del jugador que ya la tiene ocupada, en caso de que se teclee el n·mero de esa casilla , el juego mandar· un mensaje de que esa casilla ya esta  ocupada."<<endl;
			cout<<"Al terminar la partida ya sea por juego ganado , empate o partida cancelada , se preguntar· si desea volver a jugar . Si desea otra partida debera teclear la letra S , en caso contrario la tecla N."<<endl;
			cout<<"\n2.- Jugar Contra la Computadora : El usuario deber·° seleccionar quien inicia la partida. Pr·cticamente son las mimas opciones solo que en este caso la computadora jugar· el turno correspondiente ."<<endl;
			cout<<"Por default el nivel de dificultad de la computadora es nivel f·cil , si quiere modificar el nivel , cons˙ltelo en la punto 5 ."<<endl;
			cout<<"\n3.- Ver instrucciones : Actualmente te encuentras en esta opciÛn , donde puedes ver las instrucciones del juego y del programa."<<endl;
			cout<<"\n4.- Ver EstadÌsticas : AquÌ ver·s las estadÌsticas guardadas de los partidos . Estas instrucciones se borran despuÈs de cerrar el programa , cada vez que inicia el juego estas inician en 0 . Podr·s consultar las siguientes estadÌsticas:"<<endl;
			cout<<"\tN˙mero de partidas jugadas entre Jugador X y Jugador O"<<endl;
			cout<<"\tN˙mero de partidas jugadas entre Jugador y Computadora"<<endl;
			cout<<"\tN˙mero de partidas ganadas por Jugador X"<<endl;
			cout<<"\tN˙mero de partidas ganadas por Jugador O"<<endl;
			cout<<"\tN˙mero de partidas ganadas por Computadora"<<endl;
			cout<<"\tN˙mero de partidas empatadas"<<endl;
			cout<<"\tN˙mero de partidas canceladas"<<endl;
			cout<<"\n5.- Configuraciones : En esta opciÛn podr· modificar el nivel de dificultad de la computadora ya sea modo f·cil tecleando 1, o modo difÌcil tecleando 2."<<endl;
			cout<<"\n6.- Salir : Para cerrar el juego"<<endl;
			cout<<"\nPresiona Enter para regresar al Men˙ anterior"<<endl;
			cin.clear();
			cin.ignore();
			cin.get();
			break;
		default:
			bandera = false;
			break;
		}
	}while(bandera);
	
	
	
	
	
}
	//establece las configuraciones iniciales del juego .
	void configuracionInicial(){
		//establece que el inivel de dificultad inicial sea facil
		dificultad = 1;
	}
		//funcion que le pregunta al usuario  que jugador va a iniciar primero , el humano o la maquina y hace validaciones de las respuestas
		char getJugador(){
			system("cls");
			bool bandera;
			bandera = true;
			int opc;
			do{
				system("cls");
				cout<<"\tSelecciona que jugador inicia la partida :"<<endl;
				cout<<"\t1. Jugador 1."<<endl;
				cout<<"\t2. Computadora."<<endl;
				cin>>opc;
				if(opc>=1 && opc<=2)
					bandera=false;
				else{
					cout << RED<<BG_WHITE<<"OpciÛn no valida" << RESET << endl;
					cin.clear();
					cin.ignore();
					cin.get();
				}
			}while(bandera);
			if (opc == 1)
				return 'X';
			else
				return 'O';
			
		}
			//funcion que le pregunta al usuario si desea jugar de nuevo y hace validaciones de las respuestas
			char getJugarDeNuevo(){
				bool bandera;
				bandera = true;
				char opc;
				do{
					cout<<"\tøDesea jugar otra partida? S/N"<<endl;
					cin>>opc;
					if(opc=='S'|| opc=='s'|| opc=='N' || opc=='n')
						bandera=false;
					else{
						cout << RED<<BG_WHITE<<"OpciÛn no valida" << RESET << endl;
						cin.clear();
						cin.ignore();
						cin.get();
					}
				}while(bandera);
				switch (opc)
				{
				case 'N':
					opc = 'N';
					break;
					
				case 'n':
					opc = 'N';
					break;
				case 'S':
					opc = 'S';
					break;
				case 's':
					opc = 'S';
					break;
				}
				
				return opc;
				
			}
				//metodo que muestra el menu principal
				void menuPrincipal(){
					int opcionJuego;
					Estadisticas estadisticas;
					bool bandera;
					bandera = true;
					do {
						system("cls");
						cout << WHITE <<BG_BLUE<< "\n\n\n\n\t\t\tBienvenido al Juego del Gato #" <<RESET<<endl;
						cout << "\n\n";
						cout << "\t1. Multijugador"<<endl;
						cout << "\t2. Contra la computadora"<<endl;
						cout << "\t3. Instrucciones"<<endl;
						cout << "\t4. Ver Estadisticas"<<endl;
						cout << "\t5. ConfiguraciÛn"<<endl;
						cout << "\t6. Salir"<<endl;
						cout << "\n\tIngrese la opcion (1, 2, 3, 4, 5 Û 6): ";
						cin >> opcionJuego;
						switch(opcionJuego){
						case 1:
							jugarHumanoVsHumano(estadisticas);
							break;
						case 2:
							jugarContraMaquina(estadisticas);
							break;
						case 3:
							muestraInstrucciones();
							break;
						case 4:
							mostrarEstadisticas(estadisticas);
							break;
						case 5:
							setDificultad();
							break;
						case 6:
							cout<<GREEN<<BG_WHITE<<"! Hasta pronto !"<<RESET<<endl;
							bandera = false;
							break;
						default:
							cout << RED<<BG_WHITE<<"OpciÛn no valida " << RESET << endl;
							cin.clear();
							cin.ignore();
							cin.get();
							break;
							
						}
					} while (bandera);
					
				}
					void setDificultad(){
						bool bandera;
						bandera = true;
						int opc;
						do{
							system("cls");
							cout<<"\tSelecciona la dificultad de la maquina :"<<endl;
							cout<<"\t1. F·cil."<<endl;
							cout<<"\t2. DifÌcil."<<endl;
							cin>>opc;
							if(opc>=1 && opc<=2)
								bandera = false;
							else{
								cout << RED<<BG_WHITE<<"OpciÛn no valida" << RESET << endl;
								cin.clear();
								cin.ignore();
								cin.get();
							}
						}while(bandera);
						dificultad = opc;
						cout <<GREEN<<BG_WHITE<<"Se modificÛ el nivel de dificultad" << RESET << endl;
						cin.clear();
						cin.ignore();
						cin.get();
					}
						void imprimirTablero() {
							
							cout << " +---+---+---+\n";
							for (int i = 0; i < 3; i++) {
								cout << " | ";
								for (int j = 0; j < 3; j++) {
									cout << tablero[i][j] << " | ";
								}
								cout << "\n +---+---+---+\n";
							}
						}
						void inicializaTablero(){
							int cont;
							cont = 1;
							for (int i = 0; i < 3; i++) {
								for (int j = 0; j < 3; j++) {
									tablero[i][j] = '0'+cont;
									cont ++;
								}
							}
							
							
						}
							
							// Funci√≥n para verificar si hay un ganador
							bool hayGanador(char jugador) {
								//recorre el tablero de forma horizontal  y vertical
								for (int i = 0; i < 3; i++) {
									if ((tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) ||
										(tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador)) {
										return true;
									}
								}
								//recorre la matriz de forma diagonal
								if ((tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) ||
									(tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador)) {
									return true;
								}
									//no hay ganador regresa falso 
									return false;
							}
							bool prediceVictoria(char simulacionTablero[3][3],char jugador){
								//se le esta mandando una matriz auxiliar para validar que si ese movimiento futuro hace que gane
								for (int i = 0; i < 3; i++) {
									//verifica si gana por horizontal o vertical
									if ((simulacionTablero[i][0] == jugador && simulacionTablero[i][1] == jugador && simulacionTablero[i][2] == jugador) ||
										(simulacionTablero[0][i] == jugador && simulacionTablero[1][i] == jugador && simulacionTablero[2][i] == jugador)) {
										return true;
									}
								}
								//verifica si gana por diagonal
								if ((simulacionTablero[0][0] == jugador && simulacionTablero[1][1] == jugador && simulacionTablero[2][2] == jugador) ||
									(simulacionTablero[0][2] == jugador && simulacionTablero[1][1] == jugador && simulacionTablero[2][0] == jugador)) {
									return true;
								}
									
									return false;
									
							}
								
								// Funci√≥n para verificar si el tablero est√° lleno
								bool tableroLleno() {
									for (int i = 0; i < 3; i++) {
										for (int j = 0; j < 3; j++) {
											if (tablero[i][j] == '1' || tablero[i][j] == '2' || tablero[i][j] == '3' || tablero[i][j] == '4' || tablero[i][j] == '5'  || tablero[i][j] == '6'  || tablero[i][j] == '7'  || tablero[i][j] == '8'  || tablero[i][j] == '9')
												return false;
										}
									}
									return true;
								}
								
								// Funci√≥n para realizar un movimiento en el tablero
								bool realizarJugada(int fila, int columna, char jugador) {
									if ((tablero[fila][columna] == 'X') ||(tablero[fila][columna] == 'O')) {
										return false;  // Movimiento inv√°lido
									}
									
									tablero[fila][columna] = jugador;
									return true;  // Movimiento v√°lido
								}
								
								bool simulaJugada(char simulacionTablero[3][3],int fila, int columna, char jugador) {
									//hace la simulacion en una matriz auxilliar simulando el tablero original
									//verifica que la casilla no este ocupada
									if ((simulacionTablero[fila][columna] == 'X') ||(simulacionTablero[fila][columna] == 'O')) {
										return false;  // Movimiento inv√°lido la casilla esta ocupada
									}
									//casilla libre
									simulacionTablero[fila][columna] = jugador;
									return true;  // Movimiento v√°lido
								}
								
								// Funci√≥n para verificar si realizar un movimiento har√° ganar al jugador
								bool esGanadorProximoMovimiento(int fila, int columna, char jugador) {
									char tableroCopia[3][3];
									//copia el tablero a una matriz auxiliar
									copy(&tablero[0][0], &tablero[0][0] + 3 * 3, &tableroCopia[0][0]);
									
									if (simulaJugada(tableroCopia, fila, columna, jugador) && prediceVictoria(tableroCopia, jugador)) {
										return true;
									}
									
									return false;
								}
								
								// Funci√≥n para que la m√°quina en el modo f√°cil realice un movimiento aleatorio
								void jugadaMaquinaFacil() {
									int fila, columna;
									srand(time(0)); //para generar numeros aleatorios
									do {
										//genera los numeros
										fila = rand() % 3 ;
										columna = rand() % 3 ;
										//intenta realizar la jugada en la posicion generada automaticamente
										//si la casilla esta ocupada volver√° a entrar al ciclo y generar otra casilla aleatoria, hasta que se pueda realizar la jugada
									} while (!realizarJugada(fila,columna, 'O'));
								}
								
								
								// Funci√≥n para que la m√°quina en el modo dif√≠cil realice un movimiento estrat√©gico
								void movimientoMaquinaDificil() {
									// Intentar ganar
									for (int i = 0; i < 3; i++) {
										for (int j = 0; j < 3; j++) {
											//valida que el tablero tenga un lugar libre
											if(tablero[i][j]=='1' || tablero[i][j] =='2'|| tablero[i][j] =='3'|| tablero[i][j] =='4'|| tablero[i][j] =='5'|| tablero[i][j] =='6'|| tablero[i][j] =='7'|| tablero[i][j] =='8'|| tablero[i][j] =='9'){
												//ese lugar libre tiene opcion de ganar ?
												if (esGanadorProximoMovimiento(i, j, 'O')) {
													//si tiene opcion de ganar  , entonces va a realizar la jugada
													realizarJugada(i, j, 'O');
													return;
												}
											}
										}
									}
									
									// no hay opcion de ganar pues , vamos a ver si el oponente ya va ganar y si es asi bloquear su jugada
									for (int i = 0; i < 3; i++) {
										for (int j = 0; j < 3; j++) {
											if(tablero[i][j]=='1' || tablero[i][j] =='2'|| tablero[i][j] =='3'|| tablero[i][j] =='4'|| tablero[i][j] =='5'|| tablero[i][j] =='6'|| tablero[i][j] =='7'|| tablero[i][j] =='8'|| tablero[i][j] =='9'){
												if (esGanadorProximoMovimiento( i, j, 'X')) {
													realizarJugada( i, j, 'O');
													return;
												}
											}
										}
									}
									
									// no hay posibilidad de ganar y  tampoco no hay nada que bloquear, vamos a tirar aleatroiamente en una posicion del tablero
									//mandamos a llamar a la funcion que tira un numero aleatorio que es jugadamaquinafacil..
									jugadaMaquinaFacil();
								}
								
								// Funci√≥n para jugar entre dos jugadores humanos
								void jugarHumanoVsHumano(Estadisticas& estadisticas) {
									//primer ciclo que permite que se jueguen varias partidas hasta que el usuario responda N de no jugar mas
									while (true) {
										inicializaTablero();
										int opc;
										char jugadorActual = 'X';
										//inicia la partida
										while(true){
											system("cls");
											imprimirTablero();
											cout<<BLUE<<"Turno del jugador:"<<jugadorActual<<RESET<<endl;
											cout<<"Selecciona una casilla del tablero Û 0 para cancelar partida: ";
											cin >> opc;
											if (opc == 0) {
												estadisticas.partidasCanceladas++;
												cout << GREEN <<BG_WHITE <<"! Partida Cancelada !" <<RESET;
												cin.clear();
												cin.ignore();
												cin.get();
												break;
											}
											while(opc < 1 || opc > 9) {
												cout << RED<<BG_WHITE<<"N˙mero de casilla inv·lido." << RESET << endl;
												cout << "selecciona una casilla del tablero :";
												cin >> opc;
											}
											int fila = (opc - 1) / 3;
											int columna = (opc - 1) % 3;
											//una vez que se validaron las opciones de la casilla , vamos a realizar la jugada
											//si la casilla esta libre se queda la jugada, si no el jugador deber√° teclear otra casilla de nuevo
											if (!realizarJugada(fila, columna, jugadorActual)) {
												cout << RED<<BG_WHITE<<"La casilla seleccionada ya se encuentra ocupada" << RESET << endl;
												cin.clear();
												cin.ignore();
												cin.get();
												continue;
											}
											//valida si ya hay ganador
											if (hayGanador(jugadorActual)) {
												//si hay ganador entonces
												system("cls");
												imprimirTablero();
												cout << GREEN <<BG_WHITE <<"Jugador: "<<jugadorActual<<" ° Has ganado !" << RESET;
												cin.clear();
												cin.ignore();
												cin.get();
												//agrega las estadisticas
												if (jugadorActual == 'X') 
													estadisticas.partidasGanadasHumano1++;
												else 
													estadisticas.partidasGanadasHumano2++;
												estadisticas.partidasHumanoVsHumano++;
												break;
												//no hay ganador aun vamos a ver si hay tablero lleno entonces es empate
											} else if (tableroLleno()) {
												system("cls");
												imprimirTablero();
												//modificamos las estadisticas
												estadisticas.partidasEmpatadas++;
												estadisticas.partidasHumanoVsHumano++;
												cout << GREEN <<BG_WHITE <<"! Es un Empate !"<<RESET;
												cin.clear();
												cin.ignore();
												cin.get();
												break;
											}
											//cambiamos de jugador
											jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
										}
										//ya termino la partida vamos a preguntar si quiere volver a jugar 
										if (getJugarDeNuevo()=='N')
											break;
										
									}   
								}
								
								//Metodo para jugar contra la m√°quina recibe  las estadisticas
								void jugarContraMaquina(Estadisticas& estadisticas) {
									while (true){
										inicializaTablero();
										char jugadorActual = getJugador();
										//ciclo de la partida
										while (true) {
											system("cls");
											string nivel;
											if (dificultad==1)
												nivel="F·cil";
											else
												nivel="DifÌcil";
											cout<< BLUE<<"Modo:"<<nivel<<RESET<<endl;
											imprimirTablero();
											int opc;
											if (jugadorActual == 'X') {
												cout <<BLUE<<"Turno del jugador:"<<jugadorActual<<RESET<<endl;
												cout << "Selecciona una casilla del tablero Û 0 para cancelar partida: ";
												cin >> opc;
												if (opc == 0) {
													estadisticas.partidasCanceladas++;
													cout << GREEN <<BG_WHITE <<"! Partida Cancelada !" <<RESET;
													cin.clear();
													cin.ignore();
													cin.get();
													break;
												}
												while(opc < 1 || opc > 9) {
													cout << RED<<BG_WHITE<<"N˙mero de casilla inv·lido." << RESET << endl;
													cout << "selecciona una casilla del tablero :";
													cin >> opc;
												}
												//convierte la casilla seleccionada a cordenadas de la matriz
												int fila = (opc - 1) / 3;
												int columna = (opc - 1) % 3;
												//Realiza el movimiento , en caso de que la casilla seleccionada ya este ocupada mandar√° mensaje de error
												if (!realizarJugada( fila, columna, 'X')) {
													cout << RED<<BG_WHITE<<"La casilla seleccionada ya se encuentra ocupada" << RESET << endl;
													cin.clear();
													cin.ignore();
													cin.get();
													continue;
												}
											} else {
												//turno de la maquina
												if (dificultad == 1) 
													jugadaMaquinaFacil();
												else 
													movimientoMaquinaDificil();
												
											}
											//valida despues de realizar los movimientos de cada jugador si ya hay ganador o un empate
											if (hayGanador(jugadorActual)) {
												system("cls");
												imprimirTablero();
												if (jugadorActual == 'X') {
													estadisticas.partidasGanadasHumano1++; //aumenta las estadisticas de que gano el jugador x o humanos
													cout << GREEN <<BG_WHITE <<"Jugador: "<<jugadorActual<<" ° Has ganado !" << RESET;
													cin.clear();
													cin.ignore();
													cin.get();
												} else {
													//gano la maquina
													estadisticas.partidasGanadasComputadora++; //aumenta el registro de partidas ganadas de la maquina
													cout << GREEN <<BG_WHITE <<"! La maquina ha ganado !" <<RESET;
													cin.clear();
													cin.ignore();
													cin.get();
												}
												//aumenta las partidas jugadas
												estadisticas.partidasHumanoVsComputadora++; 
												break;
												//si no hubo ganadores entonces validamos si hay empate
											} else if (tableroLleno()) {
												system("cls");
												imprimirTablero();
												//aumenta estadisticas
												estadisticas.partidasEmpatadas++;
												estadisticas.partidasHumanoVsComputadora++;
												cout << GREEN <<BG_WHITE <<"! Es un Empate !"<<RESET;
												cin.clear();
												cin.ignore();
												cin.get();
												break;
											}
											//hacemos el cambio de jugador
											jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
										}
										//ya termino la partida vamos a preguntar si quiere volver a jugar 
										if (getJugarDeNuevo()=='N')
											break;
									}
									
								}
								
								//Metodo para mostrar las estad√≠sticas del partido
								void mostrarEstadisticas(const Estadisticas& estadisticas) {
									system("cls");
									cout << BLUE <<BG_WHITE << "EstadÌsticas del juego:" << RESET << endl;
									cout << "N˙mero de partidas jugadas entre Jugador X y Jugador O: " << estadisticas.partidasHumanoVsHumano <<endl;
									cout << "N˙mero de partidas jugadas entre Jugador y Computadora: " << estadisticas.partidasHumanoVsComputadora <<endl;
									cout << "N˙mero de partidas ganadas por Jugador X: " << estadisticas.partidasGanadasHumano1 <<endl;
									cout << "N˙mero de partidas ganadas por Jugador O: " << estadisticas.partidasGanadasHumano2 <<endl;
									cout << "N˙mero de partidas ganadas por Computadora: " << estadisticas.partidasGanadasComputadora <<endl;
									cout << "N˙mero de partidas empatadas: " << estadisticas.partidasEmpatadas <<endl;
									cout << "N˙mero de partidas canceladas: " << estadisticas.partidasCanceladas <<endl;
									cout << "\nPresione Enter para regresar al Men˙ Principal ";
									cin.clear();
									cin.ignore();
									cin.get();
								}
								
